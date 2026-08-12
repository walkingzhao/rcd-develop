#ifndef GATEWAYSERVER_H
#define GATEWAYSERVER_H

#include "devhandle.h"
#include "devmanage.h"
#include "zmq/zmqwrap.hpp"
#include <QByteArray>
#include <QObject>
#include <QTcpServer>
#include <string>
#include <QMutex>

typedef struct {
    uint16_t taskId;
    std::string imei;
    std::string authKey;
} taskInfo;

class GateWayServer : public QObject
{
    Q_OBJECT
public:
    explicit GateWayServer(QObject *parent = nullptr);
    ~GateWayServer();
    void Start();

public slots:
    void HandleNewConnect();
    void HandleDevDisConnected(qintptr socketDesc);
    void HandleDevReqAuth(qintptr socketDesc, const std::string &imei, int type);
    void HandleReqControlCmdResult(const std::string &imei, int cmd, int result, uint16_t taskId);
    void HandleVehicleStatus(const std::string &imei, int type, int status);
    void HandleVehicleRawData(const QByteArray &rawData);
    void HandleVehicleDelay(const std::string &imei, uint32_t delayUs);
    void HandleVehicleReportHmiMsg(const std::string &imei, int len, QByteArray &body);
    void HandleVehicleReportGnssMsg(const std::string &imei, int len, QByteArray &body);
    void HandleVehicleReportHmiHintMsg(const std::string &imei, int len, QByteArray &body);
    void HandleVehicleTaskAuthReq(const uint16_t taskId, std::string imei, std::string authkey);
    void HandleVehicleReportTrackLineMsg(const std::string &imei, int len, QByteArray &body);
    void HandleVehicleReportRoadTaskInfo(const std::string &imei, int len, QByteArray &body);
    void HandleVehicleSendSafeDecelerate(const uint8_t action);
    void HandleVehicleReportSpeedWarningMsg(const std::string &imei, int len, QByteArray &body);

signals:
    void EmitReqControlCmdSignal(const std::string &imei, uint8_t opt);
    void EmitReqSendHmiMsgCmdSignal(const std::string &imei, const QByteArray &data);
    void EmitControlData(const QByteArray &data);
//    void EmitSecretKey(const std::string &secretKey);
    void EmitTaskCancel(const QByteArray &data);
    void EmitTaskStop(quint16 taskId);
    void EmitTaskAuthResp(uint8_t result);
    void EmitReqTrackLineMsgSignal(const std::string &imei, const QByteArray &data);
    void EmitRemoteEstop(uint8_t estop);

private:
    void HandleZmqReqRemoteControl(const std::string &topic, const void *data, int len);
    void HandleZmqReqSendHmiMsg(const std::string &topic, const void *data, int len);
    void HandleZmqControlData(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskAuthInfo(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskCancelMsg(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskEndMsg(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskReplyMsg(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskGiveupMsg(const std::string &topic, const void *data, int len);
    void HandleZmqReqTrackLineMsg(const std::string &topic, const void *data, int len);
    void HandleZmqRemoteEstopMsg(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskFailMsg(const std::string &topic, const void *data, int len);
    void HandleZmqCloudTaskOperate(const std::string &topic, const void *data, int len);
    void HandleZmqReqConnect(const std::string &, const void *data, int len);

    void InitNewClient(QTcpSocket *client);

public slots:
    void handleCheckConnectTimeOut();

private:
    std::shared_ptr<DevHandle> controlFastDev = nullptr;
    DevManage devM;
    ZmqSubscriber gatewaySub;
    ZmqPublisher *gatewayPub = nullptr;
    int lastReqControlCmd;
    //add task list for authentication with vehicle
    std::list<taskInfo> taskList;

    const int maxConnection = 1;

    QTcpSocket *m_tcpSocket = nullptr;
    bool m_bNeedConnect = false;
    QMutex m_mutex;
    QTimer  *m_checkConnectTimer = nullptr;
    QString m_strIP;
};

#endif // GATEWAYSERVER_H
