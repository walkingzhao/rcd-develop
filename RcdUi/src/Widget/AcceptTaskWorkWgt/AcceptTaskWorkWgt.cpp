#include "AcceptTaskWorkWgt.h"
#include "ui_AcceptTaskWorkWgt.h"
#include <QtDebug>
AcceptTaskWorkWgt* AcceptTaskWorkWgt::s_pInstance = nullptr;

AcceptTaskWorkWgt::AcceptTaskWorkWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::AcceptTaskWorkWgt)
{
    ui->setupUi(this);
    m_pCL = new AcceptTaskWorkCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new AcceptTaskWorkModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);
    ui->label_title->setFocusPolicy(Qt::NoFocus);
    ui->label_task->setFocusPolicy(Qt::NoFocus);
}

AcceptTaskWorkWgt::~AcceptTaskWorkWgt()
{
    delete ui;
}

AcceptTaskWorkWgt *AcceptTaskWorkWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new AcceptTaskWorkWgt();
    }
    return s_pInstance;
}

void AcceptTaskWorkWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
    case AcceptTaskWorkCL::AcceptTaskWorkCLCmd_Enter:
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

void AcceptTaskWorkWgt::onModelUpdate(int cmd)
{

    AcceptTaskWorkModel::ModelCmdType tCmd = static_cast<AcceptTaskWorkModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case AcceptTaskWorkModel::MC_destStr:
    {
        break;
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        ui->label_task->setText(m_pModel->m_dest);
        //xuzk2显示该窗口
        this->show();
        ui->pushButton_ok->setFocus();

        break;
    }

    default:
        break;
    }
}


void AcceptTaskWorkWgt::on_pushButton_ok_clicked()
{
    m_pCL->keyPress("ok");
    //隐藏当前窗口
    this->hide();
}

void AcceptTaskWorkWgt::on_pushButton_cancel_clicked()
{
    m_pCL->keyPress("reject");
    //返回监控界面并隐藏当前窗口
    this->hide();
}
void AcceptTaskWorkWgt::showEvent(QShowEvent *)
{
    ui->pushButton_ok->setFocus();
    System::getInstance()->setCurrentMsg(MD_AcceptTaskWork);
}

void AcceptTaskWorkWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

//void AcceptTaskWorkWgt::keyPressEvent(QKeyEvent *event)
//{
//    qDebug()<<"AcceptTaskWorkWgt key:"<<(Qt::Key)event->key();
//    QWidget *w=QApplication::focusWidget();
//    if(w!=nullptr)
//        qDebug()<<"current focus button:"<<w->objectName();
//    QWidget::keyPressEvent(event);

//}

void AcceptTaskWorkWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
