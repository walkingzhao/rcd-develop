# RCD-UI

### 环境搭建

```bash
安装flatbuffers v2.0.0
1.下载https://github.com/google/flatbuffers.git
2. mkdir build&& cd build
cmake ..
make -j
sudo make install

安装zmq
sudo apt install libzmq3-dev
git clone https://github.com/zeromq/cppzmq.git
mkdir cppzmq/build && cd cppzmq/build
cmake -DCPPZMQ_BUILD_TESTS=OFF ../
sudo make install

安装ffmpeg
sudo apt install libsdl2-dev
----------------------------------
ubuntu20:
sudo apt install ffmpeg
sudo apt install libavcodec-dev libavdevice-dev
sudo apt install libavfilter-dev libavformat-dev libavutil-dev libpostproc-dev libswresample-dev libswscale-dev
----------------------------------
ubuntu18使用ffmepg4.2.4源代码编译
./configure --enable-shared --enable-postproc --enable-gpl
make -j
make install
----------------------------------



安装OSG
1.安装依赖sudo apt-get build-dep openscenegraph
2.安装osg3.6.5，下载源代码https://github.com/openscenegraph/OpenSceneGraph/tree/OpenSceneGraph-3.6.5
mkdir build
cd build
cmake ..
make -j
sudo make install

删除与ffmpeg重复的apt安装的库：
sudo apt remove libavcodec-dev libavcodec57 libavdevice-dev libavdevice57 libavfilter-dev  libavfilter6 libavformat-dev libavformat57 libavresample-dev libavresample3   libavutil-dev libavutil55

安装libproj
1.下载：https://download.osgeo.org/proj/proj-4.9.3.tar.gz
2. 安装：
mkdir build && cd build
cmake ..
make -j
sudo make install
```

## Rabbitmq库安装

### 1. 安装rabbitmq-c

使用v0.11.0分支

   ```shell
   git clone https://github.com/alanxz/rabbitmq-c.git
   cd rabbitmq-c
   git checkout -b v0.11.0
   mkdir build_pc && cd build_pc
   cmake  -DBUILD_TESTS=OFF -DBUILD_TOOLS=OFF -DBUILD_TOOLS_DOCS=OFF ..
   make -j
   make install
   ```

   使用master分支代码

   ```shell
   git clong https://github.com/lujfsd/SimpleAmqpClient.git
   cd SimpleAmqpClient && mkdir build && cd build
   cmake -DENABLE_TESTING=OFF ..
   make -j
   make install
   ```

   **fix cstdlib:75:15: fatal error: stdlib.h: No such file or directory**

   ```shell
   cd build
   sed -i 's/-isystem /-I/g' CMakeFiles/SimpleAmqpClient.dir/flags.make
   ```
## flatbuffer
   使用flac生成对应的头文件
`flatc --cpp --gen-mutable --gen-object-api --reflect-names  --gen-compare tgmsg.fbs`



### 部署
```bash
#ubuntu18已验证
1.下载linuxdeployqt:
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod +xlinuxdeployqt-continuous-x86_64.AppImage
2.mkdir deploy,cp RCD deploy/,cd deploy
/home/xzk/Downloads/linuxdeployqt-continuous-x86_64.AppImage RCD -qmake=/home/xzk/tools/Qt5.14.2/gcc_64/bin/qmake
3.tar zcvf deploy.tar.gz deploy
4.拷贝deploy.tar.gz到部署的机器OS版本大于等于ubuntu18，解压
5.export LD_LIBRARY_PATH=lib
6.运行AppRun，缺少哪个库，到开发OS上拷贝到deploy/lib下，直到系统可以运行（大概有三四十个库许需要手动拷贝/(ㄒoㄒ)/~~）
7.deploy做好后，以后更新，就可以只用更新RCD和新增的库了

```








### 编译方式

```bash

cd RCD

#x86平台 ：
qmake -o Makefile RCD.pro

make -j$(nproc)
```

### 运行方式

```bash
#单进程3界面：
./RCD

#启动3进程 1界面对应1进程
./RCD -M

#单启左右界面
./RCD -L
./RCD -R

```
-----

### 项目介绍：

项目原设计为单进程创建3个屏幕界面方案，但是有两个瓶颈导致不能采用这种设计方案，所以改为3个屏幕3个进程方案。

**瓶颈：**
- 1，QT有这样一个特性，只能由主线程进行GUI渲染。所以绘制3个屏幕GUI时会出现单核吃满，还卡的情况。
- 2，RTX2060显卡驱动在Ubuntu上有BUG，导致单进程多窗口时，GPU渲染视频卡顿。且CPU、GPU负载都很低，似乎出现了互相锁定情况，使用A卡和笔记本N卡都不会出现。

#### 1. 名词解释

