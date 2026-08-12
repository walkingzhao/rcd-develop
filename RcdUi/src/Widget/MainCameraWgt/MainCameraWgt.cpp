#include "MainCameraWgt.h"
#include "ui_MainCameraWgt.h"
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QPainter>
#include <QThread>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QStackedLayout>
#include "Component/btnForm.h"
#include "Component/baseForm.h"

#include "Interface/WgtFactory.h"
#include "Component/soundplay.h"

#include "public/jsonMethord.h"

MainCameraWgt* MainCameraWgt::s_pInstance = nullptr; //初始化静态数据成员

// ---> START BAIYUN 2022/08/02
#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QNetworkAddressEntry>
// <--- END

MainCameraWgt::MainCameraWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::MainCameraWgt)
{
    ui->setupUi(this);

    // 创建控制层
    m_pCL = new MainCameraCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);

    // 创建数据层
    m_pModel = new MainCameraModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    // 页面控件初始化
    ui->modelWgt->setTitleString("驾驶模式  等待连接");
    ui->pingWgt->setFrameType(TGFrame::TipUnderline);
    ui->modelWgt->setFrameType(TGFrame::TipUnderline);
    ui->cloudyStatueWgt->setFrameType(TGFrame::TipUnderline);
    ui->midVideoFrame1->setFrameType(TGFrame::VideoFrameMidPage2No1);
    ui->tachometerWgt->setParameter(RingDial::Tachometer,0,100);
    ui->speedWgt->setParameter(RingDial::Speedometer,0,60);
    ui->brakeWgt->setParameter(TriangleFill::Brake,0,100);
    ui->throttleWgt->setParameter(TriangleFill::Throttle,0,100);

    // 显示版本号
//    QString str = DCU_VERSION;
//    ui->label_rcd_version->setText(str.left(1) + str.right(8));
    QString str = QString("V%1.%2.%3").arg(DCU_MAIN_VER).arg(DCU_SUB_VER).arg(DCU_CHANGE_FLAG);
    ui->label_rcd_version->setText(str);
    //ui->wheelWgt->setValue(50);
    //ui->widget_ReversingTrackLine->setParameter(0,180);//倒车轨迹线TC
    //ui->widget_ReversingTrackLine->setCurrentValue(20);//倒车轨迹线

    // 处理页面布局
    while (ui->CVLayout->count() > 0) {
        ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
    }
    ui->CVLayout->addStretch(3);
//    QHBoxLayout *layoutVer = new QHBoxLayout();
//    layoutVer->addStretch(3);
//    layoutVer->addWidget(ui->label_rcd_version,4);
//    layoutVer->addStretch(2);
    ui->label_rcd_version->setGeometry(1180, 46, 80,30);


    // --> BEGIN 标题栏
    pHLayout = new QHBoxLayout();
    pHLayout->addStretch(2);
    pHLayout->addWidget(ui->modelWgt,5);

    //时间+司机
    pHLayout->addStretch(9);
    pHLayout->addWidget(ui->widget_date_dirver,3);


    pHLayout->addStretch(9);
    pHLayout->addWidget(ui->pingWgt,6);

//    pHLayout->addStretch(1);
    pHLayout->addSpacing(6);
    pHLayout->addWidget(ui->cloudyStatueWgt,5);
    ui->cloudyStatueWgt->hide();
    pHLayout->addStretch(2);
    // <-- END 标题栏

    //gear
//    ui->gearWgt->setParameter(true);
    //ui->gearWgt = new gearProWidget(true, this);
    ui->gearWgt->setmode(1);

    // ---> START BAIYUN 2022/08/02
    ui->netSpeedWgt->setFrameType(TGFrame::TipUnderline);
    ui->netSpeedWgt->setTitleString("网速RX   0 KB/s");
    ui->netSpeedWgt->setGeometry(50, 980, 230,40);
