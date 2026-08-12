#include "devhandle.h"
#include "devmanage.h"
#include "include/msgcmd.hpp"

#include <cstring>

#include <flatbuffers/minireflect.h>
#include "fbs/tgmsg_generated.h"

#include <QDebug>

DevHandle::DevHandle(QObject *parent, QTcpSocket *socket)
    : QObject(parent), devSocket(socket)
{
    connect(devSocket, SIGNAL(readyRead()), this, SLOT(ReadDataFromDev()));
    connect(devSocket, SIGNAL(disconnected()), this, SLOT(DevDisConnected()));

    socketDesc = devSocket->socketDescriptor();

    //set no delay to disable tcp nagle
    devSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);

    heartTimer.setInterval(GATEWAY_HEART_TIMEOUT_MS);
    connect(&heartTimer, SIGNAL(timeout()), this, SLOT(HeartTimeOutSlots()));

    reqControlCmdTimer.setInterval(REQ_CONTROL_CMD_TIEMOUT_MS);
    reqControlCmdTimer.setSingleShot(true);
    connect(&reqControlCmdTimer, SIGNAL(timeout()), this, SLOT(ControlCmdTimeOutSlots()));

    delayTimer.setInterval(REQ_DELAY_CMD_TIMEOUT_MS);
    connect(&delayTimer, SIGNAL(timeout()), this, SLOT(DelayCmdTimeOutSlots()));
    qDebug() << " Get New Client.Socket:" << socketDesc;
}

DevHandle::~DevHandle()
{
    qDebug() << " DevHandle release.Imei:" << devImei.c_str();
    heartTimer.stop();
    reqControlCmdTimer.stop();
    delayTimer.stop();
    devSocket->close();
}

void DevHandle::SendReqControlCmdToDev(uint8_t opt)
{
    qDebug() << "SendReqControlCmdToDev";
    flatbuffers::FlatBufferBuilder fbb;

    uint64_t curTimeUs = GetSysTimeMs();

    fbb.FinishSizePrefixed(
                TGMsg::CreateMsgFrame(
                    fbb, curTimeUs, TGMsg::MsgUnion_Rcd_ReqControlCmd,
                    Rcd::CreateReqControlCmd(fbb, opt == 1 ? RcdControlCmd_Start : RcdControlCmd_Finish).Union()));

    SendDataToDev(fbb.GetBufferPointer(), fbb.GetSize());
    reqControlCmdTimer.start();
}

void DevHandle::SendReqSendHmiMsgToDev(const uint8_t *data, int dataLen)
{
    qDebug() << "SendReqSendHmiMsgToDev";
    SendDataToDev(data, dataLen);
}

void DevHandle::SendControlDataToDev(const uint8_t *data, int dataLen)
{
    SendDataToDev(data, dataLen);
}

void DevHandle::SendTaskStopToDev(uint16_t taskId) {

     flatbuffers::FlatBufferBuilder fbb;
     fbb.FinishSizePrefixed(
                 TGMsg::CreateMsgFrame(
                     fbb, GetSysTimeMs(), TGMsg::MsgUnion_Rcd_ResponTaskStop,
                     Platform::CreateTakeoverTaskCancel(fbb, taskId).Union()));

     SendDataToDev(fbb.GetBufferPointer(), fbb.GetSize());
}

