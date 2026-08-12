#include "titleDateDriver.h"
#include "ui_titleDateDriver.h"
#include <QDateTime>
titleDateDriver::titleDateDriver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::titleDateDriver)
{
    ui->setupUi(this);


    QPixmap icondate(":/resource/icon/date.png");
    QPixmap icondriver(":/resource/icon/driver.png");
    icondate = icondate.scaled(ui->label_data_icon->width()-25,ui->label_data_icon->height()-25);
    icondriver = icondriver.scaled(ui->label_driver_icon->width()-25,ui->label_driver_icon->height()-25);
    ui->label_data_icon->setPixmap(icondate);
    ui->label_driver_icon->setPixmap(icondriver);
//    setCurrentDateTime("");
    setDriverName("");
    connect(&_timerDate,SIGNAL(timeout()),this,SLOT(slotUpdateTime()));
    _timerDate.start(1000);
}

titleDateDriver::~titleDateDriver()
{
    delete ui;
}
void titleDateDriver::setCurrentDateTime(QString strTime)
{
    if(strTime.isEmpty()){
        ui->label_date->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    }
    else {
        ui->label_date->setText(strTime);
    }
}
void titleDateDriver::setDriverName(QString name)
{
    if(name.isEmpty()){
        ui->label_driver->setText("未登录");
    }
    else {
        ui->label_driver->setText(name);
    }
}
void titleDateDriver::slotUpdateTime()
{
    ui->label_date->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
}
