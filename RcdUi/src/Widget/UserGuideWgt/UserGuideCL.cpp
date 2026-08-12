#include "UserGuideCL.h"
#include <QDebug>

UserGuideCL::UserGuideCL(QObject *parent) : IController(parent)
{

}

UserGuideCL::~UserGuideCL()
{

}

void UserGuideCL::doInit()
{
//    qInfo()<<"UserGuideCL::doInit()";
}

void UserGuideCL::doUnInit()
{

}

bool UserGuideCL::exitAction()
{
    return true;
}

bool UserGuideCL::intoAction()
{

    return true;
}

void UserGuideCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    AllInfoWgtCmdType Cmd = static_cast<AllInfoWgtCmdType>(cmd);

    switch (Cmd) {
    case AI_LoadNewUrl:{
        QString url = data.toString();
        m_pModel->setUrl(url);
        break;
    }

    default:{break;}
    }

}


void UserGuideCL::setModel(UserGuideModel *model)
{
    m_pModel = model;
}
