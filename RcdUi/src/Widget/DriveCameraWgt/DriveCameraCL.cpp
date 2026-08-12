#include "DriveCameraCL.h"
#include <QDebug>

DriveCameraCL::DriveCameraCL(QObject *parent) : IController(parent)
{

}

DriveCameraCL::~DriveCameraCL()
{

}

void DriveCameraCL::doInit()
{
//    qInfo()<<"DriveCameraCL::doInit()";
}

void DriveCameraCL::doUnInit()
{

}

bool DriveCameraCL::exitAction()
{
    return true;
}

bool DriveCameraCL::intoAction()
{

    return true;
}

void DriveCameraCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();

    switch (cmd) {
    case DC_UpdateCamera:{
        System::getInstance()->forwardLeft_forwardRight_Big = data.toBool();
        emit pushDataToView(CL_UpdateCamera);
        break;
    }
    case CC_StartPlay:{
        emit pushDataToView(CL_StartPlay,data);
        break;
    }


    default:{break;}
    }

}

