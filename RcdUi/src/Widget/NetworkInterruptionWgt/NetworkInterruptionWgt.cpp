#include "NetworkInterruptionWgt.h"
#include "ui_NetworkInterruptionWgt.h"
NetworkInterruptionWgt* NetworkInterruptionWgt::s_pInstance = nullptr;

NetworkInterruptionWgt::NetworkInterruptionWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::NetworkInterruptionWgt)
{
    ui->setupUi(this);
    m_pCL = new NetworkInterruptionCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new NetworkInterruptionModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

//    m_Timer = new QTimer();//用于定时刷新
//    m_Timer->setInterval(200);
//    connect(m_Timer, SIGNAL(timeout()), this, SLOT(statuSlots()));
    ui->gear->setFocusPolicy(Qt::NoFocus);
    ui->pedal->setFocusPolicy(Qt::NoFocus);
    ui->centorWheel->setFocusPolicy(Qt::NoFocus);
    ui->buttonReset->setFocusPolicy(Qt::NoFocus);
    ui->label_title->setFocusPolicy(Qt::NoFocus);
}

NetworkInterruptionWgt::~NetworkInterruptionWgt()
{
    delete ui;
}
NetworkInterruptionWgt *NetworkInterruptionWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new NetworkInterruptionWgt();
    }
    return s_pInstance;
}

void NetworkInterruptionWgt::showEvent(QShowEvent *)
{
    ui->pushButton_task_over->setFocus();
}

void NetworkInterruptionWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

void NetworkInterruptionWgt::on_pushButton_task_over_clicked()
{
    this->hide();
    m_pCL->keyPress();
}

void NetworkInterruptionWgt::statuSlots()
{
    if(m_pModel->m_selfState.isParking
            &&m_pModel->m_selfState.isNoPedal
            &&m_pModel->m_selfState.isCenterSteeringWheel
            &&m_pModel->m_selfState.isButtonReset) {
        ui->pushButton_task_over->setEnabled(true);
    } else {
        ui->pushButton_task_over->setEnabled(false);
    }

    if(m_pModel->m_selfState.isParking){//P档
        ui->gear->setCheckState(Qt::Checked);
    }else{
        ui->gear->setCheckState(Qt::Unchecked);
    }

    if(m_pModel->m_selfState.isNoPedal)//踏板无踩压
        ui->pedal->setCheckState(Qt::Checked);
    else
        ui->pedal->setCheckState(Qt::Unchecked);

    if(m_pModel->m_selfState.isCenterSteeringWheel)//方向盘回正
        ui->centorWheel->setCheckState(Qt::Checked);
    else
        ui->centorWheel->setCheckState(Qt::Unchecked);

    if(m_pModel->m_selfState.isButtonReset)//按钮复位
        ui->buttonReset->setCheckState(Qt::Checked);
    else
        ui->buttonReset->setCheckState(Qt::Unchecked);

}

void NetworkInterruptionWgt::onClDataCome(int cmd, QVariant data)
{

    data.isValid();
    switch (cmd) {
    case NetworkInterruptionCL::NetworkInterruptionCL_ShowCmd:
    {
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        System::getInstance()->setCurrentMsg(MD_NetworkInterruption);
        statuSlots();
        this->show();

        break;
    }
    case NetworkInterruptionCL::NetworkInterruptionCL_HideCmd:
    {
        this->hide();
        break;
    }
    case NetworkInterruptionCL::NetworkInterruptionCL_Enter:
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

void NetworkInterruptionWgt::onModelUpdate(int cmd)
{
    NetworkInterruptionModel::ModelCmdType tCmd = static_cast<NetworkInterruptionModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case NetworkInterruptionModel::MC_UpdateSelf:
    {
        statuSlots();
        break;
    }

    default:
        break;
    }

}

void NetworkInterruptionWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
