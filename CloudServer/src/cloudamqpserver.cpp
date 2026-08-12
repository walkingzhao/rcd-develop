#include "cloudamqpserver.h"
#include <QDebug>
#include <QProcess>
#include <curl/curl.h>
#include <flatbuffers/minireflect.h>
#include <QUrl>
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>
#include <QMetaObject>
#include <cstring>

#include "fbs/tgmsg_generated.h"

#include "download.hpp"
#include "zmq/zmqmsg.hpp"
#include "version.h"

static bool deviceLoginStatus = false;
static bool driverLoginStatus = false;
static bool taskStatus = false;



cloudAmqpServer::cloudAmqpServer(QObject *parent) : QObject(parent)
{
    initZmq();
    mac = getMac();
    if(mac.empty()) {
        qDebug() << "get mac failed";
        return;
    }

    ip = getIP();
    if(ip.empty()) {
        qDebug() << "get ip failed";
        return;
    }

    // get mq configuration information from the rcdconfig.ini file
    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += "/rcdconfig.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup(KEYPATH_MQ_GROUP);
    std::string addr = settings.value(KEYPATH_MQ_ADDR).toString().toStdString();
    int port = settings.value(KEYPATH_MQ_PORT).toInt();
    std::string username = settings.value(KEYPATH_MQ_USERNAME).toString().toStdString();
    std::string password = settings.value(KEYPATH_MQ_PASSWORD).toString().toStdString();
    qDebug() << addr.c_str() << ", " << port << ", " << username.c_str() << ", " << password.c_str();
    if(addr.empty() || port == 0 || username.empty() || password.empty()) {
        qDebug() << "get mq configuration information failed, exit!";
        exit(-1);
    }
    qDebug() << "addr:" << addr.data() << " port:" << port << " username:" << username.data() << " password:" << password.data();

    amqpQueueName = "MQ." + mac;
    amqpReportRoutingKey = AMQP_REPORT_ROUTING_KEY_PREFIX + mac;
    amqpControlRoutingKey = AMQP_CONTROL_ROUTING_KEY_PREFIX + mac;
    amqpIssuedRoutingKey = QMQP_ISSUED_ROUTING_KEY_PREFIX + mac + ".#";
    qDebug() << "queueName:" << amqpQueueName.data() << "reportRoutingKey:" << amqpReportRoutingKey.data()
             << "controlRoutingKey:" << amqpControlRoutingKey.data() << "issuedRoutingKey:" << amqpIssuedRoutingKey.data();
    try {
//        AmqpClient::Channel::OpenOpts opts;
        opts.host = addr;
        opts.port = port;
        opts.auth = AmqpClient::Channel::OpenOpts::BasicAuth(username, password);
        opts.heart_beat = 10;
        issued_connection = AmqpClient::Channel::Open(opts);
        report_connection = AmqpClient::Channel::Open(opts);

        issued_connection->DeclareQueue(amqpQueueName, false, true, false, false);
        issued_connection->BindQueue(amqpQueueName, AMQP_ISSUED_EXCHANGE_NAME, amqpIssuedRoutingKey);
        consumer_tag = issued_connection->BasicConsume(amqpQueueName, "", true, false);

        qDebug() << "connection!";
    } catch (const std::exception& e) {
        qDebug() << e.what();
        exit(-1);
    }

    //first to login cloud
    sendCabinLoginReq();

    std::thread reportLoopT([&]() {
        qDebug() << "ReportMsgLoop StartRun.";
        ReportMsgLoopThread();
    });
    reportLoopT.detach();
}

cloudAmqpServer::~cloudAmqpServer() {
    delete cloudPub;
}

