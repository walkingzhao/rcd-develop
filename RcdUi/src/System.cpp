#include "System.h"
#include <QApplication>
#include <QTime>
#include <QSharedMemory>
#include "Interface/WgtFactory.h"
#include <QDebug>
#include "public/fbsstructure.h"
#include "public/jsonMethord.h"
#define KEY_SHARED_MEMORY  "RcdSysShareData"

System *System::m_pInstance = nullptr;

System::System() : m_processType(PT_All),m_pSharedMemory(nullptr)
{
    qRegisterMetaType<ModuleDir>("ModuleDir");
    qRegisterMetaTypeStreamOperators<dispatchTaskST>("dispatchTaskST");
    qRegisterMetaTypeStreamOperators<cabinTakeoverTaskApplyST>("cabinTakeoverTaskApplyST");
    qRegisterMetaTypeStreamOperators<vehicleDataST>("vehicleDataST");
    qRegisterMetaTypeStreamOperators<SelfCheckStatusST>("SelfCheckStatusST");
    qRegisterMetaTypeStreamOperators<ReportRoadTaskInfoST>("ReportRoadTaskInfoST");


    memset(&m_sysShareData,0,sizeof(m_sysShareData));
    m_pSharedMemory = new QSharedMemory();
    m_taskId = 0;
    m_CarbinMode = CM_Monitor;
    m_currentMsg = MD_None;

    QVariant dataLogin = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Login");

    if(dataLogin.toList().isEmpty()) return;

    if(dataLogin.toList().at(0).toMap()["name"].toString().isEmpty()) return;
    setCurrentDriverLogin(dataLogin.toList().at(0).toMap()["name"].toString());
}

System::~System()
{
    m_pSharedMemory->detach();
    delete m_pSharedMemory;
}

System *System::getInstance()
{
    if(m_pInstance == nullptr){
        m_pInstance = new System();
    }
    return m_pInstance;
}

void System::createSharedMemory()
{
    m_pSharedMemory->setKey(KEY_SHARED_MEMORY);
    if(m_processType == PT_MidProc){
        if(m_pSharedMemory->isAttached()){
            m_pSharedMemory->detach();
        }
        if(!m_pSharedMemory->create(sizeof(SharedDatas))){
            qWarning() << "Unable to create SharedMemory:" << m_processType << m_pSharedMemory->errorString();
        }
    }
}

void System::readSharedMemory()
{
    if(!m_pSharedMemory->isAttached()){
        if(!m_pSharedMemory->attach(QSharedMemory::ReadOnly)){
            qWarning() << "Read attach error:"<< m_pSharedMemory->errorString();
            return;
        }
    }
    m_pSharedMemory->lock();
    memcpy(&m_sysShareData,m_pSharedMemory->constData(),sizeof(SharedDatas));
    m_pSharedMemory->unlock();

    //    if(m_processType != PT_MidProc){
    //        m_pSharedMemory->detach();
    //    }
}

void System::writeSharedMemory()
{
    if(!m_pSharedMemory->isAttached()){
        if(!m_pSharedMemory->attach(QSharedMemory::ReadWrite)){
            qWarning() << "Write attach error:" <<m_pSharedMemory->errorString();
            return;
        }
    }
    m_pSharedMemory->lock();
    memcpy(m_pSharedMemory->data(),&m_sysShareData,sizeof(SharedDatas));
    m_pSharedMemory->unlock();

    //    if(m_processType != PT_MidProc){
    //        m_pSharedMemory->detach();
    //    }
}

void System::delayMsecTime(int msecTime,int delayModel) //delayModel=0 阻塞模式延时 delayModel!=0 非阻塞模式延时
{
    if(delayModel > 0){
        QTime n = QTime::currentTime();
        QTime now;
        do{
            now = QTime::currentTime();
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
        while(n.msecsTo(now)<=msecTime);
    }else{
        QTime n = QTime::currentTime();
        QTime now;
        do{
            now = QTime::currentTime();
        }
        while(n.msecsTo(now)<=msecTime);
    }
}

ProcessType System::belongTo(ModuleType mdType)
{
    ProcessType type = PT_All;
    if(mdType >= MD_LeftCamera && mdType <= MD_UserGuide){
        type = PT_LeftProc;
    }else if(mdType >= MD_MainCamera && mdType <= MD_MainMonitor){
        type = PT_MidProc;
    }else if(mdType >= MD_RightCamera && mdType <= MD_WarnInfo){
        type = PT_RightProc;
    }
    return type;
}

bool System::messageFilter(ModuleType module)
{
    bool ret = false;
    if(m_processType & belongTo(module)){
        ret = !(WgtFactory::getFunWidget(module)->isHidden());
    }
    return ret;
}

bool System::messageFilter(ModuleType module,QString &imei)
{
    if(messageFilter(module)){
        return (QString(m_sysShareData.vehicleImei) == imei);
    }else{
        return false;
    }
}

void System::setCurrentVehicle(QString &imei)
{
    if(imei.count() < 16){
        strcpy(m_sysShareData.vehicleImei,imei.toUtf8().data());
        if(m_processType != PT_All){
            writeSharedMemory();
        }
    }
}

QString System::getCurrentVehicle()
{
    if(m_processType != PT_All){
        readSharedMemory();
    }
    return QString(m_sysShareData.vehicleImei);
}

unsigned short System::getCurrentTaskId()
{
    return  m_taskId;
}

void System::setCurrentTaskId(unsigned short &taskId)
{
    m_taskId = taskId;
}

void System::setVehicleStatus(int type)
{
    currentVehicleStatus = type;
}

int System::getVehicleStatus()
{
    return currentVehicleStatus;
}

// --> BEGIN added by ZJZ, 2022/3/22
void System::setVehicleTakeoverPurpose(int purpose)
{
    currentVehiclePurpose = purpose;
}

int System::getVehicleTakeoverPurpose()
{
    return currentVehiclePurpose;
}
// <-- END

void System::setShowEmergency(bool state)
{
    emergencyState = state;
}

bool System::getShowEmergency()
{
    return emergencyState;
}

CabinModeType System::getCurrentCabinMode()
{
    return m_CarbinMode;
}

void System::setCurrentCabinMode(CabinModeType mode)
{
    m_CarbinMode = mode;
}

void System::setProcessType(ProcessType type)
{
    m_processType = type;
    if(type != PT_All){
        createSharedMemory();
    }
}

int System::getProcessType()
{
    return m_processType;
}

System::SharedDatas* System::getSharedDatas()
{
    return &m_sysShareData;
}

ModuleType System::getCurrentMsg()
{
    return m_currentMsg;
}

void System::setCurrentMsg(ModuleType wgt)
{
    m_currentMsg = wgt;
}
void System::setCurrentDriverLogin(const QString &data)//司机登录
{

    _variantDriverInfo = data;
//    qDebug()<<_variantDriverInfo<<"----------->司机登录名称";
}
QString System::getCurrentDriverLoginStatus()//司机登录返回结果
{
    return  _variantDriverInfo;
}
