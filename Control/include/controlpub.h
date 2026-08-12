#ifndef CONTROLPUB_H
#define CONTROLPUB_H

#include "zmq/zmqmsg.hpp"
#include "zmq/zmqwrap.hpp"
#include <QObject>
#include <QTimer>
#include <atomic>
#include <cstdint>

#define CONTROLDATA_PUB_TIME_MS 50
#define LINKSTATUS_PUB_TIME_MS 1000

class ControlPub : public QObject
{
    Q_OBJECT
public:
    explicit ControlPub(QObject *parent = nullptr);

signals:

public slots:
    void HandleFisonControlRawDataSlot(const QByteArray &data);
    void HandleFisonControlDataSlot(const QByteArray &data);
    void HandleFisonStatusSlot(quint8 _status);
    void HandleFisonButtonSlot(quint32 key);
    void HandleFisonControlLightSlot(const QByteArray &data);
    void HandleVehicleStatus(quint8 _status);

private slots:
    void HandlePubDataTimerOut();
    void HandlePubStatusTimerOut();
    void HandlePubSelfCheckTimerOut();

private:
    ZmqPublisher pubObj;
    QTimer pubDataTimer;
    QTimer pubStatusTimer;
    QTimer pubSelfCheckTimer;

    ControlData cacheControlData;
    std::atomic_flag controlDataFlag = ATOMIC_FLAG_INIT;

    ControlDevLinkStatus status;
    std::atomic_flag linkStatusFlag = ATOMIC_FLAG_INIT;

    ControlLight lightData;
    std::atomic_flag controlLightFlag = ATOMIC_FLAG_INIT;  
};

#endif // CONTROLPUB_H
