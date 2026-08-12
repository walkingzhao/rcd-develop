#!/usr/bin/env bash
set -uo pipefail

# 自动进入脚本所在目录
BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
cd "$BASE_DIR" || exit 1

# ==============================
# 可执行文件自动查找
# ==============================
find_bin() {
    for name in "$@"; do
        [[ -x "./$name" ]] && { echo "$name"; return 0; }
    done
    echo "[ERROR] $* not found" >&2
    exit 1
}

UI="$(find_bin RCD rcd)"
CTRL="$(find_bin Control control)"
GATE="$(find_bin GatewayServer gatewayserver)"
CLOUD="$(find_bin CloudServer cloudserver)"

# ==============================
# 退出清理：RCD一关，全服务停止
# ==============================
cleanup() {
    echo "[shutdown] Stopping all services..."
    pkill -f "$GATE" 2>/dev/null
    pkill -f "$CTRL" 2>/dev/null
    pkill -f "$CLOUD" 2>/dev/null
    echo "[shutdown] All stopped."
}

# 捕获退出信号
trap cleanup EXIT INT TERM

# ==============================
# 启动顺序
# ==============================
echo "[start] GatewayServer → Control → CloudServer → RCD"

setsid ./$GATE  &>/dev/null &
setsid ./$CTRL  &>/dev/null &
setsid ./$CLOUD &>/dev/null &

sleep 1

# 【关键】前台启动 RCD，等待它真正退出
./$UI

# RCD 退出后，自动执行 cleanup
exit 0