void DevHandle::HandleMsg(const uint8_t *data, int dataLen)
{
    heartTimer.start();
    auto tmpMsg = TGMsg::GetMsgFrame(data);
    auto s = flatbuffers::FlatBufferToString(data, TGMsg::MsgFrameTypeTable(), false, false);
    qDebug() << s.c_str();
    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Pong: { //回复ping
        HandleDelayCmd(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportCan: { //上报can数据
//        HandleReportCan(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportFeedbackData: { //上报车辆反馈信息
        HandleReportFeedbackData(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportGpsInfo: { //上报gps消息
        HandleReportGnssMsg(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportHmi: {
        HandleReportHmiMsg(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportHmiHintMsg: {
        HandleReportHmiHintMsg(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ResponCtrlCmd: { //车端响应驾驶舱接管命令
        HandleRespControlCmd(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReqRcdAuth: { //车端向驾驶舱请求鉴权
        HandleAuth(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_TrackLineConfigMsg: { //车道线标定配置信息
        HandleReportTrackLineMsg(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportRoadTaskInfo: { //车辆运营状态上报
        HandleReportRoadTaskInfo(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_SendSafeDecelerate: { //车辆运营状态上报
        HandleSendSafeDecelerate(data, dataLen);
        break;
    }
    case TGMsg::MsgUnion_Vehicle_ReportSpeedWarningMsg: { //车辆运营状态上报
        HandleReportSpeedWarningMsg(data, dataLen);
        break;
    }
    default:
        break;
    }


}

void DevHandle::HandleAuth(const uint8_t *data, int )
{
    auto tmpMsg = TGMsg::GetMsgFrame(data);
    auto msgT = tmpMsg->msg_as_Vehicle_ReqRcdAuth();
    qDebug() << "authCode:" << msgT->authCode()->c_str()
             << "imei:" << msgT->imei()->c_str()
             << "taskId:" << msgT->taskId();

    devImei = msgT->imei()->str();
    taskId = msgT->taskId();
    secretKey = msgT->authCode()->str();

    emit VehicleTaskAuthReq(msgT->taskId(), msgT->imei()->str(), msgT->authCode()->str());

}

void DevHandle::HandleTaskAuthResp(uint8_t result) {
     qDebug() << "Authentication result: " << result;

    if(result) {
        SendRespAuthToDev(CommonResult_Success);
        emit DevReqAuth(devSocket->socketDescriptor(), devImei, devType);
        emit VehicleStatusSignal(devImei, devType, VEHICLE_STATUS_CONNECTED);
        qDebug() << "ReqAuth , IMEI:" << devImei.c_str() << " Type:" << devType << " , and emit [connected]";
    } else {
        SendRespAuthToDev(CommonResult_Fail);
    }

    delayTimer.start();
}


void DevHandle::HandleCommAck(const uint8_t *data, int dataLen)
{
    CommAck ack;
    std::memmove(&ack, data, dataLen);
    qDebug("Get Device[%s] CommAck,ack cmdId[%04x]\n", devImei.c_str(), ack.cmdId);
}

//void DevHandle::HandleReportCan(const uint8_t *data, int dataLen)
//{
//    QByteArray canDataByte(reinterpret_cast<const char *>(data), dataLen);
//    emit VehicleRawDataSignal(canDataByte);
//}

void DevHandle::HandleReportFeedbackData(const uint8_t *data, int dataLen) {
    QByteArray FeedbackDataByte(reinterpret_cast<const char *>(data), dataLen);
    emit VehicleRawDataSignal(FeedbackDataByte);
}

void DevHandle::CheckCanFailed(int pkgCount)
{
    if (pkgCount != 0)
    {
        if (canLostCounter != 0)
        {
            qDebug() << "Device[" << devImei.c_str() << "],Get Can pkg is not zero. and Emit [connected]";
            emit VehicleStatusSignal(devImei, devType, VEHICLE_STATUS_CONNECTED);
        }
        canLostCounter = 0;
    }
    else
    {
        canLostCounter++;
        if (canLostCounter >= CAN_LOST_MAX_COUNTER)
        {
            qDebug() << "Device[" << devImei.c_str() << "],lost Can pkg . and Emit [no can]";
            emit VehicleStatusSignal(devImei, devType, VEHICLE_STATUS_NO_CAN);
        }
    }
}

void DevHandle::HandleDelayCmd(const uint8_t *data, int )
{
    auto tmpMsg = TGMsg::GetMsgFrame(data);
    auto msgT = tmpMsg->msg_as_Pong();
//    qDebug() << "timestamps:" << msgT->timestamps();
    uint32_t t2 = GetCurTimeMs();
    uint32_t t1 = msgT->timestamps();
    uint32_t delayTime = (t2 - t1) / 2 * 1000;
    emit VehicleDelaySignal(devImei, delayTime);
//    qDebug() << "Get Resp Delay Cmd,t1:" << t1 << " t2:" << t2 << " Ping:" << delayTime;
}

void DevHandle::HandleRespControlCmd(const uint8_t *data, int )
{
    reqControlCmdTimer.stop();
    auto tmpMsg = TGMsg::GetMsgFrame(data);
    auto msgT = tmpMsg->msg_as_Vehicle_ResponCtrlCmd();
    qDebug() << "cmd:" << msgT->cmd() << "result:" << msgT->result();

    int result = RESP_REMOTE_CONTROL_VEHICLE_REJECT;
    if (msgT->result() == RcdControlCmdResult_Accept)
    {
        result = RESP_REMOTE_CONTROL_VEHICLE_RECV;
    }
    int cmd = msgT->cmd();
    emit ReqControlCmdResult(devImei, cmd, result, taskId);
}

void DevHandle::HandleReportHmiMsg(const uint8_t *data, int len)
{
    QByteArray body(reinterpret_cast<const char *>(data), len);
    emit VehicleReportHmiMsgSignal(devImei, len, body);
}

void DevHandle::HandleReportHmiHintMsg(const uint8_t *data, int len)
{
//    auto tmpMsg = TGMsg::GetMsgFrame(data);
//    auto msgT = tmpMsg->msg_as_Vehicle_ReportHmiHintMsg();

//    std::string a(reinterpret_cast<const char *>(msgT->msg()->Data()), msgT->msg()->size());
//    qDebug() << a.data();

    QByteArray body(reinterpret_cast<const char *>(data), len);
    emit VehicleReportHmiHintMsgSignal(devImei, len, body);
}

void DevHandle::HandleReportTrackLineMsg(const uint8_t *data, int len) {
    QByteArray body(reinterpret_cast<const char *>(data), len);
    emit VehicleReportTrackLineMsgSignal(devImei, len, body);
}

void DevHandle::HandleReportSpeedWarningMsg(const uint8_t *data, int len) {
    QByteArray body(reinterpret_cast<const char *>(data), len);
    emit VehicleReportSpeedWarningMsgSignal(devImei, len, body);
}

void DevHandle::HandleReportRoadTaskInfo(const uint8_t *data, int len) {
    QByteArray body(reinterpret_cast<const char *>(data), len);
    emit VehicleReportRoadTaskInfoSignal(devImei, len, body);
}

void DevHandle::HandleSendSafeDecelerate(const uint8_t *data, int ) {
    auto tmpMsg = TGMsg::GetMsgFrame(data);
    auto msgT = tmpMsg->msg_as_Vehicle_SendSafeDecelerate();

    emit VehicleSendSafeDecelerateSignal(msgT->action());
}

void DevHandle::HandleReportGnssMsg(const uint8_t *data, int len)
{
    QByteArray body(reinterpret_cast<const char *>(data), len);
    emit VehicleReportGnssMsgSignal(devImei, len, body);
}

void DevHandle::SendDataToDev(const uint8_t *data, int dataLen)
{
    devSocket->write(reinterpret_cast<const char *>(data), dataLen);
}

void DevHandle::SendRespAuthToDev(uint8_t result)
{
    flatbuffers::FlatBufferBuilder fbb;

    uint64_t curTimeUs = GetSysTimeMs();
    fbb.FinishSizePrefixed(
                TGMsg::CreateMsgFrame(
                    fbb, curTimeUs,
                    TGMsg::MsgUnion_Rcd_ResponVehicleAuth,
                    Rcd::CreateResponVehicleAuth(fbb, fbb.CreateString(devImei.c_str(), devImei.size()),
                                                 result ? CommonResult_Success : CommonResult_Fail).Union()));

    SendDataToDev(fbb.GetBufferPointer(), fbb.GetSize());
    qDebug("Resp Auth to Device[%s],result:%d\n", devImei.c_str(), result);
}

void DevHandle::SendReqDelayToDev()
{
    flatbuffers::FlatBufferBuilder fbb;

    uint64_t curTimeUs = GetCurTimeMs();

    fbb.FinishSizePrefixed(TGMsg::CreateMsgFrame(fbb, curTimeUs, TGMsg::MsgUnion_Ping, CreatePing(fbb, curTimeUs).Union()));

    SendDataToDev(fbb.GetBufferPointer(), fbb.GetSize());
//    qDebug() << "Req delay cmd:" << curTimeUs;
}

uint32_t DevHandle::GetCurTimeMs()
{
    auto curTimePoint = std::chrono::steady_clock::now();
    auto timeMsTp = std::chrono::time_point_cast<std::chrono::milliseconds>(curTimePoint);
    return timeMsTp.time_since_epoch().count();
}

uint64_t DevHandle::GetSysTimeMs() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

void DevHandle::ReadDataFromDev()
{
    while (true)
    {
        char data[2048] = {0x00};

        // 必须先有完整的 4 字节长度前缀，否则不要消费半个包头（避免粘包错位）
        if (devSocket->bytesAvailable() < 4) {
            return;
        }

        // 先窥探长度前缀但不取走，等整帧到齐再读
        char header[4] = {0x00};
        if (devSocket->peek(header, 4) < 4) {
            return;
        }
        uint32_t bodySize = flatbuffers::ReadScalar<flatbuffers::uoffset_t>(header);

        // 关键防护：bodySize 来自网络，连到错误 IP/端口时可能是垃圾大值，
        // 直接 read 到 2048 的栈数组会造成栈溢出崩溃。这里做边界校验。
        if (bodySize == 0 || bodySize > sizeof(data) - 4) {
            qWarning() << "invalid frame size:" << bodySize
                       << ", abort connection. Imei:" << devImei.c_str();
            devSocket->abort();
            return;
        }

        // 整帧（4 字节前缀 + bodySize）未到齐则等待下次 readyRead
        if (devSocket->bytesAvailable() < static_cast<qint64>(4 + bodySize)) {
            return;
        }

        // 一次性取走前缀 + 包体
        if (devSocket->read(data, 4 + bodySize) < static_cast<qint64>(4 + bodySize)) {
            qDebug() << "message body is not the expected length";
            return;
        }

        flatbuffers::Verifier verifer(reinterpret_cast<const uint8_t *>(data), bodySize + 4);

        if(TGMsg::VerifySizePrefixedMsgFrameBuffer(verifer)) {
            HandleMsg(reinterpret_cast<const uint8_t *>(data + 4), bodySize);
        } else {
            qDebug() << "flatbuffer verify failed, abort connection";
            devSocket->abort();
            return;
        }
    }
}

void DevHandle::DevDisConnected()
{
    qDebug() << "DevDisConnected: " << socketDesc << " ,Imei:" << devImei.c_str();
    if (!devImei.empty())
    {
        emit VehicleStatusSignal(devImei, devType, VEHICLE_STATUS_DISCONNECTED);
    }
    emit Disconnected(socketDesc);
}

void DevHandle::HeartTimeOutSlots()
{
    qDebug() << "HeartTimer out";
    qWarning() << "Device[" << devImei.c_str() << "] lost heart. close tcp";
    devSocket->close();
}

void DevHandle::ControlCmdTimeOutSlots()
{
    qDebug() << "ControlCmdTimer out";
    qWarning() << "Device[" << devImei.c_str() << "] Recv Resp ControlCmd TimeOut.";
    emit ReqControlCmdResult(devImei, REQ_REMOTE_CONTROL_UNKNOWN, RESP_REMOTE_CONTROL_VEHICLE_TIMEOUT, taskId);
}

void DevHandle::DelayCmdTimeOutSlots()
{
    SendReqDelayToDev();
}

void DevHandle::HandleReqControlCmdSlot(const std::string &imei, uint8_t opt)
{
    qDebug() << "Send ReqControl start";
    if (!devImei.empty() && !imei.empty() && (devImei.compare(imei) == 0))
    {
        SendReqControlCmdToDev(opt);
    }
}

void DevHandle::HandleReqSendHmiMsgCmdSlot(const std::string &imei,const QByteArray &data)
{
    qDebug() << "Send ReqSendHmiMsg start";
    if (!devImei.empty() && !imei.empty() && (devImei.compare(imei) == 0))
    {
        SendReqSendHmiMsgToDev(reinterpret_cast<const uint8_t *>(data.data()), data.size());
    }
}

void DevHandle::HandleReqTrackLineMsgSlot(const std::string &imei,const QByteArray &)
{
    qDebug() << "Send ReqTrackLine start";
    if (!devImei.empty() && !imei.empty() && (devImei.compare(imei) == 0))
    {
        flatbuffers::FlatBufferBuilder fbb;

        uint64_t curTimeUs = GetSysTimeMs();

        fbb.FinishSizePrefixed(TGMsg::CreateMsgFrame(fbb, curTimeUs, TGMsg::MsgUnion_Vehicle_TrackLineConfigMsg,
                                                     Vehicle::CreateTrackLineConfigMsg(fbb).Union()));

        SendDataToDev(fbb.GetBufferPointer(), fbb.GetSize());
    }
}

void DevHandle::HandleRemoteEstop(uint8_t estop)
{
    qDebug() << "Send Remote Estop";

    flatbuffers::FlatBufferBuilder fbb;

    uint64_t curTimeUs = GetCurTimeMs();

    fbb.FinishSizePrefixed(TGMsg::CreateMsgFrame(fbb, curTimeUs, TGMsg::MsgUnion_Rcd_SendRemoteEstop,
                                                 Rcd::CreateSendRemoteEstop(fbb, estop).Union()));

    SendDataToDev(fbb.GetBufferPointer(), fbb.GetSize());

}

void DevHandle::HandleControlData(const QByteArray &data)
{
    qDebug() << "Send ControlData to Dev ";
    SendControlDataToDev(reinterpret_cast<const uint8_t *>(data.data()), data.size());
}

void DevHandle::HandleTaskStop(uint16_t taskId) {
    qDebug() << "Send TaskStop to Dev ";
    SendTaskStopToDev(taskId);
}
