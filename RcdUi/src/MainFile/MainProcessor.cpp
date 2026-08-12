#include "MainProcessor.h"
#include <QApplication>
#include <QWindow>
#include <QFile>
#include <QDesktopWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QPalette>
#include "Mainwindow.h"
#include "Interface/IFunWidget.h"
#include "FunModule/IpcManager.h"
#include "FunModule/InteractiveManager.h"
#include "Interface/WgtFactory.h"
#include "Widget/CloudWebWgt/CloudWebWgt.h"
#include <QThread>

#ifndef HIK_INTERFACE
    #include "Component/iLivePlayer.h"
    #include "public/jsonMethord.h"
#endif

MainProcessor::MainProcessor(QObject *parent)
    : QObject(parent),
      m_mainWinddow(nullptr)
{
    // 初始化样式
    this->initStyle();
    // 初始化系统
    this->initSystem();
    // 初始化功能模块
    this->initFunModule();
    // 初始主窗口
    this->initMainWindow();
}

MainProcessor::~MainProcessor()
{
    emit killProc();//杀死进程
//    runShellCmd("killall RCD");

    delete m_mainWinddow;
}
//初始化样式表
void MainProcessor::initStyle()
{
    // 载入QSS样式
    QFile file(QString(":style/qss/%1.css").arg("blue"));
    file.open(QFile::ReadOnly);
    QString qss(QLatin1String(file.readAll()));
    qApp->setStyleSheet(qss);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#050B12"));
    palette.setColor(QPalette::WindowText, QColor("#D7E6F5"));
    palette.setColor(QPalette::Base, QColor("#081827"));
    palette.setColor(QPalette::AlternateBase, QColor("#0B1A2A"));
    palette.setColor(QPalette::Text, QColor("#EAF7FF"));
    palette.setColor(QPalette::Button, QColor("#102A40"));
    palette.setColor(QPalette::ButtonText, QColor("#EAF7FF"));
    palette.setColor(QPalette::Highlight, QColor("#0077B6"));
    palette.setColor(QPalette::HighlightedText, QColor("#FFFFFF"));
    qApp->setPalette(palette);
    file.close();
}
//初始化系统
void MainProcessor::initSystem()
{
    System::getInstance();
    WgtFactory::initWidget();//屏幕工厂类初始化
    int procType = System::getInstance()->getProcessType();

    // 主进程开启其他两个进程，并绑定实现任意进程退出全退出。
    if(procType == PT_MidProc){

#ifndef HIK_INTERFACE
        runShellCmd("/bin/mkdir -p log/mlog");
        PIMediaPlayer_global_init("log/mlog");
#endif

        QStringList arguments;
        arguments.append("-R");
        arguments.append("-L");
        for(auto argument : arguments){
            QProcess *pProc = new QProcess();
            connect(this,SIGNAL(killProc()),pProc,SLOT(kill()));
            connect(pProc,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(procFinished(int,QProcess::ExitStatus)));
#if 0
            if(argument == "-R")
                pProc->start("sh RCDR.sh");
            else if(argument == "-L")
                pProc->start("sh RCDL.sh");
#else

            QThread::sleep(1);

            if(argument == "-R")
            {
                QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                env.insert("LD_LIBRARY_PATH", "lib");
                env.insert("QT_PLUGIN_PATH", "plugins");
                env.insert("QML2_IMPORT_PATH", "qml");
                pProc->setProcessEnvironment(env);
            }
            else if(argument == "-L")
            {

                QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
                env.insert("LD_LIBRARY_PATH", "lib");
                env.insert("QT_PLUGIN_PATH", "plugins");
                env.insert("QML2_IMPORT_PATH", "qml");
                pProc->setProcessEnvironment(env);
            }

            pProc->start("RCD",QStringList(argument));
#endif
            pProc->waitForStarted();
        }
    }

#ifndef HIK_INTERFACE
    else if(procType == PT_LeftProc)
    {
        runShellCmd("/bin/mkdir -p log/llog");
        PIMediaPlayer_global_init("log/llog");
    }else if(procType == PT_RightProc)
    {
        runShellCmd("/bin/mkdir -p log/rlog");
        PIMediaPlayer_global_init("log/rlog");
    }
#endif

    //    QProcess process;
    //    QString path = "gifsave";
    //    process.start(path);

}
//初始化功能模块
void MainProcessor::initFunModule()
{
    // 进程通讯功能初始化
    m_pIpcManager = IpcManager::GetInstance(this);//zmq作为模块间数据交互

    connect(m_pIpcManager, SIGNAL(sendToMain(ModuleDir,int,QVariant)),
            this, SLOT(getFromAny(ModuleDir,int,QVariant)));//getFromAny() 所有消息入口

    // 交互管理初始化 （主要处理按键操作）
    InteractiveManager::GetInstance(this);

    connect(pInteractiveIns, SIGNAL(sendToMain(ModuleDir,int,QVariant)),
            this, SLOT(getFromAny(ModuleDir,int,QVariant)),Qt::QueuedConnection);

    // 播放声音
    initSound();
}
//初始化主界面
void MainProcessor::initMainWindow()
{

    // 左中右屏幕各自显示页面
    m_mainWinddow = new MainWindow();
    int procType = System::getInstance()->getProcessType();
    if(procType & PT_MidProc){//中间进程界面
        this->switchWidget(SA_MainScreen,MD_MainMonitor);
        //初始化提示窗口页面


        connect(WgtFactory::getFunWidget(MD_AcceptTaskWork)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        connect(WgtFactory::getFunWidget(MD_CompleteOperEnd)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        connect(WgtFactory::getFunWidget(MD_CompleteOperStart)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        connect(WgtFactory::getFunWidget(MD_GiveUpTakeOver)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        connect(WgtFactory::getFunWidget(MD_NetworkInterruption)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));

        // --> BEGIN added by ZJZ, 2022/3/1
        connect(WgtFactory::getFunWidget(MD_TipsPopup)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        // <-- END

        connect(WgtFactory::getFunWidget(MD_SelfTest)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));

        connect(WgtFactory::getFunWidget(MD_NotSatisfiedWithTakeover)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        connect(WgtFactory::getFunWidget(MD_TaskWorkChange)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        connect(WgtFactory::getFunWidget(MD_FastStop)->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
    }
    if(procType & PT_RightProc){//右侧进程界面

        //        this->switchWidget(SA_RightScreen,MD_CloudWeb);
        this->switchLayout(LT_Monitor);

    }
    if(procType & PT_LeftProc){//左侧进程界面
        //        this->switchWidget(SA_LeftScreen,MD_UserGuide);
        this->switchLayout(LT_Monitor);
    }
}
//展示所有界面
void MainProcessor::run()
{
    m_mainWinddow->showAll();

}
//事件过滤重写
bool MainProcessor::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress
            || event->type() == QEvent::MouseButtonDblClick
            || event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        if(e->button() == Qt::RightButton)
        {//不支持鼠标右击
            return true;
        }
    }
    else if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        this->keyPressHandle(target,keyEvent->key());

    }//过滤掉鼠标移动悬浮与离开事件
    else if(event->type() == QEvent::HoverMove
            || event->type() == QEvent::HoverEnter
            || event->type() == QEvent::HoverLeave)
    {
        return true;
    }

    return QObject::eventFilter(target, event);
}
//键盘建输入（过滤掉鼠标键）
void MainProcessor::keyPressHandle(QObject *target,int key)
{
    if(target->isWindowType()){//是否继承了window
//    if(1){
        qDebug() << "MainProcessor::keyPressHandle:" << static_cast<Qt::Key>(key)
                 << target->objectName()
                 <<System::getInstance()->getCurrentLayoutType();
        if(target->objectName() =="MessageBoxWindow"){
            return;
        }
        ModuleDir moduleDir;
        moduleDir.append(MD_InteractiveManager);//交互管理模块
        this->getFromAny(moduleDir,IA_KeyPress, QVariant(key)); //接收处理所有模块命令
    }
}
//进程退出
void MainProcessor::procFinished(int,QProcess::ExitStatus)
{
    QApplication::exit();
}
//主进程模块
void MainProcessor::mainProcess(ModuleDir &,int &cmd, QVariant &data)
{
    MainProcessorCmdType Cmd = static_cast<MainProcessorCmdType>(cmd);
    switch (Cmd)
    {
    case MP_SwitchWgt:{
        ScreenAreaType screenArea = static_cast<ScreenAreaType>(data.toList().first().toInt());
        ModuleType module = static_cast<ModuleType>(data.toList().last().toInt());
        this->switchWidget(screenArea,module);
        break;
    }
    case MP_SwitchLayout:{
        this->switchLayout(data.toInt());
        break;
    }
    case MP_SoftKeyPress:{
        // 硬件软键已经是一次明确的按键消息，不要再伪造成 QKeyEvent 发给
        // focusWindow。连接/断开车辆后 grabKeyboard/releaseKeyboard 状态变化，
        // sendEvent 可能被全局 eventFilter 重复处理，导致同一次 A1 进入
        // MainMonitorCL::inputHandler 两次，接管灯翻转两次后看起来“不亮”。
        if(QApplication::focusWindow() != nullptr
                && QApplication::focusWindow()->objectName() == "MessageBoxWindow"){
            return;
        }
        ModuleDir moduleDir;
        moduleDir.append(MD_InteractiveManager);
        this->getFromAny(moduleDir, IA_KeyPress, QVariant(data.toUInt()));

        break;
    }case MP_IpcForward:{
        ModuleDir md;
        md.append(data.toList().at(0).toInt());
        int Cmd = data.toList().at(1).toInt(); //data第一个元素是第一个参数发给哪个窗口，第二个元素是cmd，第三个元素是data
        qDebug()<<"MP_IpcForward cmd:"<<Cmd;
        this->doFromAny(md,Cmd,data.toList().last());
        break;
    }
    default:
        break;
    }
}

//
// @brief:类似中间件函数，所有通讯消息的入口
// @params: moduleDir-模块地址  cmd-命令 data-数据
// @ret:void
// @birth:created by hyx on 2020
//
void MainProcessor::getFromAny(ModuleDir moduleDir,int cmd, QVariant data)
{
    if(moduleDir.isEmpty()){
        return;
    }
    ModuleType Dir;
    Dir = static_cast<ModuleType>(moduleDir.first());
    MessageType msgType = whichMsg(Dir,cmd,data);
    switch (msgType) {
    case MT_ThisProc:{
        qDebug()<<"MT_ThisProc cmd:"<<cmd;
        this->doFromAny(moduleDir,cmd,data);
        break;

    }
    case MT_Broadcast:{
        qDebug()<<"MT_Broadcast cmd:"<<cmd;
        this->doFromAny(moduleDir,cmd,data);
        int procType = System::getInstance()->getProcessType();
        if(procType == PT_MidProc){
            m_pIpcManager->ipcForward(PT_LeftProc,moduleDir,cmd,data);
            m_pIpcManager->ipcForward(PT_RightProc,moduleDir,cmd,data);
        }else if(procType == PT_RightProc){
            m_pIpcManager->ipcForward(PT_LeftProc,moduleDir,cmd,data);
            m_pIpcManager->ipcForward(PT_MidProc,moduleDir,cmd,data);
        }else if(procType == PT_LeftProc){
            m_pIpcManager->ipcForward(PT_RightProc,moduleDir,cmd,data);
            m_pIpcManager->ipcForward(PT_MidProc,moduleDir,cmd,data);
        }
        break;
    }
    case MT_LeftProc:{
        qDebug()<<"ipcForward MT_LeftProc cmd:"<<cmd << "wgt:" <<moduleDir.first();
        m_pIpcManager->ipcForward(PT_LeftProc,moduleDir,cmd,data);
        break;
    }
    case MT_MidProc:{
        qDebug()<<"ipcForward MT_MidProc cmd:"<<cmd << "wgt:" <<moduleDir.first();
        m_pIpcManager->ipcForward(PT_MidProc,moduleDir,cmd,data);

        break;
    }
    case MT_RightProc:{
        qDebug()<<"ipcForward MT_RightProc cmd:"<<cmd << "wgt:" <<moduleDir.first();
        m_pIpcManager->ipcForward(PT_RightProc,moduleDir,cmd,data);
        break;
    }
    default:
        break;
    }

}

//
// @brief:本进程需要处理的所有消息入口
// @params: moduleDir-模块地址  cmd-命令 data-数据
// @ret:void
// @birth:created by hyx on 2020
//
void MainProcessor::doFromAny(ModuleDir moduleDir,int &cmd, QVariant &data)
{
    if(moduleDir.isEmpty()){
        return;
    }
    ModuleType Dir;
    Dir = static_cast<ModuleType>(moduleDir.first());
    moduleDir.removeFirst();
    switch (Dir){
    case MD_MainProcessor:{//主处理模块
        this->mainProcess(moduleDir,cmd,data);
        break;
    }
    case MD_IPCManager:{//进程通信管理模块
        m_pIpcManager->getFromAny(moduleDir,cmd,data);
        break;
    }
    case MD_InteractiveManager:{//输入交互管理模块name
        pInteractiveIns->getFromAny(moduleDir,cmd,data);
        break;
    }
    default:{
        IFunWidget *pFunWidget=WgtFactory::getFunWidget(Dir);
        if(pFunWidget == nullptr)
            break;
        qDebug()<<"recv cmd:" << cmd << " to:" <<pFunWidget->objectName();
        pFunWidget->getCL()->getFromAny(moduleDir,cmd,data);
        break;
    }
    }
}

MainProcessor::MessageType MainProcessor::whichMsg(ModuleType &mdType,int &cmd,QVariant &data)
{
    MessageType msgType = MT_ThisProc;
    int procType = System::getInstance()->getProcessType();
    if(mdType == MD_MainProcessor){
        MainProcessorCmdType Cmd = static_cast<MainProcessorCmdType>(cmd);
        switch (Cmd) {
        case MP_SwitchWgt:{
            ModuleType module = static_cast<ModuleType>(data.toList().last().toInt());
            int belongProc = System::getInstance()->belongTo(module);
            if(procType & belongProc){
                msgType = MT_ThisProc;
            }else {
                if(belongProc == PT_LeftProc){
                    msgType = MT_LeftProc;
                }else if(belongProc == PT_RightProc){
                    msgType = MT_RightProc;
                }else{
                    msgType = MT_MidProc;
                }
            }
            break;
        }
        case MP_UpdateSysData:
        case MP_SwitchLayout:{
            msgType = MT_Broadcast;
            break;
        }
        case MP_SoftKeyPress:
        case MP_IpcForward:{
            msgType = MT_ThisProc;
            break;
        }
        default:
            break;
        }
    }else if(mdType == MD_IPCManager || mdType == MD_InteractiveManager){
        if(procType & PT_MidProc){
            msgType = MT_ThisProc;
        }else{
            msgType = MT_MidProc;
        }
    }else{
        int belongProc = System::getInstance()->belongTo(mdType);
        if(procType & belongProc){
            msgType = MT_ThisProc;
        }else {
            if(belongProc == PT_LeftProc){
                msgType = MT_LeftProc;
            }else if(belongProc == PT_RightProc){
                msgType = MT_RightProc;
            }else{
                msgType = MT_MidProc;
            }
        }
    }
    return msgType;
}

//
// @brief:布局切换
// @params: layoutType 布局类型
// @ret:void
// @birth:created by hyx on 2020
//
void MainProcessor::switchLayout(int layoutType)
{
    LayoutType layout = static_cast<LayoutType>(layoutType);
    System::getInstance()->showLayoutMode=layout;
    int procType = System::getInstance()->getProcessType();
    switch (layout){
    case LT_Monitor:{
        System::getInstance()->forwardLeft_forwardRight_Big=false;


        if(procType & PT_MidProc){
            this->switchWidget(SA_MainScreen, MD_MainMonitor);
            // 停止播放声音
            if (isHavePlaySound) {
                playSound(false);
            }
        }
        if(procType & PT_RightProc){
            this->switchWidget(SA_RightScreen,MD_CloudWeb);
            ((CloudWebWgt*)WgtFactory::getFunWidget(MD_CloudWeb))->setFrameType(0);
        }
        if(procType & PT_LeftProc){
            this->switchWidget(SA_LeftScreen,MD_UserGuide);
        }


        break;
    }
    case LT_RemoteControl:{
        if(procType & PT_MidProc){
            this->switchWidget(SA_MainScreen, MD_MainCamera);
            // 播放声音
            if (!isHavePlaySound) {
                playSound(true);
            }
        }
        if(procType & PT_RightProc){
//            this->switchWidget(SA_RightScreenLTop, MD_RightCamera);
//            this->switchWidget(SA_RightScreenLBottom, MD_CloudWeb);
            ((CloudWebWgt*)WgtFactory::getFunWidget(MD_CloudWeb))->setFrameType(1);

//            this->switchWidget(SA_RightScreenRTop, MD_TakeOverInfo);
//            this->switchWidget(SA_RightScreenRMid, MD_LoadInstruction);

//            this->switchWidget(SA_RightScreenRBottom, MD_SystemInfo);
        }
        if(procType & PT_LeftProc){
            this->switchWidget(SA_LeftScreenTopL,MD_DriveCamera);
            this->switchWidget(SA_LeftScreenTopR,MD_LeftCamera);
            this->switchWidget(SA_LeftScreenBottomL,MD_FaultInfo);
            this->switchWidget(SA_LeftScreenBottomR,MD_VehicleData);
        }


        break;
    }
    default:
        break;
    }

    m_mainWinddow->switchLayout(layout);

    if(procType & PT_MidProc){
        pInteractiveIns->getFromAny(ModuleDir(),IA_SwitchLayout,QVariant(layoutType));
    }
}

//
// @brief:widget窗口切换
// @params: Area：切换区域  wgtId：切换目标，并进行connect信号连接
// @ret:void
// @birth:created by hyx on 2020
//
void MainProcessor::switchWidget(ScreenAreaType Area, int wgtId)
{
    // 从widget工厂获取目标widget
    IFunWidget *pSwitchWgt = WgtFactory::getFunWidget(static_cast<ModuleType>(wgtId));
    IFunWidget *pCurrenWgt = nullptr;

    auto iter = m_currentWgt.find(Area);
    if(iter != m_currentWgt.end()){
        pCurrenWgt = m_currentWgt[Area];
    }

    if(pSwitchWgt == nullptr || pCurrenWgt == pSwitchWgt) //相同页面返回
    {
        return;
    }

    if(pCurrenWgt != nullptr && !pCurrenWgt->isHidden()) //如果当前有窗口，断开信号并退出
    {
        if(!pCurrenWgt->isQuit())//是否可以退出，不可则返回
        {
            return;
        }

        if(!pSwitchWgt->isEnter())//是否可以进入，不可则返回
        {
            return;
        }
        disconnect(pCurrenWgt->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
                   this, SLOT(getFromAny(ModuleDir,int,QVariant)));
        pCurrenWgt->quit();
    }

    if (pSwitchWgt->getCL() == nullptr) {
        qCritical() << "pSwitchWgt->getCL() == nullptr " << wgtId;
    }
    connect(pSwitchWgt->getCL(), SIGNAL(sendToMain(ModuleDir,int,QVariant)),
            this, SLOT(getFromAny(ModuleDir,int,QVariant)));


    m_currentWgt[Area] = pSwitchWgt;

    pCurrenWgt = pSwitchWgt;

    pCurrenWgt->initWidget();

    m_mainWinddow->addShowWidget(Area,pCurrenWgt);

    pCurrenWgt->showedWidgetDo();
}

void MainProcessor::initSound() {
    /**
     * 在调用任何 SDK
     * 其他接口之前，需要先调用全局初始化接口，注意全局初始化进程运行期间只应调用一次。
     */
//    const char*logPath = "./log"; //日志路径，请根据需要自行修改。
//    PIMediaPlayer_global_init(logPath);
}

void MainProcessor::playSound(bool isPlaySound) {
#if 0
    if (isPlaySound && playHandle == NULL) {
        QString currImei = System::getInstance()->getCurrentVehicle();
        QVariant data = jsonMethord::getInstance()
                ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
        if(data.toList().isEmpty()){
            return;
        }
        QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
        std::string data_source = mapVehicle.value(currImei).toList().at(0).toMap().value("Sound").toString().toStdString();
        /**
         * 初始化播放器对象
         */
        playHandle = iLive_Player_create((void *)(data_source.rfind("pzsp://", 0) == 0), NULL);//创建播放器
        if(playHandle == NULL){
            qDebug() << "[player] can't create sound player!";
            return;
        }
        iLive_Player_set_data_source(playHandle, NULL, data_source.c_str());//设置收流地址
        iLive_Player_set_hwnd(playHandle, NULL);//设置窗口句柄
        iLive_Player_prepare_async(playHandle);//将播放器置为准备播放状态,一旦窗口句柄和收流地址设置完成，将自动开始播放。

        /**
         * 启动收流
         */
        iLive_Player_start(playHandle);
        isHavePlaySound = true;
    } else {
            /**
             * 停止收流
             */
            iLive_Player_stop(playHandle);

            /**
             * 销毁播放器对象
             */
            iLive_Player_shutdown(playHandle, NULL);
            iLive_Player_dec_ref(playHandle);
            playHandle = NULL;
            isHavePlaySound = false;
    }
#endif
}

void MainProcessor::runShellCmd(QString cmd)
{
    QProcess *pProc = new QProcess();
    pProc->start(cmd);
    bool isfinished = pProc->waitForFinished();
    if(isfinished){
        pProc->close();
        delete pProc;
        pProc = NULL;
    }
}
