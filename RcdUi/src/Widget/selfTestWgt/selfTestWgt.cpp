#include "selfTestWgt.h"
#include "ui_selfTestWgt.h"

#include <QApplication>
#include <QFontDatabase>

selfTestWgt* selfTestWgt::s_pInstance = nullptr;

selfTestWgt::selfTestWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::selfTestWgt)
{
    ui->setupUi(this);
    m_pCL = new selfTestCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new selfTestModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

    ui->widget->setFrameType(TGFrame::selfTesttPage1No1);

    initConfig();
    initWgt();
}

void selfTestWgt::initWgt()
{
    //DINPro font
    int fontMediumId = QFontDatabase::addApplicationFont(":/resource/font/DINPro-Medium.otf");
    int fontBoldId = QFontDatabase::addApplicationFont(":/resource/font/DINPro-Medium.otf");
    QString fontMediumName = QFontDatabase::applicationFontFamilies (fontMediumId).at(0);
    QString fontBoldName = QFontDatabase::applicationFontFamilies (fontBoldId).at(0);
    QFont fontVal;
    fontVal.setFamily(fontMediumName);

    //title
    labTitle = new QLabel("座舱部件测试", this);
    labTitle->setStyleSheet("QLabel{color:#EAF7FF;font:20px 'Source Han Sans CN';}");
    labTitle->setGeometry(21,24,128,20);

    labTitleBar = new QLabel("", this);
    labTitleBar->setStyleSheet("QLabel{background-color:#00A8FF;"
                               "border-radius: 1.5px;}");
    labTitleBar->setGeometry(22,49,120,4);

    //wheel
    QString strLeftMax = QString("%1").arg(steeringwheelLeftTotal);
    QString strRightMax = QString("%1").arg(steeringwheelRightOffset);
    QString strMedian = QString("%1").arg(steeringwheelMedian);

#if 1
    selfwheelWgt  = new SteerWheel(this);
    selfwheelWgt->setParameter(-450, 450);
    selfwheelWgt->setFixedSize(194, 194);
    int hCenter = (this->width() - selfwheelWgt->width())/2;
    selfwheelWgt->move(hCenter, 121);
//    selfwheelWgt->setValue(90);
#endif

    ui->testWheel->hide();
//    ui->testWheel->setFixedSize(194, 194);
//    int hCenter = (this->width() - wheelWgt->width())/2;
//    ui->testWheel->move(hCenter, 121);
//    ui->testWheel->setParameter(-540,540);
////    wheelWgt->setValue(90);

    labWheelFront = new QLabel(strMedian, this);
    labWheelFront->setFont(fontVal);
    labWheelFront->setFixedSize(90,38);
    labWheelFront->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labWheelFront->setStyleSheet("QLabel{color:#80ffffff;font:16px;}");
    labWheelFront->move((this->width() - 90)/2,90);

    labWheelLeft = new QLabel(strLeftMax, this);
    labWheelLeft->setFont(fontVal);
    labWheelLeft->setStyleSheet("QLabel{color:#80ffffff;font:16px;}");
    labWheelLeft->move(hCenter-20,280);

    labWheelRight = new QLabel(strRightMax, this);
    labWheelRight->setFont(fontVal);
    labWheelRight->setStyleSheet("QLabel{color:#80ffffff;font:16px;}");
    labWheelRight->move(hCenter+170,280);

    fontVal.setFamily(fontBoldName);
    labWheelBottom = new QLabel("", this);
    labWheelBottom->setFont(fontVal);
    labWheelBottom->setFixedSize(90,38);
    labWheelBottom->setStyleSheet("QLabel{color: #39D352; font: 22px;"
                                  "background-color: #163f5e;"
                                  "border-radius: 4px;"
                                  "border: 1px solid #00121f;}");
    labWheelBottom->move((this->width() - 90)/2, 320);
    labWheelBottom->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //gear
    gearProWgt = new gearProWidget(this);
    hCenter = (this->width()-gearProWgt->width())/2;
    gearProWgt->move(hCenter, 389);
    gearProWgt->setmode(0);

    //-- P
    QImage imgP(":/resource/test/gear_p.png");
    gear_p = new QLabel(this);
    gear_p->resize(30,26);
    gear_p->setPixmap(QPixmap::fromImage(imgP));
    gear_p->move(360,397);
    gear_p->hide();

    //-- brake
    QImage imgBrake(":/resource/test/gear_brake.png");
    gear_brake = new QLabel(this);
    gear_brake->resize(29,27);
    gear_brake->setPixmap(QPixmap::fromImage(imgBrake));
    gear_brake->move(this->width()-386,397);
    gear_brake->hide();

    //pedal
    //--01 电制动踏板
    electric_brake = new RingDialPro(this);
    hCenter = (this->width() - 200)/2;//464
    electric_brake->setParameter(RingDialPro::ElectricBrake_ometer, electricBrakeMin, electricBrakeMax, electricBrakeMin, electricBrakeMax);
//    electric_brake->setValue(2);
    electric_brake->setValue(0);
    electric_brake->setGeometry(hCenter-200, 436, 200, 150);

    QLabel *lab_electric_brake = new QLabel("电制动踏板", this);
    lab_electric_brake->setStyleSheet("QLabel{color:#EAF7FF;font:16px 'Source Han Sans CN';}");
    lab_electric_brake->move(hCenter-200+50,568);

    //--02 行车制动踏板
    mechanical_brake = new RingDialPro(this);
    mechanical_brake->setParameter(RingDialPro::MechanicalBrake_ometer, hydraulicBrakeMin, hydraulicBrakeMax, hydraulicBrakeMin, hydraulicBrakeMax);
//    mechanical_brake->setValue(14);
    mechanical_brake->setValue(0);
    mechanical_brake->setFont(fontVal);
    mechanical_brake->setGeometry(hCenter,436,200,150);

    QLabel *lab_mechanical_brake = new QLabel("行车制动踏板", this);
    lab_mechanical_brake->setFixedWidth(200);
    lab_mechanical_brake->setStyleSheet("QLabel{color:#EAF7FF;font:16px 'Source Han Sans CN';}");
    lab_mechanical_brake->move(hCenter+60,568);

    //--03 油门踏板
    throttle = new RingDialPro(this);
    throttle->setParameter(RingDialPro::Throttle_ometer, acceleratorMin, acceleratorMax, acceleratorMin, acceleratorMax);
//    throttle->setValue(700);
    throttle->setValue(0);
    throttle->setGeometry(hCenter+200,436,200,150);


    QLabel *lab_throttle = new QLabel("油门踏板", this);
    lab_throttle->setStyleSheet("QLabel{color:#EAF7FF;font:16px 'Source Han Sans CN';}");
    lab_throttle->move(hCenter+200+65,568);

    //light
    QImage imgLight(":/resource/test/light_off.png");
    light = new QLabel(this);
    light->resize(159,159);
    light->setPixmap(QPixmap::fromImage(imgLight));
    light->move(192,220);

    QLabel *lab_light = new QLabel("灯光旋钮", this);
    lab_light->setFixedWidth(200);
    lab_light->setStyleSheet("QLabel{color:#EAF7FF;font:16px 'Source Han Sans CN';}");
    lab_light->move(192+49,220+146);

    //lift
    QImage imgLift(":/resource/test/lift_down.png");
    lift = new QLabel(this);
    lift->resize(160,159);
    lift->setPixmap(QPixmap::fromImage(imgLift));
    lift->move(this->width()-160-192,220);

    QLabel *lab_lift = new QLabel("举升旋钮", this);
    lab_lift->setFixedWidth(200);
    lab_lift->setStyleSheet("QLabel{color:#EAF7FF;font:16px 'Source Han Sans CN';}");
    lab_lift->move(this->width()-160-192+49,220+146);

    //scram(stop)
    QImage imgScram(":/resource/test/scram_off.png");
    scramIcon = new QLabel(this);
    scramIcon->resize(93,94);
    scramIcon->setPixmap(QPixmap::fromImage(imgScram));
    scramIcon->move(this->width()-160-192+32,140);
//#if 1
    //beams
    for(int i=0;i<4;++i){
        QString str = QString(":/resource/test/left_icon%1_off.png").arg(i+1);
        QImage img(str);
        leftIcons[i] = new QLabel(this);
        leftIcons[i]->resize(90,40);
        leftIcons[i]->setPixmap(QPixmap::fromImage(img));
        leftIcons[i]->move(51,239+i*50);
    }

    //icons
    for(int i=0;i<5;++i){
        QString str = QString(":/resource/test/right_icon%1_off.png").arg(i+1);
        QImage img(str);
        rightIcons[i] = new QLabel(this);
        rightIcons[i]->resize(90,40);
        rightIcons[i]->setPixmap(QPixmap::fromImage(img));
        if(3==i){
            rightIcons[i]->move(this->width()-90-51,239+i*50);
        }else if(4==i){
            rightIcons[i]->move(this->width()-90-1,239+(i-1)*50);
        }else{
            rightIcons[i]->move(this->width()-90-51,239+i*50);
        }
    }
}

