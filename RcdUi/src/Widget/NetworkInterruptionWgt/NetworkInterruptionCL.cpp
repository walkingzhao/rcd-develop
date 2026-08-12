#include "NetworkInterruptionCL.h"
#include <QDebug>
#include "System.h"
NetworkInterruptionCL::NetworkInterruptionCL(QObject *parent) : IController(parent)
{

}

NetworkInterruptionCL::~NetworkInterruptionCL()
{

}


bool NetworkInterruptionCL::isShow()
{
    if(m_pModel->m_selfState.isParking)//P档
    {

    }else
        return true;

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

void NetworkInterruptionCL::keyPress()
{
    //向平台反馈车舱连接断开
    ModuleDir moduleDir;
    moduleDir.clear();
    moduleDir.append(MD_IPCManager);
    emit sendToMain(moduleDir,IM_Cloud_Takeover_end,QVariant::fromValue(1));//TaskEndReason_NetworkInterrupt
    qDebug()<<"UI反馈平台车舱连接断开";

    //返回全局模式
    moduleDir.clear();
    moduleDir.append(MD_MainProcessor);
    emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);
    m_pModel->_timerStatus = false;

    //切换驾驶模式到全局模式
    System::getInstance()->setCurrentCabinMode(CM_Monitor);
}

void NetworkInterruptionCL::doInit()
{
    //    qInfo()<<"NetworkInterruptionCL::doInit()";
}

void NetworkInterruptionCL::doUnInit()
{

}

bool NetworkInterruptionCL::exitAction()
{
    return true;
}

bool NetworkInterruptionCL::intoAction()
{

    return true;
}

void NetworkInterruptionCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    //    NetworkInterruptionWgtCmdType Cmd = static_cast<NetworkInterruptionWgtCmdType>(cmd);

    switch (cmd) {
    case NI_Show:{
//        VehicleStatus selfStatus = data.value<VehicleStatus>();

//        m_pModel->updateSelfState(selfStatus);
        pushDataToView(NetworkInterruptionCL_ShowCmd);
        m_pModel->_timerStatus = true;

        break;
    }
    case NI_Hide:{
        pushDataToView(NetworkInterruptionCL_HideCmd);
        break;
    }
    case CC_Enter:{
        pushDataToView(NetworkInterruptionCL_Enter);
        break;
    }
    case NI_Update:{
        {
            qDebug() << "network " << "NI_UPDATE";
            SelfCheckStatusST st=data.value<SelfCheckStatusST>();
            m_pModel->updateSelfState(st);
        }
        break;
    }
    default:{break;}
    }
}

void NetworkInterruptionCL::setModel(NetworkInterruptionModel *model)
{
    m_pModel = model;
}
