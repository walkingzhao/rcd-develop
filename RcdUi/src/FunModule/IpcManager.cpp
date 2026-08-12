#include "IpcManager.h"
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QTimer>
#include <cstdlib>
#include "../Protocol/ZmqMsgPackage.h"
#include "../Protocol/HmiCmdPackage.h"
#include <QThread>
#include <QMetaObject>
#include <mutex>
#include <thread>
#include <chrono>
#include "public/jsonMethord.h"

IpcManager* IpcManager::s_pInstance = nullptr;
IpcManager::IpcManager(QObject *parent) : IController(parent),
    m_pSubControl(nullptr),m_pSubGateway(nullptr),m_pPubUI(nullptr),
    m_pPubUIL(nullptr),m_pPubUIR(nullptr),m_pPubUIM(nullptr),
    m_pSubUIL(nullptr),m_pSubUIR(nullptr),m_pSubUIM(nullptr)
{
    /********************测试新版本zmq数据接口**********************/
    //    connect(initInstance(),SIGNAL(signalSubTopicData(const void*,int,const uint32_t & )),
    //            this,SLOT(slotTestZmq(const void*,int,const uint32_t &)));
    /******************************************************************/

    // show version
    //qDebug() << "rcdversion:" << DCU_VERSION;
    QString strVer = QString("rcdversion:V%1.%2.%3.%4.%5.%6"). \
            arg(PRODUCT_TYPE).arg(VEHICLE_TYPE).arg(MODULE_TYPE).arg(DCU_MAIN_VER).arg(DCU_SUB_VER).arg(DCU_CHANGE_FLAG);
    qDebug() << strVer;

    int procType = System::getInstance()->getProcessType();

    // 与外设进程，网关进程通讯配置部分
    m_pSubControl = new ZmqSubscriber();
    m_pSubControl->ConnectTo(ZMQ_ADDR_CONTROL);// control
    m_pSubControl->Subscribe(ZMQ_TOPIC_BUTTON, IpcManager::ctrlButtonHandler); // control 舱端按键

    if(procType & PT_MidProc){
        m_pSubControl->Subscribe(ZMQ_TOPIC_CONTROL_RAW_DATA, IpcManager::ctrlRawDataHandler);//wheel data
        m_pSubControl->Subscribe(ZMQ_TOPIC_CONTROL_DATA,IpcManager::ctrlDataHandler);////接收舱端控制数据 ControlData


        m_pSubControl->Subscribe(ZMQ_TOPIC_SELF_CHECK_STATUS,IpcManager::controlSelfCheckStatus);//自检舱端状态

        // --> BEGIN added by ZJZ, 2022/3/3
        m_pSubControl->Subscribe(ZMQ_TOPIC_CONTROL_DEVLINKSTATUS, IpcManager::controlDevlinkStatus);//车辆状态
        // <-- END

        m_pSubCloudServer = new ZmqSubscriber();
        m_pSubCloudServer->ConnectTo(ZMQ_ADDR_CLOUDSERVER);
        m_pSubCloudServer->Subscribe(ZMQ_TOPIC_CLOUD_FBS_MSG, IpcManager::CloudData);//云端数据

        m_pSubGateway = new ZmqSubscriber();
        m_pSubGateway->ConnectTo(ZMQ_ADDR_Gateway);
        m_pSubGateway->Subscribe(ZMQ_TOPIC_VEHICLE_RAWDATA, IpcManager::vehicleRawDataHandler);// 车辆数据
        m_pSubGateway->Subscribe(ZMQ_TOPIC_VEHICLE_STATUS, IpcManager::vehicleStatusHandler);//监控
        m_pSubGateway->Subscribe(ZMA_TOPIC_VEHICLE_DELAY, IpcManager::vehicleDelayHandler);//延时
        m_pSubGateway->Subscribe(ZMQ_TOPIC_RESP_REMOTE_CONTROL, IpcManager::respRemotelHandler);// 远程控制回复
        m_pSubGateway->Subscribe(ZMQ_TOPIC_REPORT_HMI_HINT_MSG, IpcManager::respHmiHintmsgHandler);//HMI提示信息
        // ---> START BAIYUN 2022/08/02
//        m_pSubGateway->Subscribe(ZMQ_TOPIC_REPORT_TRACK_LINE_MSG, IpcManager::updateTrackLineConfigHandler);//车道线标定的配置信息
        // <--- END
        m_pSubGateway->Subscribe(ZMQ_TOPIC_REPORT_ROAD_TASK_INFO, IpcManager::updateCCUTaskStatusHandler);//CCU任务状态
        m_pSubGateway->Subscribe(ZMQ_TOPIC_REPORT_GPS_DATA, IpcManager::vehicleGpsHandler);//车辆位置
        m_pSubGateway->Subscribe(ZMQ_TOPIC_SAFE_DECELERATION, IpcManager::safeDecelerationHandler);//车辆自减速
        m_pSubGateway->Subscribe(ZMQ_TOPIC_REPORT_SPEED_WARNING_MSG, IpcManager::speedWarningHandler);//车辆速度报警

        m_pPubUI =  new ZmqPublisher(ZMQ_ADDR_UI);
        modeTimer  = new QTimer(this);
        connect(modeTimer,SIGNAL(timeout()),this,SLOT(modeTimeOut()));
        modeTimer->start(100);
    }
    // 与各个屏幕进程通讯配置部分
    if(procType == PT_MidProc){
        m_pSubUIL = new ZmqSubscriber();
        m_pSubUIL->ConnectTo(ZMQ_ADDR_UI_L);
        m_pSubUIL->Subscribe(ZMQ_TOPIC_PROC_MID, IpcManager::forwardHandler);

        m_pSubUIR = new ZmqSubscriber();
        m_pSubUIR->ConnectTo(ZMQ_ADDR_UI_R);
        m_pSubUIR->Subscribe(ZMQ_TOPIC_PROC_MID, IpcManager::forwardHandler);

        m_pPubUIM = new ZmqPublisher(ZMQ_ADDR_UI_M);
    }else if(procType == PT_RightProc){
        m_pSubUIL = new ZmqSubscriber();
        m_pSubUIL->ConnectTo(ZMQ_ADDR_UI_L);
        m_pSubUIL->Subscribe(ZMQ_TOPIC_PROC_RIGHT, IpcManager::forwardHandler);

        m_pSubUIM = new ZmqSubscriber();
        m_pSubUIM->ConnectTo(ZMQ_ADDR_UI_M);
        m_pSubUIM->Subscribe(ZMQ_TOPIC_PROC_RIGHT, IpcManager::forwardHandler);

        m_pPubUIR = new ZmqPublisher(ZMQ_ADDR_UI_R);
    }else if(procType == PT_LeftProc){
        m_pSubUIM = new ZmqSubscriber();
        m_pSubUIM->ConnectTo(ZMQ_ADDR_UI_M);
        m_pSubUIM->Subscribe(ZMQ_TOPIC_PROC_LEFT, IpcManager::forwardHandler);

        m_pSubUIR = new ZmqSubscriber();
        m_pSubUIR->ConnectTo(ZMQ_ADDR_UI_R);
        m_pSubUIR->Subscribe(ZMQ_TOPIC_PROC_LEFT, IpcManager::forwardHandler);

        m_pPubUIL = new ZmqPublisher(ZMQ_ADDR_UI_L);
    }

}

