#include "ZmqMsgPackage.h"
#include "../include/can/canraw.hpp"
#include "../include/qtzmq.h"
#include "../Protocol/HmiCmdPackage.h"
#include <QDataStream>
#include <QDebug>
#include <QString>

// ---> START BAIYUN 2022/08/02
#include <QApplication>
#include <QDir>
#include "public/jsonMethord.h"
// <--- END

SelfCheckStatusST ZmqMsgPackage::_selfdata ;
ZmqMsgPackage::ZmqMsgPackage()
{
}

bool  ZmqMsgPackage::c2uButtonKey(const std::string &topic,const void *data, int)
{
    KeyButton *pKey = (KeyButton*)(data);

    qDebug() << ZMQ_ADDR_CONTROL << "[recv]ZmqMsgPackage topic:"
             << topic.c_str()<<"softKey:"<<static_cast<Qt::Key>(pKey->key);

    ModuleDir module;
    module.append(MD_MainProcessor);
    QVariant variant(QVariant::UInt);
    variant.setValue(pKey->key);

    m_moduleDirs.append(module);
    m_cmds.append(MP_SoftKeyPress);
    m_datas.append(variant);

    return true;
}

bool  ZmqMsgPackage::cabinRawData(const std::string &topic,const void *data, int len)
{
    if(false == System::getInstance()->showSelfTestWnd) return false;

    auto msg = flatbuffers::GetRoot<Rcd::CtrlRawData>(data);
    qDebug() << ZMQ_ADDR_Gateway<< "[recv]ZmqMsgPackage topic:" << topic.c_str()
             << "clutch:" << msg->clutch()
             << ", brake:" << msg->brake()
             << ", accelerator:" << msg->accelerator()
             << ", handbrake:" << msg->handbrake()
             << ", steeringwheel:" << msg->steeringwheel();

    SelfTest_CtrlRawData_St st;
    st.clutch = msg->clutch();
    st.brake = msg->brake();
    st.accelerator = msg->accelerator();
    st.handbrake = msg->handbrake();
    st.steeringwheel = msg->steeringwheel();

    ModuleDir moduleDir;
    m_datas.clear();
    m_cmds.clear();
    moduleDir.clear();
    moduleDir.append(MD_SelfTest);
    m_moduleDirs.append(moduleDir);
    m_cmds.append(selfTest_Wheel_Update);
    m_datas.append(QVariant::fromValue(st));

    return true;
}

//主摄像头界面 数据
bool ZmqMsgPackage::g2uVehicleRawData(const std::string &topic,const void *buf,int len)
{
#if 0
    auto tmpMsg = TGMsg::GetMsgFrame(buf);
        auto s = flatbuffers::FlatBufferToString(static_cast<const uint8_t*>(buf), TGMsg::MsgFrameTypeTable(), false, false);
        qDebug() << ZMQ_ADDR_Gateway << "[recv]ZmqMsgPackage topic:" << topic.c_str() << "org data:" << s.c_str();

    return true;
#endif

#if 1
    auto tmpMsg = TGMsg::GetMsgFrame(buf);
    auto s = flatbuffers::FlatBufferToString(static_cast<const uint8_t*>(buf), TGMsg::MsgFrameTypeTable(), false, false);
    qDebug() << ZMQ_ADDR_Gateway << "[recv]ZmqMsgPackage topic:" << topic.c_str() << "org data:" << s.c_str();

    switch (tmpMsg->msg_type()) {
    case TGMsg::MsgUnion_Vehicle_ReportFeedbackData:{ // 车辆检查是否满足接管
        auto msgT = tmpMsg->msg_as_Vehicle_ReportFeedbackData();
        //发送给车辆数据窗口
        vehicleDataST st;
        st.bodys.vehicleType = msgT->vehicleBodyData()->vehicleType();
        st.bodys.throttlePedal = msgT->vehicleBodyData()->throttlePedal(); //实际踩踏板百分比 0~100
        st.bodys.brakePedal = msgT->vehicleBodyData()->brakePedal();         //制动踏板位置百分比 0~100
        st.bodys.hydraulicBrake = msgT->vehicleBodyData()->hydraulicBrake();
        st.bodys.steeringWheelAngle = msgT->vehicleBodyData()->steeringWheelAngle(); //方向盘当前转角 -800~800
        st.bodys.engineSpeed = msgT->vehicleBodyData()->engineSpeed();//1rpm 发送机转速
        st.bodys.speed = msgT->vehicleBodyData()->speed();//km/h 车速

        st.bodys.batteryLevel = msgT->vehicleBodyData()->batteryLevel();
        st.bodys.cellTemperature = msgT->vehicleBodyData()->cellTemperature();
        st.bodys.fuelLevel = msgT->vehicleBodyData()->fuelLevel();
        st.bodys.engineOilPressure = msgT->vehicleBodyData()->engineOilPressure();
        st.bodys.engineCoolantTemperature = msgT->vehicleBodyData()->engineCoolantTemperature();
        st.bodys.coolantLevel = msgT->vehicleBodyData()->coolantLevel();
        st.bodys.exhaustPortEmperature = msgT->vehicleBodyData()->exhaustPortEmperature();
        st.bodys.temperature = msgT->vehicleBodyData()->temperature();
        st.bodys.waterTankLevel = msgT->vehicleBodyData()->waterTankLevel();
        st.bodys.frontAxleBrakePressure = msgT->vehicleBodyData()->frontAxleBrakePressure();
        st.bodys.rearAxleBrakePressure = msgT->vehicleBodyData()->rearAxleBrakePressure();

        st.bodys.gear = msgT->vehicleBodyData()->gear();//挡位 -1 R, 0 N, 1 D
        st.bodys.mode = msgT->vehicleBodyData()->mode();// 车辆驾驶状态 0x00手动/0x01自动
        st.bodys.bucketCtrl = msgT->vehicleBodyData()->bucketCtrl();//举升 0x00/0x01/0x02/0x03/0x04 下止点/上止点/下降/上升/保持
        st.bodys.tirePressureWarning = msgT->vehicleBodyData()->tirePressureWarning();//胎压故障告警 0 no error, >0 error
        st.bodys.exhaustBrake = msgT->vehicleBodyData()->exhaustBrake();//排气制动 11：正常开 01：短路

        st.bodys.parkingBrake = msgT->vehicleBodyData()->parkingBrake(); //停车制动 手制动电磁阀 0x01: open 0x00: close
        st.bodys.loadingBrake = msgT->vehicleBodyData()->loadingBrake(); //装载制动 0:解除 1:实施 FF:无效

        st.lights.emergencyFlash = msgT->vehicleLightsData()->emergencyFlash();//紧急双闪 00关/01开
        st.lights.left = msgT->vehicleLightsData()->left(); //左转灯isParking
        st.lights.right = msgT->vehicleLightsData()->right();//右转灯
        st.lights.lowBeam = msgT->vehicleLightsData()->lowBeam(); //近光灯
        st.lights.highBeam = msgT->vehicleLightsData()->highBeam();//远光灯
        st.lights.rotateAlarm = msgT->vehicleLightsData()->rotateAlarm();//旋转报警灯
        st.lights.airHorns = msgT->vehicleLightsData()->airHorns();  //气喇叭
        st.lights.frontFogLamp = msgT->vehicleLightsData()->frontFogLamp();//前雾灯
        st.lights.frontWorkLamp = msgT->vehicleLightsData()->frontWorkLamp();//前工作灯
        st.lights.sideLamp = msgT->vehicleLightsData()->sideLamp();//侧照灯
        st.lights.positoinLamp = msgT->vehicleLightsData()->positoinLamp();//位置灯

        qDebug() << "[recv] 车辆数据"<<"举升:" << st.bodys.bucketCtrl
                 <<"胎压:" << st.bodys.tirePressureWarning
                 <<"排气制动:" << st.bodys.exhaustBrake
                 <<"紧急双闪:" << st.lights.emergencyFlash
                 <<"车速:" << st.bodys.speed
                 <<"电池电量:" << st.bodys.batteryLevel
                 <<"电芯温度:" << st.bodys.cellTemperature
                 <<"油量:" << st.bodys.fuelLevel
                 <<"发动机油压:" << st.bodys.engineOilPressure
                 <<"发动机冷却液温度:" << st.bodys.engineCoolantTemperature
                 <<"冷却液液位:" << st.bodys.coolantLevel 
                 <<"排气口温度:" << st.bodys.exhaustPortEmperature
                 <<"前桥制动压力:" << st.bodys.frontAxleBrakePressure
                 <<"后桥制动压力:" << st.bodys.rearAxleBrakePressure
                 <<"发动机转速:" << st.bodys.engineSpeed
                 <<"挡位:" << st.bodys.gear
                 <<"车辆驾驶模式:" << st.bodys.mode
                 <<"停车制动:" << st.bodys.parkingBrake
                 <<"装载制动:" << st.bodys.loadingBrake
                 <<"左转灯:" << st.lights.left
                 <<"右转灯:" << st.lights.right
                 <<"近光灯:" << st.lights.lowBeam
                 <<"远光灯:" << st.lights.highBeam
                 <<"旋转报警灯:" << st.lights.rotateAlarm
                 <<"气喇叭:" << st.lights.airHorns
                 <<"前雾灯:" << st.lights.frontFogLamp
                 <<"前工作灯:" << st.lights.frontWorkLamp
                 <<"侧照灯:" << st.lights.sideLamp
                 <<"位置灯:" << st.lights.positoinLamp
                 <<"方向盘当前转角:" << st.bodys.steeringWheelAngle
                 <<"实际踩踏板:" << st.bodys.throttlePedal
                 <<"电制动踏板:" << st.bodys.brakePedal
                 <<"机械制动踏板:" << st.bodys.hydraulicBrake
                 <<"车辆类型:" << st.bodys.vehicleType;

        //发给车辆数据页面
        ModuleDir moduleDir;
        m_datas.clear();
        m_cmds.clear();

        moduleDir.clear();
        moduleDir.append(MD_VehicleData);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(VD_UpdateVehicleData);
        m_datas.append(QVariant::fromValue(st));

        //发给接管前车辆检查提示页面
        moduleDir.clear();
        moduleDir.append(MD_NotSatisfiedWithTakeover);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(NS_Update); //车辆不满足接管
        m_datas.append(QVariant::fromValue(st));

        //发给主摄像头页面
        moduleDir.clear();
        moduleDir.append(MD_MainCamera);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(MC_MainCamera_Vehicle_data);
        m_datas.append(QVariant::fromValue(st));
        break;
    }
    default:
        break;
    }
    return true;
#endif
}