selfTestWgt::~selfTestWgt()
{
    delete ui;
}

selfTestWgt *selfTestWgt::GetInstance()
{
    if (s_pInstance == nullptr) {
        s_pInstance = new selfTestWgt();
    }
    return s_pInstance;
}

void selfTestWgt::showEvent(QShowEvent *)
{
//    ui->pushButton_ok->setFocus();
    System::getInstance()->setCurrentMsg(MD_SelfTest);
}

void selfTestWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

//void selfTestWgt::on_pushButton_ok_clicked()
//{
//    this->hide();
//    m_pCL->keyPress();
//}

//void selfTestWgt::on_pushButton_cancel_clicked()
//{
//    this->hide();
//}

void selfTestWgt::statuSlots()
{
}

void selfTestWgt::onClDataCome(int cmd, QVariant data)
{
    data.isValid();
    m_pModel->curTipsType = cmd;
    switch (cmd) {
    case selfTestCL::selfTestCL_HideCmd:
        this->hide();
        break;
    case selfTestCL::selfTestCL_ShowCmd:
    {
//        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
//        System::getInstance()->setCurrentMsg(MD_SelfTest);
//        statuSlots();

//        activateWindow();
//        this->setWindowFlags(windowflags()| Qt::Dialog);
        this->show();
        this->move(1920+(1920 - this->width())/2,(1080 - this->height())/2);
        break;
    }
    case selfTestCL::selfTestCL_Enter:
    {
        QWidget *w=QApplication::focusWidget();
        if(w!=nullptr)
        {
            if(w->objectName()=="pushButton_ok")
            {
//                on_pushButton_ok_clicked();
            }
        }
        break;
    }
    default:
        break;
    }
}

