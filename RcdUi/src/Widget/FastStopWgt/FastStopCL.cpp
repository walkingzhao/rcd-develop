#include "FastStopCL.h"
#include "public/fbsstructure.h"

FastStopCL::FastStopCL(QObject *parent) : IController(parent)
{

}

void FastStopCL::setModel(FastStopModel *model)
{
    m_pModel = model;
}

void FastStopCL::getFromAny(ModuleDir moduleDir, int cmd, QVariant data)
{
    moduleDir.clear();

    switch (cmd) {
    case FastStopWgtCmdType::FastStop_Show:{
        emit pushDataToView(CL_Show,data);
        break;

    }
    case CC_Enter:{
        pushDataToView(CL_Enter,data);
        break;
    }

    default:{break;}
    }

}

void FastStopCL::keyPress(QString keyStr)
{
    if(keyStr == "ok")
    {
        //send fast stop信息
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_FastStop,QVariant());
        qDebug()<<"UI向平台发送fast stop";
    }
}