//更新车道线
bool ZmqMsgPackage::g2uUpdateTrackLineConfig(const std::string &topic,const void *buf,int len)
{
    TrackLineMsg msg;
    std::memmove(&msg, buf, len);
    auto tmpMsg = TGMsg::GetMsgFrame(msg.body);

    qDebug()<< ZMQ_ADDR_Gateway<<"[recv]ZmqMsgPackage topic:" << topic.c_str();
    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Vehicle_TrackLineConfigMsg:{ // 收到摄像头的配置文件信息
        auto msgT = tmpMsg->msg_as_Vehicle_TrackLineConfigMsg();
        //配置文件信息
        TrackLineCalibrationST st;
        st.valid = true;
        st.counter = 0;
        st.mirrorBackCameraFlag =  msgT->mirrorBackCameraFlag();
        st.wheelMaxAngle = msgT->wheelMaxAngle();
        st.steerMaxAngle = msgT->steerMaxAngle();
        st.FovFrontCamera = msgT->FovFrontCamera();
        st.FovBackCamera = msgT->FovBackCamera();
        st.inclinationAngleFrontCamera = msgT->inclinationAngleFrontCamera();
        st.inclinationAngleBackCamera = msgT->inclinationAngleBackCamera();
        st.heightFrontCamera = msgT->heightFrontCamera();
        st.heightBackCamera = msgT->heightBackCamera();
        st.screenWidth = msgT->screenWidth();
        st.screenHeight = msgT->screenHeight();
        st.offsetFrontCamera = msgT->offsetFrontCamera();
        st.offsetBackCamera = msgT->offsetBackCamera();
        st.distanceFrontCamera2Axles = msgT->distanceFrontCamera2Axles();
        st.distanceBackCamera2Axles = msgT->distanceBackCamera2Axles();
        st.distanceAxles = msgT->distanceAxles();
        st.distanceFrontAxles = msgT->distanceFrontAxles();
        st.distanceBackAxles = msgT->distanceBackAxles();


        qDebug()<<"[recv]方向盘最大转角："<<st.steerMaxAngle
          <<"车轮最大转角："<<st.wheelMaxAngle
          <<"前摄像头垂直可视角度(度):"<<st.FovFrontCamera
          <<"后摄像头垂直可视角度(度):"<<st.FovBackCamera
          <<"前摄像头中心线同水平面的夹角(度):"<<st.inclinationAngleFrontCamera
          <<"后摄像头中心线同水平面的夹角(度):"<<st.inclinationAngleBackCamera
          <<"前摄像头距离地面距离:"<<st.heightFrontCamera
          <<"后摄像头距离地面距离:"<<st.heightBackCamera
          <<"屏幕分辨率横向方向:"<<st.screenWidth
          <<"屏幕分辨率纵向方向:"<<st.screenHeight
          <<"前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<st.offsetFrontCamera
          <<"后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<st.offsetBackCamera
          <<"车头摄像头到车前轮中心的距离:"<<st.distanceFrontCamera2Axles
          <<"车尾摄像头到车后轮中心的距离:"<<st.distanceBackCamera2Axles
          <<"车前后轮的轴距:"<<st.distanceAxles
          <<"前车轮轴长:"<<st.distanceFrontAxles
          <<"后车轮轴长:"<<st.distanceBackAxles;

        //发给车辆数据页面
        ModuleDir moduleDir;
        m_datas.clear();
        m_cmds.clear();
        moduleDir.clear();
        moduleDir.append(MD_MainCamera);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(MC_CameraCalibration);
        m_datas.append(QVariant::fromValue(st));
        break;
    }
    default:
        break;
    }
    return true;

}

