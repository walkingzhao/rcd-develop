#include "ForwardRightCameraWgt.h"
#include "ui_ForwardRightCameraWgt.h"
#include <QVBoxLayout>
#include <QShowEvent>
#include <QPainter>
#include <QThread>
#include <QPixmap>
#include <QTimer>
#include <QSettings>
#include <QDebug>

#include "Component/TitleWgt.h"
//#include "Component/hikvisioncamera.h"
#include <QApplication>
#include "public/jsonMethord.h"
ForwardRightCameraWgt* ForwardRightCameraWgt::s_pInstance = nullptr; //初始化静态数据成员

ForwardRightCameraWgt::ForwardRightCameraWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::ForwardRightCameraWgt)
{
    ui->setupUi(this);
    m_pCL = new ForwardRightCameraCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    ui->leftVideoFrame1->setFrameType(TGFrame::VideoFrameLeftPage2No1);
    ui->playWgt->setShadowType(TGFrame::ShadowLeftPage2No1);

    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(0,0,0,0);
    pVLayout->setSpacing(0);

    pVLayout->addWidget(ui->leftVideoFrame1);

    QVBoxLayout *pFrameVLayout = new QVBoxLayout(ui->leftVideoFrame1);
    pFrameVLayout->setContentsMargins(20, 20, 20, 20);
    pFrameVLayout->setSpacing(10);
    m_pTitleWgt = new TitleWgt(ui->leftVideoFrame1);
    QString str(QString::fromUtf8("【xxxx】 右前摄像头"));
    m_pTitleWgt->setTitleString(str);
    pFrameVLayout->addWidget(m_pTitleWgt,1);
    pFrameVLayout->addWidget(ui->playWgt,9);


    ui->leftVideoFrame1->setLayout(pFrameVLayout);

    this->setLayout(pVLayout);
}

ForwardRightCameraWgt::~ForwardRightCameraWgt()
{
    delete ui;
    delete m_pCL;
    if(audioDecode != nullptr)
    {
        delete audioDecode;
        audioDecode = nullptr;
    }
}

ForwardRightCameraWgt *ForwardRightCameraWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new ForwardRightCameraWgt();
    }
    return s_pInstance;
}

void ForwardRightCameraWgt::initWidget()
{
//    qInfo()<<"ForwardRightCameraWgt::initWidget";
    m_pCL->intoAction();
}

bool ForwardRightCameraWgt::isQuit()
{
//    qInfo()<<"ForwardRightCameraWgt::isQuit";
    m_pCL->exitAction();
    return true;
}
#ifndef HIK_INTERFACE
void ForwardRightCameraWgt::updateWidget()
{
    qDebug()<<"updatexzk 调用右前updateWidget";
    static bool switchFlag=false;
    if(switchFlag!=System::getInstance()->forwardLeft_forwardRight_Big)
    {
        ui->playWgt->stopPlay();
        switchFlag = System::getInstance()->forwardLeft_forwardRight_Big;
    }
    if(System::getInstance()->forwardLeft_forwardRight_Big){
        qInfo()<<"updatexzk更新右前摄像头显示";
        QString currImei = System::getInstance()->getCurrentVehicle();
        QVariant data = jsonMethord::getInstance()
                ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
        if(data.toList().isEmpty()){
            return;
        }
        QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
        QString tmpStr = mapVehicle.value(currImei).toList().at(0).toMap().value("ForwardRight").toString();
        ui->playWgt->startPlay(tmpStr);
        tmpStr = mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString();
        tmpStr = QString::fromUtf8("【%1】 右前摄像头").arg(tmpStr);
        m_pTitleWgt->setTitleString(tmpStr);
    }
    this->update();
}
#else
void ForwardRightCameraWgt::updateWidget()
{
    qInfo()<<"更新驾驶舱摄像头显示";
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    vehicleName = mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString();
//    QString url = HikvisionCamera::instance()->getCameraUrl(vehicleName + "-Drive");
    QString cameraName = vehicleName + "-Drive";
//    if(url.isEmpty())return;
    ui->playWgt->startPlay(cameraName);
//    qDebug()<<"车辆"<<vehicleName<<"驾驶室摄像头url:"<<url;
    QString tmpStr = QString::fromUtf8("【%1】 驾驶舱摄像头").arg(vehicleName);
    m_pTitleWgt->setTitleString(tmpStr);


    //初始化音频
    if(audioDecode != nullptr)
    {
        audioDecode->stopPlay();
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        QThread::sleep(1);
        delete audioDecode;
        audioDecode = nullptr;
    }
    QString audioStr = mapVehicle.value(currImei).toList().at(0).toMap().value("AudioStream").toString();
    if(!audioStr.isEmpty()){
        qDebug()<<"驾驶室audio:"<<audioStr;
        audioDecode = new AudioDecode(audioStr.toStdString(),44100,16,2);
    }
}
#endif
void ForwardRightCameraWgt::showEvent(QShowEvent *)
{
//   this->updateWidget();
}

void ForwardRightCameraWgt::hideEvent(QHideEvent *)
{
//    qInfo()<<"updatexzk ForwardRightCameraWgt::stopPlay";
//    ui->playWgt->stopPlay();
}


void ForwardRightCameraWgt::onClDataCome(int cmd, QVariant data)
{
    switch (cmd) {
//    case ForwardRightCameraCL::CL_UpdateCamera:
//    {
//        this->updateWidget();
//        break;
//    }
    case ForwardRightCameraCL::CL_StartPlay:
    {
        if(data.toBool())
        {
            qInfo()<<"updatexzk ForwardRightCameraWgt::startPlay";
            this->updateWidget();
        }else
        {
            qInfo()<<"updatexzk ForwardRightCameraWgt::stopPlay";
            ui->playWgt->stopPlay();
            this->update();
        }
    }

    default:
        break;
    }
}

