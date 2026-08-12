#include "MainMonitorCL.h"
#include "../include/qtzmq.h"
#include <QDebug>
#include <QSettings>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include "FunModule/IpcManager.h"
#include "public/fbsstructure.h"
#include <QApplication>
#include "public/jsonMethord.h"
#include <QGraphicsDropShadowEffect>
#define MAXPLAYWGT  6

MainMonitorCL::MainMonitorCL(QObject *parent) : IController(parent)
{
    // --> BEGIN added by ZJZ, 2022/3/1
//    timer_checkCloudy = new QTimer(this);
//    connect(timer_checkCloudy, SIGNAL(timeout()), this, SLOT(slot_timer_checkCloudy()));
//    timer_checkCloudy->start(1000);
    cloudyComingTime = QTime::currentTime();
    // <-- END
}

MainMonitorCL::~MainMonitorCL()
{

}

void MainMonitorCL::doInit()
{
    //    qInfo()<<"MainMonitorCL::doInit()";
}

void MainMonitorCL::doUnInit()
{

}

bool MainMonitorCL::exitAction()
{
    return true;
}

bool MainMonitorCL::intoAction()
{
    this->refreshDisplayData();
    return true;
}

// --> BEGIN added by ZJZ, 2022/3/1
#if 0
void MainMonitorCL::slot_timer_checkCloudy()
{
    iCloudyHeartCnt--;
    if (0 == iCloudyHeartCnt) {
        timer_checkCloudy->stop();

        // 刷新座舱和云台连接状态
        QVector<ModuleDir>   m_moduleDirs;
        QVector<int>         m_cmds;
        QVector<QVariant>    m_datas;
        ModuleDir module;
        module.clear();
        m_moduleDirs.clear();
        m_cmds.clear();
        module.append(MD_MainCamera);
        m_moduleDirs.append(module);
        m_cmds.append(MC_UpdateCloudyState);
        m_datas.clear();
        m_datas<<"座舱-平台连接  未连接";
        QMetaObject::invokeMethod(IpcManager::GetInstance(),"sendToMain",
                                  Q_ARG(ModuleDir,m_moduleDirs.at(0)),
                                  Q_ARG(int,m_cmds.at(0)),
                                  Q_ARG(QVariant,m_datas.at(0)));
    }
}
#endif
// <-- END

void MainMonitorCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    MainMonitorWgtCmdType Cmd = static_cast<MainMonitorWgtCmdType>(cmd);

    switch (Cmd) {
    case MM_UpdateOnlineState:{
        // 保活
//        iCloudyHeartCnt = 6;
        cloudyComingTime = QTime::currentTime();
        // 刷新座舱和云台连接状态
        {
//            ModuleDir moduleDir;
//            moduleDir.clear();
//            moduleDir.append(MD_MainCamera);
//            emit sendToMain(moduleDir,MC_UpdateCloudyState, "座舱-平台连接  已连接");
            QVector<ModuleDir>   m_moduleDirs;
            QVector<int>         m_cmds;
            QVector<QVariant>    m_datas;
            ModuleDir module;
            module.clear();
            m_moduleDirs.clear();
            m_cmds.clear();
            module.append(MD_MainCamera);
            m_moduleDirs.append(module);
            m_cmds.append(MC_UpdateCloudyState);
            m_datas.clear();
            m_datas<<"座舱-平台连接  已连接";
            QMetaObject::invokeMethod(IpcManager::GetInstance(),"sendToMain",
                                      Q_ARG(ModuleDir,m_moduleDirs.at(0)),
                                      Q_ARG(int,m_cmds.at(0)),
                                      Q_ARG(QVariant,m_datas.at(0)));
        }
        emit pushDataToView(CL_UpdateOnlineState);
        break;
    }
    case MM_ShowEmergency:{
        bool showFlag=data.value<bool>();
        if(showFlag)
        {
            if(m_msgBox!=nullptr)
                m_msgBox->close();
            if(m_msgEmergency==nullptr)
            {
                m_msgEmergency = new QMessageBox(QMessageBox::Question,
                                           QString::fromUtf8("提示"),
                                           QString::fromUtf8("舱端紧急停车按键被按下!!"),
                                           QMessageBox::StandardButtons(QMessageBox::Ok),
                                           static_cast<QWidget*>(this->parent()->parent()));
                m_msgEmergency->setObjectName("MessageBox");
                setMessageStyle(m_msgEmergency,"急停按钮未复位!请先复位!",QSize(300,100));
                System::getInstance()->setShowFlag(true);
                m_msgEmergency->exec();
                delete m_msgEmergency;
                m_msgEmergency=nullptr;
                System::getInstance()->setShowFlag(false);
            }else
            {
                m_msgEmergency->show();
            }
        }else
        {
            if(m_msgEmergency!=nullptr)
                m_msgEmergency->close();
        }
        break;
    }
    case MM_CloseTip:{
        if(m_msgBox!=nullptr)
            m_msgBox->close();
        break;
    }
    case MM_InputKey:{
        emit pushDataToView(CL_InputKey);
        /*if((!System::getInstance()->getCurrentDriverLoginStatus().simplified().isEmpty())
          || (System::getInstance()->getCurrentCabinMode() == CM_Takeover))*/
        {
            inputHandler(static_cast<Qt::Key>(data.toInt()));
        }
        break;
    }
    case MM_VehicleStatus:{
        vehicleStatusHandler(data);
        break;
    }
    case MM_UpdateUI:{
        emit pushDataToView(CL_UpdateAll);
        break;
    }
    case MM_UpdateLoginStatus:{
        emit pushDataToView(CL_UpdateLoginStatus);
        break;
    }
    default:
    {break;}
    }
}