IpcManager::~IpcManager()
{
    // 必须先析构所有 ZmqSubscriber，否则 recv 线程一直阻塞在 zmq_msg_recv，
    // 进程主线程会在这些线程的 pthread_join 上 futex_wait 永久不返回 —— 现象就是 a.exec() 已返回但 ps 里一直还在。
    if(m_pSubControl != nullptr) {
        delete m_pSubControl; m_pSubControl = nullptr;
    }
    if(m_pSubGateway != nullptr) {
        delete m_pSubGateway; m_pSubGateway = nullptr;
    }
    if(m_pSubCloudServer != nullptr) {
        delete m_pSubCloudServer; m_pSubCloudServer = nullptr;
    }
    if(m_pSubUIL != nullptr) {
        delete m_pSubUIL; m_pSubUIL = nullptr;
    }
    if(m_pSubUIM != nullptr) {
        delete m_pSubUIM; m_pSubUIM = nullptr;
    }
    if(m_pSubUIR != nullptr) {
        delete m_pSubUIR; m_pSubUIR = nullptr;
    }
    if(m_pPubUI != nullptr) {
        delete m_pPubUI; m_pPubUI = nullptr;
    }
    if(m_pPubUIL != nullptr) {
        delete m_pPubUIL; m_pPubUIL = nullptr;
    }
    if(m_pPubUIR != nullptr) {
        delete m_pPubUIR; m_pPubUIR = nullptr;
    }
    if(m_pPubUIM != nullptr) {
        delete m_pPubUIM; m_pPubUIM = nullptr;
    }
    s_pInstance = nullptr;
}

