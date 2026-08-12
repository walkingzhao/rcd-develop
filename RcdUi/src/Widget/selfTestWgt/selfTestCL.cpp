#include "selfTestCL.h"
#include <QDebug>
#include "System.h"

selfTestCL::selfTestCL(QObject *parent) : IController(parent)
{
}

selfTestCL::~selfTestCL()
{
}

bool selfTestCL::isShow()
{
    return false;
}

void selfTestCL::keyPress()
{
}

void selfTestCL::doInit()
{
}

void selfTestCL::doUnInit()
{
}

bool selfTestCL::exitAction()
{
    return true;
}

bool selfTestCL::intoAction()
{

    return true;
}

void selfTestCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    switch (cmd) {
    case selfTest_Show:
//        {
//            popContent st = data.value<popContent>();
//            m_pModel->updateContent(st);
//        }
        pushDataToView(selfTestCL_ShowCmd);
        break;
    case selfTest_Update:{
        SelfTest_ControlData_St st = data.value<SelfTest_ControlData_St>();
        m_pModel->updateContent(st);
        break;
    }
    case selfTest_Wheel_Update:{
        SelfTest_CtrlRawData_St st = data.value<SelfTest_CtrlRawData_St>();
        m_pModel->updateWheelValue(st);
        break;
    }
    case selfTest_empty_update:{
        m_pModel->updateEmptyStatus();
        break;
    }
    case selfTest_takeover_update:{
        m_pModel->updateTakeoverStatus();
        break;
    }
    case selfTest_blind_update:{
        m_pModel->updateBlindStatus();
        break;
    }
    case selfTest_Hide:
        pushDataToView(selfTestCL_HideCmd);
        break;
    case CC_Enter:
        pushDataToView(selfTestCL_Enter);
        break;
//    case TP_Update:
//        SelfCheckStatusST st=data.value<SelfCheckStatusST>();
//        m_pModel->updateSelfState(st);
//        break;
    default:
        break;
    }
}


void selfTestCL::setModel(selfTestModel *model)
{
    m_pModel = model;
}
