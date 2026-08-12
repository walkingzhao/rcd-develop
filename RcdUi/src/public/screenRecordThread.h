#ifndef SCREENRECORDTHREAD_H
#define SCREENRECORDTHREAD_H

#include "baseThread.h"
#include <QProcess>
class screenRecordThread : public baseThread
{
public:
    screenRecordThread();
    ~screenRecordThread();
    virtual Q_INVOKABLE void startWork() override;
    virtual Q_INVOKABLE void stopWork() override;
    Q_INVOKABLE void run(){}
public slots:
    virtual Q_INVOKABLE void slotWork() override;
private:
    bool _isStop = false;
    QProcess _process;
};

#endif // SCREENRECORDTHREAD_H
