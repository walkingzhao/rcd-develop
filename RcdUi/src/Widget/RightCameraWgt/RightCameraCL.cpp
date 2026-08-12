#include "RightCameraCL.h"
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include "public/jsonMethord.h"
//#include "Component/hikvisioncamera.h"
RightCameraCL::RightCameraCL(QObject *parent) : IController(parent)
{

}

RightCameraCL::~RightCameraCL()
{

}

void RightCameraCL::doInit()
{
//    qInfo()<<"RightCameraCL::doInit()";
}

void RightCameraCL::doUnInit()
{

}

bool RightCameraCL::exitAction()
{
    return true;
}
#ifdef HIK_INTERFACE
bool RightCameraCL::intoAction()
{
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return false;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();
    const QVariantMap vehicle = mapVehicle.value(currImei).toList().at(0).toMap();
    m_pModel->m_url = vehicle.value("Right").toString();
    QString tmpStr(vehicle.value("Name").toString());
    m_pModel->vehicleName = tmpStr;
    // Keep the legacy camera name as a fallback when URL is not configured.
    m_pModel->m_cameraNameUrl = m_pModel->vehicleName + "-Right";
    m_pModel->m_name = QString::fromUtf8("【%1】 右后摄像头").arg(tmpStr);
    qDebug()<<"摄像头名字："<<m_pModel->m_name;
    return true;
}
#else
bool RightCameraCL::intoAction()
{
    QString currImei = System::getInstance()->getCurrentVehicle();
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return false;
    }
    QMap<QString, QVariant> mapVehicle = data.toList().at(0).toMap();

    m_pModel->m_url = mapVehicle.value(currImei).toList().at(0).toMap().value("Right").toString();
    QString tmpStr(mapVehicle.value(currImei).toList().at(0).toMap().value("Name").toString());
    m_pModel->m_name = QString::fromUtf8("【%1】 右后摄像头").arg(tmpStr);
    qDebug()<<"摄像头名字："<<m_pModel->m_name;
    return true;
}
#endif
void RightCameraCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
//    RightCameraWgtCmdType Cmd = static_cast<RightCameraWgtCmdType>(cmd);

    switch (cmd) {
    case CommonCmdType::CC_StartPlay:{
        emit pushDataToView(CL_StartPlay,data);
        break;
    }
    case RC_InputKey:{

        break;
    }
    case RC_UpdateForwardRihgtCamera:{//为了进程间数据同步
        System::getInstance()->forwardLeft_forwardRight_Big=data.toBool();
        break;
    }
    default:{break;}
    }

}

void RightCameraCL::inputHandler(Qt::Key key)
{

}


void RightCameraCL::setModel(RightCameraModel *model)
{
    m_pModel = model;
}
