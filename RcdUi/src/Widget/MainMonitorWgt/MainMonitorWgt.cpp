#include "MainMonitorWgt.h"
#include "ui_MainMonitorWgt.h"
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QThread>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <qpixmap.h>
#include <QImage>
#include "Interface/WgtFactory.h"
#include "../../pubinc/version.h"

MainMonitorWgt* MainMonitorWgt::s_pInstance = nullptr; //初始化静态数据成员

MainMonitorWgt::MainMonitorWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::MainMonitorWgt)
{
    ui->setupUi(this);
    // 创建控制层
    m_pCL = new MainMonitorCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);
    // 创建数据层
    m_pModel = new MainMonitorModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);
    // 布局
    //    QHBoxLayout * pHLayout = new QHBoxLayout;

    // 显示版本号
//    QString str = DCU_VERSION;
//    ui->label_rcd_version->setText(str.left(1) + str.right(8));
    QString str = QString("V%1.%2.%3").arg(DCU_MAIN_VER).arg(DCU_SUB_VER).arg(DCU_CHANGE_FLAG);
    ui->label_rcd_version->setText(str);
    ui->label_rcd_version->setGeometry(1180, 46, 80,30);


    // self test button
    QString button_style = "QToolButton {background:url(:/resource/test/selfTest.png) top center no-repeat; font-size:12px; padding-top:36px;font-family:Microsoft YaHei; color:rgb(0,0,0); border:none;}\
    QToolButton:hover {background:url(:/resource/test/selfTestClicked.png) top center no-repeat; font-size:12px; padding-top:36px;font-family:Microsoft YaHei; color:rgb(0,0,0); border:none;}\
    QToolButton:pressed {background:url(:/resource/test/selfTestClicked.png) top center no-repeat; font-size:12px; padding-top:36px;font-family:Microsoft YaHei; color:rgb(0,0,0); border:none;}\;";
    selfTestBtn = new QToolButton(this);
    selfTestBtn->setStyleSheet(button_style);
    selfTestBtn->setFixedSize(107,108);
    selfTestBtn->setIconSize(QSize(107,108));
    selfTestBtn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    selfTestBtn->setGeometry(1920-138, 1080-150, 107,108);
    selfTestBtn->setAutoRaise(true);
    connect(selfTestBtn, SIGNAL(clicked()), this, SLOT(on_selfTestBtn()));

//    m_pCurrentWgt.clear();
//    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_TipsPopup);//disconnect from cloudy
//    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
//    m_pCurrentWgt[SA_MainScreenMsg]->hide();

//    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_SelfTest);
//    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
//    m_pCurrentWgt[SA_MainScreenMsg]->hide();


    QVBoxLayout* pVLayout = new QVBoxLayout(ui->title);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->setSpacing(0);
    //时间+司机
    pVLayout->addWidget(ui->widget_date_dirver,7,Qt::AlignCenter);

    QGridLayout *pGridLayout = new QGridLayout();
    pGridLayout->setHorizontalSpacing(10);
    pGridLayout->setVerticalSpacing(20);
    pGridLayout->setContentsMargins(20,0,20,0);
    pVLayout->addLayout(pGridLayout,30);

    pVLayout->addStretch(2);

    pVLayout->addWidget(ui->pageWgt,2);
    pVLayout->addStretch(2);
    pGridLayout->addWidget(ui->midVideoFrame1,0,0,1,1);//起始行 起始列 占行数 占列数
    pGridLayout->addWidget(ui->midVideoFrame2,0,1,1,1);
    pGridLayout->addWidget(ui->midVideoFrame3,0,2,1,1);
    pGridLayout->addWidget(ui->midVideoFrame4,1,0,1,1);
    pGridLayout->addWidget(ui->midVideoFrame5,1,1,1,1);
    pGridLayout->addWidget(ui->midVideoFrame6,1,2,1,1);
    ui->title->setLayout(pVLayout);

    m_frameVector.append(ui->midVideoFrame1);
    m_frameVector.append(ui->midVideoFrame2);
    m_frameVector.append(ui->midVideoFrame3);
    m_frameVector.append(ui->midVideoFrame4);
    m_frameVector.append(ui->midVideoFrame5);
    m_frameVector.append(ui->midVideoFrame6);

    m_playWgtVector.append(ui->playWgt1);
    m_playWgtVector.append(ui->playWgt2);
    m_playWgtVector.append(ui->playWgt3);
    m_playWgtVector.append(ui->playWgt4);
    m_playWgtVector.append(ui->playWgt5);
    m_playWgtVector.append(ui->playWgt6);
    for(auto playWgt : m_playWgtVector){
        playWgt->setShadowType(TGFrame::ShadowMidPage1No1);
    }

    m_nameVector.append(ui->labelImei1);
    m_nameVector.append(ui->labelImei2);
    m_nameVector.append(ui->labelImei3);
    m_nameVector.append(ui->labelImei4);
    m_nameVector.append(ui->labelImei5);
    m_nameVector.append(ui->labelImei6);
}

