#include "SteerWheel.h"
#include <QRandomGenerator>
#include <QPainter>
#include <QDebug>

#define MAX_ANGLE       450.0
#define MIN_ANGLE       -450.0

SteerWheel::SteerWheel(QWidget *parent) : QWidget(parent),
    m_currentValue(0),
    m_targetValue(0),
    m_minValue(MIN_ANGLE),
    m_maxValue(MAX_ANGLE)
{
    m_steerWheelImage.load(":/resource/dashboard/steerwheel.png");
}

void SteerWheel::setParameter(float minValue,float maxValue)
{
    m_minValue = minValue;
    m_maxValue = maxValue;
}

void SteerWheel::setValue(float value)
{
    if(value > m_maxValue){
        m_targetValue = m_maxValue;
    }else if(value < m_minValue){
        m_targetValue = m_minValue;
    }else{
        m_targetValue = value;
    }

    update();
}

float SteerWheel::calculateAngle()
{ 
    float uiAngle = m_targetValue * (540.0/MAX_ANGLE);
    return uiAngle;
}

void SteerWheel::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::LosslessImageRendering);

    painter.translate(width() / 2, height()/2);
    qreal side = qMin(width()/240.0, height()/240.0);
    painter.scale(side , side);

    painter.rotate(calculateAngle());
    painter.drawPixmap(m_steerWheelImage.width()/(-2),m_steerWheelImage.height()/(-2),m_steerWheelImage);

    painter.end();
}
