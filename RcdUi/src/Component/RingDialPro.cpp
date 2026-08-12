#include "RingDialPro.h"
#include <QRandomGenerator>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QFontDatabase>

/////////////////////////////////////////////
//#define SPAN_ANGLE      220.0
//#define START_ANGLE     -20.0
#define SPAN_ANGLE      300.0
#define START_ANGLE     -60.0

#define REAL_WIDTH      150.0//200.0
#define REAL_HEIGHT     150.0//150.0
#define REAL_BLANK      5.0
/////////////////////////////////////////////

#define FREQUENCY       100 // 刷新频率

RingDialPro::RingDialPro(QWidget *parent) : QWidget(parent),
    m_type(BatteryVoltage_ometer),
    m_currentValue(0),
    m_targetValue(0),
    m_moveSpeed(0),
    m_startValue(0),
    m_endValue(50)
{
    // 设置窗口大小
//    this->setMinimumSize(100,115);
//    qDebug() << this->width() << " "<< this->height();

    // 设置边框默认颜色
    m_penColor = QColor(200,200,200, 50);

    // font
    int fontMediumId = QFontDatabase::addApplicationFont(":/resource/font/DINPro-Medium.otf");
    fontMediumName = QFontDatabase::applicationFontFamilies (fontMediumId).at(0);

    // 动态刷新进度条
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerHandle()));
}

void RingDialPro::setParameter(RingDialType type,float sartValue,float endValue,float minValue,float maxValue)
{
    m_type = type;
    m_startValue = sartValue;
    m_endValue = endValue;
    m_minValue = minValue;
    m_maxValue = maxValue;
}

void RingDialPro::setValue(float value)
{
    if(value > m_endValue){
        m_targetValue = m_endValue;
    }else if(value < m_startValue){
        m_targetValue = m_startValue;
    }else{
        m_targetValue = value;
    }

    if(MechanicalBrake_ometer==m_type || ElectricBrake_ometer==m_type || Throttle_ometer==m_type){
        m_selfTestValue = value;
    }

    if(abs(m_targetValue - m_currentValue) < 0.01){
        m_currentValue = m_targetValue;
        this->update();
    }else{
        m_moveSpeed = (m_targetValue - m_currentValue)*2/FREQUENCY;
        m_timer.start(1000/FREQUENCY);
    }
}

void RingDialPro::setPenColor(QColor color)
{
    m_penColor = color;
}

float RingDialPro::calculateAngle()
{
    m_currentValue += m_moveSpeed;
    if(m_moveSpeed >= 0){
        if(m_currentValue >= m_targetValue) {
            m_currentValue = m_targetValue;
            m_timer.stop();
        }
    }else{
        if(m_currentValue <= m_targetValue) {
            m_currentValue = m_targetValue;
            m_timer.stop();
        }
    }
    return ((1 - (m_currentValue-m_startValue)/(m_endValue-m_startValue))*SPAN_ANGLE);
}

void RingDialPro::timerHandle()
{
    this->update();
}

void RingDialPro::paintEvent(QPaintEvent *)
{
    QPixmap material(this->width(),this->height());
    material.fill(Qt::transparent);
    QPainter painter(&material);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::LosslessImageRendering);// 启用反锯齿

    // 获取高度中心位置
    int width = this->width();
    int height = this->height();
    int radius = ((width>height)?height:width)/2;

    // 将画笔移动到中下方
    painter.translate(width>>1, height*0.5);

    // 取消画笔
    painter.setPen(Qt::NoPen);

    // 绘制渐变圆环
    DrawCircle(painter,radius-25);
    RefreshCircle(painter,radius-25);

    // 绘制刻度数字
    DrawDigital(painter,radius-2);

    // 绘制文字
    DrawText(painter,radius/2);

    painter.end();
    QPainter mainPainter(this);
    mainPainter.drawPixmap(QPoint(0,0),material);
    mainPainter.end();
}

void RingDialPro::DrawCircle(QPainter& painter,int radius)
{
    painter.save();
    painter.setPen(QPen(m_penColor, 2));
    outerRing.setRect(REAL_WIDTH/-2+25, REAL_WIDTH/-2+25, REAL_WIDTH-50, REAL_WIDTH-50); // 宽度做外圈直径
    innerRing = outerRing;
    innerRing -= QMarginsF(15,15,15,15);    // 内圈半径小25

    int startAngle = START_ANGLE * 16;
    int spanAngle = SPAN_ANGLE * 16;

    QRadialGradient radialGradient(0,0,radius,0,0);
    radialGradient.setColorAt(0,QColor(200,200,200, 50));//0,0x1d,0x33
    radialGradient.setColorAt(0.2,QColor(200,200,200, 30));
    radialGradient.setColorAt(0.8,QColor(200,200,200, 30));
    radialGradient.setColorAt(1,QColor(200,200,200, 50));
    painter.setBrush(radialGradient);// 设置渐变色
    painter.drawPie(outerRing, startAngle, spanAngle);

    painter.setBrush(QColor(0,0x24,0x3a));
    painter.drawPie(innerRing, startAngle, (SPAN_ANGLE+60) * 16);
    painter.restore();
}