void cloudAmqpServer::initZmq() {
    cloudPub = new ZmqPublisher(ZMQ_ADDR_CLOUDSERVER);
    cloudSub.ConnectTo(ZMQ_ADDR_CONTROL);
    cloudSub.ConnectTo(ZMQ_ADDR_Gateway);
    cloudSub.ConnectTo(ZMQ_ADDR_UI);
    // subscribe control data topic
    cloudSub.Subscribe(ZMQ_TOPIC_CONTROL_DATA,
                         std::bind(&cloudAmqpServer::HandleZmqControlData,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    // subscribe rcd status topic
    cloudSub.Subscribe(ZMQ_TOPIC_CONTROL_DEVLINKSTATUS,
                         std::bind(&cloudAmqpServer::HandleZmqRcdStatus,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    // subscribe rcd remote control response topic
    cloudSub.Subscribe(ZMQ_TOPIC_RESP_REMOTE_CONTROL,
                         std::bind(&cloudAmqpServer::HandleZmqRespRemoteControl,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    // subscribe ui taskover task give up topic
    cloudSub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_GEVE_UP,
                         std::bind(&cloudAmqpServer::HandleZmqTakeoverTaskGiveUp,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    // subscribe ui takeover task request topic
    cloudSub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_REQ,
                         std::bind(&cloudAmqpServer::HandleZmqTakeoverTaskReq,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    // subscribe ui takeover task reply topic
    cloudSub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_REPLY,
                         std::bind(&cloudAmqpServer::HandleZmqTakeoverTaskReply,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    // subscribe ui takeover task end topic
    cloudSub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_END,
                         std::bind(&cloudAmqpServer::HandleZmqTakeoverTaskEnd,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));

    cloudSub.Subscribe(ZMQ_TOPIC_IC_CARD_STATUS,
                         std::bind(&cloudAmqpServer::HandleZmqIcCardStatus,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));

    cloudSub.Subscribe(ZMQ_TOPIC_FAST_STOP_REQ,
                         std::bind(&cloudAmqpServer::HandleZmqFastStopReq,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));

    cloudSub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_FAIL,
                         std::bind(&cloudAmqpServer::HandleZmqTakeoverTaskFail,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));

    cloudSub.Subscribe(ZMQ_TOPIC_TAKEOVER_TASK_OPERATE,
                         std::bind(&cloudAmqpServer::HandleZmqTakeoverTaskOperate,
                                   this,
                                   std::placeholders::_1,
                                   std::placeholders::_2,
                                   std::placeholders::_3));
    sleep(3);  //防止zmq匹配不成功
}

void cloudAmqpServer::reConnectionIssuedChannle() {
    qDebug() << "reconnection issued channle";
    while(true) {
        try {
    //        issued_connection.reset();
            qDebug() << "issued_connection ptr use count: " << issued_connection.use_count();
            if(issued_connection.use_count() > 0) {
                issued_connection.reset();
            }
            issued_connection = AmqpClient::Channel::Open(opts);
            qDebug() << "issued_connection connection---";
            issued_connection->DeclareQueue(amqpQueueName, false, true, false, false);
            issued_connection->BindQueue(amqpQueueName, AMQP_ISSUED_EXCHANGE_NAME, amqpIssuedRoutingKey);
            consumer_tag = issued_connection->BasicConsume(amqpQueueName, "", true, false);
            qDebug() << "BasicConsume";
            return;
        } catch (const std::exception& e) {
            qDebug() << "reConnectionIssuedChannle:" << e.what();
            qDebug() << "something wrong about reconnection, try again after 5s";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }


}

// do not add
void cloudAmqpServer::reConnectionReportChannle() {
    qDebug() << "reconnection report channle";
    while(true) {
        try {
    //        report_connection.reset();
            qDebug() << "report_connection ptr use count: " << report_connection.use_count();
            if(report_connection.use_count() > 0) {
                report_connection.reset();
            }
            report_connection = AmqpClient::Channel::Open(opts);
            qDebug() << "issued_connection connection---";
            return;
        } catch (const std::exception& e) {
            qDebug() << "reConnectionReportChannle:" << e.what();
            qDebug() << "something wrong about reconnection, try again after 5s";
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

}

void cloudAmqpServer::run() {

    while (true) {
        try {
            AmqpClient::Envelope::ptr_t evelope = issued_connection->BasicConsumeMessage(consumer_tag);
            issued_connection->BasicAck(evelope);
            std::string exchangesName = evelope->Exchange();
            std::string routingKey = evelope->RoutingKey();
            std::string body = evelope->Message()->Body();
            std::string msgId = evelope->Message()->MessageId();
            qDebug() << "time:" << evelope->Message()->Timestamp()
                      << " exchangesName:" << exchangesName.data()
                      << " RoutingKey:" << routingKey.data()
                      << " MessageId:" << msgId.data()
                      << " msgIdListNums: " << msgIdList.size()
                      << " Body Size:" << body.size();

            if(msgIdList.find(msgId) == msgIdList.end()) {
                msgIdList.insert(msgId);
                cloudMsgHandle(reinterpret_cast<const uint8_t *>(body.data()), static_cast<int>(body.size()));
            } else {
                qDebug() << msgId.data() << ":de-duplication";
            }

        } catch (const std::exception& e) {
            qDebug() << "BasicConsumeMessage:" << e.what();
            reConnectionIssuedChannle();
            continue;
        }
    }
}

void cloudAmqpServer::cloudMsgHandle(const uint8_t *buf, int len) {
    auto tmpMsg = TGMsg::GetMsgFrame(buf);
    auto s = flatbuffers::FlatBufferToString(buf, TGMsg::MsgFrameTypeTable(), false, false);
    qDebug() << s.c_str();
    switch (tmpMsg->msg_type())
    {
    case TGMsg::MsgUnion_Platform_DeviceLoginResult: { //驾驶舱登陆结果
        auto msgT = tmpMsg->msg_as_Platform_DeviceLoginResult();
        qDebug() << "result: " << msgT->result();
        if(msgT->result() == CommonResult_Success) {
            //下载地图
            qDebug() << "device name: " << msgT->deviceName()->c_str()
                     << "md5: " << msgT->mapMd5()->c_str()
                     << "url: " << msgT->serverUrl()->c_str();

//            if(downloadFileDeal(msgT->serverUrl()->c_str(), msgT->mapMd5()->c_str(), DOWNLOAD_MAP_PATH, "HDMap.db")) {
//                deviceLoginStatus = true;
//                qDebug() << "download success";
//            }
            sendDriverLoginReq();
        } else {
            qDebug() << "cabin login failed, resend login request";
            msgIdList.clear();
            sendCabinLoginReq();
        }
        break;
    }
    case TGMsg::MsgUnion_Platform_DriverLoginResult: { //司机登陆结果
        auto msgT = tmpMsg->msg_as_Platform_DriverLoginResult();
        if(msgT->result() == CommonResult_Success) {     
            qDebug() << "driver name:" << msgT->driverName()->c_str() << "login success!";
            driverLoginStatus = true;

        } else {
            qDebug() << "driver login failed, resend login request!";
//            sendDriverLoginReq();
        }

        break;
    }
    case TGMsg::MsgUnion_Platform_DriverLogoutResult: { //司机登出结果
        auto msgT = tmpMsg->msg_as_Platform_DriverLogoutResult();
        if(msgT->result() == CommonResult_Success) {
            qDebug() << "logout success!";
            driverLoginStatus = false;
//            msgIdList.clear(); // clear all msgID
        } else {
            qDebug() << "logout failed!";
        }

        break;
    }
    case TGMsg::MsgUnion_Platform_CabinTakeoverTaskApply: { //平台下发接管任务
        auto msgT = tmpMsg->msg_as_Platform_CabinTakeoverTaskApply();
        qDebug() << "taskId: " << msgT->taskId()
                 << "truckImei: " << msgT->truckImei()->c_str()
                 << "truckName: " << msgT->truckName()->c_str()
                 << "secretkey: " << msgT->secretKey()->c_str()
                 << "takeoverPurpose" << msgT->takeoverPurpose();
        qDebug() << "dispatchTask:-> "
                 << "taskId: " << msgT->dispatchTask()->taskId()
                 << "targetName: " << msgT->dispatchTask()->targetName()->c_str()
                 << "fileUrl: " << msgT->dispatchTask()->fileUrl()->c_str()
                 << "fileMd5: " << msgT->dispatchTask()->fileMd5()->c_str();
//        if(msgT->dispatchTask()->taskId() == 0 ||
//                msgT->dispatchTask()->fileUrl()->str().empty() ||
//                downloadFileDeal(msgT->dispatchTask()->fileUrl()->c_str(), msgT->dispatchTask()->fileMd5()->c_str(),
//                            DOWNLOAD_TASK_PATH)) {
//            qDebug() << "download takeover task success!";
            qDebug() << "key size" << msgT->secretKey()->size();
            // send task info to gateway in order to authenticate with the vehicle
            cloudPub->Publish(ZMQ_TOPIC_CLOUD_SEND_TASK_AUTH_INFO, buf, len);
            taskStatus = true;
//        }
        break;
    }
    case TGMsg::MsgUnion_Platform_CabinTakeoverTargeChange: { //平台下发目的地变更
        auto msgT = tmpMsg->msg_as_Platform_CabinTakeoverTargeChange();
        qDebug() << "taskId: " << msgT->dispatchTask()->taskId()
                 << "targetName: " << msgT->dispatchTask()->targetName()->c_str()
                 << "fileUrl: " << msgT->dispatchTask()->fileUrl()->c_str()
                 << "fileMd5: " << msgT->dispatchTask()->fileMd5()->c_str();

//        if(msgT->dispatchTask()->taskId() == 0 ||
//                msgT->dispatchTask()->fileUrl()->str().empty() ||
//                downloadFileDeal(msgT->dispatchTask()->fileUrl()->c_str(), msgT->dispatchTask()->fileMd5()->c_str(),
//                            DOWNLOAD_TASK_PATH)) {
//            qDebug() << "download takeover task change success!";

//        }
        break;
    }
    case TGMsg::MsgUnion_Platform_TakeoverTaskCancel: { //接管任务取消指派
//        auto msgT = tmpMsg->msg_as_Platform_TakeoverTaskCancel();
//        TaskCancel taskCancel;
//        taskCancel.taskId = msgT->taskId();
//        qDebug() << "Cancel task taskId:" << taskCancel.taskId;
//        cloudPub->Publish(ZMQ_TOPIC_TAKEOVER_TASK_CANCEL, &taskCancel, sizeof(taskCancel));
        break;
    }
    default:
        break;
    }

    cloudPub->Publish(ZMQ_TOPIC_CLOUD_FBS_MSG, buf, len);
}

void cloudAmqpServer::ReportMsgLoopThread() {
    QueueMsgST msg;
    for (;;)
    {
        std::memset(&msg, 0x00, sizeof(QueueMsgST));
        if (queueMsg.popMsgFromQueue(msg))
        {
            qDebug() << "get msg";
           if(!reportCloudMsg(msg.msgData, msg.msgDataLen, msg.msgType)) {
               qDebug() << "re push message";
               queueMsg.pushMsgToQueue(msg);
           }
        } else {
            qDebug() << "queue is empty";
        }

    }
}

uint64_t cloudAmqpServer::GetMs()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

std::string cloudAmqpServer::getMac() {
    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += "/rcdconfig.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup(KEYPATH_RCD_GROUP);
    return settings.value(KEYPATH_RCD_MAC).toString().toStdString();
}

std::string cloudAmqpServer::getIP() {
    QString fileName;
    fileName = QCoreApplication::applicationDirPath();
    fileName += "/rcdconfig.ini";
    QSettings settings(fileName, QSettings::IniFormat);
    settings.beginGroup(KEYPATH_RCD_GROUP);
    return settings.value(KEYPATH_RCD_IP).toString().toStdString();
}

void cloudAmqpServer::sendCabinLoginReq() {
    flatbuffers::FlatBufferBuilder fbb;
    TGMsg::MsgFrameT tmpMsgFrame;

    tmpMsgFrame.timestamps = GetMs();

    Platform::DeviceLoginT deviceLoginInfo;
    deviceLoginInfo.cabinIp = ip;
    deviceLoginInfo.authCode = mac;
    deviceLoginInfo.version = DCU_VERSION;

    tmpMsgFrame.msg.Set(std::move(deviceLoginInfo));

    fbb.Clear();
    fbb.Finish(TGMsg::MsgFrame::Pack(fbb, &tmpMsgFrame));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::sendDriverLoginReq() {
    flatbuffers::FlatBufferBuilder fbb;
    TGMsg::MsgFrameT tmpMsgFrame;

    tmpMsgFrame.timestamps = GetMs();

    Platform::DriverLoginT driverLoginInfo;

    //TODO: 使用舱内读卡器进行读取
    driverLoginInfo.cardSn = "11111111";

    tmpMsgFrame.msg.Set(std::move(driverLoginInfo));

    fbb.Clear();
    fbb.Finish(TGMsg::MsgFrame::Pack(fbb, &tmpMsgFrame));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::sendDriverLogoutReq() {
    flatbuffers::FlatBufferBuilder fbb;
    TGMsg::MsgFrameT tmpMsgFrame;

    tmpMsgFrame.timestamps = GetMs();

    Platform::DriverLogoutT driverLogoutInfo;

    //TODO: 使用舱内读卡器进行读取
    driverLogoutInfo.cardSn = "111111";

    tmpMsgFrame.msg.Set(std::move(driverLogoutInfo));

    fbb.Clear();
    fbb.Finish(TGMsg::MsgFrame::Pack(fbb, &tmpMsgFrame));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::HandleZmqControlData(const std::string &, const void *data, int len) {
//    qDebug() << "report control data";
    if(taskStatus) {
        uint8_t *msg = const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(data));
        queueMsg.pushMsgToQueue(msg + 4, len, PeriodicPlatformMsgType);//delete fbs ferfix size
    }
}

void cloudAmqpServer::HandleZmqRcdStatus(const std::string &, const void *data, int len) {
    ControlDevLinkStatus tmpStatus;
    std::memset(&tmpStatus, 0x00, sizeof(ControlDevLinkStatus));
    std::memmove(&tmpStatus, data, len);

    flatbuffers::FlatBufferBuilder fbb;
    TGMsg::MsgFrameT tmpMsgFrame;

    tmpMsgFrame.timestamps = GetMs();

    Rcd::StatusT status;
    status.task = taskStatus;
    status.wheel = tmpStatus.wheel == DEV_LINKSTATUS_CONNECTED_DATA ? 0x01 : 0x00;
    status.io = tmpStatus.io == DEV_LINKSTATUS_CONNECTED_DATA ? 0x01 : 0x00;
    status.vehicle = tmpStatus.vehicle == VEHICLE_STATUS_CONNECTED ? 0x01 : 0x00;
    tmpMsgFrame.msg.Set(std::move(status));

    fbb.Clear();
    fbb.Finish(TGMsg::MsgFrame::Pack(fbb, &tmpMsgFrame));

    qDebug() << "report status----------------------";

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize(), PeriodicPlatformMsgType);
}

bool cloudAmqpServer::downloadFileDeal(const char *url, const char *md5, const char *filepath, const char *finalname) {
//    std::string path = filepath;
    if(finalname) {
        std::string realpath = std::string(filepath) + "/" + std::string(finalname);
        remove(realpath.data());
    }
    QUrl urlinfo(url);
    std::string filename = urlinfo.fileName().toStdString();

    if(filename.empty()) {
        qDebug() << "get download file " << filename.data() << " failed";
        return false;
    }
    if(!fileDownload(filename.data(), url)) {
        qDebug() << "download file " << filename.data() << " failed";
        return false;
    }
    if(!fileCompareMd5(filename.data(), md5)) {
        qDebug() << "md5 compare " << filename.data() << " failed";
        return false;
    }
    if(!fileHandle(filename.data(), filepath, finalname)) {
        qDebug() << "handle file " << filename.data() << " failed";
        return false;
    }
    //remove download file
    remove(filename.data());
    return true;

}

bool cloudAmqpServer::fileDownload(const char *filename, const char *url, int retries) {
    for(int i = 0; i < retries; i++) {
        DownloadFile download;
        if(!download.openSaveFile(filename)) {
            continue;
        }
        if(download.downloadFromUrl(url)) {
           return true;
        }
    }
    return false;
}

bool cloudAmqpServer::fileCompareMd5(const char *filename, const char *md5) {
    QFileInfo fi(filename);
    if(fi.exists()) {
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray arr = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
        file.close();
        if(strncmp(arr.toHex().constData(), md5, 32) == 0) {
            return true;
        }
    }
    return false;
}

bool cloudAmqpServer::fileHandle(const char *filename, const char *filepath, const char *finalname) {

    qDebug() << filepath << ", " << filename << ", " << finalname;
    QDir dir(filepath);
    if(!dir.exists()) {
        qDebug() << "not exist";
        if(!dir.mkdir(filepath)) {
            qDebug() << "mkdir faild";
            return false;
        }
    }
    std::string cmd = std::string("tar -zxf ") + filename + " -C " + filepath + "/";
    if(system(cmd.data()) == -1) return false;
    qDebug() << "cmd: " << cmd.data();
    const char *p = strstr(filename, ".tar.gz");
    if(finalname != nullptr && p) {
        cmd.clear();
        char realfilename[100] = {0};
        memcpy(realfilename, filename, p - filename);
        cmd = std::string("mv ") + filepath + "/" + realfilename +  " " + filepath + "/" + finalname;
        if(system(cmd.data()) == -1) return false;
        qDebug() << "cmd: " << cmd.data();
    }
    return true;
}

void cloudAmqpServer::HandleZmqRespRemoteControl(const std::string &, const void *data, int len) {
    RespRemoteControl resp;
    std::memmove(&resp, data, len);

    qDebug() << "remote control resp " << "imei: " << reinterpret_cast<char *>(resp.imei)
             << "cmd:" << static_cast<uint32_t>(resp.cmd)
             << "result:" << static_cast<uint32_t>(resp.result)
             << " taskid: " << resp.taskId;
    if(resp.cmd == RcdControlCmd_Finish &&  resp.result == RcdControlCmdResult_Accept) {

        flatbuffers::FlatBufferBuilder fbb;
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                         TGMsg::MsgUnion_Platform_TakeoverTaskEnd,
                                         Platform::CreateTakeoverTaskEnd(fbb, resp.taskId, TaskEndReason_Normal).Union()));

        queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
        qDebug() << "report task end";
    }else if(resp.cmd == RcdControlCmd_Start && resp.result != RcdControlCmdResult_Accept) {
        flatbuffers::FlatBufferBuilder fbb;
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                          TGMsg::MsgUnion_Platform_TakeoverTaskFail,
                                          Platform::CreateTakeoverTaskFail(fbb, resp.taskId).Union()));

        queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
        qDebug() << "report task fail";
    }

}

void cloudAmqpServer::HandleZmqTakeoverTaskGiveUp(const std::string &, const void *data, int len) {
    msgIdList.clear(); // clear all msgID

    TaskGiveUp taskGiveup;
    std::memmove(&taskGiveup, data, len);
    qDebug("get giveup taskId: %04x", taskGiveup.taskId);
    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                      TGMsg::MsgUnion_Platform_TakeoverTaskGiveUp,
                                      Platform::CreateTakeoverTaskFail(fbb, taskGiveup.taskId).Union()));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());

}

bool cloudAmqpServer::reportCloudMsg(const uint8_t *data, int len, QueueMsgType msgType) {
    try {
        qDebug() << "call reportCloudMsg";
        AmqpClient::BasicMessage::ptr_t message = AmqpClient::BasicMessage::Create(std::string(data, data + len));
        message->Timestamp(std::chrono::system_clock::now().time_since_epoch().count());
        message->MessageId(std::to_string(GetMs()) + "-" + mac);
        if(msgType == PeriodicPlatformMsgType) {
            report_connection->BasicPublish(AMQP_REPORT_EXCHANGE_NAME, amqpReportRoutingKey, message);
            qDebug() << "report PeriodicPlatformMsgType";
        } else if(msgType == BusinessPlatformMsgType) {
            report_connection->BasicPublish(AMQP_REPORT_EXCHANGE_NAME, amqpControlRoutingKey, message);
            qDebug() << "report BusinessPlatformMsgType";
        } else {
            qDebug() << "what the fucking message?";
        }
    } catch(const std::exception& e) {
        qDebug() << "BasicPublish:" << e.what();
        reConnectionReportChannle();
        return false;
    }

    return true;
}

void cloudAmqpServer::HandleZmqTakeoverTaskReq(const std::string &, const void *data, int len) {
    TaskReq taskReq;
    std::memmove(&taskReq, data, len);
    std::string imei(reinterpret_cast<char *>(taskReq.imei), IMEI_LENGTH);
    qDebug() << "get Req imei:" << imei.c_str();
    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                      TGMsg::MsgUnion_Platform_CabinTakeoverTaskRequest,
                                      Platform::CreateCabinTakeoverTaskRequest(fbb,
                                                fbb.CreateString(reinterpret_cast<const char *>(taskReq.imei), sizeof(taskReq.imei)),
                                                TakeoverPurpose_AutonomousDriving).Union()));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::HandleZmqTakeoverTaskReply(const std::string &, const void *data, int len) {
    TaskReply taskReply;
    std::memmove(&taskReply, data, len);
    qDebug("Get task reply taskId:%04x, result %d, reason %s", taskReply.taskId, taskReply.result, taskReply.refuseReason);
    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                     TGMsg::MsgUnion_Platform_CabinTakeoverTaskReply,
                                     Platform::CreateCabinTakeoverTaskReply(fbb,
                                                taskReply.taskId,
                                                static_cast<CommonResult>(taskReply.result),
                                                fbb.CreateString(reinterpret_cast<char *>(taskReply.refuseReason))).Union()));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::HandleZmqTakeoverTaskEnd(const std::string &, const void *data, int len) {
    msgIdList.clear(); // clear all msgID

    TaskEnd taskend;
    std::memmove(&taskend, data, len);
    qDebug("Get task end taskId:%04x, reason:%04x", taskend.taskId, taskend.reason);
    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                     TGMsg::MsgUnion_Platform_TakeoverTaskEnd,
                                     Platform::CreateTakeoverTaskEnd(fbb, taskend.taskId, static_cast<TaskEndReason>(taskend.reason)).Union()));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::HandleZmqIcCardStatus(const std::string &, const void *data, int len) {
    IcCardStatus cardStatus;
    std::memmove(&cardStatus, data, len);

    flatbuffers::FlatBufferBuilder fbb;

    char buf[9] = {0};
    memmove(buf, cardStatus.CardSn, sizeof(cardStatus.CardSn));
    qDebug() << "card status:" << cardStatus.status << "sn:" << buf;

    if(cardStatus.status) {
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                         TGMsg::MsgUnion_Platform_DriverLogin,
                                         Platform::CreateDriverLogin(fbb,
                                                    fbb.CreateString(reinterpret_cast<const char *>(cardStatus.CardSn), sizeof(cardStatus.CardSn))
                                                                     ).Union()));
    } else {
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                         TGMsg::MsgUnion_Platform_DriverLogout,
                                         Platform::CreateDriverLogout(fbb,
                                                    fbb.CreateString(reinterpret_cast<const char *>(cardStatus.CardSn), sizeof(cardStatus.CardSn))
                                                                     ).Union()));
    }
    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
    qDebug() << "reprot driver login";
}

