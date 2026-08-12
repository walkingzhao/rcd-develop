#ifndef CompleteOperEndWgt_H
#define CompleteOperEndWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "CompleteOperEndCL.h"
#include "CompleteOperEndModel.h"
#include <QTimer>
namespace Ui {
class CompleteOperEndWgt;
}

class CompleteOperEndWgt : public IFunWidget
{
    Q_OBJECT

public:
    enum complete_oper_end_checkebox_id{
        gear_P=0,//档位P档
        no_pedal_pressure,//踏板无踩压
        steering_wheel_back_to_center, // 方向盘回正
        button_reset //按钮复位
    };
    explicit CompleteOperEndWgt(QWidget *parent = nullptr);
    ~CompleteOperEndWgt();
    static CompleteOperEndWgt *GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
    void statuSlots();

private:
    Ui::CompleteOperEndWgt *ui;
    static CompleteOperEndWgt        *s_pInstance;
    CompleteOperEndCL                *m_pCL;
    CompleteOperEndModel             *m_pModel;
    QTimer                               *m_Timer;
};

#endif // CompleteOperEndWgt_H