IpcManager *IpcManager::GetInstance(QObject *parent)
{
    if(s_pInstance == nullptr) {
        s_pInstance = new IpcManager(parent);
    }
    return s_pInstance;
}

void IpcManager::ctrlDataHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.controlMsgData(topic,data,len)){
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

//车辆在线状态
void IpcManager::controlDevlinkStatus(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.devlinkStatus(topic,data,len)){
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

void IpcManager::ctrlStatusHandler(const std::string &topic, const void *data, int len)
{
    QString qtopic(QString::fromStdString(topic));
    QString qout(QString::fromUtf8(reinterpret_cast<const char *>(data), len));
    //qDebug() << "Topic:" << qtopic << " len:" << len << " Msg:" << qout ;
}

void IpcManager::ctrlButtonHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.c2uButtonKey(topic,data,len)){
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

void IpcManager::ctrlRawDataHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.cabinRawData(topic,data,len)){
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

void IpcManager::vehicleRawDataHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.g2uVehicleRawData(topic,data,len)){
        qWarning() << "ZmqMsgPackage::g2uVehicleRawData error !" ;
        return;
    }


    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

void IpcManager::updateTrackLineConfigHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.g2uUpdateTrackLineConfig(topic,data,len)){
        qWarning() << "ZmqMsgPackage::g2uUpdateTrackLineConfig error !" ;
        return;
    }


    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}
void IpcManager::speedWarningHandler(const string &topic, const void *data, int len)
{

    ZmqMsgPackage msg;
    if(!msg.speedWarning(topic,data,len)){
        qWarning() << "ZmqMsgPackage::speedWarningHandler error !" ;
        return;
    }


    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}
void IpcManager::updateCCUTaskStatusHandler(const string &topic, const void *data, int len)
{

    ZmqMsgPackage msg;
    if(!msg.updateCCUTaskStatus(topic,data,len)){
        qWarning() << "ZmqMsgPackage::updateCCUTaskStatusHandler error !" ;
        return;
    }


    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}
void IpcManager::safeDecelerationHandler(const string &topic, const void *data, int len)
{

    ZmqMsgPackage msg;
    if(!msg.safeDeceleration(topic,data,len)){
        qWarning() << "ZmqMsgPackage::safeDecelerationHandler error !" ;
        return;
    }


    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

void IpcManager::vehicleGpsHandler(const string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.vehicleGps(topic,data,len)){
        qWarning() << "ZmqMsgPackage::vehicleGpsHandler error !" ;
        return;
    }


    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}
void IpcManager::vehicleStatusHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.g2uVehicleStatus(topic,data,len)){
        qWarning() << "ZmqMsgPackage::g2uVehicleStatus error !" ;
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

void IpcManager::vehicleDelayHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.g2uVehicleDelay(topic,data,len)){
        qWarning() << "ZmqMsgPackage::g2uVehicleDelay error !" ;
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        ModuleDir dir = msg.m_moduleDirs.at(i);
//        if(System::getInstance()->messageFilter(static_cast<ModuleType>(dir.first()),msg.m_imei))
        {
            QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                      Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                      Q_ARG(int,msg.m_cmds.at(i)),
                                      Q_ARG(QVariant,msg.m_datas.at(i)));
        }
    }
}

void IpcManager::respRemotelHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.g2uRespRemotel(topic,data,len)){
        qWarning() << "ZmqMsgPackage::g2uRespRemotel error !" ;
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        ModuleDir dir = msg.m_moduleDirs.at(i);
//        if(System::getInstance()->messageFilter(static_cast<ModuleType>(dir.first()),msg.m_imei))
        {
            QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                      Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                      Q_ARG(int,msg.m_cmds.at(i)),
                                      Q_ARG(QVariant,msg.m_datas.at(i)));
        }
    }
}



void IpcManager::respHmiHintmsgHandler(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.hmiHintMsgData(topic,data,len)){
        return;
    }

    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}
