#include "VehicleInfoW.h"
#include "ui_VehicleInfoW.h"

VehicleInfoW::VehicleInfoW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleInfoW)
{
    ui->setupUi(this);
}

VehicleInfoW::~VehicleInfoW()
{
    delete ui;
}