void selfTestWgt::initConfig() {
    // 固定使用 fison 驾驶舱参数
    acceleratorMin = 0;
    acceleratorMax = 100;
    electricBrakeMin = 0;
    electricBrakeMax = 100;
    hydraulicBrakeMin = 0;
    hydraulicBrakeMax = 100;
    steeringwheelLeftMax = -450;
    steeringwheelMedian = 0;
    steeringwheelRightMin = 450;
    steeringwheelRightOffset = 450;
    steeringwheelRightTotal = 450;
    steeringwheelLeftTotal = -450;
    steeringwheelTotal = 900;
    accTotal = 100;
    electricBrakeTotal = 100;
    hydraulicBrakeTotal = 100;
    hardBrakeMin = 0;
    hardBrakeMax = 1;
    hardBrakeTotal = 1;
}

void selfTestWgt::updateContent()
{
    //wheel
    //--icon
    //0-50-100
    float curWheel = m_pModel->m_content.vehicleCmd.steeringWheelAngle/100.00;
    qDebug() << "wheel1107 wheel=" << curWheel;
    const float leftRange = qAbs(static_cast<float>(steeringwheelLeftTotal));
    const float rightRange = qAbs(static_cast<float>(steeringwheelRightOffset));

    /*if(curWheel >= 0 && curWheel < 50){//=(50-F9)/50*180
        curWheel = -1 * (50 - curWheel) / 50.0f * leftRange;
    }else if(curWheel >= 50 && curWheel <= 100){//=(F10-50)/50*180
        curWheel = (curWheel - 50.0f) / 50.0f * rightRange;
    }*/

    curWheel = (curWheel - 50.0f) / 50.0f * rightRange;
    selfwheelWgt->setValue(curWheel);
    selfwheelWgt->update();

    //gear
    int gear = m_pModel->m_content.vehicleCmd.shiftCtrl;
    if(2 == gear){
        gearProWgt->setValue(1);
    }else if(3 == gear){
        gearProWgt->setValue(0);
    }else if(4 == gear){
        gearProWgt->setValue(-1);
    }
    //-- P
    if(1 == m_pModel->m_content.vehicleCmd.parkCtrl){
        gear_p->show();
    }else if(0 == m_pModel->m_content.vehicleCmd.parkCtrl){
        gear_p->hide();
    }
    //-- brake
    if(1 == m_pModel->m_content.vehicleCmd.loadingCtrl){
        gear_brake->show();
    }else if(0 == m_pModel->m_content.vehicleCmd.loadingCtrl){
        gear_brake->hide();
    }

#if 0
    //pedal
    //--01 电制动踏板 brakePedal
    electric_brake->setValue(m_pModel->m_content.vehicleCmd.brakePedal);
    //--02 行车制动踏板 hydraulicBrake
    mechanical_brake->setValue(m_pModel->m_content.vehicleCmd.hydraulicBrake);
    //--03 油门踏板 throttlePedal
    throttle->setValue(m_pModel->m_content.vehicleCmd.throttlePedal);
#endif

    //light
    if(1 == m_pModel->m_content.lightCmd.positoinLamp){//--示廓灯
        if((1 == m_pModel->m_content.lightCmd.highBeam) ||
           (1 == m_pModel->m_content.lightCmd.lowBeam) ||
           (1 == m_pModel->m_content.lightCmd.sideLamp)){
            light->setPixmap(QPixmap(":/resource/test/light_on.png"));
        }else{
            light->setPixmap(QPixmap(":/resource/test/light_position.png"));
        }
    }else{
        light->setPixmap(QPixmap(":/resource/test/light_off.png"));
    }

    //lift
    if(1 == m_pModel->m_content.vehicleCmd.bucketCtrl){
        lift->setPixmap(QPixmap(":/resource/test/lift_up.png"));
    }else if(2 == m_pModel->m_content.vehicleCmd.bucketCtrl){
        lift->setPixmap(QPixmap(":/resource/test/lift_down.png"));
    }else if(0 == m_pModel->m_content.vehicleCmd.bucketCtrl){
        lift->setPixmap(QPixmap(":/resource/test/lift_pause.png"));
    }

    //scram(stop)
    if(m_pModel->m_content.vehicleCmd.eStop){
        scramIcon->setPixmap(QPixmap(":/resource/test/scram_on.png"));
    }else{
        scramIcon->setPixmap(QPixmap(":/resource/test/scram_off.png"));
    }

    //beams
    //--highBeam
    if(1 == m_pModel->m_content.lightCmd.highBeam){
        leftIcons[0]->setPixmap(QPixmap(":/resource/test/left_icon1_on.png"));
    }else{
        leftIcons[0]->setPixmap(QPixmap(":/resource/test/left_icon1_off.png"));
    }
    //--lowBeam
    if(1 == m_pModel->m_content.lightCmd.lowBeam){
        leftIcons[1]->setPixmap(QPixmap(":/resource/test/left_icon2_on.png"));
    }else{
        leftIcons[1]->setPixmap(QPixmap(":/resource/test/left_icon2_off.png"));
    }
    //--left
    if(1 == m_pModel->m_content.lightCmd.left){
        leftIcons[2]->setPixmap(QPixmap(":/resource/test/left_icon3_on.png"));
    }else{
        leftIcons[2]->setPixmap(QPixmap(":/resource/test/left_icon3_off.png"));
    }
    //--right
    if(1 == m_pModel->m_content.lightCmd.right){
        leftIcons[3]->setPixmap(QPixmap(":/resource/test/left_icon4_on.png"));
    }else{
        leftIcons[3]->setPixmap(QPixmap(":/resource/test/left_icon4_off.png"));
    }

    //icons
    //--emergencyFlash
    if(1 == m_pModel->m_content.lightCmd.emergencyFlash){
        rightIcons[0]->setPixmap(QPixmap(":/resource/test/right_icon1_on.png"));
    }else{
        rightIcons[0]->setPixmap(QPixmap(":/resource/test/right_icon1_off.png"));
    }
    //--empty
    //--exhaustBrake
    if(1 == m_pModel->m_content.vehicleCmd.exhaustBrake){
        rightIcons[3]->setPixmap(QPixmap(":/resource/test/right_icon4_on.png"));
    }else{
        rightIcons[3]->setPixmap(QPixmap(":/resource/test/right_icon4_off.png"));
    }
}