bool ZmqMsgPackage::speedWarning(const string &topic, const void *buf, int len)
{
    RoadTaskInfo msg;
    std::memmove(&msg, buf, len);
    auto tmpMsg = TGMsg::GetMsgFrame(msg.body);
    qDebug()<< ZMQ_ADDR_Gateway<<"[recv]ZmqMsgPackage topic:" << topic.c_str()<<tmpMsg->msg_type();
    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Vehicle_ReportSpeedWarningMsg:{ // 收到车辆告警速度/强制降速
        auto msgT = tmpMsg->msg_as_Vehicle_ReportSpeedWarningMsg();


        qDebug()<<"[recv]车辆告警速度："<<msgT->speedWarningValue()
          <<"强制限速："<<msgT->speedReductionValue();

        System::getInstance()->reduceSpeed = msgT->speedReductionValue();
        System::getInstance()->warningSpeed = msgT->speedWarningValue();



        break;
    }
    default:
        break;
    }
    return true;
}

bool ZmqMsgPackage::updateCCUTaskStatus(const string &topic, const void *buf, int len)
{
    RoadTaskInfo msg;
    std::memmove(&msg, buf, len);
    auto tmpMsg = TGMsg::GetMsgFrame(msg.body);
    qDebug()<< ZMQ_ADDR_Gateway<<"[recv]ZmqMsgPackage topic:" << topic.c_str()<<tmpMsg->msg_type();
    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Vehicle_ReportRoadTaskInfo:{ // 收到车辆任务/装载状态
        auto msgT = tmpMsg->msg_as_Vehicle_ReportRoadTaskInfo();

        //配置文件信息
        ReportRoadTaskInfoST st;
        st.loadStatus = msgT->loadStatus();
        st.workStatus = msgT->workStatus();

        // --> BEGIN deleted by ZJZ, 2022/3/24
//        st.operType = msgT->operType();
        // <-- END


        qDebug()<<"[recv]车辆装载状态："<<st.loadStatus
          <<"任务状态："<<st.workStatus

        // --> BEGIN deleted by ZJZ, 2022/3/24
//            <<"工作状态:"<<st.operType;
            ;
        // <-- END

        //发给装载指令页面
        ModuleDir moduleDir;
        m_datas.clear();
        m_cmds.clear();
        moduleDir.clear();
        moduleDir.append(MD_LoadInstruction);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(LoadInstruction_Update);
        QVariant var;
        var.setValue(st);
        m_datas.append(var);


        //发给接管信息页
        moduleDir.clear();
        moduleDir.append(MD_TakeOverInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(TakeOver_UpdateLoadStatus);
        m_datas.append(QVariant::fromValue(st));

        if((st.workStatus>=2)&&(st.workStatus<=3))//道路预告，排队等待
        {
            if(System::getInstance()->getCurrentMsg()==MD_None)
            {
                //发给主摄像头提示页
                moduleDir.clear();
                moduleDir.append(MD_MainCameraTip);
                m_moduleDirs.append(moduleDir);
                QString tip;
                tip="未收到驶入停靠指令,请先排队等待!";
                m_cmds.append(MainCameraTip_Update);
                m_datas.append(QVariant::fromValue(tip));
            }
        }else
        {
            //隐藏摄像头提示页
            moduleDir.clear();
            moduleDir.append(MD_MainCameraTip);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MainCameraTip_Hide);
            m_datas.append(QVariant());

            //发送给装载指令
            moduleDir.clear();
            moduleDir.append(MD_LoadInstruction);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(LoadInstruction_Update);
//            m_datas.append(QVariant::fromValue(st));

//            var.setValue(st);
            m_datas.append(var);
        }

        break;
    }
    default:
        break;
    }
    return true;
}

bool ZmqMsgPackage::vehicleGps(const string &topic, const void *buf, int len)
{

    auto tmpMsg = TGMsg::GetMsgFrame(buf);
    auto s = flatbuffers::FlatBufferToString(static_cast<const uint8_t*>(buf), TGMsg::MsgFrameTypeTable(), false, false);
    qDebug() << ZMQ_ADDR_Gateway << "[recv]ZmqMsgPackage topic:" << topic.c_str() << "org data:" << s.c_str();
    switch (tmpMsg->msg_type()) {
    case TGMsg::MsgUnion_Vehicle_ReportGpsInfo:{ // 车辆位置信息
        auto msgT = tmpMsg->msg_as_Vehicle_ReportGpsInfo();

        GPSInfoST st;
//        st.gps_msec = msgT->gpsInfo()->gps;//UTC时间
        st.gps_rtk_status = msgT->gpsInfo()->gps_rtk_status();//差分状态
        st.gps_lat = msgT->gpsInfo()->gps_lat();//纬度
        st.gps_lng = msgT->gpsInfo()->gps_lng();//经度
        st.gps_heading = msgT->gpsInfo()->gps_heading();//航向角
        st.gps_ve = msgT->gpsInfo()->gps_ve();//东向速度
        st.gps_vn = msgT->gpsInfo()->gps_vn();//北向速度
        st.gps_speed = msgT->gpsInfo()->gps_speed();//合速度
        st.height = msgT->gpsInfo()->gps_height();//海拔
        st.acc_y = msgT->gpsInfo()->imu_acc_y();//纵向加速度
        st.acc_x = msgT->gpsInfo()->imu_acc_x();//横向加速度
        st.imu_yaw_z = msgT->gpsInfo()->imu_yaw_z();//横摆角速度
        st.gps_satellite_front = msgT->gpsInfo()->gps_satellite_front();//前天线卫星数
        st.gps_satellite_rear = msgT->gpsInfo()->gps_satellite_rear();//后天线卫星数
        st.gps_yaw = msgT->gpsInfo()->gps_yaw();//偏航
        st.gps_roll = msgT->gpsInfo()->gps_roll();//翻滚
        st.gps_pitch = msgT->gpsInfo()->gps_pitch();//俯仰
        st.gps_diff_flag = msgT->gpsInfo()->gps_diff_flag();//丢差分情况
        st.gnss_horizontal_speed = msgT->gpsInfo()->gnss_horizontal_speed();//bestvela输出的水平速度
        st.gps_ntime = msgT->gpsInfo()->gps_utc_time();//gps数据发布以来以系统时间基准的时间戳


        qDebug()<<"[recv]车辆位置信息，经度："<<st.gps_lng
          <<"纬度："<<st.gps_lat
         <<"高程:"<<st.height
          <<"航向角:"<<st.gps_heading
         <<"偏航yaw:"<<st.gps_yaw
        <<"横滚roll:"<<st.gps_roll
        <<"俯仰pitch:"<<st.gps_pitch;

        //发给主摄像头页面
        ModuleDir moduleDir;
        m_datas.clear();
        m_cmds.clear();
        moduleDir.clear();
        moduleDir.append(MD_MainCamera);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(MC_UpdatePosition);
        QVariant var;
        var.setValue(st);
        m_datas.append(var);
        break;
    }
    default:
        break;
    }
    return true;
}