//    pHLayoutNet = new QHBoxLayout();
////    pHLayoutNet->addStretch(2);
//    pHLayoutNet->addSpacing(6);
//    pHLayoutNet->addWidget(ui->netSpeedWgt, 1);
//    pHLayoutNet->addStretch(5);

    ui->trackLineWgt->setGeometry(0,0,1920,1080);
    // <--- END

    // --> BEGIN two camera
    ui->frontLeftVideoFrame->setFrameType(TGFrame::None);
    ui->front_rightVideoFrame->setFrameType(TGFrame::None);
    ui->frontLeftVideoFrame->setFixedSize(710,400);//460x260
    ui->front_rightVideoFrame->setFixedSize(710,400);//460x260

    pHLayoutVideo = new QHBoxLayout();
    pHLayoutVideo->addSpacing(1);//5
    pHLayoutVideo->addWidget(ui->frontLeftVideoFrame);
    pHLayoutVideo->addStretch();
    pHLayoutVideo->addWidget(ui->front_rightVideoFrame);
    pHLayoutVideo->addSpacing(1);//5
    // <-- END

    //    ui->widget_msg->showFullScreen();
    m_pCurrentWgt.clear();

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_AcceptTaskWork);// 接受任务
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    //    qDebug()<<"msg parent:"<<m_pCurrentWgt[SA_MainScreenMsg]->parentWidget()->objectName();
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_CompleteOperEnd); // 结束接管
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_CompleteOperStart);//开始接管
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_GiveUpTakeOver);//放弃任务
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_NetworkInterruption);//网络中断
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);op
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    // --> BEGIN added by ZJZ, 2022/3/1
    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_TipsPopup);//disconnect from cloudy
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();
    // <-- END

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_NotSatisfiedWithTakeover);//不满足接管
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_TaskWorkChange);//任务变更
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();


    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_MainCameraTip);//提示信息
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();


    m_pCurrentWgt[SA_MainScreenMsg] = WgtFactory::getFunWidget(MD_FastStop);//fast stop
    //    m_pCurrentWgt[SA_MainScreenMsg]->setParent(this);
    ui->gridLayout_msg->addWidget(m_pCurrentWgt[SA_MainScreenMsg]);
    m_pCurrentWgt[SA_MainScreenMsg]->hide();

    ui->CVLayout->addLayout(pHLayout,2);//3
    ui->CVLayout->addSpacing(1);//3
    ui->CVLayout->addLayout(pHLayoutVideo,3);
    ui->CVLayout->addStretch(8);//16
    ui->CVLayout->addLayout(ui->gridLayout,20);

    m_pSLayout = new QStackedLayout(this);
    m_pSLayout->setStackingMode(QStackedLayout::StackAll);
    m_pSLayout->insertWidget(0,ui->widget_msg);
    m_pSLayout->insertWidget(0,ui->cameraTitle);
    m_pSLayout->insertWidget(0,ui->widget_front);//old 图像数据显示界面
    m_pSLayout->insertWidget(0,ui->trackLineWgt);
    m_pSLayout->insertWidget(0,ui->laneBoundaryWgt);

    ui->trackLineWgt->setGeometry(0,0,1920,1080);
    ui->laneBoundaryWgt->setGeometry(0,0,1920,1080);

//    m_pSLayout->insertWidget(0,ui->widget_TrackLine);
    m_pSLayout->setCurrentWidget(ui->widget_msg);
    this->setLayout(m_pSLayout);


//    ui->widget_front->setFixedSize(1920,1080);

    //connect(&_testTimer,SIGNAL(timeout()),this,SLOT(slotTimerTest()));
    //        _testTimer.start(100);
    ui->front_leftPlayWgt->setShadowType(TGFrame::ShadowMidPage2No1);
    ui->front_rightPlayWgt->setShadowType(TGFrame::ShadowMidPage2No1);

    // ---> START BAIYUN 2022/08/02
    // show network speed
    QList<QNetworkInterface> netList =  QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface net,netList){//遍历每一个接口信息
        qDebug()<<"Device:"<<net.name();//设备名称
        if("eno" == net.name().mid(0,3)){
            strNetworkName = net.name() + ":";
        }
        qDebug()<<"strNetworkName:"<<strNetworkName;
    }

    _networkSpeedTimer = new QTimer(this);
    connect(_networkSpeedTimer,SIGNAL(timeout()),this,SLOT(get_net_usage()));
    _networkSpeedTimer->start(m_timer_interval__);

    m_net_usage_file.setFileName("net_usage.txt");
    if (!m_net_usage_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Could not open net_usage file!";
    }

    m_communication_delay_file.setFileName("communication_delay.txt");
    if (!m_communication_delay_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Could not open communication_delay file!";
    }
    // <--- END
}

MainCameraWgt::~MainCameraWgt()
{
    delete ui;
    delete m_pModel;
    m_net_usage_file.close();
    m_communication_delay_file.close();
}

