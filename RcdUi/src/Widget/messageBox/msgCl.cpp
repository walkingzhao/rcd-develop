#include "msgCl.h"
#include "../include/qtzmq.h"
#include <QDebug>
msgCl::msgCl(QObject *parent): IController(parent)
{

}
msgCl::~msgCl()
{

}

void msgCl::doInit()
{
//    qInfo()<<"MainMonitorCL::doInit()";
}

void msgCl::doUnInit()
{

}

bool msgCl::exitAction()
{
    return true;
}

bool msgCl::intoAction()
{
    this->refreshDisplayData();
    return true;
}

void msgCl::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    MsgWgtCmdType Cmd = static_cast<MsgWgtCmdType>(cmd);

    switch (Cmd) {
    case M_msg_accept_task_work:{

        break;
    }
    case M_msg_complete_oper_start:{
        break;
    }
    case M_msg_task_work_change:{
        break;
    }
    case M_msg_network_interruption:{

        break;
    }
    case M_msg_complete_oper_end:{
        break;
    }
    case M_msg_not_satisfied_with_takeover:{
        break;
    }
    case M_msg_give_up_take_over: // 放弃接管
    {
        break;
    }
    case M_msg_hint: // 提示框
    {
        break;
    }
    default:{break;}
    }

}

void msgCl::vehicleStatusHandler(QVariant &data)
{


}

void msgCl::inputHandler(Qt::Key key)
{

}

void msgCl::refreshDisplayData()
{

}

void msgCl::setModel(msgModel *model)
{
    m_pModel = model;
}
