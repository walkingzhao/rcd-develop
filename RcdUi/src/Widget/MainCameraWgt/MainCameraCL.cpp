#include "MainCameraCL.h"
#include <QStringList>
#include <QDebug>
#include <QSettings>
#include "../include/qtzmq.h"
#include "public/publicclass.h"
#include <QDir>
#include <QDateTime>
#include "FunModule/IpcManager.h"
#include "public/fbsstructure.h"
#include <QApplication>
#include "public/jsonMethord.h"
//#include "Component/hikvisioncamera.h"
MainCameraCL::MainCameraCL(QObject *parent) : IController(parent)
{
    _thread = new QThread;
    _screenThread = new screenRecordThread;
    _screenThread->moveToThread(_thread);
    connect(_thread,SIGNAL(finished()),_screenThread,SLOT(deleteLater()));
    connect(_thread,SIGNAL(started()),_screenThread,SLOT(slotWork()));

    // --> BEGIN added by ZJZ, 2022/3/3
    timer_checkSelfMode = new QTimer(this);
    connect(timer_checkSelfMode, SIGNAL(timeout()), this, SLOT(slot_timer_checkSelfMode()));
    // <-- END
}

MainCameraCL::~MainCameraCL()
{
    if(_thread->isRunning())
    {
        _screenThread->stopWork();  //关闭线程槽函数
        _thread->quit();            //退出事件循环
        _thread->wait();            //释放线程槽函数资源
    }
    _thread->deleteLater();
    _screenThread->deleteLater();
}

void MainCameraCL::doInit()
{
    //    qInfo()<<"MainCameraCL::doInit()";
}

void MainCameraCL::doUnInit()
{

}

bool MainCameraCL::exitAction()
{
    return true;
}
#ifdef HIK_INTERFACE
bool MainCameraCL::intoAction()
{
//    m_pModel->setRemoteStatus(MainCameraModel::RS_Monitoring);
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return false;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    const QVariantMap v = mapVehicle.value(currImei).toList().at(0).toMap();
    m_pModel->vehicleName = v.value("Name").toString();

    // In HIK mode, we don't necessarily play Artemis/RTSP. Prefer the stream URL configured per vehicle,
    // e.g. RTMP pulled from media server.
    m_pModel->setCameraUrl(v.value("Forward").toString(),
                           v.value("Backward").toString(),
                           "",
                           "");

    // Keep legacy camera name for other logic (if any).
    m_pModel->setCameraName(m_pModel->vehicleName + "-Forward",
                            m_pModel->vehicleName + "-Backward");
    return true;
}
#else
bool MainCameraCL::intoAction()
{
//    m_pModel->setRemoteStatus(MainCameraModel::RS_Monitoring);
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return false;
    }

    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();

    qDebug()<<"updatexzk mc intoAction:"<<mapVehicle.value(currImei).toList().at(0).toMap().value("Forward").toString()
           <<mapVehicle.value(currImei).toList().at(0).toMap().value("Backward").toString();

    m_pModel->setCameraUrl(mapVehicle.value(currImei).toList().at(0).toMap().value("Forward").toString(),
                           mapVehicle.value(currImei).toList().at(0).toMap().value("Backward").toString(),
                           "",
                           "");
    return true;
}
#endif
// --> BEGIN added by ZJZ, 2022/3/3
void MainCameraCL::slot_timer_checkSelfMode()
{
    iSelfModeCnt--;
    if (0 == iSelfModeCnt) {
        timer_checkSelfMode->stop();

        popContent st;
        st.firstPriority = 1;
        st.secondPriority = 0;
        st.cmd = TipsPopupLBtnCmd_Timeout;
        st.delay = 0;
        st.content = "等待连接超时，请检查网络状态后重新进入！";
        st.btnText = "确认";

        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_TipsPopup);
        emit sendToMain(moduleDir,TP_Show,QVariant::fromValue(st));
    }
}
// <-- END