void RingDialPro::RefreshCircle(QPainter& painter,int radius)
{
    painter.save();
    QRadialGradient radialGradient(0,0,radius,0,0);

    switch (m_type) {
    case BatteryVoltage_ometer://电池电压
        if ((m_currentValue < 24) || (m_currentValue > 30)) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case EngineCoolantTemperature_ometer://发动机冷却液温度
        if (m_currentValue >= 100) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case CoolantLevel_ometer://发动机冷却液液位
        if (m_currentValue < 12.5) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case EngineOilPressure_ometer://发动机油压
        if (m_currentValue < 100) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case FuelLevel_ometer://油量
        if (m_currentValue < 12.5) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case BatteryLevel_ometer://电池电量
        if (m_currentValue <= 20) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case CellTemperature_omter://电芯温度
        if (m_currentValue > 60) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case ExhaustPortTemperature_omter://排气口温度
        if (m_currentValue >= 100) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case Temperature_omter://温度
        if (m_currentValue > 100) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case WaterTankLevel_omter://水箱水位
        if (m_currentValue <= 20) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case FrontAxleBrakePressure_ometer://前桥压力
        if (m_currentValue >= 10) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    case RearAxleBrakePressure_ometer://后桥压力
        if (m_currentValue >= 10) {
            radialGradient.setColorAt(0,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.1,QColor(0xfb, 0x55, 0x00, 255));
            radialGradient.setColorAt(0.5,QColor(0xfb, 0x55, 0x00, 200));
            radialGradient.setColorAt(1,QColor(0xfb, 0x55, 0x00, 180));
        } else {
            radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
            radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
            radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        }
        break;

    // pedal
    case MechanicalBrake_ometer:
    case ElectricBrake_ometer:
    case Throttle_ometer:
//        radialGradient.setColorAt(0,QColor(0x3d, 0xfe, 0xfe, 255));
//        radialGradient.setColorAt(0.1,QColor(0x3d, 0xfe, 0xfe, 255));
//        radialGradient.setColorAt(0.5,QColor(0x3d, 0xfe, 0xfe, 200));
//        radialGradient.setColorAt(1,QColor(0x3d, 0xfe, 0xfe, 180));
        radialGradient.setColorAt(0,QColor("#00baff"));
        radialGradient.setColorAt(1,QColor("#00baff"));
        break;

    default:
        return;
    }

    painter.setBrush(radialGradient);

    float angle = calculateAngle();
    int startAngle = (angle + START_ANGLE) * 16;
    int spanAngle = (SPAN_ANGLE - angle) * 16;
    painter.drawPie(outerRing, startAngle, spanAngle);

//    painter.setCompositionMode(QPainter::CompositionMode_Clear); //清除多余扇形
    innerRing -= QMarginsF(1,1,1,1);
    startAngle = START_ANGLE * 16;
    painter.setBrush(QColor(0,0x24,0x3a));
    painter.drawPie(innerRing, startAngle, (SPAN_ANGLE+60) * 16);
    painter.restore();
}

void RingDialPro::DrawText(QPainter& painter,int radius)
{
    painter.save();
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setPen(Qt::white);

    QFont font = painter.font();
    font.setPixelSize(10);
    painter.setFont(font);

    switch (m_type) {
    case BatteryVoltage_ometer://电池电压
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("电池电压"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("V"));
        break;

    case EngineCoolantTemperature_ometer://发动机冷却液温度
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("冷却液温度"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("℃"));
        break;

    case CoolantLevel_ometer://发动机冷却液液位
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("冷却液液位"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("%"));
        break;

    case EngineOilPressure_ometer://发动机油压
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("机油压力"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("kpa"));
        break;

    case FuelLevel_ometer://油量
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("油量"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("%"));
        break;

    case BatteryLevel_ometer://电池电量
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("电池电量"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("%"));
        break;

    case CellTemperature_omter://电芯温度
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("电芯温度"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("℃"));
        break;

    case ExhaustPortTemperature_omter://排气口温度
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("排气口温度"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("℃"));
        break;

    case FrontAxleBrakePressure_ometer://前桥压力
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("前桥压力"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("Mpa"));
        break;

    case RearAxleBrakePressure_ometer://后桥压力
        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString("后桥压力"));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString("%"));
        break;

    // pedal
    case MechanicalBrake_ometer:
    case ElectricBrake_ometer:
        painter.restore();
        painter.save();
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

        m_leftMax = m_selfTestValue - m_startValue;
        m_RightMax = m_selfTestValue - m_endValue;
        if( ((m_leftMax > -5) && (m_leftMax <= 0)) ||
            ((m_RightMax < 5) && (m_RightMax >= 0)) ){
            painter.setPen(QColor("#39D352"));
        }else{
            painter.setPen(Qt::white);
        }

        font = painter.font();
        font.setPixelSize(10);
        painter.setFont(font);

        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString(""));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString(""));
        break;
    case Throttle_ometer:
        painter.restore();
        painter.save();
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
#if 0
        if(m_currentValue < m_minValue || m_currentValue > m_maxValue){
            painter.setPen(Qt::white);
        }else{
//            painter.setPen(Qt::green);
            painter.setPen(QColor("#39D352"));
        }
