#include "GiveUpTakeOverCL.h"
#include <QDebug>


GiveUpTakeOverCL::GiveUpTakeOverCL(QObject *parent) : IController(parent)
{

}

GiveUpTakeOverCL::~GiveUpTakeOverCL()
{

}

void GiveUpTakeOverCL::keyPress(QString keyStr)
{
    if(keyStr == "ok")
    {
        //向平台反馈放弃任务

        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        if(System::getInstance()->currentTakeoverPurpose==6)//监控行驶
            emit sendToMain(moduleDir,IM_Cloud_Takeover_end,QVariant::fromValue(0));//TaskEndReason_Normal
        else
            emit sendToMain(moduleDir,IM_Cloud_GiveUp_Task,QVariant::fromValue(System::getInstance()->getCurrentTaskId()));
        System::getInstance()->setCurrentCabinMode(CM_Monitor);
        qDebug()<<"向平台反馈放弃任务";



        moduleDir.clear();
        moduleDir.append(MD_MainProcessor);
        emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);

        System::getInstance()->setCurrentCabinMode(CM_Monitor);

//        //切换地图地址×××××××××××××××××××
//        ModuleDir module;
//        module.append(MD_CloudWeb);
//        emit sendToMain(module,CW_SwitchMapUrl,QVariant(QString("0"))); //统一命令

    }
    else {

    }
}

void GiveUpTakeOverCL::doInit()
{
//    qInfo()<<"GiveUpTakeOverCL::doInit()";
}

void GiveUpTakeOverCL::doUnInit()
{

}

bool GiveUpTakeOverCL::exitAction()
{
    return true;
}

bool GiveUpTakeOverCL::intoAction()
{

    return true;
}

void GiveUpTakeOverCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
//    GiveUpTakeOverWgtCmdType Cmd = static_cast<GiveUpTakeOverWgtCmdType>(cmd);

    switch (cmd) {
    case GU_Show:{
        emit pushDataToView(GiveUpTakeOverCLCmd_Show);
        break;
    }
    case CC_Enter:{
        emit pushDataToView(GiveUpTakeOverCLCmd_Enter);
        break;
    }

    default:{break;}
    }

}


void GiveUpTakeOverCL::setModel(GiveUpTakeOverModel *model)
{
    m_pModel = model;
}