void IpcManager::forwardHandler(const std::string &, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.u2uForward(data,len)){
        return;
    }
    QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                              Q_ARG(ModuleDir,msg.m_moduleDirs.first()),
                              Q_ARG(int,msg.m_cmds.first()),
                              Q_ARG(QVariant,msg.m_datas.first()));
}

void IpcManager::ipcForward(ProcessType type,ModuleDir &moduleDir, int &cmd, QVariant &data)
{
    QByteArray tDest;
    ZmqMsgPackage::encodeIpcForward(tDest,moduleDir,cmd,data);

    int procType = System::getInstance()->getProcessType();
    if(procType == PT_MidProc)
    {
        if(type == PT_LeftProc){
            m_pPubUIM->Publish(ZMQ_TOPIC_PROC_LEFT,tDest.constData(),tDest.length());
        }else if(type == PT_RightProc){
            m_pPubUIM->Publish(ZMQ_TOPIC_PROC_RIGHT,tDest.constData(),tDest.length());
        }
    }
    else if(procType == PT_RightProc)
    {
        if(type == PT_LeftProc){
            m_pPubUIR->Publish(ZMQ_TOPIC_PROC_LEFT,tDest.constData(),tDest.length());
        }else if(type == PT_MidProc){
            m_pPubUIR->Publish(ZMQ_TOPIC_PROC_MID,tDest.constData(),tDest.length());
        }
    }
    else if(procType == PT_LeftProc){
        if(type == PT_RightProc){
            m_pPubUIL->Publish(ZMQ_TOPIC_PROC_RIGHT,tDest.constData(),tDest.length());
        }else if(type == PT_MidProc){
            m_pPubUIL->Publish(ZMQ_TOPIC_PROC_MID,tDest.constData(),tDest.length());
        }
    }
}

