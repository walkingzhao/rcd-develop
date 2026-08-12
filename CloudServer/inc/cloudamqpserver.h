#ifndef CLOUDAMQPSERVER_H
#define CLOUDAMQPSERVER_H

#include <QObject>
#include <QTimer>
#include <unordered_set>
#include <mutex>

#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "zmq/zmqmsg.hpp"
#include "zmq/zmqwrap.hpp"
#include "queueMsg.hpp"


//#define AMQP_HOST                       "192.168.30.165"
//#define AMQP_PORT                       5672
//#define AMQP_USRNAME                    "admin"
//#define AMQP_PASSWORD                   "admin"
#define AMQP_REPORT_EXCHANGE_NAME       "cabin_platform_exchange"
#define AMQP_REPORT_ROUTING_KEY_PREFIX  "cts.cabin.report."
#define AMQP_CONTROL_ROUTING_KEY_PREFIX "cts.cabin.control."
#define AMQP_ISSUED_EXCHANGE_NAME       "cts_cabin_issued_exchange"
#define QMQP_ISSUED_ROUTING_KEY_PREFIX  "cabin."

#define DOWNLOAD_MAP_PATH               "download/map"
#define DOWNLOAD_TASK_PATH              "download/task"

#define KEYPATH_MQ_GROUP "RabbitMQ"
#define KEYPATH_MQ_ADDR "addr"
#define KEYPATH_MQ_PORT "port"
#define KEYPATH_MQ_USERNAME "username"
#define KEYPATH_MQ_PASSWORD "password"

#define KEYPATH_RCD_GROUP "Host"
#define KEYPATH_RCD_IP "ip"
#define KEYPATH_RCD_MAC "mac"


class cloudAmqpServer : public QObject
{
    Q_OBJECT
public:
    explicit cloudAmqpServer(QObject *parent = nullptr);
    virtual ~cloudAmqpServer();
    void run();


signals:

private:
    void initZmq();
    void cloudMsgHandle(const uint8_t *buf, int len);
    void sendCabinLoginReq(void);
//    void sendCabinLogoutReq(void);
    void sendDriverLoginReq(void);
    void sendDriverLogoutReq(void);
    void sendCabinStatus(void);

    void reConnectionIssuedChannle();
    void reConnectionReportChannle();

    void ReportMsgLoopThread();

    bool reportCloudMsg(const uint8_t *data, int len, QueueMsgType msgType); // 0: Periodic data, 1: Business data
    void HandleZmqControlData(const std::string &topic, const void *data, int len);
    void HandleZmqRcdStatus(const std::string &topic, const void *data, int len);
    void HandleZmqRespRemoteControl(const std::string &topic, const void *data, int len);
    void HandleZmqTakeoverTaskGiveUp(const std::string &topic, const void *data, int len);
    void HandleZmqTakeoverTaskReq(const std::string &topic, const void *data, int len);
    void HandleZmqTakeoverTaskReply(const std::string &topic, const void *data, int len);
    void HandleZmqTakeoverTaskEnd(const std::string &topic, const void *data, int len);
    void HandleZmqIcCardStatus(const std::string &topic, const void *data, int len);
    void HandleZmqFastStopReq(const std::string &topic, const void *data, int len);
    void HandleZmqTakeoverTaskFail(const std::string &topic, const void *data, int len);
    void HandleZmqTakeoverTaskOperate(const std::string &topic, const void *data, int len);

    bool downloadFileDeal(const char *url, const char *md5, const char *filepath, const char *finalname = nullptr);
    bool fileDownload(const char *filename, const char *url, int retries = 3);
    bool fileCompareMd5(const char *filename, const char *md5);
    bool fileHandle(const char *filename, const char *filepath, const char *finalname);

    uint64_t GetMs();
    std::string getMac();
    std::string getIP();


private:
    AmqpClient::Channel::ptr_t report_connection = nullptr; //发送
    AmqpClient::Channel::ptr_t issued_connection = nullptr; //接收
    ZmqSubscriber cloudSub;
    ZmqPublisher *cloudPub = nullptr;
    std::string amqpQueueName;
    std::string amqpReportRoutingKey; // periodically report
    std::string amqpControlRoutingKey; //interact with the platform
    std::string amqpIssuedRoutingKey;
    std::unordered_set<std::string> msgIdList;
    std::string mac;
    std::string ip;
    std::mutex reportMutex;

    AmqpClient::Channel::OpenOpts opts;
    QueueMsg queueMsg;
    std::string consumer_tag;

};

#endif // CLOUDAMQPSERVER_H
