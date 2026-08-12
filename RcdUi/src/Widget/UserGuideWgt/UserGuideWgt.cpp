#include "UserGuideWgt.h"
#include "ui_UserGuideWgt.h"
#include <QVBoxLayout>
#include <QDebug>

//#include "Component/Dashboard.h"
#include "Component/AnalogClock.h"

UserGuideWgt* UserGuideWgt::s_pInstance = nullptr; //初始化静态数据成员

UserGuideWgt::UserGuideWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::UserGuideWgt)
{
    ui->setupUi(this);
    m_pCL = new UserGuideCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new UserGuideModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    ui->rightTitle->setTitleString(QString::fromUtf8("设备介绍"));
    ui->rightTitle->setFrameType(TGFrame::InfoFrameRightPage1No1);

    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->setSpacing(0);
    pVLayout->addStretch(3);
    pVLayout->addWidget(ui->rightTitle,94);
    pVLayout->addStretch(3);
    this->setLayout(pVLayout);
}

UserGuideWgt::~UserGuideWgt()
{
    delete ui;
    delete m_pCL;
    delete m_pModel;
}

UserGuideWgt *UserGuideWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new UserGuideWgt();
    }
    return s_pInstance;
}

void UserGuideWgt::initWidget()
{
//    qInfo()<<"UserGuideWgt::initWidget";
    m_pCL->intoAction();
    this->updateWidget();
}

bool UserGuideWgt::isQuit()
{
//    qInfo()<<"UserGuideWgt::isQuit";
    m_pCL->exitAction();
    return true;
}

void UserGuideWgt::updateWidget()
{
//    qInfo()<<"UserGuideWgt::updateWidget";
}

void UserGuideWgt::onClDataCome(int cmd, QVariant data)
{
    data.isValid();
    switch (cmd) {
    case 1:
    {
        this->updateWidget();
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

void UserGuideWgt::onModelUpdate(int cmd)
{
    UserGuideModel::ModelCmdType tCmd = static_cast<UserGuideModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case UserGuideModel::MC_UpdateAll:
    {
        this->updateWidget();
        break;
    }
    case UserGuideModel::MC_LoadUrl:
    {

        break;
    }

    default:
        break;
    }
}