void IpcManager::getFromAny(ModuleDir,int cmd,QVariant data)
{
    QByteArray tDest;
    IPCManagerCmdType Cmd = static_cast<IPCManagerCmdType>(cmd);
    QString imei(System::getInstance()->getCurrentVehicle());


    switch (Cmd) {
    case IM_ReqRemoteStart:{
        ZmqMsgPackage::encodeReqRemote(tDest,imei,REQ_REMOTE_CONTROL_START);
        m_pPubUI->Publish(ZMQ_TOPIC_REQ_REMOTE_CONTROL,tDest.constData(),tDest.length());// 请求远程控制
        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_REQ_REMOTE_CONTROL<<"start cmd:"<<REQ_REMOTE_CONTROL_START
               <<"imei:"<<imei<<"taskId:"<<System::getInstance()->getCurrentTaskId();
        break;
    }
    case IM_ReqRemoteEnd:{
        ZmqMsgPackage::encodeReqRemote(tDest,imei,REQ_REMOTE_CONTROL_END);
        m_pPubUI->Publish(ZMQ_TOPIC_REQ_REMOTE_CONTROL,tDest.constData(),tDest.length());// 请求远程控制
        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_REQ_REMOTE_CONTROL<<"end cmd:"<<REQ_REMOTE_CONTROL_END
               <<"imei:"<<imei<<"taskId:"<<System::getInstance()->getCurrentTaskId();
        break;
    }
    case IM_Cloud_Takeover_end :{ // 结束接管
        TaskEnd task;
        task.taskId = System::getInstance()->getCurrentTaskId();
        task.reason = data.value<uint8_t>();
        m_pPubUI->Publish(ZMQ_TOPIC_TAKEOVER_TASK_END,&task,sizeof(task));
        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_TAKEOVER_TASK_END<<"网络中断"<<"taskId:"<<task.taskId;

        break;
    }
    case IM_Cloud_Takeover_failed :{ // 不满足接管

#if 0
        RespRemoteControl st;
//        uint8_t imeistr[IMEI_LENGTH];
        QString imei = System::getInstance()->getCurrentVehicle();
        if(imei.size() <I MEI_LENGTH)
        {
            qDebug()<<"IM_Cloud_Takeover_failed不满足接管:"<<imei;
            return;
        }
        const char *imeic = imei.toStdString().c_str();
        memcpy(st.imei,imeic,IMEI_LENGTH);
        st.taskId = data.value<unsigned short>();
        st.result = RESP_REMOTE_CONTROL_VEHICLE_REJECT;//不是2都可以，与恩杰约定
        m_pPubUI->Publish(ZMQ_TOPIC_RESP_REMOTE_CONTROL,&st,sizeof(st));//不满足接管
        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_RESP_REMOTE_CONTROL
               <<"imei:"<<imei<<"taskid:"<<st.taskId<<"result:"<<(int)st.result;
#endif
        TaskFail st;
        st.taskId = data.value<unsigned short>();
        m_pPubUI->Publish(ZMQ_TOPIC_TAKEOVER_TASK_FAIL, &st, sizeof(st));//不满足接管
        qDebug() << ZMQ_ADDR_UI << "[send]IpcManager topic:" << ZMQ_TOPIC_TAKEOVER_TASK_FAIL
               << "taskid:" << st.taskId;
        break;
    }
    case IM_Cloud_Reply_Task:{// 是否接受任务的回复
        if(data.toList().size()<3)
        {
            qDebug()<<"IM_Cloud_Reply_Task data error";
            break;
        }

        TaskReply taskReply;

        taskReply.taskId = data.toList().at(0).toUInt();
        taskReply.result = static_cast<CommonResult>(data.toList().at(1).toUInt());
        std::memset(taskReply.refuseReason,0,sizeof(taskReply.refuseReason));
        std::memmove(taskReply.refuseReason,
                     data.toList().at(2).toString().toStdString().c_str(),
                     data.toList().at(2).toString().toStdString().size());

        m_pPubUI->Publish(ZMQ_TOPIC_TAKEOVER_TASK_REPLY,&taskReply, sizeof(taskReply));
        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_TAKEOVER_TASK_REPLY
               <<"result:"<<taskReply.result<<"taskid:"<<taskReply.taskId
              <<"refuse reason:"<<(char*)taskReply.refuseReason;
        break;
    }
    case IM_Cloud_GiveUp_Task:{//放弃接管任务
        TaskGiveUp task;
        task.taskId = data.toUInt();
        m_pPubUI->Publish(ZMQ_TOPIC_TAKEOVER_TASK_GEVE_UP,&task,sizeof(task));//放弃接管任务
        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_TAKEOVER_TASK_GEVE_UP
               <<"taskid:"<<task.taskId;
        break;
    }
    case IM_Cloud_Request:{//主动请求
        TaskReq Tr;
        QString imei=System::getInstance()->getCurrentVehicle();
        if(imei.size()<IMEI_LENGTH)
        {
            qDebug()<<"IM_Cloud_Request 主动请求:"<<imei;
            return;
        }
        const char *imeic=imei.toStdString().c_str();
        memcpy(Tr.imei,imeic,IMEI_LENGTH);
        m_pPubUI->Publish(ZMQ_TOPIC_TAKEOVER_TASK_REQ,&Tr,sizeof(Tr));//请求任务

        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_TAKEOVER_TASK_REQ
               <<"imei:"<<imei;
        break;
    }
    case IM_ReqCameraCfg:{//请求摄像头配置文件
        TrackLineMsg st;
        memset(&st,0,sizeof(st));
        QString imei=System::getInstance()->getCurrentVehicle();
        if(imei.size()<IMEI_LENGTH)
        {
            qDebug()<<"IM_ReqCameraCfg 请求摄像头配置:"<<imei;
            return;
        }
        const char *imeic=imei.toStdString().c_str();
        memcpy(st.imei,imeic,IMEI_LENGTH);
        m_pPubUI->Publish(ZMQ_TOPIC_REPORT_TRACK_LINE_MSG_REQ,&st,sizeof(st));//请求任务

        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_REPORT_TRACK_LINE_MSG_REQ
               <<"imei:"<<imei;
        break;
    }
    case IM_FastStop:{//请求Fast Stop
        TaskReq Tr;
        QString imei=System::getInstance()->getCurrentVehicle();
        if(imei.size()<IMEI_LENGTH)
        {
            qDebug()<<"IM_FastStop 快速停车:"<<imei;
            return;
        }
        const char *imeic=imei.toStdString().c_str();
        memcpy(Tr.imei,imeic,IMEI_LENGTH);
        m_pPubUI->Publish(ZMQ_TOPIC_FAST_STOP_REQ,&Tr,sizeof(Tr));//请求任务

        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_FAST_STOP_REQ
               <<"imei:"<<imei;
        break;
    }
    case IM_ReqConnect:{
        QString imei = data.value<QString>();
        QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
        if(data.toList().isEmpty()){
            break;
        }

        QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
        QString strIP = mapVehicle.value(imei).toList().at(0).toMap().value("IP").toString();
        if (strIP.isEmpty())
        {
            qDebug() << "Vehicle's IP is empty!";
            break;
        }
        
        m_pPubUI->Publish(ZMQ_TOPIC_REQ_CONNECT, strIP.toUtf8().data(), strIP.length());

        qDebug()<<ZMQ_ADDR_UI<<"[send]IpcManager topic:"<<ZMQ_TOPIC_REQ_CONNECT
               << "imei:" << imei << ", strIP:" << strIP;
        break;
    }
    default:{break;}
    }
}

