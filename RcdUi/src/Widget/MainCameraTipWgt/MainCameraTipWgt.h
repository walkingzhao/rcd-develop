#ifndef MainCameraTipWgt_H
#define MainCameraTipWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "MainCameraTipCL.h"
#include "MainCameraTipModel.h"
#include <QTimer>
namespace Ui {
class MainCameraTipWgt;
}

class MainCameraTipWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit MainCameraTipWgt(QWidget *parent = nullptr);
    ~MainCameraTipWgt();
    static MainCameraTipWgt *GetInstance();

protected:
    void paintEvent(QPaintEvent *event);

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
    void tickTimerOut();
private:
    Ui::MainCameraTipWgt *ui;
    MainCameraTipCL                *m_pCL;//控制类
    MainCameraTipModel             *m_pModel;//模型类
    static MainCameraTipWgt        *s_pInstance;
    QTimer                         tickTimer;
    QString textString;
};

#endif // MainCameraTipWgt_H
