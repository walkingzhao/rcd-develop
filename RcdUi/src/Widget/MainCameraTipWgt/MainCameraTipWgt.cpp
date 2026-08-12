#include "MainCameraTipWgt.h"
#include "ui_MainCameraTipWgt.h"

MainCameraTipWgt* MainCameraTipWgt::s_pInstance = nullptr; //初始化静态数据成员
MainCameraTipWgt::MainCameraTipWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::MainCameraTipWgt)
{
    ui->setupUi(this);
    // 创建控制层
    m_pCL = new MainCameraTipCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);
    // 创建数据层
    m_pModel = new MainCameraTipModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    connect(&tickTimer,SIGNAL(timeout()),this ,SLOT(tickTimerOut()));
    tickTimer.start(500);
}

MainCameraTipWgt::~MainCameraTipWgt()
{
    delete ui;
}

MainCameraTipWgt *MainCameraTipWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new MainCameraTipWgt();
    }
    return s_pInstance;
}

void MainCameraTipWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
    case MainCameraTipCL::CL_UpdateText:
    {
        textString=data.toString();
//        System::getInstance()->setAllMsgHide();// 隐藏其他弹出框
//        System::getInstance()->setCurrentMsg(MD_MainCameraTip);
        this->show();
        break;
    }
    case MainCameraTipCL::CL_Hide:
    {
        this->hide();
        break;
    }

    default:
        break;
    }
}

void MainCameraTipWgt::onModelUpdate(int cmd)
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

void MainCameraTipWgt::tickTimerOut()
{
    static bool flag=true;
    if(flag)
    {
        ui->label_tip->setStyleSheet("color:white");
        ui->widget->setPenColor(QColor(0x00, 0xba, 0xff));
    }else
    {
        ui->label_tip->setStyleSheet("color:red");
        ui->widget->setPenColor(QColor(0xfa, 0x5a, 0x00));
    }
    ui->label_tip->setText(textString);
    flag=!flag;
    this->update();
}

void MainCameraTipWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),Qt::black);
}
