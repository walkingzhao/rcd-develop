#include "ForwardRightCameraCL.h"
#include <QDebug>

ForwardRightCameraCL::ForwardRightCameraCL(QObject *parent) : IController(parent)
{

}

ForwardRightCameraCL::~ForwardRightCameraCL()
{

}

void ForwardRightCameraCL::doInit()
{
//    qInfo()<<"ForwardRightCameraCL::doInit()";
}

void ForwardRightCameraCL::doUnInit()
{

}

bool ForwardRightCameraCL::exitAction()
{
    return true;
}

bool ForwardRightCameraCL::intoAction()
{

    return true;
}

void ForwardRightCameraCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();

    switch (cmd) {
//    case DC_UpdateCamera:{
//        System::getInstance()->forwardLeft_forwardRight_Big = data.toBool();
//        qDebug()<<"updatexzk ForwardRightCameraCL::UpdateCamera:"<<data.toBool();
//        emit pushDataToView(CL_UpdateCamera);
//        break;
//    }
    case CC_StartPlay:{
        System::getInstance()->forwardLeft_forwardRight_Big = data.toBool();
        emit pushDataToView(CL_StartPlay,data);
        break;
    }


    default:{break;}
    }

}

