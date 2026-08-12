#ifndef NetworkInterruptionWgt_H
#define NetworkInterruptionWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "NetworkInterruptionCL.h"
#include "NetworkInterruptionModel.h"
#include <QTimer>
namespace Ui {
class NetworkInterruptionWgt;
}

class NetworkInterruptionWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit NetworkInterruptionWgt(QWidget *parent = nullptr);
    ~NetworkInterruptionWgt();
    static NetworkInterruptionWgt* GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_task_over_clicked();
    void statuSlots();

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::NetworkInterruptionWgt *ui;
    static NetworkInterruptionWgt        *s_pInstance;
    NetworkInterruptionCL                *m_pCL;
    NetworkInterruptionModel             *m_pModel;
    QTimer                               *m_Timer;
};

#endif // NetworkInterruptionWgt_H
