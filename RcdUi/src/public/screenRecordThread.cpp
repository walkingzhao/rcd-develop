#include "screenRecordThread.h"
#include <QDebug>
screenRecordThread::screenRecordThread()
{

}
screenRecordThread::~screenRecordThread()
{
    this->deleteLater();
    if(_process.state()==QProcess::Running){
        _process.close();
        _process.kill();
    }
}
Q_INVOKABLE void screenRecordThread::startWork()
{
    _isStop = false;
}
Q_INVOKABLE void screenRecordThread::stopWork()
{
    _isStop = true;
}
Q_INVOKABLE void screenRecordThread::slotWork()
{
    while (1) {
        if(!_isStop){
            if(_process.state()==QProcess::NotRunning){
                QString path = QString("screenRecord");
                _process.start(path);
                if(_process.waitForStarted()){
                    qDebug() << "screen record 启动成功"
                             <<_process.readAllStandardOutput();
                }
                else {
                    qDebug() << "screen record 启动失败"<<_process.readAllStandardError();
                }
            }
        }
        else {
            _process.close();
            _process.kill();

        }/*
        QThread::sleep(30);*/
    }
}
