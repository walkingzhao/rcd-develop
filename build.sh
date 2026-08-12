#!/bin/bash

# 脚本所在目录即工程根目录（从任意路径执行 build.sh 均可）
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# ====================== 自动获取路径配置 ======================
# 自动获取当前登录用户的家目录（任何电脑都自动适配）
USER_HOME="$HOME"

# Qt qmake 路径（保持不变）
qmake_tool=/opt/Qt5.14.2/5.14.2/gcc_64/bin/qmake

# 各项目 .pro 文件路径
ui_profile=RcdUi/src/RCD.pro
control_profile=Control/Control.pro
gateway_profile=GatewayServer/GatewayServer.pro
cloudserver_profile=CloudServer/CloudServer.pro

# 部署目录：自动适配当前用户
deploy_path="${USER_HOME}/dcu/deploy"

# 构建根目录
build_root=_build
# ==============================================================

# 自动输入 sudo 密码
sudo_pass="dell-123"

# 确保部署目录存在
echo "准备部署目录: $deploy_path"
echo "$sudo_pass" | sudo -S mkdir -p "$deploy_path" || {
    echo "ERROR: 无法创建部署目录 $deploy_path"
    exit 1
}

# -------------------- 生成 FlatBuffers 头文件 --------------------
generate_fbs_headers() {
    local fbs_dir="${SCRIPT_DIR}/pubinc/fbs"

    echo "=================================================="
    echo "生成 FlatBuffers 头文件 (pubinc/fbs)"
    echo "=================================================="

    if ! command -v flatc >/dev/null 2>&1; then
        echo "ERROR: 未找到 flatc，请先安装 FlatBuffers 编译器"
        exit 1
    fi

    if [ ! -f "${fbs_dir}/auto.sh" ]; then
        echo "ERROR: 未找到 ${fbs_dir}/auto.sh"
        exit 1
    fi

    (
        cd "${fbs_dir}" || exit 1
        bash auto.sh
    ) || {
        echo "ERROR: FlatBuffers 头文件生成失败"
        exit 1
    }

    echo "✅ FlatBuffers 头文件已更新"
    echo ""
}

generate_fbs_headers

# 创建构建根目录
mkdir -p "$build_root"
cd "$build_root" || exit 1

# -------------------- 编译函数 --------------------
build_project() {
    local build_name="$1"
    local pro_file="$2"
    local target_name="$3"

    echo "=================================================="
    echo "开始构建: $build_name ($target_name)"
    echo "=================================================="

    rm -rf "$build_name"
    mkdir -p "$build_name"
    cd "$build_name" || exit 1

    $qmake_tool "../../$pro_file" || { echo "qmake 失败"; exit 1; }
    make -j"$(nproc)" || { echo "make 失败"; exit 1; }

    if [ ! -x "./$target_name" ]; then
        echo "未找到可执行文件 $target_name"
        exit 1
    fi

    echo "$sudo_pass" | sudo -S cp -f "./$target_name" "$deploy_path/"
    cd .. || exit 1

    echo "✅ $build_name 构建完成"
    echo ""
}

# -------------------- 开始编译 --------------------
build_project "RCD_build"          "$ui_profile"           "RCD"
build_project "Control_build"      "$control_profile"      "Control"
build_project "Gateway_build"      "$gateway_profile"      "GatewayServer"
build_project "Cloud_build"        "$cloudserver_profile"  "CloudServer"

# -------------------- 拷贝配置文件、脚本、库目录 --------------------
echo "=================================================="
echo "开始拷贝配置文件、脚本、库目录"
echo "=================================================="

cd "$SCRIPT_DIR" || exit 1

# 拷贝工程内 deploy/ 下的配置与脚本到安装目录 ~/dcu/deploy
copy_files=(
    "deploy/rcdconfig.json"
    "deploy/rcdconfig.ini"
    "deploy/RCD.sh"
    "deploy/logoicons.png"
)

for file in "${copy_files[@]}"; do
    if [ -f "$file" ]; then
        echo "拷贝 $file"
        echo "$sudo_pass" | sudo -S cp -f "$file" "$deploy_path/"
    else
        echo "WARN: 未找到 $file，跳过"
    fi
done

