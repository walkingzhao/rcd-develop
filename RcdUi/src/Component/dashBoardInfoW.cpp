#include "dashBoardInfoW.h"
#include "ui_dashBoardInfoW.h"

dashBoardInfoW::dashBoardInfoW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dashBoardInfoW)
{
    ui->setupUi(this);
}

dashBoardInfoW::~dashBoardInfoW()
{
    delete ui;
}