bool ZmqMsgPackage::safeDeceleration(const string &topic, const void *buf, int len)
{
    uint8_t *p = (uint8_t*)(buf);
    qDebug() << ZMQ_ADDR_CONTROL << "[recv]ZmqMsgPackage topic:"
             << topic.c_str()<<"value:"<<*p;

    if(*p==0){
        //start speed down

//        SoundPlay::instance()->addSound(SOUND_LEVEL_TIP,"车速过快请减速.mp3");//车速过快，请减速

    }else if(*p==1){
        //stop speed down
//        SoundPlay::instance()->addSound(SOUND_LEVEL_TIP,"speed down finish");

        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_TaskWorkChange);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(TW_Show); // 任务变更
        m_datas.append("车辆严重超速,将自动降速,请保持低速行驶");
    }

    return true;
}

//车辆状态
bool  ZmqMsgPackage::g2uVehicleStatus(const std::string &topic, const void *data, int len)
{
    VehicleStatus vehicleStatus;
    std::memcpy(&vehicleStatus,data,len);

    qDebug()<< ZMQ_ADDR_Gateway<< "[recv]ZmqMsgPackage topic:" << topic.c_str()
            << "iemi:" << QLatin1String(reinterpret_cast<char*>(vehicleStatus.imei),IMEI_LENGTH)
            << "type:" << (int)vehicleStatus.type << "status:" << (int)vehicleStatus.status;

    System::getInstance()->setVehicleStatus(vehicleStatus.status);
#if 1
    //发给全局模式窗口
    ModuleDir moduleDir;
    moduleDir.append(MD_MainMonitor);

    m_moduleDirs.append(moduleDir);
    m_cmds.append(MM_VehicleStatus);
    m_datas.append(QVariant::fromValue(vehicleStatus));
#endif

    //网络中断
    if (VEHICLE_STATUS_CONNECTED == vehicleStatus.status) {
        //if (CM_WaitTakeover == System::getInstance()->getCurrentCabinMode()) {
            qDebug() << "network " << "hide NI widget";

            moduleDir.clear();
            moduleDir.append(MD_MainProcessor);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MP_SwitchLayout);
            int layoutMode = LT_RemoteControl;
            m_datas.append(QVariant::fromValue(layoutMode));

            QString str = "监控中";
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MC_UpdateState);
            m_datas.append(QVariant::fromValue(str));
            
            moduleDir.clear();
            moduleDir.append(MD_NetworkInterruption);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(NI_Hide);
            m_datas.append(QVariant::fromValue(vehicleStatus));
        //}
    } else if (VEHICLE_STATUS_DISCONNECTED == vehicleStatus.status) {
        if (System::getInstance()->getCurrentCabinMode() == CM_Takeover ||
            System::getInstance()->getCurrentCabinMode() == CM_WaitTakeover) {// 发给网络断开
            qDebug() << "network " << "show NI widget";
            moduleDir.clear();
            moduleDir.append(MD_NetworkInterruption);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(NI_Show);
            m_datas.append(QVariant::fromValue(vehicleStatus));

            //hide MD_MainCameraTip
            moduleDir.clear();
            moduleDir.append(MD_MainCameraTip);
            m_moduleDirs.append(moduleDir);
            QString tip;
            tip="未收到驶入停靠指令,请先排队等待!";
            m_cmds.append(MainCameraTip_Hide);
            m_datas.append(QVariant::fromValue(tip));
        }

        vehicleDataST st;
        std::memset(&st, 0x00, sizeof(vehicleDataST));
        moduleDir.clear();
        moduleDir.append(MD_VehicleData);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(VD_UpdateVehicleData);
        m_datas.append(QVariant::fromValue(st));
    }
    return true;
}

//延时
bool  ZmqMsgPackage::g2uVehicleDelay(const std::string &topic, const void *data, int)
{
    VehicleDelay* pVehicleDelay = (VehicleDelay*)(data);
    m_imei = QLatin1String(reinterpret_cast<char*>(pVehicleDelay->imei),IMEI_LENGTH);

    qDebug()<< ZMQ_ADDR_Gateway << "[recv]ZmqMsgPackage topic:" << topic.c_str() << "imei:" << m_imei
            << "delay:" << pVehicleDelay->delayUs/1000 << "ms";

    ModuleDir moduleDir;
    moduleDir.append(MD_MainCamera);
    uint delayMs = pVehicleDelay->delayUs/1000;

    m_moduleDirs.append(moduleDir);
    m_cmds.append(MC_VehicleDelay);
    m_datas.append(QVariant::fromValue(delayMs));

    return true;
}

//遥控返回结果
bool  ZmqMsgPackage::g2uRespRemotel(const std::string &topic, const void *data, int )
{
    RespRemoteControl *pRespRemoteControl = (RespRemoteControl*)data;
    m_imei = QLatin1String(reinterpret_cast<char*>(pRespRemoteControl->imei),IMEI_LENGTH);

    qDebug()<< ZMQ_ADDR_Gateway << "[recv]ZmqMsgPackage topic:" << topic.c_str() << "imei:" << m_imei
            << "result:" << (int)pRespRemoteControl->result << "taskid:" << pRespRemoteControl->taskId;

    ModuleDir moduleDir;
    moduleDir.append(MD_MainCamera);
    uint remoteResule = pRespRemoteControl->result;
    m_moduleDirs.append(moduleDir);
    m_cmds.append(MC_RemoteResule);
    m_datas.append(QVariant::fromValue(remoteResule));

    return true;
}

//进程间通信
bool  ZmqMsgPackage::u2uForward(const void *data, int)
{
    IpcForwardData *forward = (IpcForwardData*)data;
    QByteArray array(reinterpret_cast<char*>(forward->forwardData),forward->length);
    QDataStream in(array);
    QVariant varData;
    in >> varData;
    QList<QVariant> variantList;
    variantList.append(QVariant::fromValue(forward->moduleType));
    variantList.append(QVariant::fromValue(forward->cmd));
    variantList.append(varData);

    ModuleDir moduleDir;
    moduleDir.append(MD_MainProcessor);

    m_moduleDirs.append(moduleDir);
    m_cmds.append(MP_IpcForward);
    m_datas.append(variantList);

    return true;
}

