#include "LeftWgt.h"
#include "ui_LeftWgt.h"
#include <QCloseEvent>
#include <QPainter>
#include <QDebug>
#include <QApplication>

#include "Interface/WgtFactory.h"
#include "FunModule/IpcManager.h"

LeftWgt::LeftWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftWgt)
{
    ui->setupUi(this);
    this->setWindowTitle("RCD");

    m_pCurrentWgt[SA_LeftScreen] = WgtFactory::getFunWidget(MD_UserGuide);
    m_pGridLayout = new QGridLayout(this);
    this->setLayout(m_pGridLayout);
    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
        iter.value()->hide();

    }
    while (m_pGridLayout->count() > 0) {
        m_pGridLayout->removeItem(m_pGridLayout->itemAt(0));
    }

    m_pGridLayout->addWidget(ui->logoWgt, 0, 0, 1, 4);
    ui->logoWgt->show();

    m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreen], 1, 0, 9, 9);
    m_pCurrentWgt[SA_LeftScreen]->show();


    for(int i=0;i<m_pGridLayout->rowCount();i++)
        m_pGridLayout->setRowStretch(i,1);
    for(int i=0;i<m_pGridLayout->columnCount();i++)
        m_pGridLayout->setColumnStretch(i,1);
}

LeftWgt::~LeftWgt()
{
    delete ui;
}

void LeftWgt::closeEvent(QCloseEvent *event)
{
    if(event->type() == QEvent::Close){
        QApplication::exit();
    }
}

void LeftWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QColor(0,0x1d,0x33));
    painter.drawRect(event->rect().x()-2,event->rect().y()-2,
                     event->rect().width()+4,event->rect().height()+4);
    //    int imgX = 0,imgY = 0;
    //    int imgW = m_bgImage.width(),imgH = m_bgImage.height();
    //    painter.drawPixmap(0,0,this->width(),this->height(),m_bgImage,imgX,imgY,imgW,imgH);
    painter.end();
}

void LeftWgt::addShowWidget(int type ,QWidget *pWgt)
{
    ScreenAreaType tType = static_cast<ScreenAreaType>(type);
    if(m_pCurrentWgt[tType] != pWgt) {
        m_pGridLayout->replaceWidget(m_pCurrentWgt[tType],pWgt);
        pWgt->setParent(this);
        pWgt->show();
        m_pCurrentWgt[tType] = pWgt;
    }
    this->repaint();
}

//void LeftWgt::setLayoutMonitor()
//{
//    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
//        iter.value()->setVisible(false);
//    }
//    while (m_pGridLayout->count() > 0) {
//        m_pGridLayout->removeItem(m_pGridLayout->itemAt(0));
//    }
//    m_pGridLayout->addLayout(m_pLogoLayout, 0, 0, 1, 1);

//    m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenBottom], 1, 0, 2, 2);
//    m_pCurrentWgt[SA_LeftScreenBottom]->setVisible(true);

//}

//void LeftWgt::setLayoutRemoteControl()
//{
//    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
//        iter.value()->setVisible(false);
//    }
//    while (m_pGridLayout->count() > 0) {
//        m_pGridLayout->removeItem(m_pGridLayout->itemAt(0));
//    }

//    m_pGridLayout->addLayout(m_pLogoLayout, 0, 0, 1, 1);

//    m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenBottom], 2, 0, 1, 2);
//    m_pCurrentWgt[SA_LeftScreenBottom]->setVisible(true);

//    m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenTopR], 0, 1, 2, 1);
//    m_pCurrentWgt[SA_LeftScreenTopR]->setVisible(true);

//    m_pGridLayout->addWidget(m_pCurrentWgt[SA_LeftScreenTopL], 1, 0, 1, 1);
//    m_pCurrentWgt[SA_LeftScreenTopL]->setVisible(true);
//}