// ---> START BAIYUN 2022/08/02
#if 0
void MainCameraCL::readTrackLineCfgFile(){
    //get current vehicle name
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return;
    }

    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    m_pModel->vehicleName = mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString();
    QString curVehicleFile = m_pModel->vehicleName + "_trackline_config.txt";
    qDebug() << "++++++++++ curVehicleFile: " << curVehicleFile;

    //get vehicle parameters path
    std::string str_vehiclename = "/" + curVehicleFile.toStdString();
    QString mainPath = QApplication::applicationDirPath();
    std::string path = mainPath.toStdString() + str_vehiclename;
    qDebug() << "++++++++++ path: " << QString::fromStdString(path);

    QDir mainDir;
    mainDir.setPath(mainPath);
    QStringList filelist = mainDir.entryList(QStringList()<<"*.txt",QDir::AllEntries | QDir::NoDot | QDir::NoDotDot, QDir::Time);
    qDebug() << "++++++++++ filelist: " << filelist;
    if(!filelist.contains(curVehicleFile)){
        return;
    }
    qDebug()<<"++++++++++ start read file data: " << curVehicleFile;

    //get vehicle parameters
    config_parser_ptr_.reset(new common::ConfigParser(path));
//    TrackLineCalibrationST st;
    m_pModel->m_TrackLineCfg.valid = true;
    m_pModel->m_TrackLineCfg.counter = 0;
    m_pModel->m_TrackLineCfg.mirrorBackCameraFlag =  config_parser_ptr_->getBool("mirrorBackCameraFlag");
    m_pModel->m_TrackLineCfg.wheelMaxAngle = config_parser_ptr_->getDouble("wheelMaxAngle");
    m_pModel->m_TrackLineCfg.steerMaxAngle = config_parser_ptr_->getDouble("steerMaxAngle");
    m_pModel->m_TrackLineCfg.FovFrontCamera = config_parser_ptr_->getDouble("FovFrontCamera");
    m_pModel->m_TrackLineCfg.FovBackCamera = config_parser_ptr_->getDouble("FovBackCamera");
    m_pModel->m_TrackLineCfg.inclinationAngleFrontCamera = config_parser_ptr_->getDouble("inclinationAngleFrontCamera");
    m_pModel->m_TrackLineCfg.inclinationAngleBackCamera = config_parser_ptr_->getDouble("inclinationAngleBackCamera");
    m_pModel->m_TrackLineCfg.heightFrontCamera = config_parser_ptr_->getDouble("heightFrontCamera");
    m_pModel->m_TrackLineCfg.heightBackCamera = config_parser_ptr_->getDouble("heightBackCamera");
    m_pModel->m_TrackLineCfg.screenWidth = config_parser_ptr_->getDouble("screenWidth");
    m_pModel->m_TrackLineCfg.screenHeight = config_parser_ptr_->getDouble("screenHeight");
    m_pModel->m_TrackLineCfg.offsetFrontCamera = config_parser_ptr_->getDouble("offsetFrontCamera");
    m_pModel->m_TrackLineCfg.offsetBackCamera = config_parser_ptr_->getDouble("offsetBackCamera");
    m_pModel->m_TrackLineCfg.distanceFrontCamera2Axles = config_parser_ptr_->getDouble("distanceFrontCamera2Axles");
    m_pModel->m_TrackLineCfg.distanceBackCamera2Axles = config_parser_ptr_->getDouble("distanceBackCamera2Axles");
    m_pModel->m_TrackLineCfg.distanceAxles = config_parser_ptr_->getDouble("distanceAxles");
    m_pModel->m_TrackLineCfg.distanceFrontAxles = config_parser_ptr_->getDouble("distanceFrontAxles");
    m_pModel->m_TrackLineCfg.distanceBackAxles = config_parser_ptr_->getDouble("distanceBackAxles");

    qDebug()<<"[recv]是否开启了后置摄像头镜像："<<m_pModel->m_TrackLineCfg.mirrorBackCameraFlag
              << "方向盘最大转角："<<m_pModel->m_TrackLineCfg.steerMaxAngle
              <<"车轮最大转角："<<m_pModel->m_TrackLineCfg.wheelMaxAngle
              <<"前摄像头垂直可视角度(度):"<<m_pModel->m_TrackLineCfg.FovFrontCamera
              <<"后摄像头垂直可视角度(度):"<<m_pModel->m_TrackLineCfg.FovBackCamera
              <<"前摄像头中心线同水平面的夹角(度):"<<m_pModel->m_TrackLineCfg.inclinationAngleFrontCamera
              <<"后摄像头中心线同水平面的夹角(度):"<<m_pModel->m_TrackLineCfg.inclinationAngleBackCamera
              <<"前摄像头距离地面距离:"<<m_pModel->m_TrackLineCfg.heightFrontCamera
              <<"后摄像头距离地面距离:"<<m_pModel->m_TrackLineCfg.heightBackCamera
              <<"屏幕分辨率横向方向:"<<m_pModel->m_TrackLineCfg.screenWidth
              <<"屏幕分辨率纵向方向:"<<m_pModel->m_TrackLineCfg.screenHeight
              <<"前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<m_pModel->m_TrackLineCfg.offsetFrontCamera
              <<"后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<m_pModel->m_TrackLineCfg.offsetBackCamera
              <<"车头摄像头到车前轮中心的距离:"<<m_pModel->m_TrackLineCfg.distanceFrontCamera2Axles
              <<"车尾摄像头到车后轮中心的距离:"<<m_pModel->m_TrackLineCfg.distanceBackCamera2Axles
              <<"车前后轮的轴距:"<<m_pModel->m_TrackLineCfg.distanceAxles
              <<"前车轮轴长:"<<m_pModel->m_TrackLineCfg.distanceFrontAxles
              <<"后车轮轴长:"<<m_pModel->m_TrackLineCfg.distanceBackAxles;