MainCameraWgt *MainCameraWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new MainCameraWgt();
    }
    return s_pInstance;
}

void MainCameraWgt::initWidget()
{
    //    qInfo()<<"MainCameraWgt::initWidget";

}

bool MainCameraWgt::isQuit()
{
    //    qInfo()<<"MainCameraWgt::isQuit";
    m_pCL->exitAction();
    return true;
}
#ifdef HIK_INTERFACE
void MainCameraWgt::updateWidget()
{
    //    qInfo()<<"MainCameraWgt::updateWidget";
    // In HIK mode, play the configured stream URL (e.g. RTMP from media server).
    if(!m_pModel->m_frontCameraUrl.isEmpty())
        ui->frontPlayWgt->startPlay(m_pModel->m_frontCameraUrl);//old 图像数据显示界面
    if(!m_pModel->m_backCameraUrl.isEmpty())
        ui->backPlayWgt->startPlay(m_pModel->m_backCameraUrl);//old 后摄像头图像数据显示界面

    ui->midVideoFrame1->hide();

    if(System::getInstance()->forwardLeft_forwardRight_Big)
    {
        ui->front_leftPlayWgt->stopPlay();
        ui->front_rightPlayWgt->stopPlay();
        ui->frontLeftVideoFrame->hide();
        ui->front_rightVideoFrame->hide();
    }else
    {
        if (m_pModel->m_front_left_CameraUrl != "")
        {
            ui->frontLeftVideoFrame->show();
            ui->front_leftPlayWgt->startPlay(m_pModel->m_front_left_CameraUrl);
        }else
        {
            ui->front_leftPlayWgt->stopPlay();
            ui->frontLeftVideoFrame->hide();
        }

        if (m_pModel->m_front_right_cameraUrl != "")
        {
            ui->front_rightVideoFrame->show();
            ui->front_rightPlayWgt->startPlay(m_pModel->m_front_right_cameraUrl);
        }else
        {
            ui->front_rightPlayWgt->stopPlay();
            ui->front_rightVideoFrame->hide();
        }
    }

    if ((m_pModel->m_front_left_CameraUrl == "") &&
        (m_pModel->m_front_right_cameraUrl == "")) {
        while (ui->CVLayout->count() > 0) {
            ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
        }
        ui->CVLayout->addStretch(3);
        ui->CVLayout->addLayout(pHLayout,2);
        ui->CVLayout->addSpacing(1);
        ui->CVLayout->addLayout(pHLayoutVideo,3);
        ui->CVLayout->addStretch(18);
        ui->CVLayout->addLayout(ui->gridLayout,20);
    } else {
        while (ui->CVLayout->count() > 0) {
            ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
        }
        ui->CVLayout->addStretch(3);
        ui->CVLayout->addLayout(pHLayout,2);
        ui->CVLayout->addStretch(1);
        ui->CVLayout->addLayout(pHLayoutVideo,3);
        if(System::getInstance()->forwardLeft_forwardRight_Big){
            ui->CVLayout->addStretch(18);
        }else{
            ui->CVLayout->addStretch(5);
        }
        ui->CVLayout->addLayout(ui->gridLayout,20);
    }

    ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  未连接"));
    ui->cloudyStatueWgt->setTitleString(QString::fromUtf8("座舱-平台连接  未连接"));
//    ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  延迟999ms"));
//    ui->cloudyStatueWgt->setTitleString(QString::fromUtf8("座舱-平台连接  已连接"));

//    ui->modelWgt->setTitleString(QString::fromUtf8("驾驶状态：监控中"));
    ui->speedWgt->setParameter(RingDial::Speedometer,m_pModel->m_speed.min,m_pModel->m_speed.max);
    ui->brakeWgt->setParameter(TriangleFill::Brake,m_pModel->m_brake.min,m_pModel->m_brake.max);
    ui->throttleWgt->setParameter(TriangleFill::Throttle,m_pModel->m_throttle.min,m_pModel->m_throttle.max);
    ui->wheelWgt->setParameter(m_pModel->m_wheel.min,m_pModel->m_wheel.max);
    //ui->widget_ReversingTrackLine->setParameter(m_pModel->m_wheel.min,m_pModel->m_wheel.max);///倒车轨迹线
    this->update();
}
#else
void MainCameraWgt::updateWidget()
{
    qInfo()<<"updatexzk MainCameraWgt::updateWidget";

    ui->frontPlayWgt->startPlay(m_pModel->m_frontCameraUrl);//old 图像数据显示界面
    ui->backPlayWgt->startPlay(m_pModel->m_backCameraUrl);//old 后摄像头图像数据显示界面

    ui->midVideoFrame1->hide();

    // --> BEGIN added by ZJZ, 2022/5/10
    if(System::getInstance()->forwardLeft_forwardRight_Big)//隐藏
    {
        ui->front_leftPlayWgt->stopPlay();
        ui->front_rightPlayWgt->stopPlay();
        ui->frontLeftVideoFrame->hide();
        ui->front_rightVideoFrame->hide();
    }else//显示
    {
        if (m_pModel->m_front_left_CameraUrl != "")
        {
            ui->frontLeftVideoFrame->show();
            ui->front_leftPlayWgt->startPlay(m_pModel->m_front_left_CameraUrl);
        }else
        {
            ui->front_leftPlayWgt->stopPlay();
            ui->frontLeftVideoFrame->hide();
        }

        if (m_pModel->m_front_right_cameraUrl != "")
        {
            ui->front_rightVideoFrame->show();
            ui->front_rightPlayWgt->startPlay(m_pModel->m_front_right_cameraUrl);
        }else
        {
            ui->front_rightPlayWgt->stopPlay();
            ui->front_rightVideoFrame->hide();
        }
    }


    if ((m_pModel->m_front_left_CameraUrl == "") &&
        (m_pModel->m_front_right_cameraUrl == "")) {
        while (ui->CVLayout->count() > 0) {
            ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
        }
        ui->CVLayout->addStretch(3);
#if 0
        ui->CVLayout->addLayout(pHLayout,3);
        ui->CVLayout->addStretch(10);
        ui->CVLayout->addLayout(pHLayoutVideo,3);
        ui->CVLayout->addStretch(16);
        ui->CVLayout->addLayout(ui->gridLayout,20);
#endif
        ui->CVLayout->addLayout(pHLayout,2);//3
        ui->CVLayout->addSpacing(1);//3
        ui->CVLayout->addLayout(pHLayoutVideo,3);
        ui->CVLayout->addStretch(18);//22
        ui->CVLayout->addLayout(ui->gridLayout,20);
    }
    // <-- END
    // --> BEGIN 每次进入单车重新布局, 2022/09/15
    else{
        if(System::getInstance()->forwardLeft_forwardRight_Big){
            while (ui->CVLayout->count() > 0) {
                ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
            }
            ui->CVLayout->addStretch(3);
            ui->CVLayout->addLayout(pHLayout,2);
            ui->CVLayout->addStretch(1);
            ui->CVLayout->addLayout(pHLayoutVideo,3);
//            ui->CVLayout->addStretch(25);
            ui->CVLayout->addStretch(18);
            ui->CVLayout->addLayout(ui->gridLayout,20);
        }else{
            while (ui->CVLayout->count() > 0) {
                ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
            }
            ui->CVLayout->addStretch(3);
            ui->CVLayout->addLayout(pHLayout,2);
            ui->CVLayout->addStretch(1);
            ui->CVLayout->addLayout(pHLayoutVideo,3);
//            ui->CVLayout->addStretch(8);
            ui->CVLayout->addStretch(5);
            ui->CVLayout->addLayout(ui->gridLayout,20);
        }
    }
    // <-- END


    if ("等待连接" == strDriveMode) {
        ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  未连接"));
    }else{
        if(m_pModel->m_vehicleDelay == 0){
            ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  延迟<1 ms"));
        }else{
            ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  延迟%1 ms").arg(m_pModel->m_vehicleDelay));
        }
    }

    ui->speedWgt->setParameter(RingDial::Speedometer,m_pModel->m_speed.min,m_pModel->m_speed.max);
    ui->brakeWgt->setParameter(TriangleFill::Brake,m_pModel->m_brake.min,m_pModel->m_brake.max);
    ui->throttleWgt->setParameter(TriangleFill::Throttle,m_pModel->m_throttle.min,m_pModel->m_throttle.max);
    ui->wheelWgt->setParameter(m_pModel->m_wheel.min,m_pModel->m_wheel.max);
    //ui->widget_ReversingTrackLine->setParameter(m_pModel->m_wheel.min,m_pModel->m_wheel.max);///倒车轨迹线

    this->update();
}
#endif