void selfTestWgt::updateWheelContent()
{
    float curWheel = m_pModel->m_content.vehicleCmd.steeringWheelAngle/100.00;
    qDebug() << "wheel1107 wheel=" << curWheel;
    const float leftRange = qAbs(static_cast<float>(steeringwheelLeftTotal));
    const float rightRange = qAbs(static_cast<float>(steeringwheelRightOffset));

    /*if(curWheel >= 0 && curWheel < 50){//=(50-F9)/50*180
        curWheel = -1 * (50 - curWheel) / 50.0f * leftRange;
    }else if(curWheel >= 50 && curWheel <= 100){//=(F10-50)/50*180
        curWheel = (curWheel - 50.0f) / 50.0f * rightRange;
    }*/

    int icurValue = (curWheel - 50.0f) / 50.0f * rightRange;
    icurValue = qBound(-450, icurValue, 450);
    if (qAbs(icurValue) <= 15) {
        labWheelBottom->setStyleSheet("QLabel{color: #39D352; font: 22px;"
                                      "background-color: #163f5e;"
                                      "border-radius: 4px;"
                                      "border: 1px solid #00121f;}");
    } else {
        labWheelBottom->setStyleSheet("QLabel{color: #ffffff; font: 22px;"
                                      "background-color: #163f5e;"
                                      "border-radius: 4px;"
                                      "border: 1px solid #00121f;}");
    }

//    qDebug() << "zjz wheel:" << m_pModel->m_wheelData.steeringwheel
//             << ", icurValue:" << icurValue
//             << ", leftValue:" << leftValue
//             << ", rightValue:" << rightValue;

    QString str = QString("%1").arg(icurValue);
    labWheelBottom->setText(str);

    //pedal
    //--01 电制动踏板 brakePedal
    electric_brake->setValue(m_pModel->m_wheelData.clutch);
    //--02 行车制动踏板 hydraulicBrake
    mechanical_brake->setValue(m_pModel->m_wheelData.brake);
    //--03 油门踏板 throttlePedal
    throttle->setValue(m_pModel->m_wheelData.accelerator);
}

