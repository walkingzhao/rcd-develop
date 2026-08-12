#include "gatewayserver.h"

#include <cstring>
#include <memory>
#include <QCoreApplication>
#include <QMetaObject>

#include "devmanage.h"
#include "fbs/tgmsg_generated.h"


GateWayServer::GateWayServer(QObject *parent) : QObject(parent)
{
    gatewaySub.ConnectTo(ZMQ_ADDR_UI);
    gatewaySub.ConnectTo(ZMQ_ADDR_CONTROL);
    gatewaySub.ConnectTo(ZMQ_ADDR_CLOUDSERVER);
    gatewayPub = new ZmqPublisher(ZMQ_ADDR_Gateway);
    m_checkConnectTimer = new QTimer(this);
    connect(m_checkConnectTimer,SIGNAL(timeout()),this,SLOT(handleCheckConnectTimeOut()));
    m_checkConnectTimer->start(50);
}

GateWayServer::~GateWayServer()
{
    controlFastDev = nullptr;
    delete gatewayPub;
    delete m_checkConnectTimer;
}

void GateWayServer::Start()
{
    gatewaySub.Subscribe(ZMQ_TOPIC_REQ_REMOTE_CONTROL,
                         std::bind(&GateWayServer::HandleZmqReqRemoteControl,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));
//    gatewaySub.Subscribe(ZMQ_TOPIC_REQ_SEND_HMIMSG,
//                         std::bind(&GateWayServer::HandleZmqReqSendHmiMsg,
//                                   this, std::placeholders::_1,
//                                   std::placeholders::_2, std::placeholders::_3));
    gatewaySub.Subscribe(ZMQ_TOPIC_CLOUD_SEND_TASK_AUTH_INFO,
                         std::bind(&GateWayServer::HandleZmqCloudTaskAuthInfo,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));
    // add send task from platform cancel to vehicle
    gatewaySub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_CANCEL,
                         std::bind(&GateWayServer::HandleZmqCloudTaskCancelMsg,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));

    // add send task from ui end to vehicle
    gatewaySub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_END,
                         std::bind(&GateWayServer::HandleZmqCloudTaskEndMsg,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));

    // add send task from ui reply to vehicle
    gatewaySub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_REPLY,
                         std::bind(&GateWayServer::HandleZmqCloudTaskReplyMsg,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));
    // add send task from ui reply to vehicle
    gatewaySub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_GEVE_UP,
                         std::bind(&GateWayServer::HandleZmqCloudTaskGiveupMsg,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));
    // add send task from ui reply to vehicle
    gatewaySub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_FAIL,
                         std::bind(&GateWayServer::HandleZmqCloudTaskFailMsg,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));

    gatewaySub.Subscribe(ZMQ_TOPIC_REPORT_TRACK_LINE_MSG_REQ,
                         std::bind(&GateWayServer::HandleZmqReqTrackLineMsg,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));

    gatewaySub.Subscribe(ZMQ_TOPIC_REMOTE_ESTOP,
                         std::bind(&GateWayServer::HandleZmqRemoteEstopMsg,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));

    gatewaySub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_OPERATE,
                         std::bind(&GateWayServer::HandleZmqCloudTaskOperate,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));

    gatewaySub.Subscribe(ZMQ_TOPIC_REQ_CONNECT,
                         std::bind(&GateWayServer::HandleZmqReqConnect,
                                   this, std::placeholders::_1,
                                   std::placeholders::_2, std::placeholders::_3));


}


void GateWayServer::HandleNewConnect()
{
    qDebug() << "HandleNewConnect";
    InitNewClient(m_tcpSocket);
}

void GateWayServer::HandleDevDisConnected(qintptr socketDesc)
{
    devM.DelDev(socketDesc);
}

void GateWayServer::HandleDevReqAuth(qintptr socketDesc,
                                     const std::string &imei, int type)
{
    devM.UpdateDev(socketDesc, imei, type);
}