void MainCameraWgt::showEvent(QShowEvent *)
{
    QWidget *pWidget = static_cast<QWidget*>(this->parent());
    pWidget->activateWindow();
    pWidget->grabKeyboard(); //强制抓取键盘输入，并使当前界面获取键盘焦点。
}

void MainCameraWgt::hideEvent(QHideEvent *)
{
}

void MainCameraWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {

    case MainCameraCL::CL_StartPlay:
    {
        if(data.toBool())
        {
            qInfo()<<"updatexzk MainCameraWgt::startPlay";
            m_pCL->intoAction();
            this->updateWidget();
        }else
        {
            qInfo()<<"updatexzk MainCameraWgt::stopPlay";
            ui->frontPlayWgt->stopPlay();//old 图像数据显示界面
            ui->backPlayWgt->stopPlay();

            ui->front_leftPlayWgt->stopPlay();
            ui->front_rightPlayWgt->stopPlay();
        }
        break;
    }
    case MainCameraCL::CL_UpdateFrontLeftRightCamera:
    {
        m_pCL->intoAction();
        this->updateWidget();
        break;
    }
    case MainCameraCL::CL_UpdatePosition:
    {
//        qDebug()<<"主摄像头收到位置更新报文";
        if(m_pModel->gpsAvailable==false)
            ui->widget_LaneBoundary->newConnect(m_pModel->m_GpsInfo);
        else
            ui->widget_LaneBoundary->boundaryComputer(m_pModel->m_GpsInfo);

        m_pModel->gpsAvailable=true;
        ui->widget_LaneBoundary->show();
        break;
    }
    case MainCameraCL::CL_InputKey:
    {
        QWidget *pWidget = static_cast<QWidget*>(this->parent());
//        if(pWidget==nullptr) return;
        pWidget->activateWindow();
        pWidget->releaseKeyboard(); //有按键按下，完成抓取，释放全局按键抓取。
        break;
    }
    case MainCameraCL::CL_UpdateLoginStatus:
    {
        ui->widget_date_dirver->setDriverName(System::getInstance()->getCurrentDriverLoginStatus().simplified());
        break;
    }
    case MainCameraCL::CL_UpdateState:
    {
        if (strDriveMode != data.toString()) {
            strDriveMode = data.toString();
            if("等待连接" == strDriveMode){
                ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  未连接"));
                System::getInstance()->setCurrentCabinMode(CM_WaitTask);
            }else if("监控中" == strDriveMode){
                System::getInstance()->setCurrentCabinMode(CM_WaitTakeover);
            }
            ui->modelWgt->setTitleString("驾驶模式  " + strDriveMode);
        }
        break;
    }
    case MainCameraCL::CL_UpdateCloudyState:
    {
        ui->cloudyStatueWgt->setTitleString(data.toString());
        break;
    }
    default:
        break;
    }
}

