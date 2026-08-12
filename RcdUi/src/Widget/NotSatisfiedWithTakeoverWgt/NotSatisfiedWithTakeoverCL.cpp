#include "NotSatisfiedWithTakeoverCL.h"
#include <QDebug>

NotSatisfiedWithTakeoverCL::NotSatisfiedWithTakeoverCL(QObject *parent) : IController(parent)
{

}

NotSatisfiedWithTakeoverCL::~NotSatisfiedWithTakeoverCL()
{

}

void NotSatisfiedWithTakeoverCL::keyPress(QString keyStr)
{
    if(keyStr == "end")
    {
        //向平台反馈接管失败
        ModuleDir moduleDir;
        // --> BEGIN deleted by ZJZ, 2022/3/14
#if 1
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_Cloud_Takeover_failed,QVariant(System::getInstance()->getCurrentTaskId()));
#endif
        // <-- END

        //返回全局
        moduleDir.clear();
        moduleDir.append(MD_MainProcessor);
        emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);

        //设置状态
        System::getInstance()->setCurrentCabinMode(CM_Monitor);

    }else if(keyStr == "checkCabin") //检查车端
    {
        //通知驾驶舱前置条件检查
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_CompleteOperStart);
        emit sendToMain(moduleDir,COS_Show);
    }
}

void NotSatisfiedWithTakeoverCL::doInit()
{
//    qInfo()<<"NotSatisfiedWithTakeoverCL::doInit()";
}

void NotSatisfiedWithTakeoverCL::doUnInit()
{

}

bool NotSatisfiedWithTakeoverCL::exitAction()
{
    return true;
}

bool NotSatisfiedWithTakeoverCL::intoAction()
{

    return true;
}

void NotSatisfiedWithTakeoverCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
//    NotSatisfiedWithTakeoverWgtCmdType Cmd = static_cast<NotSatisfiedWithTakeoverWgtCmdType>(cmd);

    switch (cmd) {
    case NS_Update:{
        vehicleDataST st=data.value<vehicleDataST>();
        m_pModel->setVehicleState(st);

//        qDebug()<<"NotSatisfiedWithTakeoverCL NS_Update:"
//             <<st.speed<<(int)st.gear<<(int)st.mode<<(int)st.handBrake
//            <<"近光灯:"<<(int)st.lowBeam<<"双闪:"<<st.emergencyFlash
//           <<"排气制动"<<st.exhaustBrake;
        break;
    }
    case NS_Show:{
        if(isShow())
        {
            System::getInstance()->setCurrentCabinMode(CM_WaitTakeover);

            //车端条件不满足
            emit pushDataToView(NotSatisfiedWithTakeoverCL_Show);
#if 0
            //向平台反馈接管失败
            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_IPCManager);
            emit sendToMain(moduleDir,IM_Cloud_Takeover_failed,QVariant(System::getInstance()->getCurrentTaskId()));
            qDebug()<<"UI反馈平台车端条件不满足，接管失败";
#endif
        }else
        {
            //通知驾驶舱前置条件检查
            ModuleDir moduleDir;
            moduleDir.clear();
            moduleDir.append(MD_CompleteOperStart);
            emit sendToMain(moduleDir,COS_Show);
        }
        break;
    }
    case CC_Enter:{
        pushDataToView(NotSatisfiedWithTakeoverCL_Enter);
        break;
    }

    default:{break;}
    }
}


void NotSatisfiedWithTakeoverCL::setModel(NotSatisfiedWithTakeoverModel *model)
{
    m_pModel = model;
}

// 检查复选框不满足接管的条件，都满足则返回false，只要有一个不满足则返回true
bool NotSatisfiedWithTakeoverCL::isShow()
{return false;
    if(m_pModel->m_vehicleData.bodys.speed < 0.2) {//速度为0
    }else
    {
        qDebug()<<"1";
        return true;
    }
        

    if(m_pModel->m_vehicleData.bodys.gear == 0) {//N挡
    }
    else{
        
        qDebug()<<"2";
        return true;
    }

    /*if(m_pModel->m_vehicleData.bodys.mode == 0x01) {//自动模式
    }
    else{
        
        qDebug()<<"3";
        return true;
    }*/

//    if(m_pModel->m_vehicleData.handBrake == 0x01){//手刹使能
//    }
//    else
//        return true;
    return false;
}
