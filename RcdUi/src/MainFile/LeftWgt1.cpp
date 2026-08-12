#include "LeftWgt1.h"
#include "ui_LeftWgt1.h"
#include <QCloseEvent>
#include <QPainter>
#include <QDebug>

#include "Interface/WgtFactory.h"

LeftWgt1::LeftWgt1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftWgt1)
{
    ui->setupUi(this);
    this->setWindowTitle("RCD");
    m_pCurrentWgt.clear();



    //    m_pLogoLayout = new QHBoxLayout();
    //    m_pLogoLayout->addWidget(ui->logoWgt);
    //    m_pLogoLayout->addStretch(2);

    //    m_pGridLayout = new QGridLayout(this);
    ui->m_pGridLayout->setContentsMargins(50,30,50,30);
    //    m_pGridLayout->setHorizontalSpacing(30);
    //    m_pGridLayout->setVerticalSpacing(20);
    //    m_pGridLayout->setRowStretch(0, 8);
    //    m_pGridLayout->setRowStretch(1, 54);
    //    m_pGridLayout->setRowStretch(2, 36);
    //    m_pGridLayout->setColumnStretch(0, 7);
    //    m_pGridLayout->setColumnStretch(1, 8);


    //    m_pCurrentWgt[SA_LeftScreen] = WgtFactory::getFunWidget(MD_UserGuide);
    m_pCurrentWgt[SA_LeftScreenTopL] = WgtFactory::getFunWidget(MD_DriveCamera);
    m_pCurrentWgt[SA_LeftScreenTopR] = WgtFactory::getFunWidget(MD_LeftCamera);
    m_pCurrentWgt[SA_LeftScreenBottomL] = WgtFactory::getFunWidget(MD_FaultInfo);
    m_pCurrentWgt[SA_LeftScreenBottomR] = WgtFactory::getFunWidget(MD_VehicleData);

    this->setLayout(ui->m_pGridLayout);
    //    this->setLayoutMonitor();
    this->setLayoutRemoteControl();
    //    connect(&_timerSwitch,SIGNAL(timeout()),this,SLOT(slotUpdateSwitch()));
    //    _timerSwitch.start(200);
}

LeftWgt1::~LeftWgt1()
{
    delete ui;
}

void LeftWgt1::closeEvent(QCloseEvent *event)
{
    if(event->type() == QEvent::Close){
        QApplication::exit();
    }
}

void LeftWgt1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QColor(0,0x1d,0x33));
    painter.drawRect(event->rect().x()-2,event->rect().y()-2,
                     event->rect().width()+4,event->rect().height()+4);

    painter.end();
}

void LeftWgt1::addShowWidget(int type ,QWidget *pWgt)
{
    ScreenAreaType tType = static_cast<ScreenAreaType>(type);
    if(m_pCurrentWgt[tType] != pWgt) {
        ui->m_pGridLayout->replaceWidget(m_pCurrentWgt[tType],pWgt);
        pWgt->setParent(this);
        pWgt->show();
        m_pCurrentWgt[tType] = pWgt;
    }
    this->repaint();
}

void LeftWgt1::setLayoutMonitor()
{
    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
        iter.value()->hide();

    }
    while (ui->m_pGridLayout->count() > 0) {
        ui->m_pGridLayout->removeItem(ui->m_pGridLayout->itemAt(0));
    }

    ui->m_pGridLayout->addWidget(ui->logoWgt, 0, 0, 1, 4);
    ui->logoWgt->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreen], 1, 0, 9, 9);//10行9列
    m_pCurrentWgt[SA_LeftScreen]->show();


    for(int i=0;i<ui->m_pGridLayout->rowCount();i++)
        ui->m_pGridLayout->setRowStretch(i,1);
    for(int i=0;i<ui->m_pGridLayout->columnCount();i++)
        ui->m_pGridLayout->setColumnStretch(i,1);

}

void LeftWgt1::setLayoutRemoteControl()
{
    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
        iter.value()->hide();

    }
    while (ui->m_pGridLayout->count() > 0) {
        ui->m_pGridLayout->removeItem(ui->m_pGridLayout->itemAt(0));
    }
    QLayoutItem *child;
    while ((child = ui->m_pGridLayout->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(NULL);
            child->widget()->hide();
        }

        delete child;
    }

    ui->m_pGridLayout->addWidget(ui->logoWgt, 0, 0, 1, 4);//1x4
    ui->logoWgt->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenTopL], 1, 0, 9, 4);//9x4
    m_pCurrentWgt[SA_LeftScreenTopL]->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenTopR], 0, 4, 6, 5);//6x5
    m_pCurrentWgt[SA_LeftScreenTopR]->show();

    //ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenBottomL], 6, 0, 4, 4);//4x4
    //m_pCurrentWgt[SA_LeftScreenBottomL]->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenBottomR], 6, 4, 4, 5);//4x5
    m_pCurrentWgt[SA_LeftScreenBottomR]->show();

#if 0
    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenTopL], 1, 0, 5, 4);//5x4
    m_pCurrentWgt[SA_LeftScreenTopL]->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenTopR], 0, 4, 6, 5);//6x5
    m_pCurrentWgt[SA_LeftScreenTopR]->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenBottomL], 6, 0, 4, 4);//4x4
    m_pCurrentWgt[SA_LeftScreenBottomL]->show();

    ui->m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenBottomR], 6, 4, 4, 5);//4x5
    m_pCurrentWgt[SA_LeftScreenBottomR]->show();
#endif
}