void GateWayServer::HandleReqControlCmdResult(const std::string &imei, int cmd,
                                              int result, uint16_t taskId)
{
    if ((result == RESP_REMOTE_CONTROL_VEHICLE_RECV) && (lastReqControlCmd == REQ_REMOTE_CONTROL_START))
    {

        controlFastDev = devM.GetDevHandle(imei);
        gatewaySub.Subscribe(ZMQ_TOPIC_CONTROL_DATA, std::bind(&GateWayServer::HandleZmqControlData,
                                                               this, std::placeholders::_1,
                                                               std::placeholders::_2, std::placeholders::_3));

        connect(this, SIGNAL(EmitControlData(const QByteArray &)),
                controlFastDev.get(), SLOT(HandleControlData(const QByteArray &)));

        qDebug() << "Subscribe " << ZMQ_TOPIC_CONTROL_DATA << " on device[" << imei.c_str() << "]";

    }
    else
    {
        gatewaySub.UnSubscribe(ZMQ_TOPIC_CONTROL_DATA);
        if (controlFastDev != nullptr)
        {
            disconnect(this, SIGNAL(EmitControlData(const QByteArray &)),
                       controlFastDev.get(), SLOT(HandleControlData(const QByteArray &)));
        }
        qDebug() << "UnSubscribe " << ZMQ_TOPIC_CONTROL_DATA << " on device[" << imei.c_str() << "]";

        controlFastDev = nullptr;
    }

    RespRemoteControl resp;
    std::memmove(resp.imei, imei.c_str(), sizeof(resp.imei));
    resp.cmd = cmd;
    resp.result = result;
    resp.taskId = taskId;
    gatewayPub->Publish(ZMQ_TOPIC_RESP_REMOTE_CONTROL, reinterpret_cast<const void *>(&resp), sizeof(RespRemoteControl));
}

void GateWayServer::HandleVehicleStatus(const std::string &imei, int type,
                                        int status)
{
    if ((status != VEHICLE_STATUS_CONNECTED) && (controlFastDev != nullptr) && (controlFastDev == devM.GetDevHandle(imei)))
    {
        gatewaySub.UnSubscribe(ZMQ_TOPIC_CONTROL_DATA);

        disconnect(this, SIGNAL(EmitControlData(const QByteArray &)),
                   controlFastDev.get(), SLOT(HandleControlData(const QByteArray &)));
        // add to publish task end msg to cloudServer when lastReqControlCmd is start and status is disconnected
//        if(lastReqControlCmd == REQ_REMOTE_CONTROL_START) {
//            for (auto it = taskList.begin(); it != taskList.end(); it++) {
//                if(it->imei == imei) {
//                    TaskEnd taskEnd;
//                    taskEnd.taskId = it->taskId;
//                    taskEnd.reason = TaskEndReason::TaskEndReason_NetworkInterrupt; //network interrupt
//                    gatewayPub->Publish(ZMQ_TOPIC_TAKEOVER_TASK_END, &taskEnd, sizeof(taskEnd));
//                    qDebug() << "publish task end msg to cloud server";
//                    break;
//                }
//            }
//        }

        controlFastDev = nullptr;
        qDebug() << "del fast dev.";
    }

    VehicleStatus vstatus;
    std::memmove(vstatus.imei, imei.c_str(), imei.size());
    vstatus.type = static_cast<uint8_t>(type);
    vstatus.status = static_cast<uint8_t>(status);
    qDebug() << "Get Status Signal:" << vstatus.status << " " << imei.c_str();
    gatewayPub->Publish(ZMQ_TOPIC_VEHICLE_STATUS, reinterpret_cast<const void *>(&vstatus), sizeof(VehicleStatus));
}

void GateWayServer::HandleVehicleRawData(const QByteArray &rawData)
{
    gatewayPub->Publish(ZMQ_TOPIC_VEHICLE_RAWDATA, rawData.data(), rawData.size());
}

