#include "gearProWidget.h"
#include "ui_gearProWidget.h"
#include <QPainter>
#include <QtDebug>

gearProWidget::gearProWidget(/*bool remote, */QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gearProWidget)
{
    ui->setupUi(this);
#if 0
    if(remote) {
        m_gearWgtImage.load(":/resource/logo/gear.png");

        QImage imgP(":/resource/test/gear_p.png");
        ui->brake1->resize(30,26);
        ui->brake1->setPixmap(QPixmap::fromImage(imgP));
        ui->brake1->hide();

        QImage imgBrake(":/resource/test/gear_brake.png");
        ui->brake2->resize(29,27);
        ui->brake2->setPixmap(QPixmap::fromImage(imgBrake));
        ui->brake2->hide();
    }else{
        ui->brake1->hide();
        ui->brake2->hide();
    }
#endif

    resetStyle();
    setValue(1);
}

gearProWidget::~gearProWidget()
{
    delete ui;
}

void gearProWidget::setmode(int value)
{
    imode = value;
    if(1 == imode) {
        m_gearWgtImage.load(":/resource/logo/gear.png");

        QImage imgP(":/resource/test/gear_p.png");
        ui->brake1->resize(30,26);
        ui->brake1->setPixmap(QPixmap::fromImage(imgP));

        QImage imgBrake(":/resource/test/gear_brake.png");
        ui->brake2->resize(29,27);
        ui->brake2->setPixmap(QPixmap::fromImage(imgBrake));
    }

    ui->brake1->hide();
    ui->brake2->hide();

//    ui->brake1->show();
//    ui->brake2->show();

    resetStyle();
}
void gearProWidget::setParking(int value)
{
    if(1 == value){
        ui->brake1->show();
    }else if(0 == value){
        ui->brake1->hide();
    }
}

void gearProWidget::setLoading(int value)
{
    if(1 == value){
        ui->brake2->show();
    }else if(0 == value){
        ui->brake2->hide();
    }
}

void gearProWidget::setValue(int value)
{
    m_currentValue = static_cast<GearProWgtType>(value);

    this->update();
    resetStyle();

    switch (m_currentValue) {

    case GearProWgtType::Gear_R:
        ui->gear_R->setStyleSheet("QLabel{color: rgb(250,89,0);"
                                  "background-color: rgb(0, 57, 99);"
                                  "border-top-left-radius: 20px;"
                                  "border-bottom-left-radius: 20px;"
                                  "border:1px solid rgb(0,18,31);"
                                  "border-right:none;}");
        break;

    case GearProWgtType::Gear_N:
        ui->gear_N->setStyleSheet("QLabel{color: rgb(250,89,0);"
                                  "background-color: rgb(0, 57, 99);"
                                  "border:1px solid rgb(0,18,31);"
                                  "border-left:none;"
                                  "border-right:none;}");
        break;

    case GearProWgtType::Gear_D:
        ui->gear_D->setStyleSheet("QLabel{color: rgb(250,89,0);"
                                  "background-color: rgb(0, 57, 99);"
                                  "border-top-right-radius: 20px;"
                                  "border-bottom-right-radius: 20px;"
                                  "border:1px solid rgb(0,18,31);"
                                  "border-left:none;}");
        break;

    default:
        return;
    }
}

void gearProWidget::paintEvent(QPaintEvent *)
{
    if(imode != 1) return;

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::LosslessImageRendering);

    painter.translate(width()/2, height()/2);
    qreal side = qMin(width()/630.0, height()/60.0);
    painter.scale(side , side);

    painter.drawPixmap(m_gearWgtImage.width()/(-2),m_gearWgtImage.height()/(-2),m_gearWgtImage);
    painter.setPen(Qt::white);
    painter.end();
}

void gearProWidget::resetStyle()
{
    ui->lineSpace1->setFixedWidth(5);
    ui->lineSpace2->setFixedWidth(5);

    ui->lineSpace1->setFixedHeight(ui->gear_D->height());
    ui->lineSpace2->setFixedHeight(ui->gear_D->height());

//    if(imode==1){
//        ui->lineSpace1->setStyleSheet("QLabel{color: rgb(0,18,31);"
//                                      "background-color: #00ffffff;"
//                                      "border:none;}");
//    }

    ui->gear_R->setStyleSheet("QLabel{color: rgb(88, 106, 124);"
                              "background-color: rgb(0, 44, 77);"
                              "border-top-left-radius: 20px;"
                              "border-bottom-left-radius: 20px;"
                              "border:1px solid rgb(0,18,31);"
                              "border-right:none;}");

    ui->gear_N->setStyleSheet("QLabel{color: rgb(88, 106, 124);"
                              "background-color: rgb(0, 44, 77);"
                              "border:1px solid rgb(0,18,31);"
                              "border-left:none;"
                              "border-right:none;}");

    ui->gear_D->setStyleSheet("QLabel{color: rgb(88, 106, 124);"
                              "background-color: rgb(0, 44, 77);"
                              "border-top-right-radius: 20px;"
                              "border-bottom-right-radius: 20px;"
                              "border:1px solid rgb(0,18,31);"
                              "border-left:none;}");
}
