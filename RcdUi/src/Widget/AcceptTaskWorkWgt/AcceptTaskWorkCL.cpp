#include "AcceptTaskWorkCL.h"
#include <QDebug>
#include "public/fbsstructure.h"

AcceptTaskWorkCL::AcceptTaskWorkCL(QObject *parent) : IController(parent)
{

}

AcceptTaskWorkCL::~AcceptTaskWorkCL()
{

}

void AcceptTaskWorkCL::keyPress(QString keyStr)
{
    if(keyStr == "ok")
    {
        //向平台反馈接受信息
        QVariantList data;
        data.clear();
        data<<m_pModel->m_taskId<<1<<QString("接受任务成功");//success

        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_Cloud_Reply_Task,QVariant::fromValue(data));
        qDebug()<<"UI向平台发送接受任务";
        System::getInstance()->setCurrentTaskId(m_pModel->m_taskId);
//        System::getInstance()->setCurrentCabinMode(CM_WaitTakeover);

        // --> BEGIN deleted by ZJZ, 2022/3/9
#if 0
        //更新驾驶状态为监控中
        moduleDir.clear();
        moduleDir.append(MD_MainCamera);
        emit sendToMain(moduleDir,MC_UpdateState,"监控中");
#endif
        if (1 == System::getInstance()->getVehicleStatus()) {
            //更新驾驶状态为监控中
            moduleDir.clear();
            moduleDir.append(MD_MainCamera);
            emit sendToMain(moduleDir,MC_UpdateState,"监控中");
        }
        // <-- END

//        //切换地图地址
//        ModuleDir module;
//        module.append(MD_CloudWeb);
//        QString str = "1";//单车
//        emit sendToMain(module,CW_SwitchMapUrl,QVariant::fromValue(str)); //统一命令

    }else if(keyStr == "reject")
    {
        //向平台反馈拒绝信息
        QVariantList data;
        data.clear();
        data<<m_pModel->m_taskId<<0<<QString("舱端驾驶员拒绝接管");//cabin driver reject to take over

        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_Cloud_Reply_Task,QVariant::fromValue(data));
        qDebug()<<"UI向平台发送拒绝任务";


        moduleDir.clear();
        moduleDir.append(MD_MainProcessor);
        emit sendToMain(moduleDir,MP_SwitchLayout,LT_Monitor);
        System::getInstance()->setCurrentCabinMode(CM_Monitor);
    }
}


void AcceptTaskWorkCL::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    cabinTakeoverTaskApplyST st = data.value<cabinTakeoverTaskApplyST>();

    switch (cmd) {
    case AT_NewTask:{
        int destType = st.takeoverPurpose;
        QString dest;
        switch (destType) {
        case 0:
            dest = "靠边停车";
            break;
        case 1:
            dest = "精确停靠";
            break;
        case 2:
            dest = "避障绕行";
            break;
        case 3:
            dest = "行驶至调度目标";
            break;
        case 4:
            dest = "主动接管";//AutonomousDriving 无人驾驶
            break;
        case 5:
            dest = "尝试行驶";
            break;
        case 6:
            dest = "监控行驶";
            break;
        default:
            dest = "未知";
            break;
        }

        //更新调度目标
        ModuleDir moduleDir;
        moduleDir.clear();
        moduleDir.append(MD_TakeOverInfo);
        emit sendToMain(moduleDir,TakeOver_UpdateDispatchTask,dest);


        dest = "接管目标：" + dest;
        m_pModel->setDest(dest, st.taskId);

        //请求配置文件
        moduleDir.clear();
        moduleDir.append(MD_IPCManager);
        emit sendToMain(moduleDir,IM_ReqCameraCfg,
                        QVariant::fromValue(System::getInstance()->getCurrentVehicle()));
        qDebug()<<"UI向车端请求摄像头配置参数";

        ////清空camera配置文件有效性
        TrackLineCalibrationST st;
        st.valid = false;
        moduleDir.clear();
        moduleDir.append(MD_MainCamera);
        emit sendToMain(moduleDir,MC_CameraCalibration,
                        QVariant::fromValue(st));

        keyPress("ok");

        break;
    }
    case CC_Enter:
    {
        pushDataToView(AcceptTaskWorkCLCmd_Enter);
        break;
    }

    default:{break;}
    }

}


void AcceptTaskWorkCL::setModel(AcceptTaskWorkModel *model)
{
    m_pModel = model;
}
