#ifndef IPCMANAGER
#define IPCMANAGER

#include "Interface/IController.h"
#include "../include/qtzmq.h"
#include "../../pubinc/version.h"
#include <QTimer>
#define ZMQ_ADDR_UI_L "ipc://@UILPub"
#define ZMQ_ADDR_UI_R "ipc://@UIRPub"
#define ZMQ_ADDR_UI_M "ipc://@UIMPub"

#define ZMQ_TOPIC_PROC_LEFT "ProcessLeft"
#define ZMQ_TOPIC_PROC_MID  "ProcessMid"
#define ZMQ_TOPIC_PROC_RIGHT "ProcessRight"

// 进程通讯管理器，使用ZMQ进行进程通信
class IpcManager : public IController
{
     Q_OBJECT
public:
    explicit IpcManager(QObject *parent = nullptr);
    ~IpcManager();

    static IpcManager *GetInstance(QObject *parent = nullptr);

    static void ctrlDataHandler(const std::string &topic, const void *data, int len);
    static void controlDevlinkStatus(const std::string &topic, const void *data, int len);//在线状态
    static void controlSelfCheckStatus(const std::string &topic, const void *data, int len);
    static void ctrlStatusHandler(const std::string &topic, const void *data, int len);
    static void ctrlButtonHandler(const std::string &topic, const void *data, int len);
    static void ctrlRawDataHandler(const std::string &topic, const void *data, int len);
    static void vehicleRawDataHandler(const std::string &topic, const void *data, int len);
    static void updateTrackLineConfigHandler(const std::string &topic, const void *data, int len);
    static void updateCCUTaskStatusHandler(const std::string &topic, const void *data, int len);
    static void speedWarningHandler(const std::string &topic, const void *data, int len);


    static void vehicleStatusHandler(const std::string &topic, const void *data, int len);
    static void vehicleDelayHandler(const std::string &topic, const void *data, int len);
    static void respRemotelHandler(const std::string &topic, const void *data, int len);
    static void safeDecelerationHandler(const std::string &topic, const void *data, int len);
    static void vehicleGpsHandler(const std::string &topic, const void *data, int len);


    static void respHmiHintmsgHandler(const std::string &topic, const void *data, int len);
    static void forwardHandler(const std::string &topic, const void *data, int len);
    static void CloudData(const std::string &topic,const /*uint8_t*/void *buf,int len);//cloudServer

    void ipcForward(ProcessType type,ModuleDir &moduleDir, int &cmd, QVariant &data);
    void getFromAny(ModuleDir moduleDir, int cmd, QVariant data) override;
public slots:
    void modeTimeOut();

private:

    static IpcManager       *s_pInstance;

    ZmqSubscriber           *m_pSubControl;
    ZmqSubscriber           *m_pSubGateway;

    ZmqPublisher            *m_pPubUI;
    ZmqSubscriber           *m_pSubCloudServer;//pingtaishuju
    ZmqPublisher            *m_pPubUIL;
    ZmqPublisher            *m_pPubUIR;
    ZmqPublisher            *m_pPubUIM;
    ZmqSubscriber           *m_pSubUIL;
    ZmqSubscriber           *m_pSubUIR;
    ZmqSubscriber           *m_pSubUIM;

    QTimer  *modeTimer;

};

#endif // IPCMANAGER


