#ifndef NotSatisfiedWithTakeoverWgt_H
#define NotSatisfiedWithTakeoverWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "NotSatisfiedWithTakeoverCL.h"
#include "NotSatisfiedWithTakeoverModel.h"
#include <QTimer>

namespace Ui {
class NotSatisfiedWithTakeoverWgt;
}

class NotSatisfiedWithTakeoverWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit NotSatisfiedWithTakeoverWgt(QWidget *parent = nullptr);
    ~NotSatisfiedWithTakeoverWgt();
    static NotSatisfiedWithTakeoverWgt* GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_task_over_clicked();

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
    void statuSlots();

private:
    Ui::NotSatisfiedWithTakeoverWgt *ui;
    static NotSatisfiedWithTakeoverWgt        *s_pInstance;
    NotSatisfiedWithTakeoverCL                *m_pCL;
    NotSatisfiedWithTakeoverModel             *m_pModel;
    QTimer                                    *m_Timer;
};

#endif // NotSatisfiedWithTakeoverWgt_H