#if 1
bool  ZmqMsgPackage::encodeIpcForward(QByteArray &dest, ModuleDir &moduleDir, int &cmd, QVariant &data)
{
    QByteArray array;
    QDataStream out(&array,QIODevice::ReadWrite);
    out << data;

    IpcForwardData  forwardptr;;

    forwardptr.moduleType = moduleDir.first();
    forwardptr.cmd = cmd;
    forwardptr.length = array.length();

    memset(forwardptr.forwardData,0,sizeof(forwardptr.forwardData));

    if(forwardptr.length>4096)
    {
        qCritical()<<"encodeIpcForward lenght error:"<<array.length();
        forwardptr.length=4096;
    }
    memcpy(forwardptr.forwardData,array.data(),forwardptr.length);

    dest = QByteArray(reinterpret_cast<char*>(&forwardptr),sizeof(forwardptr));

    return true;
}
#else
bool  ZmqMsgPackage::encodeIpcForward(QByteArray &dest, ModuleDir &moduleDir, int &cmd, QVariant &data)
{
    QByteArray array;
    QDataStream out(&array,QIODevice::ReadWrite);
    out << data;
    uint16_t len = sizeof(IpcForwardData) + sizeof(char) * array.length();

    auto  forwardptr = std::unique_ptr<IpcForwardData,void(*)(void*)>(static_cast<IpcForwardData*>(malloc(len)),free);

    forwardptr->moduleType = moduleDir.first();
    forwardptr->cmd = cmd;
    forwardptr->length = array.length();
    memcpy(forwardptr->forwardData,array.data(),forwardptr->length);

    dest = QByteArray(reinterpret_cast<char*>(forwardptr.get()),len);

    return true;
}
#endif

bool  ZmqMsgPackage::encodeReqRemote(QByteArray &dest, QString &imei,uint8_t cmd)
{
    ReqRemoteControl reqRemote = {{0x00},0x00};
    memcpy(reqRemote.imei,imei.toUtf8().data(),IMEI_LENGTH);
    reqRemote.opt = cmd;
    reqRemote.taskId = System::getInstance()->getCurrentTaskId();
    dest = QByteArray(reinterpret_cast<char*>(&reqRemote),sizeof(reqRemote));

    return true;
}

bool  ZmqMsgPackage::encodeReqSendHmiMsg(QByteArray &dest, QString &imei,QByteArray &data)
{
    HmiMsg reqHmiMsg = {{0x00},0x00,{0x00}};
    memcpy(reqHmiMsg.imei,imei.toUtf8().data(),IMEI_LENGTH);
    reqHmiMsg.bodyLen = data.size();
    memcpy(reqHmiMsg.body,data.constData(),reqHmiMsg.bodyLen);
    dest = QByteArray(reinterpret_cast<char*>(&reqHmiMsg),sizeof(HmiMsg));

    return true;
}

//控制数据ControlData
bool ZmqMsgPackage::controlMsgData(const std::string &topic,const void *buf,int len)
{
    auto tmpMsg = TGMsg::GetMsgFrame((uint8_t*)buf+4);
    auto s = flatbuffers::FlatBufferToString(static_cast<const uint8_t*>(buf)+4, TGMsg::MsgFrameTypeTable(), false, false);
    qDebug()<< ZMQ_ADDR_CONTROL <<"[recv]ZmqMsgPackage topic:" << topic.c_str()
            <<"org data:"<< s.c_str();

    auto msgT = tmpMsg->msg_as_Rcd_ControlData();
    auto cmdData = msgT->vehicleCmd();
    auto lightData = msgT->lightCmd();

    SelfTest_ControlData_St st;
    st.vehicleCmd.steeringWheelAngle = cmdData->steeringWheelAngle();
    st.vehicleCmd.throttlePedal = cmdData->throttlePedal();
    st.vehicleCmd.brakePedal = cmdData->brakePedal();
    st.vehicleCmd.hydraulicBrake = cmdData->hydraulicBrake();
    st.vehicleCmd.retarderCtrl = cmdData->retarderCtrl();
    st.vehicleCmd.exhaustBrake = cmdData->exhuastBrake();
    st.vehicleCmd.parkCtrl = cmdData->parkCtrl();
    st.vehicleCmd.bucketCtrl = cmdData->bucketCtrl();
    st.vehicleCmd.shiftCtrl = cmdData->shiftCtrl();
    st.vehicleCmd.eStop = cmdData->eStop();
    st.vehicleCmd.loadingCtrl = cmdData->loadingCtrl();

    ModuleDir moduleDir;
    m_datas.clear();
    m_cmds.clear();

    if(false == System::getInstance()->showSelfTestWnd){
        if(cmdData->eStop()){//急停控制.true:急停按下;false:急停复位
            if(System::getInstance()->getCurrentCabinMode()==CM_Monitor){
                System::getInstance()->setShowEmergency(true);//show the window for emergency button pressed
            }else{
                System::getInstance()->setShowEmergency(false);//send emergency msg
            }
        }else{
            System::getInstance()->setShowEmergency(false);
        }

#if 0
        //if((cmdData->brakePedal()>5000)       // 电制动
        if((cmdData->hydraulicBrake() > 5000) &&    // 机械制动
           (System::getInstance()->getCurrentCabinMode() == CM_WaitTakeover) &&//监控中
           (System::getInstance()->getCurrentMsg() != MD_NetworkInterruption))//fast stop && task=监控行驶
        {//xuzhk
            moduleDir.clear();
            moduleDir.append(MD_FastStop);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(FastStop_Show);
            m_datas.append(QVariant());
        }
#endif
        return true;
    }else{
        st.lightCmd.left = lightData->left();
        st.lightCmd.right = lightData->right();
        st.lightCmd.lowBeam = lightData->lowBeam();
        st.lightCmd.highBeam = lightData->heighBeam();
        st.lightCmd.rotateAlarm = lightData->rotatingWarningLight();
        st.lightCmd.airHorns = lightData->speaker();
        st.lightCmd.frontFogLamp = lightData->frontFog();
        st.lightCmd.frontWorkLamp = lightData->frontStatus();
        st.lightCmd.sideLamp = lightData->side();
        st.lightCmd.positoinLamp = lightData->rearPosition();
        st.lightCmd.emergencyFlash = lightData->emergency();
        st.lightCmd.brake = lightData->brake();
        st.lightCmd.back = lightData->back();
        st.lightCmd.rearStatus = lightData->rearStatus();

        moduleDir.clear();
        moduleDir.append(MD_SelfTest);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(selfTest_Update);
        m_datas.append(QVariant::fromValue(st));
    }

//    if(System::getInstance()->getShowEmergency())
//    {
//        //show提示窗
//        moduleDir.clear();
//        moduleDir.append(MD_MainMonitor);
//        m_moduleDirs.append(moduleDir);
//        m_cmds.append(MM_ShowEmergency);
//        m_datas.append(QVariant(true));
//    }else
//    {
//        //关闭提示窗
//        moduleDir.clear();
//        moduleDir.append(MD_MainMonitor);
//        m_moduleDirs.append(moduleDir);
//        m_cmds.append(MM_ShowEmergency);
//        m_datas.append(QVariant(false));
//    }

    return true;
}

