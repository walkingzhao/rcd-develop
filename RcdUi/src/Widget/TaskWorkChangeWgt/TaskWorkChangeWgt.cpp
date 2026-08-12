#include "TaskWorkChangeWgt.h"
#include "ui_TaskWorkChangeWgt.h"
TaskWorkChangeWgt* TaskWorkChangeWgt::s_pInstance = nullptr;

TaskWorkChangeWgt::TaskWorkChangeWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::TaskWorkChangeWgt)
{
    ui->setupUi(this);
    m_pCL = new TaskWorkChangeCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new TaskWorkChangeModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    connect(&tickTimer,SIGNAL(timeout()),this ,SLOT(tickTimerOut()));
    tickTimer.start(500);

}

TaskWorkChangeWgt::~TaskWorkChangeWgt()
{
    delete ui;
}
TaskWorkChangeWgt *TaskWorkChangeWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new TaskWorkChangeWgt();
    }
    return s_pInstance;
}
void TaskWorkChangeWgt::setData(QVariant data)
{
    if(data.toString().isEmpty()){
        return;
    }
    ui->label_task->setText(data.toString());
}

void TaskWorkChangeWgt::onClDataCome(int cmd, QVariant data)
{
    data.isValid();
    switch (cmd) {
    case TaskWorkChangeCL::TaskWorkChangeCL_ShowCmd:
    {
//        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
        ui->label_task->setText(data.toString());
        this->show();
        System::getInstance()->setCurrentMsg(MD_TaskWorkChange);
        QTimer::singleShot(3000, [&](){
            this->hide();
            if(System::getInstance()->getCurrentMsg()==MD_TaskWorkChange)
                System::getInstance()->setCurrentMsg(MD_None);
        });

        break;
    }
    case 2:
    {

        break;
    }

    case 3:
    {

        break;
    }

    default:
        break;
    }

}

void TaskWorkChangeWgt::onModelUpdate(int cmd)
{

    TaskWorkChangeModel::ModelCmdType tCmd = static_cast<TaskWorkChangeModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case TaskWorkChangeModel::MC_UpdateAll:
    {
        break;
    }

    default:
        break;
    }
}

void TaskWorkChangeWgt::tickTimerOut()
{

    static bool flag=true;
    if(flag)
    {
        ui->label_task->setStyleSheet("color:white");
        ui->widget->setPenColor(QColor(0x00, 0xba, 0xff));
    }else
    {
        ui->label_task->setStyleSheet("color:red");
        ui->widget->setPenColor(QColor(0xfa, 0x5a, 0x00));
    }

    flag=!flag;
}

void TaskWorkChangeWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