// 数据更新触发页面更新
void MainCameraWgt::onModelUpdate(int cmd)
{
    MainCameraModel::ModelCmdType tCmd = static_cast<MainCameraModel::ModelCmdType>(cmd);
    switch (tCmd) {

    case MainCameraModel::MC_UpdateAll:
    {
        // this->updateWidget();
        break;
    }

    case MainCameraModel::MC_ThrottleBrakeWheel:// ZJZ: unused
    {
        ui->brakeWgt->setValue(m_pModel->m_brake.current);//刹车

        ui->wheelWgt->setValue(m_pModel->m_wheel.current);//方向盘角度

        ui->throttleWgt->setValue(m_pModel->m_throttle.current);

        break;
    }
    case MainCameraModel::MC_Brake:{
        // --> BEGIN added by ZJZ, 2022/5/10
        ui->brakeWgt->setBrakeType(m_pModel->brakeType);
        // <-- END

        ui->brakeWgt->setValue(m_pModel->m_brake.current);
        break;
    }
    case MainCameraModel::MC_Throttle:{//加速踏板百分比
        ui->throttleWgt->setValue(m_pModel->m_throttle.current);
        break;
    }
    case MainCameraModel::MC_Wheel:{//方向盘转角
        ui->wheelWgt->setValue(m_pModel->m_wheel.current);

        qDebug()<<"方向盘转角:"<<m_pModel->m_wheel.current<<"档位："<<m_pModel->m_gear;
        try{
            // ---> START BAIYUN 2022/08/02
#if 0
            if(m_pModel->m_gear==gearWidget::Gear_D){
                ui->widget_TrackLine->trackLineShow(m_pModel->m_wheel.current,FRONT_MODE,m_pModel->m_TrackLineCfg);//前进车线
            }
            else if(m_pModel->m_gear==gearWidget::Gear_R){
                ui->widget_TrackLine->trackLineShow(m_pModel->m_wheel.current,BACK_MODE,m_pModel->m_TrackLineCfg);//倒车轨迹线
            }else{
                ui->widget_TrackLine->hide();
            }
#endif
            if(m_pModel->m_gear==gearProWidget::Gear_R){
                ui->widget_TrackLine->trackLineShow(m_pModel->m_wheel.current,BACK_MODE,m_pModel->m_TrackLineCfg);//倒车轨迹线
            }else{
                ui->widget_TrackLine->trackLineShow(m_pModel->m_wheel.current,FRONT_MODE,m_pModel->m_TrackLineCfg);//前进车线
            }
            // <--- END
        }catch(const std::out_of_range& oor){
            qDebug()<<"angle out_of_range,so not result:"<<m_pModel->m_wheel.current;
        }
        break;
    }
    case MainCameraModel::MC_Speed://速度
    {
        ui->speedWgt->setDialMaxValue(System::getInstance()->warningSpeed);
        ui->speedWgt->setValue(m_pModel->m_speed.current);
        if(m_pModel->m_speed.current >= System::getInstance()->warningSpeed)
        {
//            ui->speedWgt->setPenColor(QColor(255,0,0));

            SoundPlay::instance()->addSound(SOUND_LEVEL_TIP,"qrc:/resource/voice/车速过快请减速.mp3");//车速过快，请减速
        }else
        {
//            ui->speedWgt->setPenColor(QColor(0x3d, 0xfe, 0xfe));
        }
        break;
    }
    case MainCameraModel::MC_Gear://档位
    {
        if(m_pModel->m_TrackLineCfg.valid)
        {
              qDebug() << "+++++++++==+= 0808 valid = true";
        }
        else
        {
            qDebug() << "+++++++++==+= 0808 valid = false";
        }
        // ---> START BAIYUN 2022/08/02
        if(false == System::getInstance()->forwardLeft_forwardRight_Big){
            if(m_pModel->m_gear == gearProWidget::Gear_R){
                if (m_pModel->m_front_left_CameraUrl != ""){
                    ui->frontLeftVideoFrame->hide();
                }
                if (m_pModel->m_front_right_cameraUrl != ""){
                    ui->front_rightVideoFrame->hide();
                }
            }else{
                if (m_pModel->m_front_left_CameraUrl != ""){
                    ui->frontLeftVideoFrame->show();
                }
                if (m_pModel->m_front_right_cameraUrl != ""){
                    ui->front_rightVideoFrame->show();
                }
            }
        }

        if(m_pModel->m_gear==gearProWidget::Gear_N){
//            ui->widget_TrackLine->hide();
            ui->widget_TrackLine->show();
        }else if(m_pModel->m_gear==gearProWidget::Gear_D && m_pModel->m_TrackLineCfg.valid) {
            ui->widget_TrackLine->show();
        }
        else if(m_pModel->m_gear==gearProWidget::Gear_R && m_pModel->m_TrackLineCfg.valid){
            ui->widget_TrackLine->show();
        }
#if 0
        else if (m_pModel->m_gear==gearProWidget::Gear_P) {
//            ui->widget_TrackLine->hide();
            ui->widget_TrackLine->show();
        }
#endif
        //-- P
//        if(1 == m_pModel->m_content.vehicleCmd.parkCtrl){
//            gear_p->show();
//        }else if(0 == m_pModel->m_content.vehicleCmd.parkCtrl){
//            gear_p->hide();
//        }
        // <--- END

        this->changeLayout(m_pModel->m_gear);
        ui->gearWgt->setValue(m_pModel->m_gear);
        qDebug() << "current m_gear=" << m_pModel->m_gear;

        qDebug()<<"widget_LaneBoundary size:"<<ui->widget_LaneBoundary->size()
               <<ui->widget_TrackLine->size();
        break;
    }
    case MainCameraModel::MC_Parking:
    {
        ui->gearWgt->setParking(m_pModel->m_parking);
        break;
    }
    case MainCameraModel::MC_Loading:
    {
        ui->gearWgt->setLoading(m_pModel->m_loading);
        break;
    }
    case MainCameraModel::MC_Delay:
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
        QTextStream out(&m_communication_delay_file);
        if(m_pModel->m_vehicleDelay == 0){
            ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  延迟<1 ms"));
            QString str = QString("%1 - 座舱-车辆连接  延迟<1 ms\n");
            QString resultString = str.arg(dateTimeString);
            out << resultString;
        }else{
            ui->pingWgt->setTitleString(QString::fromUtf8("座舱-车辆连接  延迟%1 ms").arg(m_pModel->m_vehicleDelay));
            QString str = QString("%1 - 座舱-车辆连接  延迟%2 ms\n");
            QString resultString = str.arg(dateTimeString).arg(m_pModel->m_vehicleDelay);
            out << resultString;
        }
        break;
    }
    case MainCameraModel::MC_RemoteStatus:
    {
        ui->modelWgt->setTitleString(getRemoteStatusStr(m_pModel->m_remoteStatus));
        break;
    }
    case MainCameraModel::MC_Throttle_RingDila://转速单位换算需要÷100
    {
        ui->tachometerWgt->setDialMaxValue(35);
        ui->tachometerWgt->setValue(m_pModel->m_speed_raw.current/100);
        break;
    }
    case MainCameraModel::MC_Keyboard_msg:{


        break;
    }
    default:
        break;
    }
}