MainMonitorWgt::~MainMonitorWgt()
{
    delete ui;
    delete m_pModel;
}

MainMonitorWgt *MainMonitorWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new MainMonitorWgt();
    }
    return s_pInstance;
}

void MainMonitorWgt::initWidget()
{
    //    qInfo()<<"MainMonitorWgt::initWidget";
    m_pCL->intoAction();
}

bool MainMonitorWgt::isQuit()
{
    //    qInfo()<<"MainMonitorWgt::isQuit";
    m_pCL->exitAction();
    return true;
}

void MainMonitorWgt::updateWidget()
{
//    bool selected=false;
    for(int i = 0;i < 6;i++){
        QString &imei = m_pModel->m_showVehicle[i];
        if(imei.isEmpty()){//全部不在线
            m_nameVector[i]->clear();
            m_playWgtVector[i]->hideLabel();
            m_frameVector[i]->setFrameType(TGFrame::VideoFrameMidPage2No2);
        }else{
            if(System::getInstance()->onlineVehicle.find(imei)!=System::getInstance()->onlineVehicle.end())//在线 
            {
                m_nameVector[i]->setText(QString::fromUtf8("【%1】").arg(m_pModel->m_vehicleMap[imei].name));
                m_playWgtVector[i]->showLabel(":/resource/car/履带车.jpeg");
                m_frameVector[i]->setFrameType(TGFrame::VideoFrameMidPage1No1);
//                selected = true;
            }else//不在线
            {
                m_nameVector[i]->setText(QString::fromUtf8("【%1】").arg(m_pModel->m_vehicleMap[imei].name));
                m_playWgtVector[i]->showLabel(":/resource/car/履带车.jpeg");
                m_frameVector[i]->setFrameType(TGFrame::VideoFrameMidPage2No2);    
            }
        }
        if(i == m_pModel->m_select){
            m_frameVector[i]->setFrameType(TGFrame::VideoFrameMidPage1No2);
        }
    }
//    if(!selected)
//        m_pModel->m_select = -1;
    ui->pageWgt->setPage(m_pModel->m_pageIndex);
    ui->pageWgt->setMaxPage(m_pModel->m_maxPage);
}

void MainMonitorWgt::showEvent(QShowEvent *)
{
    System::getInstance()->currentTakeoverPurpose=-1;
    QWidget *pWidget = static_cast<QWidget*>(this->parent());
    pWidget->activateWindow();
    pWidget->grabKeyboard(); //强制抓取键盘输入，并使当前界面获取键盘焦点。
    this->updateWidget();
}

void MainMonitorWgt::hideEvent(QHideEvent *)
{
    for(int i = 0;i < 6;i++){
        //        m_playWgtVector[i]->stopPlay();
    }
}

void MainMonitorWgt::onClDataCome(int cmd, QVariant )
{

    MainMonitorCL::CLCmdType tCmd = static_cast<MainMonitorCL::CLCmdType>(cmd);
    switch (tCmd) {
    case MainMonitorCL::CL_UpdateOnlineState:{
        updateWidget();
        break;
    }
    case MainMonitorCL::CL_UpdateAll:{
        if(!this->isHidden()){
            this->updateWidget();
        }
        break;
    }
    case MainMonitorCL::CL_UpdateLoginStatus:{
        ui->widget_date_dirver->setDriverName(System::getInstance()->getCurrentDriverLoginStatus().simplified());
        break;
    }
    case MainMonitorCL::CL_UpdateSelect:{
        updateWidget();
        break;
    }
    case MainMonitorCL::CL_InputKey:{
        QWidget *pWidget = static_cast<QWidget*>(this->parent());
        pWidget->activateWindow();
        pWidget->releaseKeyboard(); //有按键按下，完成抓取，释放全局按键抓取。
        break;
    }
    default:
        break;
    }
}

void MainMonitorWgt::onModelUpdate(int cmd)
{
    MainMonitorModel::ModelCmdType tCmd = static_cast<MainMonitorModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case MainMonitorModel::MC_UpdateAll:
    {
        break;
    }
    case MainMonitorModel::MC_UpdateVehicle:
    {

        break;
    }

    default:
        break;
    }
}

void MainMonitorWgt::on_selfTestBtn()
{
    qDebug() << "++++++++++++++++++++++ on_selfTestBtn";
    m_pCL->keyPress();
}