#endif
        m_leftMax = m_selfTestValue - m_startValue;
        m_RightMax = m_selfTestValue - m_endValue;
        if( ((m_leftMax > -10) && (m_leftMax <= 0)) ||
            ((m_RightMax < 10) && (m_RightMax >= 0)) ){
            painter.setPen(QColor("#39D352"));
        }else{
            painter.setPen(Qt::white);
        }

        font = painter.font();
        font.setPixelSize(10);
        painter.setFont(font);

        painter.drawText(-50,-28, 100, 22,Qt::AlignCenter,QString(""));
        painter.drawText(-25,16, 50, 20,Qt::AlignCenter,QString(""));
        break;

    default:
        return;
    }

    if(MechanicalBrake_ometer==m_type || ElectricBrake_ometer==m_type || Throttle_ometer==m_type){
        font.setFamily(fontMediumName);
        font.setPixelSize(22);
        painter.setFont(font);
//        painter.setFont(font);
//        painter.drawText(-50,-22, 100, 40,Qt::AlignCenter,QString("%1").arg(QString::number(m_currentValue,'.',0)));
        painter.drawText(-50,-22, 100, 40,Qt::AlignCenter,QString("%1").arg(QString::number(m_selfTestValue,'.',0)));
    }else{
        font.setPixelSize(32);
        painter.setFont(font);
        painter.drawText(-50,-16, 100, 40,Qt::AlignCenter,QString("%1").arg(QString::number(m_currentValue,'.',0)));
    }
    painter.restore();
}

void RingDialPro::DrawDigital(QPainter& painter,int radius)
{
    // 设置字体
    QFont font;

    // 设置画笔
    if(MechanicalBrake_ometer==m_type || ElectricBrake_ometer==m_type || Throttle_ometer==m_type){
        painter.setPen(QColor("#80FFFFFF"));

        font.setFamily(fontMediumName);
        font.setPixelSize(16);
        painter.setFont(font);
    }else{
        painter.setPen(QColor(98,246,255));

        font.setFamily("SimHei");
        font.setPointSize(10);
        painter.setFont(font);
    }

    //////////////////////////////////////////////////////
    // 绘制4个数字
    //-start
    QPointF point(0,0);

    painter.save();
    // 计算并移动绘图对象中心点
    if(MechanicalBrake_ometer==m_type || ElectricBrake_ometer==m_type || Throttle_ometer==m_type){
        point.setX(radius*qCos(((240-1*20)*M_PI)/180));
        point.setY(radius*qSin(((240-1*20)*M_PI)/180));
    }else{
        point.setX(radius*qCos(((240-0*20)*M_PI)/180));
        point.setY(radius*qSin(((240-0*20)*M_PI)/180));
    }

    painter.translate(point.x(),-point.y());// 计算并移动绘图对象的中心点
//    painter.rotate(-150);
    painter.drawText(-15, -15, 30, 20,Qt::AlignCenter,QString::number(m_startValue));//绘制路径
    painter.restore();

    //-end
    painter.save();

    if(MechanicalBrake_ometer==m_type || ElectricBrake_ometer==m_type || Throttle_ometer==m_type){
        point.setX(radius*qCos(((240-14*20)*M_PI)/180));
        point.setY(radius*qSin(((240-14*20)*M_PI)/180));
    }else{
        point.setX(radius*qCos(((240-15*20)*M_PI)/180));
        point.setY(radius*qSin(((240-15*20)*M_PI)/180));
    }

    painter.translate(point.x(),-point.y());
//    painter.rotate(-150+15*20);
    painter.drawText(-15, -15, 30, 20,Qt::AlignCenter,QString::number(m_endValue));
    painter.restore();

    if(MechanicalBrake_ometer==m_type || ElectricBrake_ometer==m_type || Throttle_ometer==m_type){
        painter.setPen(Qt::NoPen);
        return;
    }
    //-min
    if (m_minValue != m_startValue) {
        painter.save();
        float tmp = 300*m_minValue/(m_endValue-m_startValue);
        point.setX(radius*qCos(((240-tmp)*M_PI)/180));
        point.setY(radius*qSin(((240-tmp)*M_PI)/180));
        painter.translate(point.x(),-point.y());
        painter.rotate(-150+tmp);
        painter.drawText(-15, 0, 25, 20,Qt::AlignCenter,QString::number(m_minValue));
        painter.restore();
    }

    //-max
    if (m_maxValue != m_endValue) {
        painter.save();
        float tmp = 300*m_maxValue/(m_endValue-m_startValue);
        point.setX(radius*qCos(((240-tmp)*M_PI)/180));
        point.setY(radius*qSin(((240-tmp)*M_PI)/180));
        painter.translate(point.x(),-point.y());
        painter.rotate(-150+tmp);
        painter.drawText(-15, 0, 25, 20,Qt::AlignCenter,QString::number(m_maxValue));
        painter.restore();
    }
    //////////////////////////////////////////////////////

    // 去掉画笔
    painter.setPen(Qt::NoPen);
}