QString MainCameraWgt::getRemoteStatusStr(MainCameraModel::RemoteStatus status)
{
    switch (status) {
    case MainCameraModel::RS_Monitoring: {
        if ("等待连接" == strDriveMode) {
            return QString::fromUtf8("驾驶模式  等待连接");
        }
        return QString::fromUtf8("驾驶模式  监控中");
        break;
    }
    case MainCameraModel::RS_RemoteControl: {
        return QString::fromUtf8("驾驶模式  远程接管中");
        break;
    }
    case MainCameraModel::RS_RemoteControlFail: {
        return QString::fromUtf8("驾驶模式  遥控失败");
        break;
    }
    case MainCameraModel::RS_RemoteControlDisconnect: {
        return QString::fromUtf8("驾驶模式  已断连");
        break;
    }
    case MainCameraModel::RS_RemoteConnectionRefused: {
        return QString::fromUtf8("驾驶模式  车辆拒绝");
        break;
    }
    case MainCameraModel::RS_RemoteConnectionTimedOut: {
        return QString::fromUtf8("驾驶模式  连接超时");
        break;
    }
    case MainCameraModel::RS_RemoteControlUnknownVehicle: {
        return QString::fromUtf8("驾驶模式  车辆未知");
        break;
    }
    default:
        break;
    }
    return QString();
}

