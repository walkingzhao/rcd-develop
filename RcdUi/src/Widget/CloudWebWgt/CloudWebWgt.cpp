#include "CloudWebWgt.h"
#include "ui_CloudWebWgt.h"
#include <QScreen>
#include <QVBoxLayout>
#include <QDebug>

#include "Component/WebEngine.h"

CloudWebWgt* CloudWebWgt::s_pInstance = nullptr; //初始化静态数据成员

CloudWebWgt::CloudWebWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::CloudWebWgt)
{
    ui->setupUi(this);
    m_pCL = new CloudWebCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new CloudWebModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    ui->webFrame1->setTitleString(QString::fromUtf8("行车地图"));
    smallMapType = 1;
    ui->webFrame1->setFrameType(TGFrame::InfoFrameRightPage2No8);

    m_pWeb = new WebEngine();
    QVBoxLayout* pVLayout = new QVBoxLayout(ui->webFrame1);
    pVLayout->setContentsMargins(20,50,20,20);
    pVLayout->setSpacing(6);

    pVLayout->addWidget(m_pWeb);
    ui->webFrame1->setLayout(pVLayout);


    pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(0, 0, 0, 0);
    pVLayout->setSpacing(0);

    pVLayout->addWidget(ui->webFrame1);
    this->setLayout(pVLayout);

    connect(m_pWeb,SIGNAL(loadFinished(bool)),this,SLOT(slotLoadFinished(bool)));

//    connect(&_timerSwitchMap,SIGNAL(timeout()),this,SLOT(slotUpdateMap()));
//    _timerSwitchMap.start(20*1000);
}

void CloudWebWgt::slotLoadFinished(bool ret)
{
    loadMapResult = ret;
    if(!loadMapResult){
        setFrameType(smallMapType);
//        QTimer::singleShot(5*1000,this,SLOT(on_pushButton_ok_clicked()));
    }
}

CloudWebWgt::~CloudWebWgt()
{
    delete ui;
    delete m_pCL;
    delete m_pModel;
}

CloudWebWgt *CloudWebWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new CloudWebWgt();
    }
    return s_pInstance;
}

void CloudWebWgt::resizeEvent(QResizeEvent *event)
{
    /*QScreen *pScreen = QGuiApplication::primaryScreen();
    if(smallMapType==0)
    {
        if(event->size().height() > pScreen->size().height()/2){
            ui->webFrame1->setFrameType(TGFrame::InfoFrameLeftPage1No1);
        }else{
            ui->webFrame1->setFrameType(TGFrame::InfoFrameLeftPage2No1);
        }
    }else */if(smallMapType==1)
        ui->webFrame1->setFrameType(TGFrame::InfoFrameRightPage2No8);
    //    qDebug()<<"CloudWebWgt resizeEvent:"<<smallMapType;
}

void CloudWebWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QImage image;
    image.load(":/image/1.png");
    QPixmap mapImage = QPixmap::fromImage(image);
    mapImage = mapImage.scaled(this->rect().width(), this->rect().height(), Qt::KeepAspectRatio);

    painter.drawPixmap(this->rect(), mapImage);
}

void CloudWebWgt::initWidget()
{
//    qInfo()<<"CloudWebWgt::initWidget";
    m_pCL->intoAction();
    this->updateWidget();
}

bool CloudWebWgt::isQuit()
{
//    qInfo()<<"CloudWebWgt::isQuit";
    m_pCL->exitAction();
    return true;
}

void CloudWebWgt::updateWidget()
{
//    qInfo()<<"CloudWebWgt::updateWidget"<<m_pModel->m_url;
//    m_pWeb->load(m_pModel->m_url);
}

void CloudWebWgt::setFrameType(int small)
{
    smallMapType = small;
    /*if(small==0)//monitor
    {
        //m_pWeb->load(m_pModel->m_url);
//        m_pWeb->load(m_pModel->m_url+"/"+System::getInstance()->getCurrentVehicle());
        ui->webFrame1->setFrameType(TGFrame::InfoFrameLeftPage1No1);
        qDebug()<<"全局模式地图url:"<<m_pModel->m_url;
//        m_pWeb->reload();
    }
    else */if(small==1)//remote
    {
        //m_pWeb->load(m_pModel->m_url+"/"+System::getInstance()->getCurrentVehicle());
        ui->webFrame1->setFrameType(TGFrame::InfoFrameRightPage2No8);
        qDebug()<<"单车模式地图url:"<<m_pModel->m_url+"/"+System::getInstance()->getCurrentVehicle();
//        m_pWeb->reload();
    }
}

void CloudWebWgt::onClDataCome(int cmd, QVariant data)
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

void CloudWebWgt::onModelUpdate(int cmd)
{
    CloudWebModel::ModelCmdType tCmd = static_cast<CloudWebModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case CloudWebModel::MC_UpdateAll:
    {
        this->updateWidget();
        break;
    }
    case CloudWebModel::MC_LoadUrl:
    {
        //m_pWeb->load(m_pModel->m_url);

        break;
    }
    case CloudWebModel::MC_SwitchMap:
    {
        /*if(m_pModel->_mapMode == "0"){

            m_pWeb->load(m_pModel->m_url);

        }
        else if(m_pModel->_mapMode == "1"){
            m_pWeb->load(m_pModel->m_url+"/"+System::getInstance()->getCurrentVehicle());
        }*/
        break;
    }

    default:
        break;
    }
}

void CloudWebWgt::slotUpdateMap()
{
#if 0
    if(System::getInstance()->getCurrentLayoutType() == LT_Monitor){

        if(_mapId != 0){
            m_pWeb->load(m_pModel->m_url);

            _mapId = 0;
        }
    }
    else if (System::getInstance()->getCurrentLayoutType() == LT_RemoteControl/*&&
             (System::getInstance()->getCurrentCabinMode()==CM_WaitTakeover||
              System::getInstance()->getCurrentCabinMode()==CM_Takeover)*/) {
        if(_mapId !=1){
            m_pWeb->load(m_pModel->m_url+"/"+System::getInstance()->getCurrentVehicle());
            _mapId =1;
        }
    }
#endif
    setFrameType(smallMapType);
    _timerSwitchMap.stop();
}
