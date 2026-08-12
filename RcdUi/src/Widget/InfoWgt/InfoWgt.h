#ifndef INFOWGT_H
#define INFOWGT_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QList>
#include <QStringList>
#include <QTimer>
#include "Interface/IFunWidget.h"
#include "infocl.h"
#include "infomodel.h"

namespace Ui {
class InfoWgt;
}

class InfoWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit InfoWgt(QWidget *parent = nullptr);
    ~InfoWgt();
    void insertMessage(const QString &message);
    void setType(int messageType);//0:故障信息,1:系统信息

private:
    QWidget* left_widget();
    QWidget* right_widget();
    void read_fault_data();

private slots:
    void testData();//测试
    void on_blinkFaultTimer();
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::InfoWgt *ui;
    QTimer *_testTimer = nullptr;//测试
    int _num =15 ;
    int messageType;
    InfoCL                *m_pCL;
    InfoModel             *m_pModel;

    QHBoxLayout *pHLayout = nullptr;
    QVBoxLayout* pVLayout = nullptr;
    QWidget* leftWidget = nullptr;
    QWidget* rightWidget = nullptr;
    QLabel* rightWidgetTitle = nullptr;

    QLabel* faultIcon[6];
    QLabel* faultText[6];
    QTimer* blinkFaultTimer = nullptr;
    int numTick[6];
    int led_status[6];
};

#endif // INFOWGT_H