void MainMonitorCL::vehicleStatusHandler(QVariant &datavar)
{
    VehicleStatus vehstatus = datavar.value<VehicleStatus>();
    MainMonitorModel::VehicleInfo tVehicle;
    tVehicle.imei = QLatin1String(reinterpret_cast<char*>(vehstatus.imei),IMEI_LENGTH);

    // --> BEGIN added by ZQ, 2024/3/26
    static int vehicleStatus = 0;
    if (vehicleStatus != vehstatus.status)
    {
        if (vehstatus.status == 1)
        {
            m_pModel->m_onlineVehImei = tVehicle.imei;
        }
        else
        {
            m_pModel->m_onlineVehImei = "";
        }
        vehicleStatus = vehstatus.status;
        emit pushDataToView(CL_UpdateOnlineState);
    }
    // <-- END

    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    // 防护：连接错误 IP 时 gateway 会下发不在配置表中的 imei，
    // 此时 mapVehicle.value(imei) 为空 QVariant，直接 .toList().at(0) 会越界崩溃。
    QVariantList vehInfoList = mapVehicle.value(tVehicle.imei).toList();
    if (vehInfoList.isEmpty()) {
        qWarning() << "vehicle imei not found in rcdconfig.json, skip:" << tVehicle.imei;
        return;
    }
    QMap<QString, QVariant> vehInfo = vehInfoList.at(0).toMap();
    tVehicle.name = vehInfo.value("Name").toString();
    tVehicle.url = vehInfo.value("Forward").toString();
    m_pModel->vehicleName = tVehicle.name;

    if(m_pModel->addVehicle(tVehicle)){
        this->refreshDisplayData();
        emit pushDataToView(CL_UpdateAll);
    }
}

