#ifndef DEVHANDLE_H
#define DEVHANDLE_H

#include "include/rcdmsg.hpp"
#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <string>

#define GATEWAY_HEART_TIMEOUT_MS (2000)
#define REQ_CONTROL_CMD_TIEMOUT_MS (2000)
#define REQ_DELAY_CMD_TIMEOUT_MS (1000)

#define CAN_LOST_MAX_COUNTER 5

class DevHandle : public QObject
{
    Q_OBJECT
public:
    explicit DevHandle(QObject *parent = nullptr, QTcpSocket *socket = nullptr);
    virtual ~DevHandle();

private:
    void HandleMsg(const uint8_t *data, int dataLen);
    void HandleAuth(const uint8_t *data, int dataLen);
    void HandleCommAck(const uint8_t *data, int dataLen);
//    void HandleReportCan(const uint8_t *data, int dataLen);
    void CheckCanFailed(int pkgCount);
    void HandleDelayCmd(const uint8_t *data, int dataLen);
    void HandleRespControlCmd(const uint8_t *data, int dataLen);
    void HandleReportHmiMsg(const uint8_t *data, int dataLen);
    void HandleReportHmiHintMsg(const uint8_t *data, int dataLen);
    void HandleReportGnssMsg(const uint8_t *data, int dataLen);
    void HandleReportFeedbackData(const uint8_t *data, int dataLen);
    void HandleReportTrackLineMsg(const uint8_t *data, int dataLen);
    void HandleReportRoadTaskInfo(const uint8_t *data, int dataLen);
    void HandleSendSafeDecelerate(const uint8_t *data, int dataLen);
    void HandleReportSpeedWarningMsg(const uint8_t *data, int dataLen);

    void SendReqControlCmdToDev(uint8_t opt);
    void SendReqSendHmiMsgToDev(const uint8_t *data, int dataLen);
    void SendControlDataToDev(const uint8_t *data, int dataLen);
    void SendDataToDev(const uint8_t *data, int dataLen);
    void SendRespAuthToDev(uint8_t result);
    void SendReqDelayToDev();
    void SendTaskStopToDev(uint16_t taskId);

    inline uint32_t GetCurTimeMs(); //the time interval will not change due to system time
    inline uint64_t GetSysTimeMs(); //the absolute time point

signals:
    void Disconnected(qintptr socketDesc);
    void DevReqAuth(qintptr socketDesc, const std::string &imei, int type);
    void ReqControlCmdResult(const std::string &imei, int cmd, int result, uint16_t taskId);
    void VehicleStatusSignal(const std::string &imei, int type, int status);
    void VehicleRawDataSignal(const QByteArray &rawData);
    void VehicleDelaySignal(const std::string &imei, uint32_t delayUs);
    void VehicleReportHmiMsgSignal(const std::string &imei, int len, QByteArray &body);
    void VehicleReportGnssMsgSignal(const std::string &imei, int len, QByteArray &body);
    void VehicleReportHmiHintMsgSignal(const std::string &imei, int len, QByteArray &body);
    void VehicleTaskAuthReq(const uint16_t taskId, std::string imei, std::string authkey);
    void VehicleReportTrackLineMsgSignal(const std::string &imei, int len, QByteArray &body);
    void VehicleReportRoadTaskInfoSignal(const std::string &imei, int len, QByteArray &body);
    void VehicleSendSafeDecelerateSignal(const uint8_t cation);
    void VehicleReportSpeedWarningMsgSignal(const std::string &imei, int len, QByteArray &body);

public slots:
    void ReadDataFromDev();
    void DevDisConnected();
    void HeartTimeOutSlots();
    void ControlCmdTimeOutSlots();
    void DelayCmdTimeOutSlots();
    void HandleReqControlCmdSlot(const std::string &imei, uint8_t opt);
    void HandleReqSendHmiMsgCmdSlot(const std::string &imei, const QByteArray &);
    void HandleReqTrackLineMsgSlot(const std::string &imei, const QByteArray &);
    void HandleControlData(const QByteArray &data);
    void HandleTaskAuthResp(uint8_t result);
    void HandleTaskStop(quint16 taskId);
    void HandleRemoteEstop(uint8_t estop);

private:
    QTcpSocket *devSocket = nullptr;
    std::string devImei;
    std::string secretKey;
    uint8_t devType = 0;
    uint16_t taskId;
    qintptr socketDesc;
    QTimer heartTimer;

    int canLostCounter = 0;
    QTimer reqControlCmdTimer;

    QTimer delayTimer;
};

#endif // DEVHANDLE_H
