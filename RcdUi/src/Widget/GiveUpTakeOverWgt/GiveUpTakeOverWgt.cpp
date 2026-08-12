#include "GiveUpTakeOverWgt.h"
#include "ui_GiveUpTakeOverWgt.h"
GiveUpTakeOverWgt* GiveUpTakeOverWgt::s_pInstance = nullptr;

GiveUpTakeOverWgt::GiveUpTakeOverWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::GiveUpTakeOverWgt)
{
    ui->setupUi(this);
    m_pCL = new GiveUpTakeOverCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new GiveUpTakeOverModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);
    ui->label_title->setFocusPolicy(Qt::NoFocus);
    ui->label_task->setFocusPolicy(Qt::NoFocus);
}

GiveUpTakeOverWgt::~GiveUpTakeOverWgt()
{
    delete ui;
}

GiveUpTakeOverWgt *GiveUpTakeOverWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new GiveUpTakeOverWgt();
    }
    return s_pInstance;
}

void GiveUpTakeOverWgt::showEvent(QShowEvent *)
{
    ui->pushButton_cancel->setFocus();
    System::getInstance()->setCurrentMsg(MD_GiveUpTakeOver);
}

void GiveUpTakeOverWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

void GiveUpTakeOverWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
    case GiveUpTakeOverCL::GiveUpTakeOverCLCmd_Show:
    {
        if(System::getInstance()->getCurrentMsg()!=MD_None)
            break;
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        this->show();

        break;
    }
    case GiveUpTakeOverCL::GiveUpTakeOverCLCmd_Enter:
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

void GiveUpTakeOverWgt::onModelUpdate(int cmd)
{

    GiveUpTakeOverModel::ModelCmdType tCmd = static_cast<GiveUpTakeOverModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case GiveUpTakeOverModel::MC_UpdateAll:
    {
        break;
    }

    default:
        break;
    }
}

void GiveUpTakeOverWgt::on_pushButton_cancel_clicked()
{
    m_pCL->keyPress("cancel");
    this->hide();
}

void GiveUpTakeOverWgt::on_pushButton_ok_clicked()
{
    m_pCL->keyPress("ok");
    this->hide();
}

void GiveUpTakeOverWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