bool ZmqMsgPackage::hmiHintMsgData(const string &topic, const void *buf, int len)
{
    HmiHintMsg msg;
    std::memmove(&msg, buf, len);
    auto tmpMsg = TGMsg::GetMsgFrame(msg.body);
    auto msgT = tmpMsg->msg_as_Vehicle_ReportHmiHintMsg();

    std::string s(reinterpret_cast<const char *>(msgT->msg()->Data()), msgT->msg()->size());


    qDebug()<< ZMQ_ADDR_Gateway <<"[recv]ZmqMsgPackage topic:" << topic.c_str() <<"org data:"<< s.c_str();
    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Vehicle_ReportHmiHintMsg:
    {
        QString tmpStr = QString(s.c_str());

        //发给系统信息页面
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_SystemInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(IF_InsertMsg);
        m_datas.append(QVariant::fromValue(tmpStr));

        if(tmpStr.contains("[故障]") || tmpStr.right(3)=="已消除")
        {//发给故障信息页面
            moduleDir.clear();
            moduleDir.append(MD_FaultInfo);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(IF_InsertMsg);
            m_datas.append(QVariant::fromValue(tmpStr));
        }
        break;
    }
    default:
        break;
    }
    return  true;
}

//云平台数据解析 //rcd 数据
bool ZmqMsgPackage::cloudMsgData(const std::string &topic,const /*uint8_t*/void *buf,int len )
{
    auto tmpMsg = TGMsg::GetMsgFrame(buf);
    auto s = flatbuffers::FlatBufferToString(static_cast<const uint8_t*>(buf), TGMsg::MsgFrameTypeTable(), false, false);
    qDebug()<< ZMQ_ADDR_CLOUDSERVER << "[recv]ZmqMsgPackage topic:" << topic.c_str() << "org data:" <<s.c_str();

    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Platform_FastStopResponse:{//平台下发快速停车结果

        auto msgT = tmpMsg->msg_as_Platform_FastStopResponse();
        QString tmpStr;
        if(msgT->result()==CommonResult::CommonResult_Success)
        {
            tmpStr = "[RCD]平台下发快速停车成功";
        }else
        {
            tmpStr = "[RCD]平台下发快速停车失败";
        }


        //发给系统信息页面,更新快速停车的结果
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_SystemInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(IF_InsertMsg);
        m_datas.append(QVariant::fromValue(tmpStr));

        break;
    }
    case TGMsg::MsgUnion_Platform_TruckOnlineInfo:{
        //车辆在线状态
        auto msgT = tmpMsg->msg_as_Platform_TruckOnlineInfo();

        auto imeiList = msgT->imei();
        if(imeiList == nullptr)
            break;
        System::getInstance()->onlineVehicle.clear();
        for(flatbuffers::uoffset_t i = 0; i < imeiList->size();i++)
        {
            System::getInstance()->onlineVehicle.insert(QString(imeiList->Get(i)->c_str()));
        }
        //更新在线状态
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_MainMonitor);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(MM_UpdateOnlineState);
        m_datas.append(QVariant());
        break;
    }
    case TGMsg::MsgUnion_Platform_CabinTakeoverTaskApply://坐舱接收到平台下发的接管任务
    {
        auto msgT = tmpMsg->msg_as_Platform_CabinTakeoverTaskApply();

        //解析数据
        cabinTakeoverTaskApplyST st;
        st.taskId = msgT->taskId();
        st.truckImei = QString(msgT->truckImei()->str().c_str());
        st.truckName = QString(msgT->truckName()->str().c_str());

        // ---> START BAIYUN 2022/08/02
        vehicleName = st.truckName;
        // <--- END

        st.truckIp = QString(msgT->truckIp()->str().c_str());
        st.secretKey = QString(msgT->secretKey()->str().c_str());
        st.takeoverPurpose = msgT->takeoverPurpose();

        st.dispatchTask.taskId = msgT->dispatchTask()->taskId();
        st.dispatchTask.targetName = QString(msgT->dispatchTask()->targetName()->str().c_str());
        st.dispatchTask.fileUrl = QString(msgT->dispatchTask()->fileUrl()->str().c_str());
        st.dispatchTask.fileMd5 = QString(msgT->dispatchTask()->fileMd5()->str().c_str());

        qDebug()<<"[recv]平台下发接管任务taskId:"<<st.taskId<<"imei:"<<st.truckImei<<"Name:"<<st.truckName
               <<"ip:"<<st.truckIp<<"secretKey:"<<st.secretKey<<"purpose:"<<st.takeoverPurpose
              <<"dispacth.taskId:"<<st.dispatchTask.taskId<<"dispatch.name:"<<st.dispatchTask.targetName
             <<"dispatch.url:"<<st.dispatchTask.fileUrl<<"dispatch.md5:"<<st.dispatchTask.fileMd5;

        //急停未复位 -> 向平台反馈拒绝信息
        if(System::getInstance()->getShowEmergency()) {
            QVariantList data;
            data.clear();

            // --> BEGIN modify by ZJZ, 2022/3/22
//            data<<st.taskId<<0<<QString("carbin emergency button not reset");
            data << st.taskId << 0 << QString("急停未复位");
            // <-- END

            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_IPCManager);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(IM_Cloud_Reply_Task);
            m_datas.append(QVariant::fromValue(data));
            qDebug()<<"舱向平台发送拒绝任务";
            break;
        }

        //未找到imei号 -> 向平台反馈拒绝信息
        if(!System::getInstance()->getCurrentImeiList().contains(st.truckImei)) {
            QString strReason = QString("请在本地配置文件rcdconfig.json中添加车辆：");
            strReason.append(st.truckImei);
            QVariantList data;
            data.clear();
            data<<st.taskId<<0<<strReason;//imei is not recgonized

            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_IPCManager);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(IM_Cloud_Reply_Task);
            m_datas.append(QVariant::fromValue(data));
            qDebug()<<"舱向平台发送拒绝任务";
            break;
        }

        System::getInstance()->setCurrentVehicle(st.truckImei);
        System::getInstance()->setCurrentTaskId(st.taskId);
        System::getInstance()->setVehicleTakeoverPurpose(st.takeoverPurpose);

        //发给接管信息页
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_TakeOverInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(TakeOver_UpdateTask);
        m_datas.append(QVariant::fromValue(st));

        //判断司机是否登录
        if(!System::getInstance()->getCurrentDriverLoginStatus().simplified().isEmpty()){//已登陆
            System::getInstance()->currentTakeoverPurpose =  st.takeoverPurpose;

            //关闭全局模式的提示窗
            moduleDir.clear();
            moduleDir.append(MD_MainMonitor);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MM_CloseTip);
            m_datas.append(QVariant());

            //切换到单车模式
            moduleDir.clear();
            moduleDir.append(MD_MainProcessor);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MP_SwitchLayout);
            m_datas.append(LT_RemoteControl);

            //发给接受新任务提示
            moduleDir.clear();
            moduleDir.append(MD_AcceptTaskWork);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(AT_NewTask);
            m_datas.append(QVariant::fromValue(st));

//            System::getInstance()->setCurrentCabinMode(CM_WaitTask);

            // ---> START BAIYUN 2022/08/02
            readTrackLineCfgFile(vehicleName);

            //发给车辆数据页面
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MC_CameraCalibration);
            m_datas.append(QVariant::fromValue(m_TrackLineCfg));
            // <--- END
        }else{//未登陆
            //向平台反馈拒绝信息
            QVariantList data;
            data.clear();
            data<<st.taskId<<0<<QString("用户未登录");// user is not login

            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_IPCManager);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(IM_Cloud_Reply_Task);
            m_datas.append(QVariant::fromValue(data));
            qDebug()<<"舱向平台发送拒绝任务";
        }

