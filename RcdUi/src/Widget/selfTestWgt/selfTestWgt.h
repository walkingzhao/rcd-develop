#ifndef selfTestWgt_H
#define selfTestWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "selfTestCL.h"
#include "selfTestModel.h"
#include <QTimer>

#include <QLabel>
#include "Component/SteerWheel.h"
#include "Component/RingDialPro.h"
#include "Component/gearProWidget.h"
#include <QDebug>

namespace Ui {
class selfTestWgt;
}

class selfTestWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit selfTestWgt(QWidget *parent = nullptr);
    ~selfTestWgt();
    static selfTestWgt* GetInstance();

    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

private:
    void initWgt();
    void initConfig();
    void updateContent();
    void updateWheelContent();
    void updateTakeoverContent();
    void updateBlindContent();
    void updateEmptyContent();

protected:
//    void paintEvent(QPaintEvent *event);

private slots:
    void statuSlots();
//    void on_pushButton_ok_clicked();
//    void on_pushButton_cancel_clicked();

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::selfTestWgt *ui;
    static selfTestWgt        *s_pInstance;
    selfTestCL                *m_pCL;
    selfTestModel             *m_pModel;

    //title
    QLabel *labTitle = nullptr;
    QLabel *labTitleBar = nullptr;

    //wheel
    SteerWheel *selfwheelWgt = nullptr;             //steer wheel
    QLabel *labWheelFront = nullptr;
    QLabel *labWheelLeft = nullptr;
    QLabel *labWheelRight = nullptr;
    QLabel *labWheelBottom = nullptr;

    //gear
    gearProWidget *gearProWgt = nullptr;
    QLabel *gear_p = nullptr;
    QLabel *gear_brake = nullptr;

    //pedal
    RingDialPro *mechanical_brake = nullptr;    //行车制动踏板
    RingDialPro *electric_brake = nullptr;      //电制动踏板
    RingDialPro *throttle = nullptr;            //油门踏板

    //light/lift
    QLabel *light = nullptr;
    QLabel *lift = nullptr;

    //scram
    QLabel *scramIcon = nullptr;

    //left beams
    QLabel *leftIcons[4];

    //right icons
    QLabel *rightIcons[5];

    //value
    int acceleratorMin;
    int acceleratorMax;

    int electricBrakeMin;
    int electricBrakeMax;

    int hydraulicBrakeMin;
    int hydraulicBrakeMax;

    int steeringwheelLeftMax;
    int steeringwheelMedian;
    int steeringwheelRightMin;
    int steeringwheelRightOffset;
    const int steeringwheelRightMax = 0xFFFF;

    int steeringwheelRightTotal;
    int steeringwheelLeftTotal;
    int steeringwheelTotal;

    int electricBrakeTotal;
    int hydraulicBrakeTotal;
    int accTotal;

    int hardBrakeMin;
    int hardBrakeMax;
    int hardBrakeTotal;
};

#endif // selfTestWgt_H
