#include "QsLog.h"
#include "QsLogDest.h"
#include "controlpub.h"
#include "fison.h"
#include "zmq/zmqwrap.hpp"
#include <functional>
#include <hidapi/hidapi.h>
#include <QCoreApplication>
#include <QDir>
#include <QThread>

using namespace QsLogging;

void outputLog(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    Level logLevel = QsLogging::DebugLevel;
    switch (type)
    {
    case QtDebugMsg:
        logLevel = QsLogging::DebugLevel;
        break;
    case QtInfoMsg:
        logLevel = QsLogging::InfoLevel;
        break;
    case QtWarningMsg:
        logLevel = QsLogging::WarnLevel;
        break;
    case QtCriticalMsg:
        logLevel = QsLogging::ErrorLevel;
        break;
    case QtFatalMsg:
        logLevel = QsLogging::FatalLevel;
        break;
    default:
        break;
    }
    Logger &logger = Logger::instance();
    if (logger.loggingLevel() <= logLevel)
    {
        logger.writeToLog(logLevel, msg);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Logger &logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::DebugLevel); //设置日志等级
    const QString logDirPath(QDir(a.applicationDirPath()).filePath("log"));
    QDir().mkpath(logDirPath);
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log/control.txt"));
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
        sLogPath, EnableLogRotation, MaxSizeBytes(20 * 1024 * 1024), MaxOldLogCount(30))); //设置log文件大小20M，保存30个文件
    logger.addDestination(fileDestination);

    DestinationPtr consoleDestination(DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(consoleDestination);

    qInstallMessageHandler(outputLog);

    qDebug() << "Start Control !!!";
    //驾驶舱  <--serial-->  control  <--zmq-->  UI/cloudServer/gatewayServer

    //负责定时zmq发送捕获的驾驶舱数据
    ControlPub pubObj;
    //斐视驾驶舱TCP收发处理obj
    fison fisonObj;
    QObject::connect(&fisonObj,
                     SIGNAL(EmitControlRawData(const QByteArray &)),
                     &pubObj,
                     SLOT(HandleFisonControlRawDataSlot(const QByteArray &)));
    QObject::connect(&fisonObj,
                     SIGNAL(EmitControlData(const QByteArray &)),
                     &pubObj,
                     SLOT(HandleFisonControlDataSlot(const QByteArray &)));

    QObject::connect(&fisonObj,
                     SIGNAL(EmitStatus(quint8)),
                     &pubObj,
                     SLOT(HandleFisonStatusSlot(quint8)));

    QObject::connect(&fisonObj,
                     SIGNAL(EmitButton(quint32)),
                     &pubObj,
                     SLOT(HandleFisonButtonSlot(quint32)));

    QObject::connect(&fisonObj,
                     SIGNAL(EmitControlLight(const QByteArray &)),
                     &pubObj,
                     SLOT(HandleFisonControlLightSlot(const QByteArray &)));

    QObject::connect(&fisonObj,
                     SIGNAL(EmitVehicleStatus(quint8)),
                     &pubObj,
                     SLOT(HandleVehicleStatus(quint8)));

    fisonObj.StartRun();
    int ret = a.exec();
    return ret;
}
