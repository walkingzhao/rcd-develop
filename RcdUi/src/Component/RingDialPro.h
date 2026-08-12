#ifndef _RINGDIALPRO_H
#define _RINGDIALPRO_H

#include <QWidget>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QTimer>
#include <QPen>

class RingDialPro : public QWidget
{
    Q_OBJECT
public:
    enum RingDialType {
        BatteryVoltage_ometer = 0x1,    // 电池电压 0-50V
        EngineCoolantTemperature_ometer,// 发动机冷却液温度 -40~210°C
        CoolantLevel_ometer,// 发动机冷却液温度 -40~210°C
        EngineOilPressure_ometer,       // 发动机油压 0~1000kP
        FuelLevel_ometer,               // 油量 0-100%

        MechanicalBrake_ometer,         // 行车制动踏板
        ElectricBrake_ometer,           // 电制动踏板
        Throttle_ometer,                // 油门踏板

        BatteryLevel_ometer,            //电池电量
        CellTemperature_omter,          //电芯温度
        ExhaustPortTemperature_omter,   //排气口温度
        Temperature_omter,              //温度
        WaterTankLevel_omter,           //水箱水位
        FrontAxleBrakePressure_ometer,  //前桥制动压力
        RearAxleBrakePressure_ometer    //后桥制动压力

    };

    explicit RingDialPro(QWidget *parent = nullptr);
    void setParameter(RingDialType type,float sartValue,float endValue,float minValue,float maxValue);
    void setValue(float value);
    void setPenColor(QColor color);

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    float calculateAngle();

    void DrawCircle(QPainter&,int);     // 绘制渐变圆环
    void RefreshCircle(QPainter&,int);  // 绘制渐变圆环
    void DrawDigital(QPainter&,int);    // 绘制刻度数字
    void DrawText(QPainter&,int);       // 绘制文字

private slots:
    void timerHandle();

private:
    RingDialType   m_type;
    QTimer         m_timer;
    QColor         m_penColor;// 边框颜色

    QRectF         outerRing;
    QRectF         innerRing;

    float          m_currentValue;
    float          m_targetValue;
    float          m_moveSpeed;

    float          m_leftMax;
    float          m_RightMax;
    float          m_selfTestValue;

    float          m_startValue = 0;
    float          m_endValue;
    float          m_minValue;
    float          m_maxValue;

    QString        fontMediumName;
};

#endif // _RINGDIALPRO_H
