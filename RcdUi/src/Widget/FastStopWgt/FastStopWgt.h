#ifndef FastStopWgt_H
#define FastStopWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "FastStopCL.h"
#include "FastStopModel.h"
#include <QTimer>
namespace Ui {
class FastStopWgt;
}

class FastStopWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit FastStopWgt(QWidget *parent = nullptr);
    ~FastStopWgt();
    static FastStopWgt *GetInstance();

protected:
    void paintEvent(QPaintEvent *event);

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::FastStopWgt *ui;
    FastStopCL                *m_pCL;//控制类
    FastStopModel             *m_pModel;//模型类
    static FastStopWgt        *s_pInstance;
    QTimer                         tickTimer;
    QString textString;
};

#endif // FastStopWgt_H