void GateWayServer::HandleVehicleDelay(const std::string &imei, uint32_t delayUs)
{
    VehicleDelay delay = {{0x00},0x00};
    std::memmove(delay.imei, imei.c_str(), IMEI_LENGTH);
    delay.delayUs = delayUs;
    gatewayPub->Publish(ZMA_TOPIC_VEHICLE_DELAY, &delay, sizeof(delay));
}

void GateWayServer::HandleVehicleReportHmiMsg(const std::string &imei, int len, QByteArray &body)
{
    HmiMsg msg = {{0x00},0x00,{0x00}};
    std::memmove(msg.imei, imei.c_str(), IMEI_LENGTH);
    msg.bodyLen = len;
    std::memmove(msg.body, body.data(), len);
    gatewayPub->Publish(ZMQ_TOPIC_REQ_SEND_HMIMSG, &msg, sizeof(msg));
}

void GateWayServer::HandleVehicleReportHmiHintMsg(const std::string &imei, int len, QByteArray &body) {
    HmiHintMsg msg = {{0x00},0x00,{0x00}};
    std::memmove(msg.imei, imei.c_str(), IMEI_LENGTH);
    msg.bodyLen = len;
    std::memmove(msg.body, body.data(), len);
    qDebug() << "send hmi hint msg";
    gatewayPub->Publish(ZMQ_TOPIC_REPORT_HMI_HINT_MSG, &msg, sizeof(msg));
}

void GateWayServer::HandleVehicleReportTrackLineMsg(const std::string &imei, int len, QByteArray &body) {
    TrackLineMsg msg = {{0x00},0x00,{0x00}};
    std::memmove(msg.imei, imei.c_str(), IMEI_LENGTH);
    msg.bodyLen = len;
    std::memmove(msg.body, body.data(), len);
    qDebug() << "send track line msg";
    gatewayPub->Publish(ZMQ_TOPIC_REPORT_TRACK_LINE_MSG, &msg, sizeof(msg));
}

void GateWayServer::HandleVehicleReportSpeedWarningMsg(const std::string &imei, int len, QByteArray &body) {
    SpeedWarningMsg msg = {{0x00},0x00,{0x00}};
    std::memmove(msg.imei, imei.c_str(), IMEI_LENGTH);
    msg.bodyLen = len;
    std::memmove(msg.body, body.data(), len);
    qDebug() << "send speed warning msg";
    gatewayPub->Publish(ZMQ_TOPIC_REPORT_SPEED_WARNING_MSG, &msg, sizeof(msg));
}


void GateWayServer::HandleVehicleReportRoadTaskInfo(const std::string &imei, int len, QByteArray &body) {
    RoadTaskInfo msg = {{0x00},0x00,{0x00}};
    std::memmove(msg.imei, imei.c_str(), IMEI_LENGTH);
    msg.bodyLen = len;
    std::memmove(msg.body, body.data(), len);
    qDebug() << "send road task info msg";
    gatewayPub->Publish(ZMQ_TOPIC_REPORT_ROAD_TASK_INFO, &msg, sizeof(msg));
}

void GateWayServer::HandleVehicleTaskAuthReq(const uint16_t taskId, std::string imei, std::string authkey) {
    qDebug() << "HandleVehicleTaskAuthReq taskid:" << taskId << ", imei:" << imei.c_str() << ", key: " << authkey.c_str();

    emit EmitTaskAuthResp(1);
    qDebug() << "auth success--------------";
    return ;
#if 0
    for (auto it = taskList.begin(); it != taskList.end(); it++) {
        qDebug() << "for------" << it->taskId << ", " << it->imei.c_str() << ", " << it->authKey.c_str();
        if(it->imei == imei && it->taskId == taskId && it->authKey == authkey) {
            emit EmitTaskAuthResp(1);
            qDebug() << "auth success--------------";
            return ;
        }
    }
    emit EmitTaskAuthResp(0);
    qDebug() << "auth failed------------------------";
#endif
}

