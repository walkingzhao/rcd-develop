#include "TipsPopupWgt.h"
#include "ui_TipsPopupWgt.h"

TipsPopupWgt* TipsPopupWgt::s_pInstance = nullptr;

TipsPopupWgt::TipsPopupWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::TipsPopupWgt)
{
    ui->setupUi(this);
    m_pCL = new TipsPopupCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new TipsPopupModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    ui->checkbox1->setFocusPolicy(Qt::NoFocus);
    ui->checkbox2->setFocusPolicy(Qt::NoFocus);
    ui->checkbox3->setFocusPolicy(Qt::NoFocus);
    ui->checkbox4->setFocusPolicy(Qt::NoFocus);
    ui->label_title->setFocusPolicy(Qt::NoFocus);

    ui->checkbox1->hide();
    ui->checkbox2->hide();
    ui->checkbox3->hide();
    ui->checkbox4->hide();
    ui->pushButton_ok->hide();
    ui->pushButton_cancel->hide();
    qDebug() << "TipsPopupWgt create";
}

TipsPopupWgt::~TipsPopupWgt()
{
    delete ui;
}

TipsPopupWgt *TipsPopupWgt::GetInstance()
{
    if (s_pInstance == nullptr) {
        s_pInstance = new TipsPopupWgt();
    }
    return s_pInstance;
}

void TipsPopupWgt::showEvent(QShowEvent *)
{
    ui->pushButton_ok->setFocus();
    System::getInstance()->setCurrentMsg(MD_TipsPopup);
}

void TipsPopupWgt::hideEvent(QHideEvent *)
{
    System::getInstance()->setCurrentMsg(MD_None);
}

void TipsPopupWgt::on_pushButton_ok_clicked()
{
    this->hide();
    m_pCL->keyPress();
}

void TipsPopupWgt::on_pushButton_cancel_clicked()
{
    this->hide();
}

void TipsPopupWgt::statuSlots()
{
#if 0
    if(m_pModel->m_selfState.isParking
            &&m_pModel->m_selfState.isNoPedal
            &&m_pModel->m_selfState.isCenterSteeringWheel
            &&m_pModel->m_selfState.isButtonReset)
    {
        ui->pushButton_task_over->setEnabled(true);
    }
    else
    {
        ui->pushButton_task_over->setEnabled(false);
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
#endif
}

void TipsPopupWgt::updateContent()
{
//    if (m_pModel->curFirstPriority < m_pModel->m_content.firstPriority) {
//        return;
//    } else if (m_pModel->curFirstPriority == m_pModel->m_content.firstPriority) {
//        if (m_pModel->curSecondPriority < m_pModel->m_content.secondPriority) {
//            return;
//        }
//    }
    m_pModel->curFirstPriority = m_pModel->m_content.firstPriority;
    m_pModel->curSecondPriority = m_pModel->m_content.secondPriority;
    ui->label_title->setText(m_pModel->m_content.content);
    qDebug() << "label_title=" << m_pModel->m_content.content;
    qDebug() << "btnText=" << m_pModel->m_content.btnText;
    if (m_pModel->m_content.btnText.isEmpty()) {
        ui->pushButton_ok->hide();
        ui->pushButton_cancel->hide();
    } else {
        ui->pushButton_ok->show();
        ui->pushButton_ok->setEnabled(true);
        ui->pushButton_ok->setFocus();
        ui->pushButton_ok->setText(m_pModel->m_content.btnText);
    }
    if (TipsPopupLBtnCmd_GiveupMonitor == m_pModel->m_content.cmd) {
        ui->pushButton_cancel->show();
    } else {
        ui->pushButton_cancel->hide();
    }
}

void TipsPopupWgt::onClDataCome(int cmd, QVariant data)
{
    data.isValid();
    m_pModel->curTipsType = cmd;
    switch (cmd) {
    case TipsPopupCL::TipsPopupCL_ShowCmd:
    {
        qDebug() << "++++++++++++ 11-11";
        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        System::getInstance()->setCurrentMsg(MD_TipsPopup);
//        statuSlots();
        this->show();
        if (m_pModel->m_content.delay > 0) {
            QTimer::singleShot(m_pModel->m_content.delay,this,SLOT(on_pushButton_ok_clicked()));
        }
        break;
    }
    case TipsPopupCL::TipsPopupCL_Enter:
    {
        QWidget *w=QApplication::focusWidget();
        if(w!=nullptr)
        {
            if(w->objectName()=="pushButton_ok")
            {
                on_pushButton_ok_clicked();
            }
        }
        break;
    }
    case TipsPopupCL::TipsPopupCL_HideCmd:
    {
        this->hide();
        System::getInstance()->setCurrentMsg(MD_None);
        break;
    }
    default:
        break;
    }
}

void TipsPopupWgt::onModelUpdate(int cmd)
{
    TipsPopupModel::ModelCmdType tCmd = static_cast<TipsPopupModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case TipsPopupModel::TP_Update_content:
    {
        updateContent();
        break;
    }
    default:
        break;
    }
}

void TipsPopupWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}