#if 0//zjz test fault
        QString tmpStr = "15:20:39  [故障]燃油油位低告警";
        moduleDir.clear();
        moduleDir.append(MD_FaultInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(IF_InsertMsg);
        m_datas.append(QVariant::fromValue(tmpStr));

        tmpStr = "15:20:40  燃油油位低告警已消除";
        moduleDir.clear();
        moduleDir.append(MD_FaultInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(IF_InsertMsg);
        m_datas.append(QVariant::fromValue(tmpStr));

        tmpStr = "15:20:39  [故障]燃油油位低告警";
        moduleDir.clear();
        moduleDir.append(MD_FaultInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(IF_InsertMsg);
        m_datas.append(QVariant::fromValue(tmpStr));

        tmpStr = "15:20:39  平台连接信号质量差";
        moduleDir.clear();
        moduleDir.append(MD_SystemInfo);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(IF_InsertMsg);
        m_datas.append(QVariant::fromValue(tmpStr));
#endif
        break;
    }
    case TGMsg::MsgUnion_Platform_CabinTakeoverTargeChange:{ // 目的变更

        auto msgT = tmpMsg->msg_as_Platform_CabinTakeoverTargeChange();
        dispatchTaskST st;
        st.taskId = msgT->dispatchTask()->taskId();
        st.fileMd5 = QString(msgT->dispatchTask()->fileMd5()->str().c_str());
        st.fileUrl = QString(msgT->dispatchTask()->fileUrl()->str().c_str());
        st.targetName = QString(msgT->dispatchTask()->targetName()->c_str()); //调度目标

        qDebug()<<"[recv]平台下发变更派遣dispacth.taskId:"<<st.taskId<<"dispatch.name:"<<st.targetName
             <<"dispatch.url:"<<st.fileUrl<<"dispatch.md5:"<<st.fileMd5;

//        System::getInstance()->setCurrentTaskId(st.taskId);
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_TaskWorkChange);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(TW_Show); // 任务变更
        m_datas.append("请注意！接管目标已变更！");
        if(st.taskId==0)
        {
            moduleDir.clear();
            moduleDir.append(MD_TakeOverInfo);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(TakeOver_UpdateDispatchTask); // 清空调度目标
            m_datas.append("无");
        }else
        {
            moduleDir.clear();
            moduleDir.append(MD_TakeOverInfo);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(TakeOver_UpdateDispatchTask); // 清空调度目标
            m_datas.append(st.targetName);
        }

        break;
    }
    case TGMsg::MsgUnion_Platform_DriverLoginResult:{
        //驾驶舱登录结果
        auto msgT = tmpMsg->msg_as_Platform_DriverLoginResult();

        qDebug()<<"[recv]司机登陆:"<<msgT->driverName()->c_str()
                  <<"result:"<<(int)msgT->result();

        if(msgT->result() == CommonResult::CommonResult_Success){
            System::getInstance()->setCurrentDriverLogin(msgT->driverName()->c_str());
            //发给全局模式窗口
            ModuleDir moduleDir;

            //发送给全局模式窗口
            moduleDir.append(MD_MainMonitor);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MM_UpdateLoginStatus);
            m_datas.append(QVariant());

            //发送给单车模式窗口
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MC_UpdateLoginStatus);
            m_datas.append(QVariant());
        }

        break;
    }
    case TGMsg::MsgUnion_Platform_DriverLogoutResult:{//驾驶舱司机登出
        auto msgT = tmpMsg->msg_as_Platform_DriverLogoutResult();
        qDebug()<<"[recv]司机登出result:"<<(int)msgT->result();
        if(msgT->result() == CommonResult::CommonResult_Success){
            System::getInstance()->setCurrentDriverLogin("");
            ModuleDir moduleDir;
            //发送给全局模式窗口
            moduleDir.append(MD_MainMonitor);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MM_UpdateLoginStatus);
            m_datas.append(QVariant());

            //发送给单车模式窗口
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(MC_UpdateLoginStatus);
            m_datas.append(QVariant());
        }
        break;
    }
    case TGMsg::MsgUnion_Platform_TakeoverTaskCancel:{//平台取消任务
        auto msgT = tmpMsg->msg_as_Platform_TakeoverTaskCancel();

        qDebug()<<"[recv]平台取消任务taskid:"<<(int)msgT->taskId();

        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        //切换到监控模式
        ModuleDir moduleDir;
        moduleDir.append(MD_MainProcessor);
        m_moduleDirs.append(moduleDir);
        m_cmds.append(MP_SwitchLayout);
        m_datas.append(LT_Monitor);

        //TODO: 发送taskCancel topic

        break;
    }
    default:
        break;
    }
    return  true;
}

// ---> START BAIYUN 2022/08/02
void ZmqMsgPackage::readTrackLineCfgFile(QString name){
    //get current vehicle name
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return;
    }

    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    vehicleName = mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString();
    QString curVehicleFile = vehicleName + "_trackline_config.txt";
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
    m_TrackLineCfg.valid = true;
    m_TrackLineCfg.counter = 0;
    m_TrackLineCfg.mirrorBackCameraFlag =  config_parser_ptr_->getBool("mirrorBackCameraFlag");
    m_TrackLineCfg.wheelMaxAngle = config_parser_ptr_->getDouble("wheelMaxAngle");
    m_TrackLineCfg.steerMaxAngle = config_parser_ptr_->getDouble("steerMaxAngle");
    m_TrackLineCfg.FovFrontCamera = config_parser_ptr_->getDouble("FovFrontCamera");
    m_TrackLineCfg.FovBackCamera = config_parser_ptr_->getDouble("FovBackCamera");
    m_TrackLineCfg.inclinationAngleFrontCamera = config_parser_ptr_->getDouble("inclinationAngleFrontCamera");
    m_TrackLineCfg.inclinationAngleBackCamera = config_parser_ptr_->getDouble("inclinationAngleBackCamera");
    m_TrackLineCfg.heightFrontCamera = config_parser_ptr_->getDouble("heightFrontCamera");
    m_TrackLineCfg.heightBackCamera = config_parser_ptr_->getDouble("heightBackCamera");
    m_TrackLineCfg.screenWidth = config_parser_ptr_->getDouble("screenWidth");
    m_TrackLineCfg.screenHeight = config_parser_ptr_->getDouble("screenHeight");
    m_TrackLineCfg.offsetFrontCamera = config_parser_ptr_->getDouble("offsetFrontCamera");
    m_TrackLineCfg.offsetBackCamera = config_parser_ptr_->getDouble("offsetBackCamera");
    m_TrackLineCfg.distanceFrontCamera2Axles = config_parser_ptr_->getDouble("distanceFrontCamera2Axles");
    m_TrackLineCfg.distanceBackCamera2Axles = config_parser_ptr_->getDouble("distanceBackCamera2Axles");
    m_TrackLineCfg.distanceAxles = config_parser_ptr_->getDouble("distanceAxles");
    m_TrackLineCfg.distanceFrontAxles = config_parser_ptr_->getDouble("distanceFrontAxles");
    m_TrackLineCfg.distanceBackAxles = config_parser_ptr_->getDouble("distanceBackAxles");

    qDebug()<<"[recv]是否开启了后置摄像头镜像："<<m_TrackLineCfg.mirrorBackCameraFlag
              << "方向盘最大转角："<<m_TrackLineCfg.steerMaxAngle
              <<"车轮最大转角："<<m_TrackLineCfg.wheelMaxAngle
              <<"前摄像头垂直可视角度(度):"<<m_TrackLineCfg.FovFrontCamera
              <<"后摄像头垂直可视角度(度):"<<m_TrackLineCfg.FovBackCamera
              <<"前摄像头中心线同水平面的夹角(度):"<<m_TrackLineCfg.inclinationAngleFrontCamera
              <<"后摄像头中心线同水平面的夹角(度):"<<m_TrackLineCfg.inclinationAngleBackCamera
              <<"前摄像头距离地面距离:"<<m_TrackLineCfg.heightFrontCamera
              <<"后摄像头距离地面距离:"<<m_TrackLineCfg.heightBackCamera
              <<"屏幕分辨率横向方向:"<<m_TrackLineCfg.screenWidth
              <<"屏幕分辨率纵向方向:"<<m_TrackLineCfg.screenHeight
              <<"前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<m_TrackLineCfg.offsetFrontCamera
              <<"后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<m_TrackLineCfg.offsetBackCamera
              <<"车头摄像头到车前轮中心的距离:"<<m_TrackLineCfg.distanceFrontCamera2Axles
              <<"车尾摄像头到车后轮中心的距离:"<<m_TrackLineCfg.distanceBackCamera2Axles
              <<"车前后轮的轴距:"<<m_TrackLineCfg.distanceAxles
              <<"前车轮轴长:"<<m_TrackLineCfg.distanceFrontAxles
              <<"后车轮轴长:"<<m_TrackLineCfg.distanceBackAxles;