void GateWayServer::HandleVehicleReportGnssMsg(const std::string &imei, int len, QByteArray &body)
{
    GpsMsg msg = {{0x00},0x00,{0x00}};
    std::memmove(msg.imei, imei.c_str(), IMEI_LENGTH);
    msg.bodyLen = len;
    std::memmove(msg.body, body.data(), len);
    gatewayPub->Publish(ZMQ_TOPIC_REPORT_GPS_DATA, &msg, sizeof(msg));
}

void GateWayServer::HandleZmqReqRemoteControl(const std::string &,
                                              const void *data, int )
{
    ReqRemoteControl reqControl = {{0x00},0x00, 0x00};
    std::memmove(&reqControl, data, sizeof(ReqRemoteControl));
    std::string imei(reinterpret_cast<char *>(reqControl.imei), IMEI_LENGTH);
    qDebug() << "Get ReqRemoteControl Cmd.Imei: " << imei.c_str()
             << " ,Opt:" << reqControl.opt;
    auto devHandleTmp = devM.GetDevHandle(imei);
    if (devHandleTmp == nullptr){
        qDebug() << "Not Found Dev:" << imei.c_str();
        RespRemoteControl resp;
        std::memmove(resp.imei, imei.c_str(), imei.size());
        resp.cmd = reqControl.opt;
        resp.result = RESP_REMOTE_CONTROL_VEHICLE_DISCONNECT;
        resp.taskId = reqControl.taskId;
        gatewayPub->Publish(ZMQ_TOPIC_RESP_REMOTE_CONTROL, reinterpret_cast<const void *>(&resp), sizeof(RespRemoteControl));
        return;
    }

    lastReqControlCmd = reqControl.opt;
    emit EmitReqControlCmdSignal(imei, reqControl.opt);
}

void GateWayServer::HandleZmqReqSendHmiMsg(const std::string &,
                                              const void *data, int )
{
    HmiMsg reqSendMsg = {{0x00},0x00,{0x00}};
    std::memmove(&reqSendMsg, data, sizeof(HmiMsg));
    std::string imei(reinterpret_cast<char *>(reqSendMsg.imei), IMEI_LENGTH);
    qDebug() << "Get ReqSendHmiMgs Cmd.Imei: " << imei.c_str()
             << " ,Len:" << reqSendMsg.bodyLen;

    auto devHandleTmp = devM.GetDevHandle(imei);
    if (devHandleTmp == nullptr)
    {
        qWarning() << "Not Found Dev:" << imei.c_str();
        return;
    }
//    lastReqControlCmd = reqControl.opt;
    QByteArray tmpData(reinterpret_cast<const char *>(reqSendMsg.body), sizeof(reqSendMsg.bodyLen));
    emit EmitReqSendHmiMsgCmdSignal(imei, tmpData);
}

void GateWayServer::HandleZmqControlData(const std::string &,
                                         const void *data, int len)
{
    QByteArray tmpB(reinterpret_cast<const char *>(data), len);
    emit EmitControlData(tmpB);
}

void GateWayServer::HandleZmqCloudTaskAuthInfo(const std::string &, const void *data, int ) {
    auto tmpMsg = TGMsg::GetMsgFrame(data);
    auto msgT = tmpMsg->msg_as_Platform_CabinTakeoverTaskApply();

    taskInfo taskinfo;
    taskinfo.taskId = msgT->taskId();
    taskinfo.imei = msgT->truckImei()->str();
    taskinfo.authKey = msgT->secretKey()->str();

    taskList.push_back(taskinfo);
    qDebug() << "add taskInfo taskId:" << taskinfo.taskId << " imei:" << taskinfo.imei.c_str() << " key:" << taskinfo.authKey.c_str();
}

void GateWayServer::HandleZmqCloudTaskCancelMsg(const std::string &, const void *data, int len) {
    TaskCancel taskCancel;
    std::memmove(&taskCancel, data, len);
    emit EmitTaskStop(taskCancel.taskId);
    for (auto it = taskList.begin(); it != taskList.end(); it++)
    {
        if (it->taskId == taskCancel.taskId)
        {
            qDebug() << "cancel task, delete task id:" << it->taskId;
            taskList.erase(it);
            break;
        }
    }
}

