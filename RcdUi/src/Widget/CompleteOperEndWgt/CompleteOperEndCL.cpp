#include "CompleteOperEndCL.h"
#include <QDebug>

CompleteOperEndCL::CompleteOperEndCL(QObject *parent) : IController(parent)
{

}

CompleteOperEndCL::~CompleteOperEndCL()
{

}

void CompleteOperEndCL::doInit()
{
//    qInfo()<<"CompleteOperEndCL::doInit()";
}

void CompleteOperEndCL::doUnInit()
{

}

bool CompleteOperEndCL::exitAction()
{
    return true;
}

bool CompleteOperEndCL::intoAction()
{

    return true;
}

void CompleteOperEndCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    //    CompleteOperEndWgtCmdType Cmd = static_cast<CompleteOperEndWgtCmdType>(cmd);

    switch (cmd) {
    case COE_Show:{
        pushDataToView(CompleteOperEndCL_ShowCmd);
        break;
    }
    case CC_Enter:{
        pushDataToView(CompleteOperEndCL_Enter);
        break;
    }
    case COE_Update:{
        SelfCheckStatusST st=data.value<SelfCheckStatusST>();
        //        qDebug()<<"COE:"<<st.isParking<<st.isNoPedal<<st.isCenterSteeringWheel<<st.isButtonReset;
        m_pModel->updateSelfState(st);
        break;
    }

    default:{break;}
    }

}


void CompleteOperEndCL::setModel(CompleteOperEndModel *model)
{
    m_pModel = model;
}

void CompleteOperEndCL::keyPress()
{
    //向平台反馈结束接管
    ModuleDir moduleDir;
    moduleDir.clear();
    moduleDir.append(MD_IPCManager);
    emit sendToMain(moduleDir,IM_ReqRemoteEnd,QVariant::fromValue(System::getInstance()->getCurrentTaskId()));
    qDebug()<<"向平台反馈结束接管";
    //返回全局模式
    moduleDir.clear();
    moduleDir.append(MD_MainProcessor);
    emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);

    System::getInstance()->setCurrentCabinMode(CM_Monitor);

    m_pModel->_timerStatus =false;
}

bool CompleteOperEndCL::isShow()
{
    /*if(m_pModel->m_selfState.isParking)//P档
    {

    }else
        return true;
*/
    if(m_pModel->m_selfState.isNoPedal)//踏板无踩压
    {}
    else
        return true;

    if(m_pModel->m_selfState.isCenterSteeringWheel)//方向盘回正
    {}
    else
        return true;

    if(m_pModel->m_selfState.isButtonReset)//按钮复位
    {}
    else
        return true;

    return false;
}