void MainMonitorCL::inputHandler(Qt::Key key)
{
    int flag = 0;

    switch (key) {
    case Qt::Key_PageUp:
        pageUpkeyPress();
        return;

    case Qt::Key_PageDown:
        keyPress();
        return;

    case Qt::Key_Control:
        keyEmpty();
        return;

    case Qt::Key_Up:{
        flag = 1;
        if(m_pModel->m_select < 3){
            if(m_pModel->m_pageIndex > 0){
                m_pModel->m_pageIndex -= 1;
                flag = 2;
            }
        }else{
            m_pModel->m_select -= 3;
        }
        break;
    }
    case Qt::Key_Down:{
        flag = 1;
        if(m_pModel->m_select < 3){
            m_pModel->m_select += 3;
        }else{
            if(m_pModel->m_pageIndex < m_pModel->m_maxPage - 1){
                m_pModel->m_pageIndex += 1;
                flag = 2;
            }
        }
        break;
    }
    case Qt::Key_Left:{
//        if(System::getInstance()->onlineVehicle.size()==0)
//            return;
        flag = 1;
        if(m_pModel->m_select < 1){
            if(m_pModel->m_pageIndex > 0){
                m_pModel->m_pageIndex -= 1;
                flag = 2;
            }
            m_pModel->m_select = 5;
        }else{
            m_pModel->m_select -= 1;
        }
        break;
    }
    case Qt::Key_Right:{
//        if(System::getInstance()->onlineVehicle.size()==0)
//            return;
        flag = 1;
        if(m_pModel->m_select < 5){
            m_pModel->m_select += 1;
        }else{
            if(m_pModel->m_pageIndex < m_pModel->m_maxPage - 1){
                m_pModel->m_pageIndex += 1;
                flag = 2;
            }
            m_pModel->m_select = 0;
        }
        break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:{
        qDebug()<<"m_pModel->m_select="<<m_pModel->m_select;
        if(m_pModel->m_select < 0)
            return;
        flag = 3;
        break;
    }
    case Qt::Key_Escape:{
        qDebug() << "+++++++++== showSelfTestWnd = 1";
        if(System::getInstance()->showSelfTestWnd) {
            qDebug() << "+++++++++== showSelfTestWnd = 0";
            System::getInstance()->showSelfTestWnd = false;
            popContent st;
            st.firstPriority = 1;
            st.secondPriority = 0;
            st.cmd = TipsPopupLBtnCmd_Timeout;
            st.delay = 0;
            st.content = "等待连接超时，请检查网络状态后重新进入！";
            st.btnText = "确认";

            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_SelfTest);
            emit sendToMain(moduleDir,selfTest_Hide,QVariant::fromValue(st));
            return;
        }

        flag = 4;
        break;
    }
    case Qt::Key_Space:{
        flag = 5;
        break;
    }
    case Qt::Key_Z:{
        flag = 6;
        break;
    }
    default:
        qDebug() << "not used this key:" << key;
        break;
    }


    if(flag == 1){
        emit pushDataToView(CL_UpdateSelect);
    }else if(flag == 2){
        this->refreshDisplayData();
        emit pushDataToView(CL_UpdateAll);
    }else if(flag == 3){
        QString &imei = m_pModel->m_showVehicle[m_pModel->m_select];
        if(!imei.isEmpty() && !System::getInstance()->getShowFlag()){
            bool shouldReturn=false;
            // --> BEGIN modify by ZQ, 2024/3/17
            /*
            //判定车辆是否在线
            if(System::getInstance()->onlineVehicle.find(imei)==System::getInstance()->onlineVehicle.end()){
                m_msgBox = new QMessageBox(QMessageBox::Question,
                                           QString::fromUtf8("提示"),
                                           "",
                                           QMessageBox::StandardButtons(QMessageBox::Yes),
                                           static_cast<QWidget*>(this->parent()->parent()));
                m_msgBox->setObjectName("MessageBox");
                setMessageStyle(m_msgBox,"车辆离线,无法申请连接",QSize(600,100));
                System::getInstance()->setShowFlag(true);
                m_msgBox->setButtonText(QMessageBox::Yes,QString::fromUtf8("确定"));
                m_msgBox->setDefaultButton(QMessageBox::Yes);
                m_msgBox->exec();
                delete m_msgBox;
                System::getInstance()->setShowFlag(false);
                m_msgBox=nullptr;
                shouldReturn=true;
            }

            //判定是否登陆成功
            if(System::getInstance()->getCurrentDriverLoginStatus().simplified().isEmpty()){
                m_msgBox = new QMessageBox(QMessageBox::Question,
                                           QString::fromUtf8("提示"),
                                           "",
                                           QMessageBox::StandardButtons(QMessageBox::Yes),
                                           static_cast<QWidget*>(this->parent()->parent()));
                m_msgBox->setObjectName("MessageBox");
                setMessageStyle(m_msgBox,"座舱未登陆！请先登陆，再申请连接车辆",QSize(600,100));
                System::getInstance()->setShowFlag(true);
                m_msgBox->setButtonText(QMessageBox::Yes,QString::fromUtf8("确定"));
                m_msgBox->setDefaultButton(QMessageBox::Yes);
                m_msgBox->exec();
                delete m_msgBox;
                System::getInstance()->setShowFlag(false);
                m_msgBox=nullptr;
                shouldReturn=true;
            }

            //判断云端是否掉线
            //timer_checkCloudy->start(1000);
            int elapsed = cloudyComingTime.msecsTo(QTime::currentTime());
            elapsed = abs(elapsed);
            qDebug() << "elapsed =" << elapsed << "ms";
            if (elapsed > 6000) {
                m_msgBox = new QMessageBox(QMessageBox::Question,
                                           QString::fromUtf8("提示"),
                                           "",
                                           QMessageBox::StandardButtons(QMessageBox::Yes),
                                           static_cast<QWidget*>(this->parent()->parent()));
                m_msgBox->setObjectName("MessageBox");
                setMessageStyle(m_msgBox,"座舱与云控平台连接断开！请检查后重试。",QSize(600,100));
                System::getInstance()->setShowFlag(true);
                m_msgBox->setButtonText(QMessageBox::Yes,QString::fromUtf8("确定"));
                m_msgBox->setDefaultButton(QMessageBox::Yes);
                m_msgBox->exec();
                delete m_msgBox;
                System::getInstance()->setShowFlag(false);
                m_msgBox=nullptr;
                shouldReturn=true;
            }
            */
#if 0
            if(1 != System::getInstance()->getVehicleStatus() || m_pModel->m_onlineVehImei != imei)
            {
                m_msgBox = new QMessageBox(QMessageBox::Question,
                                           QString::fromUtf8("提示"),
                                           "",
                                           QMessageBox::StandardButtons(QMessageBox::Yes),
                                           static_cast<QWidget*>(this->parent()->parent()));
                m_msgBox->setObjectName("MessageBox");
                setMessageStyle(m_msgBox,"车辆离线",QSize(600,100));
                System::getInstance()->setShowFlag(true);
                m_msgBox->setButtonText(QMessageBox::Yes,QString::fromUtf8("确定"));
                m_msgBox->setDefaultButton(QMessageBox::Yes);
                m_msgBox->exec();
                delete m_msgBox;
                System::getInstance()->setShowFlag(false);
                m_msgBox=nullptr;
                shouldReturn=true;
            }
#endif
            // <-- END

            //判断舱端是否按下了紧急停车
            if(System::getInstance()->getShowEmergency()){
                ModuleDir moduleDir;
                moduleDir.append(MD_MainMonitor);
                emit sendToMain(moduleDir,MM_ShowEmergency,true);
                shouldReturn=true;
            }

            if(shouldReturn) return;

            //////////////////////////////////////////////////////

            {
                QVector<ModuleDir>   m_moduleDirs;
                QVector<int>         m_cmds;
                QVector<QVariant>    m_datas;
                ModuleDir module;
                QString imei =  m_pModel->m_showVehicle[m_pModel->m_select];
                System::getInstance()->setCurrentVehicle(m_pModel->m_showVehicle[m_pModel->m_select]);
                m_datas<<imei;
                module.append(MD_IPCManager);
                m_moduleDirs.append(module);
                m_cmds.append(IM_ReqConnect);
                QMetaObject::invokeMethod(IpcManager::GetInstance(),"sendToMain",
                                          Q_ARG(ModuleDir,m_moduleDirs.at(0)),
                                          Q_ARG(int,m_cmds.at(0)),
                                          Q_ARG(QVariant,m_datas.at(0)));
                
#if 0
                
                //设置当前车辆
                qDebug()<<"current imei:"<<m_pModel->m_showVehicle[m_pModel->m_select];
                System::getInstance()->setCurrentVehicle(m_pModel->m_showVehicle[m_pModel->m_select]);
                ModuleDir moduleDir;
                moduleDir.append(MD_MainProcessor);
                emit sendToMain(moduleDir,MP_SwitchLayout,LT_RemoteControl);

                //设置当前舱端模式: 等待连接
                System::getInstance()->setCurrentCabinMode(CM_WaitTakeover);

                //主动向平台请求接管
                QVector<ModuleDir>   m_moduleDirs;
                QVector<int>         m_cmds;
                QVector<QVariant>    m_datas;
                ModuleDir module;
                QString imei =  m_pModel->m_showVehicle[m_pModel->m_select];
                m_datas<<imei;
                module.append(MD_IPCManager);
                m_moduleDirs.append(module);
                m_cmds.append(IM_Cloud_Request);//请求平台任务
                QMetaObject::invokeMethod(IpcManager::GetInstance(),"sendToMain",
                                          Q_ARG(ModuleDir,m_moduleDirs.at(0)),
                                          Q_ARG(int,m_cmds.at(0)),
                                          Q_ARG(QVariant,m_datas.at(0)));
                qDebug()<<"UI请求平台接管任务";

                //变更状态
                module.clear();
                m_moduleDirs.clear();
                m_cmds.clear();
                module.append(MD_MainCamera);
                m_moduleDirs.append(module);
                m_cmds.append(MC_UpdateState);
                m_datas.clear();
                m_datas<<"监控中";
                QMetaObject::invokeMethod(IpcManager::GetInstance(),"sendToMain",
                                          Q_ARG(ModuleDir,m_moduleDirs.at(0)),
                                          Q_ARG(int,m_cmds.at(0)),
                                          Q_ARG(QVariant,m_datas.at(0)));
#endif

            }

        }

    }else if(flag == 4){
        // 勿与 getShowFlag() 绑定：该标志若未恢复为 false，会静默跳过本分支导致不按 Esc
        // 也永远不 QApplication::exit，RCD 进程会一直留在 ps 里。
        m_msgBox = new QMessageBox(QMessageBox::Question, QString::fromUtf8("提示"), "",
                                          QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),
                                          static_cast<QWidget*>(this->parent()->parent()));
        m_msgBox->setObjectName("MessageBox");
        setMessageStyle(m_msgBox,"是否退出程序?",QSize(200,100));
        System::getInstance()->setShowFlag(true);
        m_msgBox->setButtonText(QMessageBox::Yes,QString::fromUtf8("确认"));
        m_msgBox->setButtonText(QMessageBox::No,QString::fromUtf8("返回"));
        m_msgBox->setDefaultButton(QMessageBox::No);

        if(m_msgBox->exec() == QMessageBox::Yes){
            QApplication::exit();
        }
        delete m_msgBox;
        System::getInstance()->setShowFlag(false);
        m_msgBox=nullptr;

    }else if(flag == 5){

        //        saveGifForm::instance()->showForm();
        //        MoviePlayer::instance()->close();
    }
    else if (6 == flag) {/*
        saveGifForm::instance()->close();
        MoviePlayer::instance()->showMaximized();*/
    }
    qDebug() << "+++++++++++++++++++++++++++++++++ flag=" << flag;
}