| 名词   | 解释 |
|-------|-----|
| 模块 (Module) | 实现一类功能的代码集合，模块之间独立解耦，原则上不允许直接相互调用或访问，信息交互可通过通讯接口。|
| 数据层 (Model) | 组层模块的三层之一，将模块中的数据抽象成model类。(非必须)|
| 控制层 (Control) | 组层模块的三层之一，将模块中的逻辑控制，状态管理抽象成类。(必须)|
| 表示层 (Widget) | 组层模块的三层之一，将模块中显示的动画图表相关抽象成类，目前继承QWidget类，有需要可使用qml替换。(非必须)|

#### 2. 目录结构

| 文件名| 说明 |
|-------|-----|
| config | 进程配置文件 |
| include | 需调用的其他项目头文件 |
| tools | 调测工具文件 |
| src/Component | 自写功能组件类，模块可直接实例化调用 |
| src/FunModule | 功能模块 |
| src/Interface | 多态基类 |
| src/MainFile | 主文件 |
| src/Protocol | 协议实现 |
| src/QsLog | 日志实现 |
| src/qss | 样式文件 |
| src/resource | 素材资源文件 |
| src/Widget | 带UI的功能模块 |
| System.h/.cpp | 系统类 |

#### 2. 架构图


##### 2.1 软件架构

```c++
// 当前全部模块
enum ModuleType
{
    MD_MainProcessor=0,       //核心处理模块
    MD_IPCManager,            //进程通信管理模块
    MD_InteractiveManager,    //输入交互管理模块

    MD_LeftCamera,            //左摄像头界面
    MD_DriveCamera,           //驾驶室摄像头界面
    MD_CloudWeb,              //web界面

    MD_MainCamera,            //主摄像头界面
    MD_MainMonitor,           //主监控界面

    MD_RightCamera,           //右摄像头界面
    MD_VehicleInfo,           //车辆信息界面
    MD_AllInfo,               //所有信息界面
    MD_WarnInfo,              //警告信息界面

    MD_Max
};
```

结构：

```mermaid
graph LR
IPC(IPCManager) --- MP((MainProcessor))
MCa(MainCamera) --- MP
LCa(LeftCamera) --- MP
MP --- RCa(RightCamera)
MP --- MM(MainMonitor)
MP --- CW(CloudWeb)
```

- 说明：软件结构呈现星型，通讯汇总于MainProcessor，它充当中间件并实现一些系统处理，线表示信号/槽通讯。

##### 2.2 模块内架构

```mermaid
graph LR
MD["[模块]"] ==>|通信| Control
Control -->|通信| MD
subgraph "[模块]"
Control((控制层)) ==>|修改| Model((数据层))
Model ==>|更新| Show
Model -->|获取| Control
Show((表示层)) -->|调用| Control
Show -->|更新| Model
end
```

##### 2.3 进程间架构

- 进层间通过ZMQ通信。

```mermaid
graph TD
subgraph "[中屏幕进程]"
MIPC(IPCManager) --> MMP(MainProcessor)
MMP --> MOTH(其他模块)
end
subgraph "[左屏幕进程]"
LIPC(IPCManager) --> LMP(MainProcessor)
LMP --> LOTH(其他模块)
end
subgraph "[右屏幕进程]"
RIPC(IPCManager) --> RMP(MainProcessor)
RMP --> ROTH(其他模块)
end
MIPC --- LIPC
MIPC --- RIPC
RIPC --- LIPC
```
### 2. 安装 [cppzmq@master](https://github.com/zeromq/cppzmq.git)

   ```shell
   git clone https://github.com/zeromq/cppzmq.git
   cd cppzmq
   mkdir build & cd build
   cmake -DCPPZMQ_BUILD_TESTS=off ..
   sudo make -j4 install
   ```

## Rabbitmq库安装

### 1. 安装rabbitmq-c

使用v0.11.0分支

   ```shell
   git clone https://github.com/alanxz/rabbitmq-c.git
   cd rabbitmq-c
   git checkout -b v0.11.0
   mkdir build_pc && cd build_pc
   cmake  -DBUILD_TESTS=OFF -DBUILD_TOOLS=OFF -DBUILD_TOOLS_DOCS=OFF ..
   make -j
   make install
   ```

### 2. 安装SimpleAmqpClient

   使用master分支代码

   ```shell
   git clong https://github.com/lujfsd/SimpleAmqpClient.git
   cd SimpleAmqpClient && mkdir build && cd build
   cmake -DENABLE_TESTING=OFF ..
   make -j
   make install
   ```

   **fix cstdlib:75:15: fatal error: stdlib.h: No such file or directory**

   ```shell
   cd build
   sed -i 's/-isystem /-I/g' CMakeFiles/SimpleAmqpClient.dir/flags.make
   ```
## flatbuffer
   使用flac生成对应的头文件
`flatc --cpp --gen-mutable --gen-object-api --reflect-names  --gen-compare tgmsg.fbs`


