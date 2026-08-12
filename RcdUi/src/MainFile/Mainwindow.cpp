#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include <QCloseEvent>
#include <QPainter>
#include <QDebug>
#include <QScreen>
#include <QSettings>
#include "System.h"
#include "LeftWgt1.h"
#include "MidWgt.h"
#include "RightWgt1.h"
#include "LeftWgt.h"
#include "Component/buttonForm.h"
#include "public/jsonMethord.h"
#define USEMAIN false

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("RCD");
    //this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowTitleHint );

    // 布局选择
#if USEMAIN
    QHBoxLayout * pHLayout = new QHBoxLayout();
    pHLayout->setContentsMargins(0,0,0,0);
    pHLayout->setSpacing(0);

    m_pLeftWgt = new  LeftWgt();
    m_pMidWgt = new  MidWgt();
    m_pRightWgt = new  RightWgt();

    pHLayout->addWidget(m_pLeftWgt,1);
    pHLayout->addWidget(m_pMidWgt,1);
    pHLayout->addWidget(m_pRightWgt,1);

    ui->Background->setLayout(pHLayout);
#else
    int procType = System::getInstance()->getProcessType();
    if(procType & PT_RightProc){
        m_pRightWgt = new  RightWgt1();
    }
    if(procType & PT_MidProc){
        m_pMidWgt = new  MidWgt();
    }
    if(procType & PT_LeftProc){
        m_pLeftWgt = new  LeftWgt1();
        m_pLeftWgt_Monitor = new LeftWgt();

    }

#endif

}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_pLeftWgt != nullptr)
        delete m_pLeftWgt;
    if(m_pLeftWgt_Monitor != nullptr)
        delete  m_pLeftWgt_Monitor;
    if(m_pMidWgt != nullptr)
        delete m_pMidWgt;
    if(m_pRightWgt != nullptr)
        delete m_pRightWgt;
}
//分屏展示
void MainWindow::showAll()
{

#if USEMAIN
    this->show();
#else
    QList<QScreen *> allScreen =  QGuiApplication::screens();
    QVariant dataScreen= jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","ScreenNum");
    if(dataScreen.toList().isEmpty()) return;
    int index = 0;

    int procType = System::getInstance()->getProcessType();
    if(procType & PT_RightProc){
        index = dataScreen.toList()[0].toMap().value("Right").toInt();
        if(index < allScreen.count()){
            m_pRightWgt->setGeometry(allScreen[index]->geometry());
        }
        m_pRightWgt->showFullScreen();
    }
    if(procType & PT_MidProc){
        index = dataScreen.toList()[0].toMap().value("Mid").toInt();
        if(index < allScreen.count()){
            m_pMidWgt->setGeometry(allScreen[index]->geometry());
        }
        m_pMidWgt->showFullScreen();
    }
    if(procType & PT_LeftProc){
        index = dataScreen.toList()[0].toMap().value("Left").toInt();
        if(index < allScreen.count()){
            m_pLeftWgt->setGeometry(allScreen[index]->geometry());
            m_pLeftWgt_Monitor->setGeometry(allScreen[index]->geometry());
        }
        //m_pLeftWgt->hide();
        //m_pLeftWgt_Monitor->showFullScreen();
        m_pLeftWgt->showFullScreen();
        m_pLeftWgt_Monitor->hide();
    }
#endif
}

void MainWindow::switchLayout(int layoutType)
{
    int procType = System::getInstance()->getProcessType();
    LayoutType layout = static_cast<LayoutType>(layoutType);
    switch (layout){
    case LT_Monitor:{//监控时布局
        if(procType & PT_LeftProc){
            //m_pLeftWgt_Monitor->showFullScreen();
            //m_pLeftWgt->hide();
            m_pLeftWgt->showFullScreen();
            m_pLeftWgt_Monitor->hide();
        }
        if(procType & PT_RightProc){
            /*m_pRightWgt->setLayoutMonitor();*/
            m_pRightWgt->setLayoutRemoteControl();
        }
        break;
    }
    case LT_RemoteControl:{//遥控时布局
        if(procType & PT_LeftProc){
            m_pLeftWgt->showFullScreen();
            m_pLeftWgt_Monitor->hide();
        }
        if(procType & PT_RightProc){
            m_pRightWgt->setLayoutRemoteControl();
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::addShowWidget(int type ,QWidget *pWgt)
{
    ScreenAreaType tType = static_cast<ScreenAreaType>(type);
    int procType = System::getInstance()->getProcessType();
    switch (tType) {
    case SA_MainScreen:{
        if(procType & PT_MidProc){
            m_pMidWgt->addShowWidget(type,pWgt);
        }
    }break;

    case SA_RightScreenL:

    case SA_RightScreenR:
//    {
//        if(procType & PT_RightProc){
//            m_pRightWgt->addShowWidget(type,pWgt);
//        }
//    }
        break;
    case SA_LeftScreenTopL:
    case SA_LeftScreenTopR:
    case SA_LeftScreenBottom:{
        if(procType & PT_LeftProc){
            m_pLeftWgt->addShowWidget(type,pWgt);
        }
    }break;

    case SA_RightScreen:
//    {
//        if(procType & PT_RightProc){
//            m_pRightWgt->addShowWidget(type,pWgt);
//        }
//    }
        break;
    default:break;
    }
}