void MainMonitorCL::refreshDisplayData()
{
    int total = m_pModel->m_vehicleList.count();
    m_pModel->m_maxPage = total/MAXPLAYWGT;
    m_pModel->m_maxPage += total%MAXPLAYWGT ? 1 : 0;

    if(m_pModel->m_pageIndex >= m_pModel->m_maxPage){
        m_pModel->m_pageIndex = 0;
        if(m_pModel->m_maxPage > 0){
            m_pModel->m_pageIndex = m_pModel->m_maxPage - 1;
        }
    }

    int pageIndex = m_pModel->m_pageIndex*MAXPLAYWGT;

    for(int i = 0;i < MAXPLAYWGT;i++){
        if(pageIndex + i < total){
            m_pModel->m_showVehicle[i] = m_pModel->m_vehicleList[pageIndex+i];
        }else{
            m_pModel->m_showVehicle[i].clear();
        }
    }
}

void MainMonitorCL::setMessageStyle(QMessageBox *m,QString text,QSize size)
{
    QString style=
    "QMessageBox QLabel {"
            "min-width: %1px;"
            "min-height: %2px;"
    "}"
    "QMessageBox {"
            "background-color: rgb(54,76,98);"
            "border-color: rgb(0,186,255);"
            "border: 2px solid #298DFF;"
    "}"
    "QMessageBox QPushButton {"
            "border: 1px solid #298DFF;"
            "border-radius: 3px;"
            "background-color: rgb(40,76,96);"
            "color: white;"
            "font-size: 10pt;"
            "min-width: 70px;"
            "min-height: 25px;"
    "}"
    "QMessageBox QPushButton:focus {"
            "border: 1px solid #298DFF;"
            "border-radius: 3px;"
            "background-color: rgb(0,186,255);"
            "color: white;"
            "font-size: 10pt;"
            "min-width: 70px;"
            "min-height: 25px;"
    "}";
    style=style.arg(QString::number(size.width())).arg(QString::number(size.height()));


    m->setStyleSheet(style);

    text=("<font size='5'  color='white'>" ) + text;
    text += ("</font>");
    m->setText(text);
    m->setObjectName("MessageBox");
    m->setWindowOpacity(0.8);
    m->setIcon(QMessageBox::NoIcon);
    m->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    m->move(1920/2-size.width()/2,200);
}

void MainMonitorCL::setModel(MainMonitorModel *model)
{
    m_pModel = model;
}

void MainMonitorCL::keyEmpty()
{//self test takeover
    if(false == System::getInstance()->showSelfTestWnd) return;

    ModuleDir moduleDir;
    moduleDir.clear();
    moduleDir.append(MD_SelfTest);
    emit sendToMain(moduleDir,selfTest_empty_update,true);
}

void MainMonitorCL::pageUpkeyPress()
{//self test takeover
    if(false == System::getInstance()->showSelfTestWnd) return;

    ModuleDir moduleDir;
    moduleDir.clear();
    moduleDir.append(MD_SelfTest);
    emit sendToMain(moduleDir,selfTest_takeover_update,true);
}

void MainMonitorCL::keyPress()
{
    ModuleDir moduleDir;
    moduleDir.clear();

    if(System::getInstance()->showSelfTestWnd) {
        moduleDir.append(MD_SelfTest);
        emit sendToMain(moduleDir,selfTest_blind_update,true);
        return;
    }

    System::getInstance()->showSelfTestWnd = true;

    moduleDir.append(MD_SelfTest);
    emit sendToMain(moduleDir,selfTest_Show,true);
}
