#include <QDir>
#include <QFile>
#include <QApplication>
#include "MainFile/Mainwindow.h"
#include "MainFile/MainProcessor.h"
#include "QsLog.h"
#include "QsLogDest.h"

#include "public/jsonMethord.h"
#include <cstdio>
#ifdef Q_OS_UNIX
#include <unistd.h>
#endif
using namespace QsLogging;
//log日志
void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    Level logLevel = QsLogging::InfoLevel;
    switch(type) {
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
    Logger& logger = Logger::instance();
    if(logger.loggingLevel() <= logLevel){
        logger.writeToLog(logLevel,msg);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 与 closeAllWindows / quit 行为一致，避免“界面没了但还留在 ps”时误以为已退出
    QApplication::setQuitOnLastWindowClosed(true);

    QString logFileName("./log/RcdUiLog");
    System::getInstance()->setProcessType(PT_MidProc);
    // 根据参数设置当前进程类型
    if(argc > 1){
        QString Argument(QString::fromLocal8Bit(argv[1]));
        if(Argument == "-R"){
            System::getInstance()->setProcessType(PT_RightProc);
        }else if(Argument == "-M"){
            System::getInstance()->setProcessType(PT_MidProc);
        }else if(Argument == "-L"){
            System::getInstance()->setProcessType(PT_LeftProc);
        }else{
            return 0;
        }
        logFileName += Argument;
    }

    logFileName += "log";
    // 日志类单例和配置
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::DebugLevel); //设置日志等级
    // 创建日志目录并赋予可读可写可执行权限(777)，避免目录不存在导致日志写不出。
    const QString logDirPath(QDir(a.applicationDirPath()).filePath("log"));
    QDir().mkpath(logDirPath);
    QFile::setPermissions(logDirPath,
                          QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
                          QFile::ReadGroup | QFile::WriteGroup | QFile::ExeGroup |
                          QFile::ReadOther | QFile::WriteOther | QFile::ExeOther);
    const QString sLogPath(QDir(a.applicationDirPath()).filePath(logFileName));

    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
                                       sLogPath, QsLogging::EnableLogRotation, MaxSizeBytes(20*1024*1024), MaxOldLogCount(100))); //设置log文件大小20M，保存30个文件
    logger.addDestination(fileDestination);

    DestinationPtr consoleDestination(DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(consoleDestination);
    // 调用QT安装消息处理函数
    qInstallMessageHandler(messageHandler);
    QObject::connect(&a, &QCoreApplication::aboutToQuit, []() {
        qWarning() << "[RCD-EXIT-TRACE] aboutToQuit emitted";
    });


//    AudioDecode audio("rtsp://admin:123456@192.168.23.210/live/stream0",44100,16,2);

    jsonMethord::getInstance();
    ///////////////////////////////////////////
    // main 启动：先让 ~MainProcessor 在 Logger 仍存在时执行，以便能记录子 RCD 进程收尾；并先结束子进程再销毁日志。
    int ret = 0;
    qWarning() << "[RCD-EXIT-TRACE] RCD argv:" << a.arguments() << "pid" << a.applicationPid();
    {
        MainProcessor app;
        a.installEventFilter(&app);//注册事件过滤
        app.run();
        qWarning() << "[RCD-EXIT-TRACE] entering a.exec()";
        ret = a.exec();
        qWarning() << "[RCD-EXIT-TRACE] a.exec() returned, ret =" << ret;
    }
    qWarning() << "[RCD-EXIT-TRACE] after ~MainProcessor (child RCD -L/-R should be gone if mid was parent)";
    // 在 Logger 仍有效时先析构可能打日志的模块；随后必须 qInstallMessageHandler(nullptr)，
    // 否则 destroyInstance 之后若再 qWarning，messageHandler 里 Logger::instance() 会 UB/崩溃，日志里会「少了最后几行」。
    delete System::getInstance();
#ifdef Q_OS_UNIX
    std::fprintf(stderr, "[RCD-EXIT-TRACE] past delete System pid=%ld\n", static_cast<long>(getpid()));
#else
    std::fprintf(stderr, "[RCD-EXIT-TRACE] past delete System\n");
#endif
    qInstallMessageHandler(nullptr);
    Logger::destroyInstance();
#ifdef Q_OS_UNIX
    std::fprintf(stderr, "[RCD-EXIT-TRACE] past Logger::destroyInstance pid=%ld (after this 勿用 qDebug/qWarning 写 QsLog)\n",
                 static_cast<long>(getpid()));
#else
    std::fprintf(stderr, "[RCD-EXIT-TRACE] past Logger::destroyInstance\n");
#endif
    std::fprintf(stderr, "[RCD-EXIT-TRACE] main() return, about to destroy QApplication\n");
    // 调试用别用无换行的 std::cout << "x"：到终端常为行缓冲，无 \n 则留在缓冲区；若之后在 ~MainProcessor/~QApp 中卡住，进程不结束，整盘缓冲可能一直不刷出来，误以为「没执行到」。
    std::fflush(stdout);
    std::fflush(stderr);
    return ret;
}
