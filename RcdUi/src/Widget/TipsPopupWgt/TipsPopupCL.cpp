#include "TipsPopupCL.h"
#include <QDebug>
#include "System.h"
TipsPopupCL::TipsPopupCL(QObject *parent) : IController(parent)
{
}

TipsPopupCL::~TipsPopupCL()
{
}

bool TipsPopupCL::isShow()
{
//    if(m_pModel->m_selfState.isParking)//P档
//    {

//    }else
//        return true;

//    if(m_pModel->m_selfState.isNoPedal)//踏板无踩压
//    {}
//    else
//        return true;

//    if(m_pModel->m_selfState.isCenterSteeringWheel)//方向盘回正
//    {}
//    else
//        return true;
//    if(m_pModel->m_selfState.isButtonReset)//按钮复位
//    {}
//    else
//        return true;
    return false;
}

void TipsPopupCL::keyPress()
{
    ModuleDir moduleDir;
    if (TipsPopupLBtnCmd_None == m_pModel->m_content.cmd) {// 不需要別的操作
        return;
    }

    //切换驾驶模式到全局模式
    System::getInstance()->setCurrentCabinMode(CM_Monitor);

    //返回全局模式
    moduleDir.clear();
    moduleDir.append(MD_MainProcessor);
    emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);
    m_pModel->_timerStatus = false;

    if (TipsPopupLBtnCmd_DevLink == m_pModel->m_content.cmd) {
        uint8_t reason = 0;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_Cloud_Takeover_end,QVariant::fromValue(reason));//System::getInstance()->getCurrentTaskId()
        qDebug()<<"UI反馈平台：“座舱控制单元掉线！即将结束任务，请复位座舱。”";
    } else if (TipsPopupLBtnCmd_Timeout == m_pModel->m_content.cmd) {
        uint8_t reason = 0;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_Cloud_Takeover_end,QVariant::fromValue(reason));
        qDebug()<<"UI反馈平台：“等待连接超时，请检查网络状态后重新进入”";
    } else if (TipsPopupLBtnCmd_GiveupMonitor == m_pModel->m_content.cmd) {
        uint8_t reason = 0;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_Cloud_Takeover_end,QVariant::fromValue(reason));
        qDebug()<<"UI反馈平台：“确认结束监控？”";
    }
}

void TipsPopupCL::doInit()
{
    //    qInfo()<<"NetworkInterruptionCL::doInit()";
}

void TipsPopupCL::doUnInit()
{

}

bool TipsPopupCL::exitAction()
{
    return true;
}

bool TipsPopupCL::intoAction()
{

    return true;
}

void TipsPopupCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    switch (cmd) {
    case TP_Show:
        {
            popContent st = data.value<popContent>();
            m_pModel->updateContent(st);
        }
        pushDataToView(TipsPopupCL_ShowCmd);
        break;
    case TP_Hide:
        pushDataToView(TipsPopupCL_HideCmd);
        break;
    case CC_Enter:
        pushDataToView(TipsPopupCL_Enter);
        break;
//    case TP_Update:
//        SelfCheckStatusST st=data.value<SelfCheckStatusST>();
//        m_pModel->updateSelfState(st);
//        break;
    default:
        break;
    }
}


void TipsPopupCL::setModel(TipsPopupModel *model)
{
    m_pModel = model;
}