# remotedriving.desktop：直接写入绝对路径，不再依赖 sed 替换模板
install_desktop_shortcut() {
    local applications_dir="${USER_HOME}/.local/share/applications"
    local installed_desktop="${applications_dir}/remotedriving.desktop"
    local deploy_desktop="${deploy_path}/remotedriving.desktop"
    local exec_path="${deploy_path}/RCD.sh"
    local icon_path="${deploy_path}/logoicons.png"
    local pixmaps_dir="${USER_HOME}/.local/share/pixmaps"

    if [ ! -f "$exec_path" ]; then
        echo "WARN: 未找到 $exec_path，跳过快捷方式安装"
        return 0
    fi
    if [ ! -f "$icon_path" ]; then
        echo "WARN: 未找到图标 $icon_path，快捷方式可能无图标"
    fi

    mkdir -p "$applications_dir" "$pixmaps_dir"
    if [ -f "$icon_path" ]; then
        cp -f "$icon_path" "${pixmaps_dir}/rcd-logoicons.png"
    fi

    cat > "$installed_desktop" <<EOF
[Desktop Entry]
Encoding=UTF-8
Type=Application
Name=RCD
Comment=remote driving
Exec=${exec_path} %F
Terminal=false
Icon=${icon_path}
EOF

    chmod 644 "$installed_desktop"
    cp -f "$installed_desktop" "$deploy_desktop" || {
        echo "$sudo_pass" | sudo -S cp -f "$installed_desktop" "$deploy_desktop"
    }

    if command -v update-desktop-database >/dev/null 2>&1; then
        update-desktop-database "$applications_dir" 2>/dev/null || true
    fi

    echo "已安装快捷方式: ${installed_desktop}"
    echo "  Exec=${exec_path} %F"
    echo "  Icon=${icon_path}"
    if grep -q '@DEPLOY_PATH@' "$installed_desktop"; then
        echo "ERROR: 快捷方式内容异常，仍含 @DEPLOY_PATH@"
        return 1
    fi
}
install_desktop_shortcut

# 拷贝 lib & libs
copy_dirs=(
    "RcdUi/src/lib"
    "RcdUi/src/libs"
)

for dir in "${copy_dirs[@]}"; do
    if [ -d "$dir" ]; then
        echo "拷贝目录 $dir"
        dir_name=$(basename "$dir")
        echo "$sudo_pass" | sudo -S rm -rf "$deploy_path/$dir_name"
        echo "$sudo_pass" | sudo -S cp -rf "$dir" "$deploy_path/"
    fi
done

# -------------------- 权限设置 --------------------
echo "=================================================="
echo "设置文件权限"
echo "=================================================="

# 1. 可执行文件加执行权限
executables=(
    "RCD"
    "Control"
    "GatewayServer"
    "CloudServer"
    "RCD.sh"
)

for f in "${executables[@]}"; do
    if [ -f "$deploy_path/$f" ]; then
        echo "添加可执行权限: $f"
        echo "$sudo_pass" | sudo -S chmod 755 "$deploy_path/$f"
    fi
done

# 2. 配置文件可读写（方便编辑）
config_files=(
    "rcdconfig.json"
    "rcdconfig.ini"
)

for f in "${config_files[@]}"; do
    if [ -f "$deploy_path/$f" ]; then
        echo "设置可读写权限: $f"
        echo "$sudo_pass" | sudo -S chmod 644 "$deploy_path/$f"
    fi
done

# 3. 库目录权限
echo "$sudo_pass" | sudo -S chmod -R 755 "$deploy_path/lib"  2>/dev/null
echo "$sudo_pass" | sudo -S chmod -R 755 "$deploy_path/libs" 2>/dev/null

# ====================== 给部署文件夹设置可读可写 ======================
echo "=================================================="
echo "设置 dcu、deploy 文件夹权限为 777（可读可写可执行）"
echo "=================================================="

DCU_PATH="${USER_HOME}/dcu"
DEPLOY_PATH="${USER_HOME}/dcu/deploy"

echo "$sudo_pass" | sudo -S chmod -R 777 "$DCU_PATH"
echo "$sudo_pass" | sudo -S chmod -R 777 "$DEPLOY_PATH"

echo ""
echo "=================================================="
echo "✅ 全部完成！编译 + 拷贝 + 权限设置成功"
echo "部署目录：$deploy_path"
echo "=================================================="