void GateWayServer::HandleZmqCloudTaskEndMsg(const std::string &, const void *data, int len) {
    TaskEnd taskEnd;
    std::memmove(&taskEnd, data, len);
    emit EmitTaskStop(taskEnd.taskId);
    for (auto it = taskList.begin(); it != taskList.end(); it++)
    {
        if (it->taskId == taskEnd.taskId)
        {
            qDebug() << "task end, delete task id:" << it->taskId;
            taskList.erase(it);
            break;
        }
    }
}

void GateWayServer::HandleZmqCloudTaskReplyMsg(const std::string &, const void *data, int len) {
    qDebug() << "task reply";
    TaskReply taskReply;
    std::memmove(&taskReply, data, len);
    if(taskReply.result == CommonResult_Fail) {
        qDebug() << "reply result is fail";
        emit EmitTaskStop(taskReply.taskId);
        for (auto it = taskList.begin(); it != taskList.end(); it++)
        {
            if (it->taskId == taskReply.taskId)
            {
                qDebug() << "reply task fail, delete task id:" << it->taskId;
                taskList.erase(it);
                break;
            }
        }
    }
}

void GateWayServer::HandleZmqCloudTaskGiveupMsg(const std::string &, const void *data, int len) {
    qDebug() << "task give up";
    TaskGiveUp task;
    std::memmove(&task, data, len);
    emit EmitTaskStop(task.taskId);
    for (auto it = taskList.begin(); it != taskList.end(); it++)
    {
        if (it->taskId == task.taskId)
        {
            qDebug() << "give up task, delete task id:" << it->taskId;
            taskList.erase(it);
            break;
        }
    }
}

void GateWayServer::HandleZmqCloudTaskFailMsg(const std::string &, const void *data, int len) {
    qDebug() << "task fail";
    TaskFail task;
    std::memmove(&task, data, len);
    emit EmitTaskStop(task.taskId);
    for (auto it = taskList.begin(); it != taskList.end(); it++)
    {
        if (it->taskId == task.taskId)
        {
            qDebug() << "task fail, delete task id:" << it->taskId;
            taskList.erase(it);
            break;
        }
    }
}

void GateWayServer::HandleZmqCloudTaskOperate(const std::string &, const void *data, int len) {
    TaskOperSt task;
    std::memmove(&task, data, len);
    uint16_t taskId = 0;
    switch (task.taskType) {
    case TakeoverTask_Reply:{
        if(task.TaskUnion.taskReply.result == CommonResult_Success) return;
        taskId = task.TaskUnion.taskReply.taskId;
        qDebug() << "task reply is fail";
        break;
    }
    case TakeoverTask_GiveUp: {
        taskId = task.TaskUnion.taskGiveUp.taskId;
        qDebug() << "task give up";
        break;
    }
    case TakeoverTask_Cancel: {
        taskId = task.TaskUnion.taskCancel.taskId;
        qDebug() << "task cancel";
        break;
    }
    case TakeoverTask_End: {
        taskId = task.TaskUnion.taskEnd.taskId;
        qDebug() << "task end";
        break;
    }
    case TakeoverTask_Fail: {
        taskId = task.TaskUnion.taskFail.taskId;
        qDebug() << "task fail";
        break;
    }
    default:
        return;
    }

    emit EmitTaskStop(taskId);

    // delete task
    for (auto it = taskList.begin(); it != taskList.end(); it++)
    {
        if (it->taskId == taskId)
        {
            qDebug() << "delete task id:" << static_cast<int>(it->taskId);
            taskList.erase(it);
            break;
        }
    }
}

