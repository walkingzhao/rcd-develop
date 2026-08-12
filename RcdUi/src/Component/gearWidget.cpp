#include "gearWidget.h"
#include "ui_gearWidget.h"
#include <QPainter>
#include <QtDebug>
gearWidget::gearWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gearWidget)
{
    ui->setupUi(this);
    m_gearWgtImage.load(":/resource/logo/gear.png");
//    setValue(GearWgtType::Gear_P);
//    setValue(GearWgtType::Gear_D);
}

gearWidget::~gearWidget()
{
    delete ui;
}
void gearWidget::setValue(int value)
{
    m_currentValue = static_cast<GearWgtType>(value);
    this->update();
    clearStyle();
    switch (m_currentValue) {
    case GearWgtType::Gear_D:{
        ui->gear_D->setStyleSheet("QLabel{background-color:rgb(114, 159, 207);"
                                  "color: rgb(186, 189, 182);"
                                  "border-top-right-radius: 20px;"
                                  "border-bottom-right-radius: 20px;}");
        break;
    }
    case GearWgtType::Gear_N:{
        ui->gear_N->setStyleSheet("QLabel{background:rgb(114, 159, 207);}");
        break;
    }
    case GearWgtType::Gear_R:{
        ui->gear_R->setStyleSheet("QLabel{background:rgb(114, 159, 207);}");
        break;
    }
    case GearWgtType::Gear_P:{
        ui->gear_P->setStyleSheet("QLabel{background-color:rgb(114, 159, 207);"
                                  "color: rgb(186, 189, 182);"
                                  "border-top-left-radius: 20px;"
                                  "border-bottom-left-radius: 20px;}");
        break;
    }
    }
}

void gearWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::LosslessImageRendering);

    painter.translate(width()/2, height()/2);
    qreal side = qMin(width()/630.0, height()/60.0);
    painter.scale(side , side);

    painter.drawPixmap(m_gearWgtImage.width()/(-2),m_gearWgtImage.height()/(-2),m_gearWgtImage);
    painter.setPen(Qt::white);
    //    QFont font = painter.font();
    //    font.setPixelSize(25);
    //    painter.setFont(font);

    //    QPoint Dpoint(m_gearWgtImage.width()/(-3),10);
    //    QPoint Npoint(0,10);
    //    QPoint Rpoint(m_gearWgtImage.width()/3 - 20,10);

    //    painter.drawText(Dpoint,QString::fromUtf8("D"));
    //    painter.drawText(Npoint,QString::fromUtf8("N"));
    //    painter.drawText(Rpoint,QString::fromUtf8("R"));

    //    painter.setPen(QPen(QColor(0xfa, 0x5a, 0x00),2));
    //    QPoint point;
    //    QString gearStr;

    //    switch (m_currentValue) {
    //    case Gear_D:
    //        point = Dpoint;
    //        gearStr = QString::fromUtf8("D");
    //        break;
    //    case Gear_N:
    //        point = Npoint;
    //        gearStr = QString::fromUtf8("N");
    //        break;
    //    case Gear_R:
    //        point = Rpoint;
    //        gearStr = QString::fromUtf8("R");
    //        break;
    //    default:
    //        point = Npoint;
    //        gearStr = QString::fromUtf8("N");
    //        qDebug() << "no this Gear_";
    //        break;
    //    }
    //    painter.drawText(point,gearStr);
    //    point += QPoint(0,10);
    //    point -= QPoint(12,0);
    //    QLine line(point,point+QPoint(40,0));
    //    painter.drawLine(line);

    painter.end();
}
//更新当前样式
void gearWidget::clearStyle()
{
    ui->gear_D->setStyleSheet("QLabel{background-color:rgb(32, 74, 135);"
                              "color: rgb(186, 189, 182);"
                              "border-top-right-radius: 20px;"
                              "border-bottom-right-radius: 20px;}");

    ui->gear_P->setStyleSheet("QLabel{color: rgb(186, 189, 182);"
                              "background-color: rgb(32, 74, 135);"
                              "border-top-left-radius: 20px;"
                              "border-bottom-left-radius: 20px;}");

    ui->gear_N->setStyleSheet("QLabel{color: rgb(186, 189, 182);"
                              "background-color: rgb(32, 74, 135);}");

    ui->gear_R->setStyleSheet("QLabel{color: rgb(186, 189, 182);"
                              "background-color: rgb(32, 74, 135);}");

}
