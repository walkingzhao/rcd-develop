#include "TakeOverInfoWgt.h"
#include "ui_TakeOverInfoWgt.h"
#include <QDebug>
TakeOverInfoWgt* TakeOverInfoWgt::s_pInstance = nullptr; //初始化静态数据成员

TakeOverInfoWgt::TakeOverInfoWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::TakeOverInfoWgt)
{
    ui->setupUi(this);
    // 创建控制层
    m_pCL = new TakeOverInfoCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);
    // 创建数据层
    m_pModel = new TakeOverInfoModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    ui->Title->setFrameType(TGFrame::InfoFrameRightPage2No5);
    ui->Title->setTitleString(QString::fromUtf8("接管信息"));


    QHBoxLayout *pHLayout = new QHBoxLayout();
    pHLayout->addStretch(2);
    pHLayout->addWidget(ui->frame,10);
    pHLayout->addStretch(2);
    pHLayout->addWidget(ui->frame_2,10);
    pHLayout->addStretch(2);

    QVBoxLayout* pVLayout = new QVBoxLayout(ui->Title);
    pVLayout->addStretch(2);
    pVLayout->addLayout(pHLayout,10);
    pVLayout->addStretch(1);





    pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(ui->Title);
    setLayout(pVLayout);
//    ui->label_car_icon->setPixmap(QPixmap(QString("resource/car/no_load.png")));
}

TakeOverInfoWgt::~TakeOverInfoWgt()
{
    delete ui;
}

TakeOverInfoWgt *TakeOverInfoWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new TakeOverInfoWgt();
    }
    return s_pInstance;
}

void TakeOverInfoWgt::onClDataCome(int cmd, QVariant data)
{

}

void TakeOverInfoWgt::onModelUpdate(int cmd)
{
    TakeOverInfoModel::ModelCmdType tCmd = static_cast<TakeOverInfoModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case TakeOverInfoModel::MC_UpdateAll:
    {
        ui->label_work_info->setText(m_pModel->m_destName);//接管目标
        ui->label_car_num->setText(m_pModel->m_curName);//矿卡编号
        ui->label_load_area->setText(m_pModel->m_orgDestName);//装载区域
        if(m_pModel->m_loadStatus==0x01)//空载
        {
            ui->label_car_icon->setPixmap(QPixmap(":/resource/car/no_load.png"));
        }else if(m_pModel->m_loadStatus==0x02)//满载
        {
            ui->label_car_icon->setPixmap(QPixmap(":/resource/car/full_load.png"));
        }else if(m_pModel->m_loadStatus==0x03)//半载
        {
            ui->label_car_icon->setPixmap(QPixmap(":/resource/car/half_load.png"));
        }
        break;
    }

    default:
        break;
    }
}
