#include "FastStopWgt.h"
#include "ui_FastStopWgt.h"

FastStopWgt* FastStopWgt::s_pInstance = nullptr; //初始化静态数据成员
FastStopWgt::FastStopWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::FastStopWgt)
{
    ui->setupUi(this);
    // 创建控制层
    m_pCL = new FastStopCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);
    // 创建数据层
    m_pModel = new FastStopModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

//    connect(&tickTimer,SIGNAL(timeout()),this ,SLOT(tickTimerOut()));
//    tickTimer.start(500);
}

FastStopWgt::~FastStopWgt()
{
    delete ui;
}

FastStopWgt *FastStopWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new FastStopWgt();
    }
    return s_pInstance;
}

void FastStopWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
    case FastStopCL::CL_Show:
    {
        if(System::getInstance()->getCurrentMsg()!=MD_None)
            break;
        System::getInstance()->setAllMsgHide();
        System::getInstance()->setCurrentMsg(MD_FastStop);
        this->show();
        break;
    }
    case FastStopCL::CL_Enter:
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

void FastStopWgt::onModelUpdate(int cmd)
{
    switch (cmd) {
    case 0:
    {
        break;
    }

    default:
        break;
    }
}

void FastStopWgt::showEvent(QShowEvent *)
{
    ui->pushButton_ok->setFocus();
    System::getInstance()->setCurrentMsg(MD_FastStop);
}

void FastStopWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}



void FastStopWgt::on_pushButton_ok_clicked()
{
    m_pCL->keyPress("ok");
    this->hide();
}

void FastStopWgt::on_pushButton_cancel_clicked()
{
    this->hide();
}

void FastStopWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
