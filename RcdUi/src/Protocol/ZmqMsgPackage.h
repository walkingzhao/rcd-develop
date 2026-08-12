#ifndef ZmqMsgPackage_H
#define ZmqMsgPackage_H

#include "System.h"
#include <QVariant>
#include "tgmsg_generated.h"
#include "public/fbsstructure.h"
#include <flatbuffers/minireflect.h>
#include <iostream>
#include <string>

// ---> START BAIYUN 2022/08/02
#include "../../Component/common/config_parser.hpp"
// <--- END

typedef struct
{
    uint8_t moduleType;
    uint8_t cmd;
    uint16_t length;
    char forwardData[4096];
} IpcForwardData;

// Zmq消息包编解码处理类
class ZmqMsgPackage
{
public:
    ZmqMsgPackage();

    bool     c2uButtonKey(const std::string &topic, const void *data, int len);
    bool     cabinRawData(const std::string &topic, const void *data, int len);
    bool     g2uVehicleRawData(const std::string &topic,const void *buf,int len);//new 车辆数据
    bool     g2uUpdateTrackLineConfig(const std::string &topic,const void *buf,int len);
    bool     updateCCUTaskStatus(const std::string &topic,const void *buf,int len);
    bool     speedWarning(const std::string &topic, const void *buf, int len);

    bool     safeDeceleration(const std::string &topic, const void *buf, int len);
    bool     vehicleGps(const std::string &topic, const void *buf, int len);


    bool     controlMsgData(const std::string &topic,const void *buf,int len);

    bool     g2uVehicleStatus(const std::string &topic, const void *data, int len);
    bool     g2uVehicleDelay(const std::string &topic, const void *data, int len);
    bool     g2uRespRemotel(const std::string &topic, const void *data, int len);
    bool     u2uForward(const void *data, int len);
    bool     mapData(const QList<QVariant> &data);//地图数据
    bool     cloudMsgData(const std::string &topic,const void *buf,int len);
    bool     hmiHintMsgData(const std::string &topic,const void *buf,int len);
    bool     selfCheckStatus(const std::string &topic, const void *data, int len);//舱端自检
    bool     devlinkStatus(const std::string &topic,const void *data, int len);//车辆在现状态

    static  bool  encodeIpcForward(QByteArray &dest, ModuleDir &moduleDir, int &cmd, QVariant &data);
    static  bool  encodeReqRemote(QByteArray &dest, QString &imei,uint8_t cmd);
    static  bool  encodeReqSendHmiMsg(QByteArray &dest, QString &imei,QByteArray &data);

// ---> START BAIYUN 2022/08/02
private:
    void readTrackLineCfgFile(QString name);
    QString vehicleName;
    common::ConfigParserPtr config_parser_ptr_;//配置文件获取
    TrackLineCalibrationST m_TrackLineCfg;
// <--- END

public:

    QVector<ModuleDir>   m_moduleDirs;
    QVector<int>         m_cmds;
    QVector<QVariant>    m_datas;
    QString              m_imei;
    static SelfCheckStatusST _selfdata;

};

#endif // ZmqMsgPackage_H
