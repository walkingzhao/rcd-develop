#include "DriveCameraWgt.h"
#include "ui_DriveCameraWgt.h"
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
DriveCameraWgt* DriveCameraWgt::s_pInstance = nullptr; //初始化静态数据成员

DriveCameraWgt::DriveCameraWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::DriveCameraWgt)
{
    ui->setupUi(this);
    m_pCL = new DriveCameraCL();
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
    QString str(QString::fromUtf8("【xxxx】 驾驶舱摄像头"));
    m_pTitleWgt->setTitleString(str);
    pFrameVLayout->addWidget(m_pTitleWgt, 1);
    pFrameVLayout->addWidget(ui->playWgt, 15);


    ui->leftVideoFrame1->setLayout(pFrameVLayout);

    this->setLayout(pVLayout);
}

DriveCameraWgt::~DriveCameraWgt()
{
    delete ui;
    delete m_pCL;
    if(audioDecode != nullptr)
    {
        delete audioDecode;
        audioDecode = nullptr;
    }
}

DriveCameraWgt *DriveCameraWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new DriveCameraWgt();
    }
    return s_pInstance;
}

void DriveCameraWgt::initWidget()
{
//    qInfo()<<"DriveCameraWgt::initWidget";
    m_pCL->intoAction();
}

bool DriveCameraWgt::isQuit()
{
//    qInfo()<<"DriveCameraWgt::isQuit";
    m_pCL->exitAction();
    return true;
}
#ifndef HIK_INTERFACE
void DriveCameraWgt::updateWidget()
{
    static bool switchFlag = false;
    if(switchFlag != System::getInstance()->forwardLeft_forwardRight_Big){
        ui->playWgt->stopPlay();
        switchFlag = System::getInstance()->forwardLeft_forwardRight_Big;
    }

    if(System::getInstance()->forwardLeft_forwardRight_Big){
        qInfo()<<"updatexzk更新左前摄像头显示";
        QString currImei = System::getInstance()->getCurrentVehicle();
        QVariant data = jsonMethord::getInstance()
                ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
        if(data.toList().isEmpty()){
            return;
        }
        QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
        QString tmpStr = mapVehicle.value(currImei).toList().at(0).toMap().value("ForwardLeft").toString();
        ui->playWgt->startPlay(tmpStr);
        tmpStr = mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString();
        tmpStr = QString::fromUtf8("【%1】 左前摄像头").arg(tmpStr);
        m_pTitleWgt->setTitleString(tmpStr);
    }else{
        qInfo()<<"updatexzk更新驾驶舱摄像头显示";
        QString currImei = System::getInstance()->getCurrentVehicle();
        QVariant data = jsonMethord::getInstance()
                ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
        if(data.toList().isEmpty()){
            return;
        }
        QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
        QString tmpStr = mapVehicle.value(currImei).toList().at(0).toMap().value("Drive").toString();

        ui->playWgt->startPlay(tmpStr);

        tmpStr = mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString();
        tmpStr = QString::fromUtf8("【%1】 驾驶舱摄像头").arg(tmpStr);
        m_pTitleWgt->setTitleString(tmpStr);
    }
    this->update();

#if 0
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
#endif
}
#else
void DriveCameraWgt::updateWidget()
{
    qInfo()<<"更新驾驶舱摄像头显示";
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    const QVariantMap vehicle = mapVehicle.value(currImei).toList().at(0).toMap();
    vehicleName = vehicle.value("Name").toString();
    QString playUrl = vehicle.value("Drive").toString();
    if(playUrl.isEmpty()){
        playUrl = vehicleName + "-Drive";
    }
    ui->playWgt->startPlay(playUrl);
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
    QString audioStr = vehicle.value("AudioStream").toString();
    if(!audioStr.isEmpty()){
        qDebug()<<"驾驶室audio:"<<audioStr;
        audioDecode = new AudioDecode(audioStr.toStdString(),44100,16,2);
    }
}
#endif
void DriveCameraWgt::showEvent(QShowEvent *)
{
//    this->updateWidget();
}

void DriveCameraWgt::hideEvent(QHideEvent *)
{
//    qInfo()<<"DriveCameraWgt::stopPlay";
//    ui->playWgt->stopPlay();
//    if(audioDecode!=nullptr)
//        audioDecode->stopPlay();
}


void DriveCameraWgt::onClDataCome(int cmd, QVariant data)
{
    data.isValid();
    switch (cmd) {
    case DriveCameraCL::CL_UpdateCamera:
    {
        this->updateWidget();
        break;
    }
    case DriveCameraCL::CL_StartPlay:
    {
        if(data.toBool())
        {
            qDebug()<<"updatexzk DriveCameraCL:startplay";
            this->updateWidget();
        }else
        {
            qInfo()<<"updatexzk DriveCameraWgt::stopPlay";
            ui->playWgt->stopPlay();
            if(audioDecode!=nullptr){
                audioDecode->stopPlay();
            }
            this->update();
        }
        break;
    }

    default:
        break;
    }
}

