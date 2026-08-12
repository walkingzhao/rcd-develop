#include "CompleteOperStartWgt.h"
#include "ui_CompleteOperStartWgt.h"
#include <QtDebug>
CompleteOperStartWgt *CompleteOperStartWgt::s_pInstance=nullptr;
CompleteOperStartWgt::CompleteOperStartWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::CompleteOperStartWgt)
{
    ui->setupUi(this);
    m_pCL = new CompleteOperStartCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new CompleteOperStartModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    m_Timer = new QTimer();//用于定时刷新
    m_Timer->setInterval(200);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(statuSlots()));
    ui->gear->setFocusPolicy(Qt::NoFocus);
    ui->pedal->setFocusPolicy(Qt::NoFocus);
    ui->centorWheel->setFocusPolicy(Qt::NoFocus);
    ui->label_title->setFocusPolicy(Qt::NoFocus);
//    ui->pushButton_start_task->setFocusPolicy(Qt::StrongFocus);
}

CompleteOperStartWgt::~CompleteOperStartWgt()
{
    delete ui;
}

CompleteOperStartWgt *CompleteOperStartWgt::GetInstance()
{

    if(s_pInstance == nullptr) {
        s_pInstance = new CompleteOperStartWgt();
    }
    return s_pInstance;
}

void CompleteOperStartWgt::showEvent(QShowEvent *)
{
    m_Timer->start();
    ui->pushButton_start_task->setFocus();
    System::getInstance()->setCurrentMsg(MD_CompleteOperStart);
}

void CompleteOperStartWgt::hideEvent(QHideEvent *)
{
    m_Timer->stop();
    System::getInstance()->setCurrentMsg(MD_None);
}

void CompleteOperStartWgt::on_pushButton_start_task_clicked()
{
    this->hide();
    m_pCL->keyPress();
}

void CompleteOperStartWgt::statuSlots()
{
    return;
    if(m_pCL->isShow())//不满足条件
    {
        ui->pushButton_start_task->setEnabled(false);
    }else//满足条件
    {
        ui->pushButton_start_task->setEnabled(true);
    }
}

void CompleteOperStartWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
    case CompleteOperStartCL::CompleteOperStartCL_Show:
    {
        if(System::getInstance()->getCurrentMsg()!=MD_None)
            break;

        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        this->show();
        System::getInstance()->setCurrentMsg(MD_CompleteOperStart);
//        if(!m_Timer->isActive())
            m_Timer->start();
        break;
    }
    case CompleteOperStartCL::CompleteOperStartCL_Enter:
    {
        QWidget *w=QApplication::focusWidget();
        if(w!=nullptr)
        {
            if((ui->pushButton_start_task->isEnabled())
                    &&(w->objectName()=="pushButton_start_task"))
            {
                on_pushButton_start_task_clicked();
            }
        }
        break;
    }
    default:
        break;
    }
}

void CompleteOperStartWgt::onModelUpdate(int cmd)
{
    CompleteOperStartModel::ModelCmdType tCmd = static_cast<CompleteOperStartModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case CompleteOperStartModel::MC_Update:
    {
        //        qDebug()<<"开始接管："<<m_pModel->m_selfState.isParking<<m_pModel->m_selfState.isNoPedal
        //                  <<m_pModel->m_selfState.isCenterSteeringWheel<<m_pModel->m_selfState.isButtonReset;
        if(m_pModel->m_selfState.isParking)//P档
        {
            ui->gear->setCheckState(Qt::Checked);
        }else
            ui->gear->setCheckState(Qt::Unchecked);

        if(m_pModel->m_selfState.isNoPedal)//踏板无踩压
            ui->pedal->setCheckState(Qt::Checked);
        else
            ui->pedal->setCheckState(Qt::Unchecked);

        if(m_pModel->m_selfState.isCenterSteeringWheel)//方向盘回正
            ui->centorWheel->setCheckState(Qt::Checked);
        else
            ui->centorWheel->setCheckState(Qt::Unchecked);

        if(m_pCL->isShow())//不满足条件
        {
            ui->pushButton_start_task->setEnabled(false);
        }else//满足条件
        {
            ui->pushButton_start_task->setEnabled(true);
            if(System::getInstance()->getCurrentMsg()==MD_CompleteOperStart)
                ui->pushButton_start_task->setFocus();
        }


        break;
    }

    default:
        break;
    }
}

void CompleteOperStartWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
