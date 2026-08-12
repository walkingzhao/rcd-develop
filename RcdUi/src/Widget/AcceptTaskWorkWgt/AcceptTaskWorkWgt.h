#ifndef AcceptTaskWorkWgt_H
#define AcceptTaskWorkWgt_H

#include <QWidget>
#include <QKeyEvent>
#include <Interface/IFunWidget.h>
#include "AcceptTaskWorkCL.h"
#include "AcceptTaskWorkModel.h"
namespace Ui {
class AcceptTaskWorkWgt;
}
//接受任务
class AcceptTaskWorkWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit AcceptTaskWorkWgt(QWidget *parent = nullptr);
    ~AcceptTaskWorkWgt();
    static AcceptTaskWorkWgt *GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;
//    void keyPressEvent(QKeyEvent * event);

protected:
    void paintEvent(QPaintEvent *event);

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

//    void on_pushButton_ok_pressed();

private:
    Ui::AcceptTaskWorkWgt *ui;
    static AcceptTaskWorkWgt        *s_pInstance;
    AcceptTaskWorkCL                *m_pCL;
    AcceptTaskWorkModel             *m_pModel;
    bool _isOk = true;
};

#endif // AcceptTaskWorkWgt_H