void GateWayServer::HandleZmqReqTrackLineMsg(const std::string &, const void *data, int) {
    qDebug() << "track line req msg";

    TrackLineMsg msg = {{0x00},0x00,{0x00}};
    std::memmove(&msg, data, sizeof(TrackLineMsg));
    std::string imei(reinterpret_cast<char *>(msg.imei), IMEI_LENGTH);
    qDebug() << "Get ReqTrackLineMgs Cmd.Imei: " << imei.c_str()
             << " ,Len:" << msg.bodyLen;

    auto devHandleTmp = devM.GetDevHandle(imei);
    if (devHandleTmp == nullptr)
    {
        qWarning() << "Not Found Dev:" << imei.c_str();
        return;
    }

    QByteArray tmpData(reinterpret_cast<const char *>(msg.body), sizeof(msg.bodyLen));
    emit EmitReqTrackLineMsgSignal(imei, tmpData);

}

void GateWayServer::HandleZmqRemoteEstopMsg(const std::string &, const void *data, int len) {

    uint8_t estop;
    std::memmove(&estop, data, len);
    qDebug() << "send estop status:" << static_cast<int>(estop);
    emit EmitRemoteEstop(estop);
}

void GateWayServer::HandleZmqReqConnect(const std::string &, const void *data, int len)
{
    m_mutex.lock();
    m_strIP.clear();
    m_strIP = QString::fromUtf8(static_cast<const char*>(data), len);
    qDebug() << "m_strIP:" << m_strIP;
    if (!m_strIP.isEmpty())
    {
        m_bNeedConnect = true;
    }
    m_mutex.unlock();
}

void GateWayServer::handleCheckConnectTimeOut()
{
    m_mutex.lock();
    if (m_bNeedConnect)
    {
        m_bNeedConnect = false;
        m_checkConnectTimer->stop();
        if (!m_tcpSocket)
        {
            m_tcpSocket = new QTcpSocket(this);
            //connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(HandleNewConnect()));
        }

        m_tcpSocket->abort();
        m_tcpSocket->close();
        m_strIP = m_strIP.trimmed();
        if (m_strIP.isEmpty())
        {
            qWarning() << "connect ip is empty, skip";
            m_checkConnectTimer->start(50);
            m_mutex.unlock();
            return;
        }
        m_tcpSocket->connectToHost(m_strIP, 8886);
        if (m_tcpSocket->waitForConnected(3000))
        {
            HandleNewConnect();
            m_checkConnectTimer->start(50);
        }
        else
        {
            m_tcpSocket->abort();
            m_tcpSocket->close();
            VehicleStatus vstatus;
            const std::string imei = "861617051838026";
            std::memmove(vstatus.imei, imei.c_str(), imei.size());
            vstatus.type = 0;
            vstatus.status = 2;
            gatewayPub->Publish(ZMQ_TOPIC_VEHICLE_STATUS, reinterpret_cast<const void *>(&vstatus), sizeof(VehicleStatus));
            m_checkConnectTimer->start(50);
        }
    }
    m_mutex.unlock();
}

void GateWayServer::HandleVehicleSendSafeDecelerate(const uint8_t action) {
    qDebug() << "send safe deceleration, action:" << action;
    gatewayPub->Publish(ZMQ_TOPIC_SAFE_DECELERATION, &action, sizeof(action));
}