//    m_pModel->m_TrackLineCfg = data.value<TrackLineCalibrationST>();
}
// <--- END

bool ZmqMsgPackage::mapData(const QList<QVariant> &data)
{
    ModuleDir moduleDir;
    moduleDir.append(MD_VehicleInfo);

    m_moduleDirs.append(moduleDir);
    m_cmds.append(VI_Map);
    m_datas.append(data);
    //     qDebug()<<"--------------------"<<data;
    return true;
}

//舱端状态自检
bool ZmqMsgPackage::selfCheckStatus(const std::string &topic, const void *data, int len)
{
    SelfCheckStatusST selfdata;
    memcpy(&selfdata,data,sizeof(selfdata));
    _selfdata = selfdata;
    m_moduleDirs.clear();
    m_cmds.clear();
    m_datas.clear();

    qDebug() << ZMQ_ADDR_CONTROL << "[recv]ZmqMsgPackage topic:"
             << topic.c_str()<<"isParking:"<<selfdata.isParking
                <<"isNoPedal:"<<selfdata.isNoPedal
                  <<"isCenterSteeringWheel:"<<selfdata.isCenterSteeringWheel
                    <<"isButtonReset:"<<selfdata.isButtonReset;

    ModuleDir moduleDir;
    moduleDir.append(MD_CompleteOperEnd);
    m_moduleDirs.append(moduleDir);
    m_cmds.append(COE_Update);// 结束接管
    m_datas.append(QVariant::fromValue(selfdata));

    moduleDir.clear();
    moduleDir.append(MD_CompleteOperStart);
    m_moduleDirs.append(moduleDir);
    m_cmds.append(COS_Update);// 开始接管
    m_datas.append(QVariant::fromValue(selfdata));

    moduleDir.clear();
    moduleDir.append(MD_NetworkInterruption);
    m_moduleDirs.append(moduleDir);
    m_cmds.append(NI_Update);//网络中断
    m_datas.append(QVariant::fromValue(selfdata));
    return true;
}

// --> BEGIN modify by ZJZ, 2022/3/3
//网络状态
bool ZmqMsgPackage::devlinkStatus(const std::string &topic,const void *data, int len)
{

//    qDebug() << ZMQ_ADDR_CONTROL << "[recv]ZmqMsgPackage topic:"
//             << topic.c_str()<<"softKey:"<<static_cast<Qt::Key>(pKey->key);

//    ModuleDir moduleDir;
//    ControlDevLinkStatus pDate ;
//    std::memmove(&pDate,data,len);
//    if(pDate.vehicle == 0x01){

//        if(System::getInstance()->getCurrentCabinMode()==CM_Takeover){
//            //发给网络断开
//            moduleDir.clear();
//            moduleDir.append(MD_NetworkInterruption);
//            m_moduleDirs.append(moduleDir);
//            m_cmds.append(NI_Hide);
//            m_datas.append(QVariant::fromValue(_selfdata));
//        }
//    }
//    else {
//        if(System::getInstance()->getCurrentCabinMode()==CM_Takeover){

//            //发给网络断开
//            moduleDir.clear();
//            moduleDir.append(MD_NetworkInterruption);
//            m_moduleDirs.append(moduleDir);
//            m_cmds.append(NI_Show);
//            m_datas.append(QVariant::fromValue(_selfdata));

////            qDebug()<<&_selfdata
////                   <<"网络状态：" <<pDate.vehicle
////                  <<"档位P档："<<_selfdata.isParking
////                 <<"踏板无踩压："<<_selfdata.isNoPedal
////                <<"方向盘回正："<<_selfdata.isCenterSteeringWheel
////               <<"按钮复位："<<_selfdata.isButtonReset<<"^^^^^^^^^^^^^^^^^^";
//        }

//    }

    // --> BEGIN add code
    // get data
    ControlDevLinkStatus st_DevLinkStatus;
    std::memcpy(&st_DevLinkStatus, data, len);

    // write log
    qDebug() << ZMQ_ADDR_CONTROL << "[recv]ZmqMsgPackage topic:" << topic.c_str()
             << "wheel:" << (int)st_DevLinkStatus.wheel
             << "io:" << (int)st_DevLinkStatus.io
             << "vehicle:" << (int)st_DevLinkStatus.vehicle;
/*
    // popup tips window if the device is disconnected
    if (System::getInstance()->getCurrentCabinMode() != CM_Monitor) {
        if (st_DevLinkStatus.wheel != 0x02 || st_DevLinkStatus.io != 0x02) {
            popContent st;
            st.firstPriority = 1;
            st.secondPriority = 0;
            st.cmd = TipsPopupLBtnCmd_DevLink;
            st.delay = 3000;
            st.content = "座舱控制单元掉线！即将结束任务，请复位座舱。";
            st.btnText = "";

            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_TipsPopup);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(TP_Show);
            m_datas.append(QVariant::fromValue(st));
        }
    }
    // <-- END
*/
    return true;
}
