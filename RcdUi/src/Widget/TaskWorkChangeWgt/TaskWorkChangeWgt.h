#ifndef TaskWorkChangeWgt_H
#define TaskWorkChangeWgt_H

#include <QWidget>
#include <QTimer>
#include "Interface/IFunWidget.h"
#include "TaskWorkChangeCL.h"
#include "TaskWorkChangeModel.h"
namespace Ui {
class TaskWorkChangeWgt;
}

class TaskWorkChangeWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit TaskWorkChangeWgt(QWidget *parent = nullptr);
    ~TaskWorkChangeWgt();
    static TaskWorkChangeWgt* GetInstance();
    void setData(QVariant data);

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
    void tickTimerOut();
private:
    Ui::TaskWorkChangeWgt *ui;
    static TaskWorkChangeWgt        *s_pInstance;
    TaskWorkChangeCL                *m_pCL;
    TaskWorkChangeModel             *m_pModel;
    QTimer tickTimer;
};

#endif // TaskWorkChangeWgt_H
