#include "CompleteOperStartCL.h"
#include <QDebug>
#include "public/fbsstructure.h"

CompleteOperStartCL::CompleteOperStartCL(QObject *parent) : IController(parent)
{

}

CompleteOperStartCL::~CompleteOperStartCL()
{

}

void CompleteOperStartCL::doInit()
{
//    qInfo()<<"CompleteOperStartCL::doInit()";
}

void CompleteOperStartCL::doUnInit()
{

}

bool CompleteOperStartCL::exitAction()
{
    return true;
}

bool CompleteOperStartCL::intoAction()
{

    return true;
}

void CompleteOperStartCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    //    CompleteOperStartWgtCmdType Cmd = static_cast<CompleteOperStartWgtCmdType>(cmd);

    switch (cmd) {
    case COS_Update:{
        SelfCheckStatusST st = data.value<SelfCheckStatusST>();
        //        qDebug()<<"COS:"<<st.isParking<<st.isNoPedal<<st.isCenterSteeringWheel<<st.isButtonReset;
        m_pModel->updateState(st);
        break;
    }
    case CC_Enter:{
        emit pushDataToView(CompleteOperStartCL_Enter);
        break;
    }
    case COS_Show:{
        //        if(isShow())//不满足条件
        {
            emit pushDataToView(CompleteOperStartCL_Show);
             m_pModel->_timerStatus = true;//启动定时器
        }
        break;
    }

    default:{break;}
    }

}

void CompleteOperStartCL::keyPress()
{
    //点击开始接管
    ModuleDir moduleDir;
    moduleDir.clear();
    moduleDir.append(MD_IPCManager);
    emit sendToMain(moduleDir,IM_ReqRemoteStart);
    m_pModel->_timerStatus = false;//停止定时器
    qDebug()<<"向平台反馈开始接管";
}


void CompleteOperStartCL::setModel(CompleteOperStartModel *model)
{
    m_pModel = model;
}

bool CompleteOperStartCL::isShow()
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

    return false;
}