//    m_pModel->m_TrackLineCfg = data.value<TrackLineCalibrationST>();
}
#endif
// <--- END

// 处理模块支持的命令
void MainCameraCL::getFromAny(ModuleDir,int cmd,QVariant data)
{
//    MainCameraWgtCmdType Cmd = static_cast<MainCameraWgtCmdType>(cmd);
    switch (cmd) {
    case CC_StartPlay:{ // 开始播放
        emit pushDataToView(CL_StartPlay,data);
        break;
    }

    case MC_UpdatePosition:{ // 车辆位置信息
        m_pModel->m_GpsInfo = data.value<GPSInfoST>();
        //更新边界显示图像
        emit pushDataToView(CL_UpdatePosition);
        break;
    }
    case MC_CameraCalibration:{ // 摄像头标定
        m_pModel->m_TrackLineCfg = data.value<TrackLineCalibrationST>();
        break;
    }
    case MC_UpdateState:{ // 更新状态
        emit pushDataToView(CL_UpdateState,data);
        if ("等待连接" == data.toString() && false == timer_checkSelfMode->isActive()) {
            iSelfModeCnt = 15;
            timer_checkSelfMode->start(1000);
        } else if ("监控中" == data.toString()) {
            if (timer_checkSelfMode->isActive()) {
                timer_checkSelfMode->stop();
            }
        }
        break;
    }
    case MC_UpdateCloudyState: {
        emit pushDataToView(CL_UpdateCloudyState,data);
        break;
    }
    case MC_RemoteResule:{
        uint resule = data.toUInt();
        switch (resule)
        {
        case RESP_REMOTE_CONTROL_VEHICLE_RECV:{ // 车辆已接受 2
            if(System::getInstance()->getCurrentCabinMode()==CM_WaitTakeover){// 按下pageup返回成功
                resule = MainCameraModel::RS_RemoteControl;
                System::getInstance()->setCurrentCabinMode(CM_Takeover);// 已经按下pageUP并且返回成功
            }
            else if(System::getInstance()->getCurrentCabinMode()==CM_Takeover) { // 接管中
                resule = MainCameraModel::RS_Monitoring;
            }

            break;
        }
        case RESP_REMOTE_CONTROL_VEHICLE_DISCONNECT:{ // 车辆未知 （找不到车）1
            resule = MainCameraModel::RS_RemoteControlUnknownVehicle;
            break;
        }
        case RESP_REMOTE_CONTROL_VEHICLE_REJECT:{ // 车辆拒绝 （车辆返回）4
            resule = MainCameraModel::RS_RemoteConnectionRefused;
            break;
        }
        case RESP_REMOTE_CONTROL_VEHICLE_TIMEOUT:{ //连接超时3
            resule = MainCameraModel::RS_RemoteConnectionTimedOut;
            break;
        }
        default:{
            resule = MainCameraModel::RS_RemoteControlFail; // 控制失败
            break;
        }
        }
        m_pModel->setRemoteStatus(resule);
        break;
    }
    case MC_VehicleDelay:{ // 延迟
        m_pModel->setVehicleDelay(data.toUInt());
        break;
    }
    case MC_MainCamera_Vehicle_data:{
        vehicleDataST st = data.value<vehicleDataST>();


//        qDebug()<<"MainCameraCL MC_MainCamera_Vehicle_data:"
//             <<st.speed<<(int)st.gear<<(int)st.mode<<(int)st.handBrake
//            <<"近光灯:"<<(int)st.lowBeam<<"双闪:"<<st.emergencyFlash
//           <<"排气制动"<<st.exhaustBrake;


        m_pModel->setThrottle(st.bodys.throttlePedal);//加速踏板百分比

        // --> BEGIN modified by ZJZ, 2022/5/10
//        m_pModel->setBrake(st.brakePedal);//制动踏板位置百分比 0~100%

        if (st.bodys.vehicleType == 1) {
            m_pModel->setBrake(1, st.bodys.brakePedal);//dian
        } else {
            m_pModel->setBrake(0, st.bodys.hydraulicBrake);//ye ya
        }
        // <-- END

        m_pModel->setSpeedRaw(st.bodys.engineSpeed);//发动机转速

        m_pModel->setSpeed(st.bodys.speed);////km/h 车速

        float gear = st.bodys.gear;
        if(gear<0){ //档位 -1:R 0:N 1:D
            m_pModel->setGear(-1);//R
        }else if(gear>0) {
            m_pModel->setGear(1);//D
        }
//        else if(st.bodys.handBrake == 0x00&&gear==0){
//            m_pModel->setGear(0);//空档位
//        }
//        if(st.bodys.handBrake == 0x01&&gear==0){
//            m_pModel->setGear(2);//驻车制动
//        }

        /////////////////////////////
        else if(gear==0){
            m_pModel->setGear(0);//空档位
        }

        int parkingBrake = static_cast<int>(st.bodys.parkingBrake);
        int loadingBrake = static_cast<int>(st.bodys.loadingBrake);
        m_pModel->setParkingBrake(parkingBrake);
        m_pModel->setLoadingBrake(loadingBrake);
        /////////////////////////////

        m_pModel->setWheel(st.bodys.steeringWheelAngle);//方向盘当前转角 -800~800
        break;
    }
    case MC_InputKey:{
        emit pushDataToView(CL_InputKey);
        /*if((!System::getInstance()->getCurrentDriverLoginStatus().simplified().isEmpty())
          || (System::getInstance()->getCurrentCabinMode() == CM_Takeover))*/{
            qDebug()<<"MainMonitor处理按键消息";
            inputHandler(static_cast<Qt::Key>(data.toInt()));
        }
        break;
    }
    case MC_UpdateLoginStatus:{
        emit pushDataToView(CL_UpdateLoginStatus);
        break;
    }
    default:
        break;

    }

}

