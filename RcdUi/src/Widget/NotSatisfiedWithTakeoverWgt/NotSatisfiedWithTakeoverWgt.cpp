#include "NotSatisfiedWithTakeoverWgt.h"
#include "ui_NotSatisfiedWithTakeoverWgt.h"
#include <QDebug>
NotSatisfiedWithTakeoverWgt* NotSatisfiedWithTakeoverWgt::s_pInstance = nullptr;

NotSatisfiedWithTakeoverWgt::NotSatisfiedWithTakeoverWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::NotSatisfiedWithTakeoverWgt)
{
    ui->setupUi(this);
    m_pCL = new NotSatisfiedWithTakeoverCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new NotSatisfiedWithTakeoverModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    m_Timer = new QTimer();//用于定时刷新
    m_Timer->setInterval(200);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(statuSlots()));

    ui->gear->setFocusPolicy(Qt::NoFocus);
    ui->mode->setFocusPolicy(Qt::NoFocus);
    ui->breakState->setFocusPolicy(Qt::NoFocus);
    ui->speed->setFocusPolicy(Qt::NoFocus);
    ui->label_title->setFocusPolicy(Qt::NoFocus);
}

NotSatisfiedWithTakeoverWgt::~NotSatisfiedWithTakeoverWgt()
{
    delete ui;
}
NotSatisfiedWithTakeoverWgt *NotSatisfiedWithTakeoverWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new NotSatisfiedWithTakeoverWgt();
    }
    return s_pInstance;
}

void NotSatisfiedWithTakeoverWgt::showEvent(QShowEvent *)
{
    ui->pushButton_task_over->setFocus();
    System::getInstance()->setCurrentMsg(MD_NotSatisfiedWithTakeover);
}

void NotSatisfiedWithTakeoverWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

void NotSatisfiedWithTakeoverWgt::on_pushButton_task_over_clicked()
{
    //修改车端不满足条件的逻辑
    m_pCL->keyPress("end");

    this->hide();
    m_Timer->stop();
}

void NotSatisfiedWithTakeoverWgt::onClDataCome(int cmd, QVariant data)
{

    switch (cmd) {
    case NotSatisfiedWithTakeoverCL::NotSatisfiedWithTakeoverCL_Show:
    {
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        if(m_pCL->isShow())
        {
            this->show();
            m_Timer->start();
        }
//        else//车端不满足条件的窗口不显示，直接显示舱端条件
//        {
//            m_pCL->keyPress("checkCabin");
//        }
        break;
    }
    case NotSatisfiedWithTakeoverCL::NotSatisfiedWithTakeoverCL_Enter:
    {
        QWidget *w=QApplication::focusWidget();
        if(w!=nullptr)
        {
            if(w->objectName()=="pushButton_task_over")
            {
                on_pushButton_task_over_clicked();
            }
        }
        break;
    }

    default:
        break;
    }
}

void NotSatisfiedWithTakeoverWgt::onModelUpdate(int cmd)
{
    NotSatisfiedWithTakeoverModel::ModelCmdType tCmd = static_cast<NotSatisfiedWithTakeoverModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case NotSatisfiedWithTakeoverModel::MC_Update:
    {
//        qDebug()<<"NotSatisfiedWithTakeoverModel::MC_Update:"
//             <<m_pModel->m_vehicleData.speed<<(int)m_pModel->m_vehicleData.gear<<(int)m_pModel->m_vehicleData.mode<<(int)m_pModel->m_vehicleData.handBrake
//            <<"近光灯:"<<(int)m_pModel->m_vehicleData.lowBeam<<"双闪:"<<m_pModel->m_vehicleData.emergencyFlash
//           <<"排气制动"<<m_pModel->m_vehicleData.exhaustBrake;

        if(m_pModel->m_vehicleData.bodys.speed < 0.2)//速度为0
        {
            ui->speed->setCheckState(Qt::Checked);
        }else
            ui->speed->setCheckState(Qt::Unchecked);

        if(m_pModel->m_vehicleData.bodys.gear == 0)//空挡
            ui->gear->setCheckState(Qt::Checked);
        else
            ui->gear->setCheckState(Qt::Unchecked);

        if(m_pModel->m_vehicleData.bodys.mode == 0x01)//自动模式
            ui->mode->setCheckState(Qt::Checked);
        else
            ui->mode->setCheckState(Qt::Unchecked);

//        if(m_pModel->m_vehicleData.handBrake == 0x01)//手刹使能
//            ui->breakState->setCheckState(Qt::Checked);
//        else
//            ui->breakState->setCheckState(Qt::Unchecked);

        //////////////////////////
        if(m_pModel->m_vehicleData.bodys.parkingBrake == 0x01)//手刹使能
            ui->breakState->setCheckState(Qt::Checked);
        else
            ui->breakState->setCheckState(Qt::Unchecked);
        /////////////////////////

        break;
    }

    default:
        break;
    }
}

void NotSatisfiedWithTakeoverWgt::statuSlots()
{
//    qDebug()<<"NotSatisfiedWithTakeoverWgt 窗口定时器"
//           <<m_pModel->m_vehicleData.speed
//          <<(int)m_pModel->m_vehicleData.gear
//         <<(int)m_pModel->m_vehicleData.mode
//        <<(int)m_pModel->m_vehicleData.handBrake;
    if(m_pCL->isShow())
    {
        if(m_pModel->m_vehicleData.bodys.speed < 0.2)//速度为0
        {
            ui->speed->setCheckState(Qt::Checked);
        }else
            ui->speed->setCheckState(Qt::Unchecked);

        if(m_pModel->m_vehicleData.bodys.gear == 0)//空挡
            ui->gear->setCheckState(Qt::Checked);
        else
            ui->gear->setCheckState(Qt::Unchecked);

        if(m_pModel->m_vehicleData.bodys.mode == 0x01)//自动模式
            ui->mode->setCheckState(Qt::Checked);
        else
            ui->mode->setCheckState(Qt::Unchecked);

//        if(m_pModel->m_vehicleData.handBrake == 0x01)//手刹使能
//            ui->breakState->setCheckState(Qt::Checked);
//        else
//            ui->breakState->setCheckState(Qt::Unchecked);

        /////////////////////////
        if(m_pModel->m_vehicleData.bodys.parkingBrake == 0x01)//手刹使能
            ui->breakState->setCheckState(Qt::Checked);
        else
            ui->breakState->setCheckState(Qt::Unchecked);
        /////////////////////////
    }else
    {

        ui->speed->setCheckState(Qt::Checked);
        ui->gear->setCheckState(Qt::Checked);
        ui->mode->setCheckState(Qt::Checked);
        ui->breakState->setCheckState(Qt::Checked);

        m_Timer->stop();
        //修改车端不满足条件的逻辑
//        this->hide();
//        m_pCL->keyPress("checkCabin");

    }
}

void NotSatisfiedWithTakeoverWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
