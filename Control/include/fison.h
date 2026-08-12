#ifndef FEISHI_H
#define FEISHI_H

#include "zmq/zmqmsg.hpp"
#include "zmq/zmqwrap.hpp"
#include <QByteArray>
#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class fison : public QObject
{
    Q_OBJECT
public:
    explicit fison(QObject *parent = nullptr);
    virtual ~fison() = default;
    void StartRun();

signals:
    void EmitControlRawData(const QByteArray &data);
    void EmitControlData(const QByteArray &data);
    void EmitStatus(quint8 status);
    void EmitButton(quint32 dirKey);
    void EmitControlLight(const QByteArray &data);
    void EmitVehicleStatus(quint8 status);

private slots:
    void HandleSocketConnected();
    void HandleSocketDisconnected();
    void HandleSocketReadyRead();
    void HandleSocketError(QAbstractSocket::SocketError socketError);
    void HandlePollTimerSlot();
    void HandleReconnectTimerSlot();

private:
    void ConnectToCabin();
    void ResetConnectionState(quint8 status);
    void SendReadRequest();
    void ParsePackets();
    bool HandlePacket(const QByteArray &packet);
    void PublishControlData(const QByteArray &packet);
    void PublishControlRawData(qint16 steering, quint8 throttle, quint8 brake);
    void HandleZmqVehicleStatus(std::string &topic, const void *data, int len);

private:
    QTcpSocket socket;
    QByteArray recvBuffer;
    ZmqSubscriber subObj;
    QTimer pollTimer;
    QTimer reconnectTimer;
    QString tcpHost = "192.168.101.10";
    quint16 tcpPort = 2000;
    int pollIntervalMs = 50;
    int reconnectIntervalMs = 1000;
    quint8 pollMessageId = 0;
    bool hasValidData = false;
    quint64 pollCountWithoutData = 0;
    bool lastA1TakeoverPressed = false;
    qint64 lastA1TakeoverEmitMs = 0;
};

#endif // FEISHI_H
