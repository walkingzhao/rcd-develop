#include "TaskWorkChangeCL.h"
#include <QDebug>

TaskWorkChangeCL::TaskWorkChangeCL(QObject *parent) : IController(parent)
{

}

TaskWorkChangeCL::~TaskWorkChangeCL()
{

}

void TaskWorkChangeCL::doInit()
{
//    qInfo()<<"TaskWorkChangeCL::doInit()";
}

void TaskWorkChangeCL::doUnInit()
{

}

bool TaskWorkChangeCL::exitAction()
{
    return true;
}

bool TaskWorkChangeCL::intoAction()
{

    return true;
}

void TaskWorkChangeCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    TaskWorkChangeWgtCmdType Cmd = static_cast<TaskWorkChangeWgtCmdType>(cmd);

    switch (Cmd) {
    case TW_Show:{
        if(System::getInstance()->getCurrentMsg()!=MD_None)
            break;

        pushDataToView(TaskWorkChangeCL_ShowCmd,data);
        break;
    }

    default:{break;}
    }

}


void TaskWorkChangeCL::setModel(TaskWorkChangeModel *model)
{
    m_pModel = model;
}