void GateWayServer::InitNewClient(QTcpSocket *client)
{
    auto tmpHandle = std::make_shared<DevHandle>(this, client);
    devM.AddDev(client->socketDescriptor(), tmpHandle);

    connect(tmpHandle.get(), SIGNAL(Disconnected(qintptr)),
            this, SLOT(HandleDevDisConnected(qintptr)));
    connect(tmpHandle.get(), SIGNAL(DevReqAuth(qintptr, const std::string &, int)),
            this, SLOT(HandleDevReqAuth(qintptr, const std::string &, int)));
    connect(tmpHandle.get(), SIGNAL(ReqControlCmdResult(const std::string &, int, int, uint16_t)),
            this, SLOT(HandleReqControlCmdResult(std::string, int, int, uint16_t)));
    connect(tmpHandle.get(), SIGNAL(VehicleStatusSignal(const std::string &, int, int)),
            this, SLOT(HandleVehicleStatus(std::string, int, int)));
    connect(tmpHandle.get(), SIGNAL(VehicleRawDataSignal(const QByteArray &)),
            this, SLOT(HandleVehicleRawData(const QByteArray &)));
    connect(tmpHandle.get(), SIGNAL(VehicleDelaySignal(const std::string &, uint32_t)),
            this, SLOT(HandleVehicleDelay(const std::string &, uint32_t)));
    connect(tmpHandle.get(), SIGNAL(VehicleReportHmiMsgSignal(const std::string &, int, QByteArray &)),
            this, SLOT(HandleVehicleReportHmiMsg(const std::string &, int, QByteArray &)));
    connect(tmpHandle.get(), SIGNAL(VehicleReportGnssMsgSignal(const std::string &, int, QByteArray &)),
            this, SLOT(HandleVehicleReportGnssMsg(const std::string &, int, QByteArray &)));
    connect(tmpHandle.get(), SIGNAL(VehicleReportHmiHintMsgSignal(const std::string &, int, QByteArray &)),
            this, SLOT(HandleVehicleReportHmiHintMsg(const std::string &, int, QByteArray &)));
    connect(tmpHandle.get(), SIGNAL(VehicleReportTrackLineMsgSignal(const std::string &, int, QByteArray &)),
            this, SLOT(HandleVehicleReportTrackLineMsg(const std::string &, int, QByteArray &)));
    connect(tmpHandle.get(), SIGNAL(VehicleReportRoadTaskInfoSignal(const std::string &, int, QByteArray &)),
            this, SLOT(HandleVehicleReportRoadTaskInfo(const std::string &, int, QByteArray &)));
    connect(tmpHandle.get(), SIGNAL(VehicleSendSafeDecelerateSignal(const uint8_t)),
            this, SLOT(HandleVehicleSendSafeDecelerate(const uint8_t)));
    connect(tmpHandle.get(), SIGNAL(VehicleReportSpeedWarningMsgSignal(const std::string &, int, QByteArray &)),
            this, SLOT(HandleVehicleReportSpeedWarningMsg(const std::string &, int, QByteArray &)));

    connect(tmpHandle.get(), SIGNAL(VehicleTaskAuthReq(const uint16_t, std::string, std::string)),
            this, SLOT(HandleVehicleTaskAuthReq(const uint16_t, std::string, std::string)));

    connect(this, SIGNAL(EmitReqControlCmdSignal(const std::string &, uint8_t)),
            tmpHandle.get(), SLOT(HandleReqControlCmdSlot(const std::string &, uint8_t)));
    connect(this, SIGNAL(EmitReqSendHmiMsgCmdSignal(const std::string &,const QByteArray &)),
            tmpHandle.get(), SLOT(HandleReqSendHmiMsgCmdSlot(const std::string &,const QByteArray &)));
    connect(this, SIGNAL(EmitReqTrackLineMsgSignal(const std::string &,const QByteArray &)),
            tmpHandle.get(), SLOT(HandleReqTrackLineMsgSlot(const std::string &,const QByteArray &)));
    connect(this, SIGNAL(EmitRemoteEstop(uint8_t )),
            tmpHandle.get(), SLOT(HandleRemoteEstop(uint8_t )));
    //TODO: add signal-slot to send msg from cloud by zmq to devhandle
//    connect(this, SIGNAL(EmitSecretKey(const std::string &)),
//            tmpHandle.get(), SLOT(HandleSecretKey(const std::string &)));

    connect(this, SIGNAL(EmitTaskStop(quint16)),
               tmpHandle.get(), SLOT(HandleTaskStop(quint16)));

    connect(this, SIGNAL(EmitTaskAuthResp(uint8_t)),
               tmpHandle.get(), SLOT(HandleTaskAuthResp(uint8_t)));
}
