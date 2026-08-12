#include "RightCameraWgt.h"
#include "ui_RightCameraWgt.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QShowEvent>
#include <QPainter>
#include <QThread>
#include <QPixmap>
#include <QTimer>
#include <QDebug>

#include "Component/TitleWgt.h"
//#include "Component/hikvisioncamera.h"

RightCameraWgt* RightCameraWgt::s_pInstance = nullptr; //初始化静态数据成员

RightCameraWgt::RightCameraWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::RightCameraWgt)
{
    ui->setupUi(this);
    m_pCL = new RightCameraCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new RightCameraModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);


    ui->playWgt->setShadowType(TGFrame::ShadowRightPage2No1);
    ui->rightVideoFrame1->setFrameType(TGFrame::VideoFrameRightPage2No1);/*
    ui->rightVideoFrame1->setFixedHeight(800);*/
    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->setSpacing(0);
    pVLayout->addWidget(ui->rightVideoFrame1);

    QVBoxLayout *pFrameVLayout = new QVBoxLayout(ui->rightVideoFrame1);
    pFrameVLayout->setContentsMargins(20, 20, 20, 20);
    pFrameVLayout->setSpacing(10);
    m_pTitleWgt = new TitleWgt(ui->rightVideoFrame1);
    QString str(QString::fromUtf8("【xxxx】 右后摄像头"));
    m_pTitleWgt->setTitleString(str);
    pFrameVLayout->addWidget(m_pTitleWgt,1);
    pFrameVLayout->addWidget(ui->playWgt,15);
    ui->rightVideoFrame1->setLayout(pFrameVLayout);
    setLayout(pVLayout);
}

RightCameraWgt::~RightCameraWgt()
{
    delete ui;
    delete m_pCL;
    delete m_pModel;
}

RightCameraWgt *RightCameraWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new RightCameraWgt();
    }
    return s_pInstance;
}

void RightCameraWgt::initWidget()
{
//    qInfo()<<"RightCameraWgt::initWidget";
    m_pCL->intoAction();
}

bool RightCameraWgt::isQuit()
{
//    qInfo()<<"RightCameraWgt::isQuit";
    m_pCL->exitAction();
    return true;
}
#ifdef HIK_INTERFACE
void RightCameraWgt::updateWidget()
{
//    qInfo()<<"RightCameraWgt::updateWidget";
    if(!m_pModel->m_url.isEmpty())
        ui->playWgt->startPlay(m_pModel->m_url);
    else if(!m_pModel->m_cameraNameUrl.isEmpty())
        ui->playWgt->startPlay(m_pModel->m_cameraNameUrl);
//    qDebug()<<"右后摄像头url:"<<m_pModel->m_url;
    m_pTitleWgt->setTitleString(m_pModel->m_name);
    this->update();
}
#else
void RightCameraWgt::updateWidget()
{
    qInfo()<<"updatexzk RightCameraWgt::updateWidget";
    ui->playWgt->startPlay(m_pModel->m_url);
    m_pTitleWgt->setTitleString(m_pModel->m_name);
    this->update();

}
#endif
void RightCameraWgt::showEvent(QShowEvent *)
{


}

void RightCameraWgt::hideEvent(QHideEvent *)
{

}

void RightCameraWgt::onClDataCome(int cmd, QVariant data)
{
    RightCameraCL::CLCmdType tCmd = static_cast<RightCameraCL::CLCmdType>(cmd);
    switch (tCmd) {
    case RightCameraCL::CL_StartPlay:
    {
        if(data.toBool())
        {
            qDebug()<<"updatexzk 右后摄像头 startPlay";
            m_pCL->intoAction();
            this->updateWidget();
        }else
        {
             qInfo()<<"updatexzk 右后摄像头 stopPlay";

             ui->playWgt->stopPlay();
        }
        break;
    }
    case RightCameraCL::CL_UpdateSelect:
    {

        break;
    }
    case RightCameraCL::CL_InputKey:
    {
        break;
        QWidget *pWidget = static_cast<QWidget*>(this->parent());
        pWidget->activateWindow();
        pWidget->releaseKeyboard(); //有按键按下，完成抓取，释放全局按键抓取。
        break;
    }
    default:
        break;
    }
}

void RightCameraWgt::onModelUpdate(int cmd)
{
    RightCameraModel::ModelCmdType tCmd = static_cast<RightCameraModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case RightCameraModel::MC_UpdateAll:
    {
        this->updateWidget();
        break;
    }

    default:
        break;
    }
}

