#include "RightWgt1.h"
#include "ui_RightWgt1.h"
#include <QCloseEvent>
#include <QPainter>
#include <QDebug>
#include <QApplication>

#include "Interface/WgtFactory.h"
#include "FunModule/IpcManager.h"

RightWgt1::RightWgt1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RightWgt1)
{
    ui->setupUi(this);
    this->setWindowTitle("RCD");
    //this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    QWidget *pWgt = WgtFactory::getFunWidget(MD_CloudWeb);
    m_pCurrentWgt[SA_RightScreen] = pWgt; //全屏幕

    pWgt = WgtFactory::getFunWidget(MD_RightCamera);
    m_pCurrentWgt[SA_RightScreenLTop] = pWgt; //右屏幕左区域 上

    pWgt = WgtFactory::getFunWidget(MD_CloudWeb);
    m_pCurrentWgt[SA_RightScreenLBottom] = pWgt; //右屏幕左区域 下

    pWgt = WgtFactory::getFunWidget(MD_TakeOverInfo);
    m_pCurrentWgt[SA_RightScreenRTop] = pWgt; //右屏幕右区域 上

    pWgt = WgtFactory::getFunWidget(MD_LoadInstruction);
    m_pCurrentWgt[SA_RightScreenRMid] = pWgt; //右屏幕右区域 中

    pWgt = WgtFactory::getFunWidget(MD_ForwardRightCamera);
    m_pCurrentWgt[SA_RightScreenRTopMid] = pWgt; //右屏幕右区域 上中

    pWgt = WgtFactory::getFunWidget(MD_SystemInfo);
    m_pCurrentWgt[SA_RightScreenRBottom] = pWgt; //右屏幕右区域 下

    m_pGridLayout = new QGridLayout;
    m_pGridLayout->setContentsMargins(50,30,50,30);


    this->setLayout(m_pGridLayout);
    this->setLayoutMonitor();
}

RightWgt1::~RightWgt1()
{
    delete ui;
}

void RightWgt1::closeEvent(QCloseEvent *event)
{
    if(event->type() == QEvent::Close){
        QApplication::exit();
    }
}

void RightWgt1::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QColor(0,0x1d,0x33));
    painter.drawRect(event->rect().x()-2,event->rect().y()-2,
                     event->rect().width()+4,event->rect().height()+4);
    painter.end();
}

void RightWgt1::addShowWidget(int type ,QWidget *pWgt)
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

void RightWgt1::setLayoutMonitor()
{
    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
        iter.value()->hide();
    }
    while (m_pGridLayout->count() > 0) {
        m_pGridLayout->removeItem(m_pGridLayout->itemAt(0));
    }

    m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreen], 0, 0, 10, 16);//10row 16col

    static bool init=false;
    if(!init)
    {
        init=true;
        for(int i=0;i<m_pGridLayout->rowCount();i++)
            m_pGridLayout->setRowStretch(i,1);
        for(int i=0;i<m_pGridLayout->columnCount();i++)
            m_pGridLayout->setColumnStretch(i,1);
    }

    m_pCurrentWgt[SA_RightScreen]->show();
}

void RightWgt1::setLayoutRemoteControl()
{
    for(auto iter = m_pCurrentWgt.begin();iter != m_pCurrentWgt.end();iter++){
        iter.value()->hide();
    }
    while (m_pGridLayout->count() > 0) {
        m_pGridLayout->removeItem(m_pGridLayout->itemAt(0));
    }


    //m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenLTop], 0, 0, 10, 9);
    m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenLTop], 0, 0, 10, 16);
    m_pCurrentWgt[SA_RightScreenLTop]->show();
    //WgtFactory::getFunWidget(MD_RightCamera)->getCL()->intoAction();
    //WgtFactory::getFunWidget(MD_RightCamera)->updateWidget();

    //m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenLBottom], 0, 9, 10, 7);
    //m_pCurrentWgt[SA_RightScreenLBottom]->show();
#if 0
    if(System::getInstance()->forwardLeft_forwardRight_Big)
    {
        m_pCurrentWgt[SA_RightScreenRTop]->hide();
        m_pCurrentWgt[SA_RightScreenRMid]->hide();

        m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenRTopMid], 0, 9, 6, 7);
        m_pCurrentWgt[SA_RightScreenRTopMid]->show();
    }else
    {
        m_pCurrentWgt[SA_RightScreenRTopMid]->hide();

        m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenRTop], 0, 9, 3, 7);
        m_pCurrentWgt[SA_RightScreenRTop]->show();

        m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenRMid], 3, 9, 3, 7);
        m_pCurrentWgt[SA_RightScreenRMid]->show();
    }

    m_pGridLayout->addWidget(m_pCurrentWgt[SA_RightScreenRBottom], 6, 9, 4, 7);
    m_pCurrentWgt[SA_RightScreenRBottom]->show();
#endif
}