void selfTestWgt::updateEmptyContent()
{
    static int cnt2 = 0;
    cnt2++;
    if(cnt2%2==0){
        cnt2 = 0;
        rightIcons[1]->setPixmap(QPixmap(":/resource/test/right_icon2_off.png"));
    }else{
        rightIcons[1]->setPixmap(QPixmap(":/resource/test/right_icon2_on.png"));
    }
}

void selfTestWgt::updateTakeoverContent()
{
    static int cnt3 = 0;
    cnt3++;
    if(cnt3%2==0){
        cnt3 = 0;
        rightIcons[2]->setPixmap(QPixmap(":/resource/test/right_icon3_off.png"));
    }else{
        rightIcons[2]->setPixmap(QPixmap(":/resource/test/right_icon3_on.png"));
    }
}

void selfTestWgt::updateBlindContent()
{
    static int cnt1 = 0;
    cnt1++;
    if(cnt1%2==0){
        cnt1 = 0;
        rightIcons[4]->setPixmap(QPixmap(":/resource/test/right_icon5_off.png"));
    }else{
        rightIcons[4]->setPixmap(QPixmap(":/resource/test/right_icon5_on.png"));
    }
}

void selfTestWgt::onModelUpdate(int cmd)
{
    selfTestModel::ModelCmdType tCmd = static_cast<selfTestModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case selfTestModel::Self_Update_content:{
        updateContent();
        break;
    }
    case selfTestModel::Self_Update_wheel_content:{
        updateWheelContent();
        break;
    }
    case selfTestModel::Self_Update_takeover_content:{
        updateTakeoverContent();
        break;
    }
    case selfTestModel::Self_Update_blind_content:{
        updateBlindContent();
        break;
    }
    case selfTestModel::Self_Update_empty_content:{
        updateEmptyContent();
        break;
    }
    default:
        break;
    }
}

//void selfTestWgt::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    painter.fillRect(this->rect(),Qt::black);
//}
