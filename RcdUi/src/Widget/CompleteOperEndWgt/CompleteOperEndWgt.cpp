#include "CompleteOperEndWgt.h"
#include "ui_CompleteOperEndWgt.h"
#include <QDebug>
CompleteOperEndWgt* CompleteOperEndWgt::s_pInstance = nullptr;
CompleteOperEndWgt::CompleteOperEndWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::CompleteOperEndWgt)
{
    ui->setupUi(this);
    m_pCL = new CompleteOperEndCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new CompleteOperEndModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    m_Timer = new QTimer();//用于定时刷新
    m_Timer->setInterval(200);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(statuSlots()));

    ui->gear->setFocusPolicy(Qt::NoFocus);
    ui->pedal->setFocusPolicy(Qt::NoFocus);
    ui->centorWheel->setFocusPolicy(Qt::NoFocus);
    ui->buttonReset->setFocusPolicy(Qt::NoFocus);
    ui->label_title->setFocusPolicy(Qt::NoFocus);


}

CompleteOperEndWgt::~CompleteOperEndWgt()
{
    delete ui;
}

CompleteOperEndWgt *CompleteOperEndWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new CompleteOperEndWgt();
    }
    return s_pInstance;
}

void CompleteOperEndWgt::showEvent(QShowEvent *)
{
    ui->pushButton_cancel->setFocus();
    System::getInstance()->setCurrentMsg(MD_CompleteOperEnd);
}

void CompleteOperEndWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

void CompleteOperEndWgt::on_pushButton_ok_clicked()
{
    this->hide();
    m_pCL->keyPress();
}

void CompleteOperEndWgt::on_pushButton_cancel_clicked()
{
    this->hide();
    m_Timer->stop();
}

void CompleteOperEndWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
    case CompleteOperEndCL::CompleteOperEndCL_ShowCmd:
    {
        if(System::getInstance()->getCurrentMsg()!=MD_None)
            break;
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        System::getInstance()->setCurrentMsg(MD_CompleteOperEnd);
        this->show();
        m_Timer->start();

        break;
    }
    case CompleteOperEndCL::CompleteOperEndCL_Enter:
    {
        QWidget *w=QApplication::focusWidget();
        if(w!=nullptr)
        {
            if(w->objectName()=="pushButton_ok")
            {
                on_pushButton_ok_clicked();
            }else if(w->objectName()=="pushButton_cancel")
            {
                on_pushButton_cancel_clicked();
            }
        }
        break;
    }

    default:
        break;
    }

}

void CompleteOperEndWgt::onModelUpdate(int cmd)
{
    CompleteOperEndModel::ModelCmdType tCmd = static_cast<CompleteOperEndModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case CompleteOperEndModel::MC_Show:
    {
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        this->show();
        break;
    }
    case CompleteOperEndModel::MC_UpdateSelf:
    {
        statuSlots();
        break;
    }

    default:
        break;
    }

}

void CompleteOperEndWgt::statuSlots()
{
    if(m_pCL->isShow())
    {
        ui->pushButton_ok->setEnabled(false);
//        qDebug()<<"禁用OK button";
    }
    else
    {
        ui->pushButton_ok->setEnabled(true);
//        qDebug()<<"使能OK button";
    }


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

    if(m_pModel->m_selfState.isButtonReset)//按钮复位
        ui->buttonReset->setCheckState(Qt::Checked);
    else
        ui->buttonReset->setCheckState(Qt::Unchecked);


}

void CompleteOperEndWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