void IpcManager::modeTimeOut()
{
//    qDebug()<<"updatexzk modeTimeout";
    static LayoutType lastMode=LT_Monitor;
    if(System::getInstance()->showLayoutMode!=lastMode)
    {
        lastMode=System::getInstance()->showLayoutMode;
        qDebug()<<"updatexzk show Layout mode:"<<lastMode;
        if(lastMode == LT_Monitor)
        {
            //关闭所有视频流
            QVector<ModuleDir>   m_moduleDirs;
            QVector<int>         m_cmds;
            QVector<QVariant>    m_datas;

            //发给主摄像头,主窗口的前右前左
            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(false));

            //发给驾驶舱
            moduleDir.clear();
            moduleDir.append(MD_DriveCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(false));

            //发给左摄像头
            moduleDir.clear();
            moduleDir.append(MD_LeftCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(false));

            //发给右摄像头
            moduleDir.clear();
            moduleDir.append(MD_RightCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(false));

            //发给前右摄像头
            moduleDir.clear();
            moduleDir.append(MD_ForwardRightCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(false));

            for (int i = 0;i < m_cmds.size(); i++)
            {
                ModuleDir dir = m_moduleDirs.at(i);

                QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                          Q_ARG(ModuleDir,m_moduleDirs.at(i)),
                                          Q_ARG(int,m_cmds.at(i)),
                                          Q_ARG(QVariant,m_datas.at(i)));

            }
        }else if(lastMode == LT_RemoteControl)
        {
            qDebug()<<"updatexzk切换到接管";
            //开启前/前左/前右/左/右/驾驶舱摄像头

            QVector<ModuleDir>   m_moduleDirs;
            QVector<int>         m_cmds;
            QVector<QVariant>    m_datas;

            //发给主摄像头
            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(true));

            //发给驾驶舱
            moduleDir.clear();
            moduleDir.append(MD_DriveCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(true));

            //发给右前摄像头
//            moduleDir.clear();
//            moduleDir.append(MD_ForwardRightCamera);
//            m_moduleDirs.append(moduleDir);
//            m_cmds.append(CC_StartPlay);
//            m_datas.append(QVariant::fromValue(true));


            //发给左后摄像头
            moduleDir.clear();
            moduleDir.append(MD_LeftCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(true));

            //发给右后摄像头
            moduleDir.clear();
            moduleDir.append(MD_RightCamera);
            m_moduleDirs.append(moduleDir);
            m_cmds.append(CC_StartPlay);
            m_datas.append(QVariant::fromValue(true));


            for (int i = 0;i < m_cmds.size(); i++)
            {
//                QThread::msleep(400);
                ModuleDir dir = m_moduleDirs.at(i);

                QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                          Q_ARG(ModuleDir,m_moduleDirs.at(i)),
                                          Q_ARG(int,m_cmds.at(i)),
                                          Q_ARG(QVariant,m_datas.at(i)));

            }
        }


    }
}

void IpcManager::CloudData(const std::string &topic,const /*uint8_t*/void *buf,int len)
{
    ZmqMsgPackage msg;
    if(!msg.cloudMsgData(topic,buf,len)){
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}

//接管前自检查
void IpcManager::controlSelfCheckStatus(const std::string &topic, const void *data, int len)
{
    ZmqMsgPackage msg;
    if(!msg.selfCheckStatus(topic,data,len)){
        return;
    }
    for (int i = 0;i < msg.m_cmds.size(); i++) {
        QMetaObject::invokeMethod(s_pInstance,"sendToMain",
                                  Q_ARG(ModuleDir,msg.m_moduleDirs.at(i)),
                                  Q_ARG(int,msg.m_cmds.at(i)),
                                  Q_ARG(QVariant,msg.m_datas.at(i)));
    }
}
