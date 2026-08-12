#include "LeftCameraCL.h"
#include <QDebug>
#include <QSettings>
#include "public/jsonMethord.h"
#include <QApplication>
//#include "Component/hikvisioncamera.h"
LeftCameraCL::LeftCameraCL(QObject *parent) : IController(parent)
{

}

LeftCameraCL::~LeftCameraCL()
{

}

void LeftCameraCL::doInit()
{
//    qInfo()<<"LeftCameraCL::doInit()";
}

void LeftCameraCL::doUnInit()
{

}

bool LeftCameraCL::exitAction()
{
    return true;
}

#ifdef HIK_INTERFACE
bool LeftCameraCL::intoAction()
{
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return false;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    const QVariantMap vehicle = mapVehicle.value(currImei).toList().at(0).toMap();
    m_pModel->m_url = vehicle.value("Left").toString();
    QString tmpStr(vehicle.value("Name").toString());
    m_pModel->vehicleName = tmpStr;
    // Keep the legacy camera name as a fallback when URL is not configured.
    m_pModel->m_cameraNameUrl = m_pModel->vehicleName + "-Left";
    m_pModel->m_name = QString::fromUtf8("【%1】 左后摄像头").arg(tmpStr);
    return true;
}
#else
bool LeftCameraCL::intoAction()
{
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return false;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    m_pModel->m_url = mapVehicle.value(currImei).toList().at(0).toMap().value("Left").toString();
    QString tmpStr(mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString());
    m_pModel->m_name = QString::fromUtf8("【%1】 左后摄像头").arg(tmpStr);
    return true;
}
#endif
void LeftCameraCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    Q_UNUSED(data)
//    LeftCameraWgtCmdType Cmd = static_cast<LeftCameraWgtCmdType>(cmd);

    switch (cmd) {
    case CommonCmdType::CC_StartPlay:{
        emit pushDataToView(CL_StartPlay,data);
        break;
    }


    default:{break;}
    }

}


void LeftCameraCL::setModel(LeftCameraModel *model)
{
    m_pModel = model;
}
