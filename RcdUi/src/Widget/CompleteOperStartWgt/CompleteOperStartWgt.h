#ifndef CompleteOperStartWgt_H
#define CompleteOperStartWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "CompleteOperStartCL.h"
#include "CompleteOperStartModel.h"
#include <QTimer>
namespace Ui {
class CompleteOperStartWgt;
}

class CompleteOperStartWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit CompleteOperStartWgt(QWidget *parent = nullptr);
    ~CompleteOperStartWgt();
    static CompleteOperStartWgt *GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_start_task_clicked();

public slots:
    void statuSlots();
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::CompleteOperStartWgt *ui;
    static CompleteOperStartWgt        *s_pInstance;
    CompleteOperStartCL                *m_pCL;
    CompleteOperStartModel             *m_pModel;
    QTimer                             *m_Timer;
};

#endif // CompleteOperStartWgt_H