// 控制按键处理
void MainCameraCL::inputHandler(Qt::Key key)
{
    qDebug()<<"updatexzk MainCameraCL::inputHandler"<<key;
    if(key == Qt::Key_PageDown){
        //左前、右前均没有配置，则按键无反应
        if(m_pModel->m_front_left_CameraUrl == "" && m_pModel->m_front_right_cameraUrl == ""){
            return;
        }
        qDebug() << "front left: " << m_pModel->m_front_left_CameraUrl
                 << ", front right: " << m_pModel->m_front_right_cameraUrl
                 << ", enable: " << System::getInstance()->forwardLeft_forwardRight_Big;

        //切换标志位状态
        System::getInstance()->forwardLeft_forwardRight_Big = !System::getInstance()->forwardLeft_forwardRight_Big;

        //更新【单车界面】（左前、右前显示/隐藏）
        emit pushDataToView(CL_UpdateFrontLeftRightCamera,System::getInstance()->forwardLeft_forwardRight_Big);

        //更新左前摄像头
        ModuleDir moduleDir;
        if(m_pModel->m_front_left_CameraUrl != ""){
            moduleDir.clear();
            moduleDir.append(MD_DriveCamera);
            emit sendToMain(moduleDir,DC_UpdateCamera,System::getInstance()->forwardLeft_forwardRight_Big);
        }

        //更新右前摄像头
        if(m_pModel->m_front_right_cameraUrl != ""){
            moduleDir.clear();
            moduleDir.append(MD_ForwardRightCamera);
            emit sendToMain(moduleDir,CC_StartPlay,System::getInstance()->forwardLeft_forwardRight_Big);

            moduleDir.clear();
            moduleDir.append(MD_RightCamera);
            emit sendToMain(moduleDir,RC_UpdateForwardRihgtCamera,System::getInstance()->forwardLeft_forwardRight_Big);
        }

        //
        moduleDir.clear();
        moduleDir.append(MD_MainProcessor);
        emit sendToMain(moduleDir,MP_SwitchLayout,LT_RemoteControl);
    }
    else if(key == Qt::Key_PageUp){
        qDebug() << "zjz1115" << System::getInstance()->getCurrentCabinMode();
        if(System::getInstance()->getCurrentCabinMode() == CM_Takeover){
            //            _thread->quit();
            ModuleDir moduleDir;
            moduleDir.append(MD_CompleteOperEnd);
            emit sendToMain(moduleDir,COE_Show);
        }else if(System::getInstance()->getCurrentCabinMode() == CM_WaitTakeover){
            /*if(!System::getInstance()->getCurrentDriverLoginStatus().simplified().isEmpty())*/{//判断司机是否登录
                //                _thread->start();
                ModuleDir moduleDir;
                moduleDir.append(MD_NotSatisfiedWithTakeover);
                emit sendToMain(moduleDir,NS_Show);
            }
        }

        // --> BEGIN added by ZJZ, 2022/3/3
        else if(System::getInstance()->getCurrentCabinMode() == CM_WaitTask){// 等待连接
            popContent st;
            st.firstPriority = 2;
            st.secondPriority = 2;
            st.cmd = TipsPopupLBtnCmd_None;
            st.delay = 3000;
            st.content = "请等待座舱与车辆连接后再申请接管。";
            st.btnText = "";

            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_TipsPopup);
            emit sendToMain(moduleDir,TP_Show,QVariant::fromValue(st));
        }
        // <-- END
    }

    else if((key == Qt::Key_Return)||(key == Qt::Key_Enter)){
        if(System::getInstance()->getCurrentMsg() != MD_None)//窗口有显示，发送enter
        {
            ModuleDir moduleDir;
            moduleDir.append(System::getInstance()->getCurrentMsg());
            emit sendToMain(moduleDir,CC_Enter);
        }
    }else if(key == Qt::Key_Escape){
        if(System::getInstance()->getCurrentMsg()!=MD_None) {
            qDebug() << "[error] you have exited!";
            return;
        }

        qDebug() << "cabin mode: " << System::getInstance()->getCurrentCabinMode()
                 << ", takeover purpose" << System::getInstance()->getVehicleTakeoverPurpose();

        if(System::getInstance()->getCurrentCabinMode() == CM_WaitTakeover) {
            if(/*System::getInstance()->getVehicleTakeoverPurpose() == 6*/1)//监控任务6：监控行驶
            {
                // --> BEGIN modify by ZJZ, 2022/3/17
#if 0
                ModuleDir moduleDir;
                moduleDir.append(MD_CompleteOperEnd);
                emit sendToMain(moduleDir,COE_Show);
#endif
#if 1
                popContent st;
                st.firstPriority = 2;
                st.secondPriority = 2;
                st.cmd = TipsPopupLBtnCmd_GiveupMonitor;
                st.delay = 0;
                st.content = "确认结束监控？";
                st.btnText = "确认";

                ModuleDir moduleDir;
                moduleDir.clear();
                moduleDir.append(MD_TipsPopup);
                emit sendToMain(moduleDir,TP_Show,QVariant::fromValue(st));
                // <-- END
#endif
            }else
            {
                ModuleDir moduleDir;
                moduleDir.append(MD_GiveUpTakeOver);
                emit sendToMain(moduleDir,GU_Show);

                // ---> START 隐藏排队等待弹窗 2022/09/15
                moduleDir.clear();
                moduleDir.append(MD_MainCameraTip);
                emit sendToMain(moduleDir, MainCameraTip_Hide);
                // <--- END
            }
        } else  if ((System::getInstance()->getCurrentCabinMode()==CM_WaitTask)
                 && (System::getInstance()->getCurrentMsg()==MD_None)) {
            // --> BEGIN modify by ZJZ, 2022/3/17
#if 0
            ModuleDir moduleDir;
            moduleDir.append(MD_MainProcessor);
            emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);
            System::getInstance()->setCurrentCabinMode(CM_Monitor);
#endif
            ModuleDir moduleDir;
            moduleDir.append(MD_GiveUpTakeOver);
            emit sendToMain(moduleDir,GU_Show);
            // <-- END

            // ---> START 隐藏排队等待弹窗 2022/09/15
            moduleDir.clear();
            moduleDir.append(MD_MainCameraTip);
            emit sendToMain(moduleDir, MainCameraTip_Hide);
            // <--- END
        }
        // --> BEGIN added by ZJZ, 2022/3/4
        else if(System::getInstance()->getCurrentCabinMode()==CM_Takeover) {
//            ModuleDir moduleDir;
//            moduleDir.append(MD_GiveUpTakeOver);
//            emit sendToMain(moduleDir,GU_Show);
            return;
        }
        // <-- END
    }
}

void MainCameraCL::setModel(MainCameraModel *model)
{
    m_pModel = model;
}