void cloudAmqpServer::HandleZmqFastStopReq(const std::string &, const void *data, int len) {
    std::string imei(reinterpret_cast<const char *>(data), len);

    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                     TGMsg::MsgUnion_Platform_FastStopRequest,
                                     Platform::CreateFastStopRequest(fbb,
                                                fbb.CreateString(imei)).Union()));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
    qDebug() << "send fast stop req, imei: " << imei.c_str();
}

void cloudAmqpServer::HandleZmqTakeoverTaskFail(const std::string &, const void *data, int len) {
    TaskFail taskfail;
    std::memmove(&taskfail, data, len);

    qDebug("Get task fail taskId:%04x", taskfail.taskId);

    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                                      TGMsg::MsgUnion_Platform_TakeoverTaskFail,
                                      Platform::CreateTakeoverTaskFail(fbb, taskfail.taskId).Union()));

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());
}

void cloudAmqpServer::HandleZmqTakeoverTaskOperate(const std::string &, const void *data, int len) {
    TaskOperSt task;
    std::memmove(&task, data, len);

    flatbuffers::FlatBufferBuilder fbb;

    switch (task.taskType) {
    case TakeoverTask_Reply:{
        qDebug("Get task reply taskId:%04x, result %d, reason %s",
                                            task.TaskUnion.taskReply.taskId,
                                            task.TaskUnion.taskReply.result,
                                            task.TaskUnion.taskReply.refuseReason);


        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                         TGMsg::MsgUnion_Platform_CabinTakeoverTaskReply,
                         Platform::CreateCabinTakeoverTaskReply(fbb,
                                    task.TaskUnion.taskReply.taskId,
                                    static_cast<CommonResult>(task.TaskUnion.taskReply.result),
                                    fbb.CreateString(reinterpret_cast<char *>(task.TaskUnion.taskReply.refuseReason))
                                                                ).Union()));

        break;
    }
    case TakeoverTask_GiveUp: {

        qDebug("get giveup taskId: %04x", task.TaskUnion.taskGiveUp.taskId);

        flatbuffers::FlatBufferBuilder fbb;
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                          TGMsg::MsgUnion_Platform_TakeoverTaskGiveUp,
                          Platform::CreateTakeoverTaskFail(fbb, task.TaskUnion.taskGiveUp.taskId).Union()));
        break;
    }
    case TakeoverTask_Cancel: {
        break;
    }
    case TakeoverTask_End: {

        qDebug("Get task end taskId:%04x, reason:%04x", task.TaskUnion.taskEnd.taskId, task.TaskUnion.taskEnd.reason);

        flatbuffers::FlatBufferBuilder fbb;
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                         TGMsg::MsgUnion_Platform_TakeoverTaskEnd,
                         Platform::CreateTakeoverTaskEnd(fbb, task.TaskUnion.taskEnd.taskId,
                                                         static_cast<TaskEndReason>(task.TaskUnion.taskEnd.reason)).Union()));

        break;
    }
    case TakeoverTask_Fail: {

        qDebug("Get task fail taskId:%04x", task.TaskUnion.taskFail.taskId);

        flatbuffers::FlatBufferBuilder fbb;
        fbb.Finish(TGMsg::CreateMsgFrame(fbb, GetMs(),
                          TGMsg::MsgUnion_Platform_TakeoverTaskFail,
                          Platform::CreateTakeoverTaskFail(fbb, task.TaskUnion.taskFail.taskId).Union()));
        break;
    }
    default:
        return;
    }

    queueMsg.pushMsgToQueue(fbb.GetBufferPointer(), fbb.GetSize());

}