void MainCameraWgt::clearLayout()
{
    QLayoutItem *child;
    while ((child = ui->gridLayout_msg->takeAt(0)) != 0)
    {//setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
}

// 倒档时的后视镜布局改变处理。
void MainCameraWgt::changeLayout(int layout)
{
//    static int sLastType = gearProWidget::Gear_P;
    static int sLastType = gearProWidget::Gear_R;
    if(layout == sLastType) return;
    if(layout == gearProWidget::Gear_R){//R档
        m_pSLayout->removeWidget(ui->frontPlayWgt);
        ui->minPLayout->removeWidget(ui->backPlayWgt);
        m_pSLayout->insertWidget(0,ui->backPlayWgt);//
        ui->minPLayout->addWidget(ui->frontPlayWgt,1);
        ui->frontPlayWgt->setShadowType(TGFrame::ShadowMidPage2No1);
        ui->backPlayWgt->show();
//        ui->backPlayWgt->startPlay(m_pModel->m_backCameraUrl);
        ui->frontPlayWgt->show();
        ui->midVideoFrame1->show();

        // ---> START BAIYUN 2022/08/02
        while (ui->CVLayout->count() > 0) {
            ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
        }
        ui->CVLayout->addStretch(3);
        ui->CVLayout->addLayout(pHLayout,2);//3
        ui->CVLayout->addSpacing(1);//3
//        ui->CVLayout->addLayout(pHLayoutVideo,3);
        ui->CVLayout->addStretch(27);//16
        ui->CVLayout->addLayout(ui->gridLayout,20);
        // <--- END
    }
//    else if(layout != gearWidget::Gear_R && sLastType == gearWidget::Gear_R){
    else if(sLastType == gearProWidget::Gear_R)// if(layout == gearWidget::Gear_D && sLastType != gearWidget::Gear_D)
    {
        m_pSLayout->removeWidget(ui->backPlayWgt);
        ui->minPLayout->removeWidget(ui->frontPlayWgt);
        m_pSLayout->insertWidget(0,ui->frontPlayWgt);
        ui->minPLayout->addWidget(ui->backPlayWgt,1);
        ui->frontPlayWgt->show();
        ui->frontPlayWgt->setShadowType(TGFrame::None);
        ui->midVideoFrame1->hide();
//        ui->backPlayWgt->stopPlay();
        ui->backPlayWgt->hide();

        // ---> START BAIYUN 2022/08/02
        while (ui->CVLayout->count() > 0) {
            ui->CVLayout->removeItem(ui->CVLayout->itemAt(0));
        }
        ui->CVLayout->addStretch(3);
        ui->CVLayout->addLayout(pHLayout,2);//3
        ui->CVLayout->addSpacing(1);//3
        ui->CVLayout->addLayout(pHLayoutVideo,3);
        ui->CVLayout->addStretch(8);//16
        ui->CVLayout->addLayout(ui->gridLayout,20);
        // <--- END
    }
    sLastType = layout;
}

void  MainCameraWgt::slotTimerTest()
{
}

// ---> START BAIYUN 2022/08/02
// show network speed
bool MainCameraWgt::get_net_usage() {
    QProcess process;
    process.start("cat /proc/net/dev");
    connect(&process, &QProcess::readyReadStandardOutput, [&]()
    {
        QTextStream in(&process);
        while(!in.atEnd()) {
            QString str = in.readLine();
            str.replace("\n","");
            str.replace(QRegExp("( ){1,}")," ");
            auto lst = str.split(" ");
            qDebug() << "str:" << str;
            if(lst.size() > 9 && lst[1] == strNetworkName) {//ens33 "eno1:"
                double recv = 0;
                double send = 0;
                if(lst.size() > 1)
                    recv= lst[2].toDouble();
                if(lst.size() > 9)
                    send= lst[10].toDouble();
            
                double recvData = (recv - m_recv_bytes__) / (m_timer_interval__ / 1000.0) / 1024;
                QString str = QString::number(recvData, 'f', 2);
                if(str=="0.00") str = "0";
                str = QString("网速RX   %1 KB/s").arg(str);
                ui->netSpeedWgt->setTitleString(str);

                // Write to file
                QDateTime currentDateTime = QDateTime::currentDateTime();
                QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
                QString resultString = QString("%1 - 网速RX %2 KB/s\n").arg(dateTimeString).arg(QString::number(recvData, 'f', 2));
                    
                QTextStream out(&m_net_usage_file);
                out << resultString;

                m_recv_bytes__= recv;
                m_send_bytes__= send;
            }
        }
    });
    process.waitForFinished();
#if 0
    process.readLine();
    process.readLine();
    while(!process.atEnd()) {
        QString str = process.readLine();
        str.replace("\n","");
        str.replace(QRegExp("( ){1,}")," ");
        auto lst= str.split(" ");

//        qDebug("str=%s", str.toStdString().c_str());
//        qDebug("list size=%d", lst.size());
//        qDebug() << "lst[0]=" << lst[1];

        if(lst.size() > 9 && lst[1] == strNetworkName) {//ens33 "eno1:"
            double recv = 0;
            double send = 0;
            if(lst.size() > 1)
                recv= lst[2].toDouble();
            if(lst.size() > 9)
                send= lst[10].toDouble();

//            qDebug("%s 接收速度:%.0lfbyte/s 发送速度:%.0lfbyte/s",
//                    lst[1].toStdString().c_str(),
//                    recvData,
//                    (send - m_send_bytes__) / (m_timer_interval__ / 1000.0) / 1024);

            double recvData = (recv - m_recv_bytes__) / (m_timer_interval__ / 1000.0) / 1024;
            QString str = QString::number(recvData, 'f', 2);
            if(str=="0.00") str = "0";
            str = QString("网速RX   %1 KB/s").arg(str);
            ui->netSpeedWgt->setTitleString(str);

            m_recv_bytes__= recv;
            m_send_bytes__= send;
        }
    }
#endif
    return true;
}
// <--- END
