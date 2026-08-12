#include "WgtFactory.h"
#include <QDebug>

#include "Widget/MainCameraWgt/MainCameraWgt.h"
#include "Widget/RightCameraWgt/RightCameraWgt.h"
#include "Widget/LeftCameraWgt/LeftCameraWgt.h"
#include "Widget/CloudWebWgt/CloudWebWgt.h"
#include "Widget/MainMonitorWgt/MainMonitorWgt.h"
#include "Widget/DriveCameraWgt/DriveCameraWgt.h"
#include "Widget/WarnInfoWgt/WarnInfoWgt.h"
#include "Widget/UserGuideWgt/UserGuideWgt.h"
#include "Widget/LoadInstructionWgt/LoadInstructionWgt.h"
#include "Widget/InfoWgt/InfoWgt.h"
#include "Widget/TakeOverInfoWgt/TakeOverInfoWgt.h"
#include "Widget/VehicleDataWgt/VehicleDataWgt.h"
#include "Widget/GiveUpTakeOverWgt/GiveUpTakeOverWgt.h"
#include "Widget/AcceptTaskWorkWgt/AcceptTaskWorkWgt.h"
#include "Widget/CompleteOperEndWgt/CompleteOperEndWgt.h"
#include "Widget/CompleteOperStartWgt/CompleteOperStartWgt.h"
#include "Widget/NetworkInterruptionWgt/NetworkInterruptionWgt.h"
#include "Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverWgt.h"
#include "Widget/TaskWorkChangeWgt/TaskWorkChangeWgt.h"
#include "Widget/MainCameraTipWgt/MainCameraTipWgt.h"
#include "Widget/FastStopWgt/FastStopWgt.h"
#include "Widget/ForwardRightCameraWgt/ForwardRightCameraWgt.h"

// --> BEGIN added by ZJZ, 2022/3/1
#include "Widget/TipsPopupWgt/TipsPopupWgt.h"
// <-- END

#include "Widget/selfTestWgt/selfTestWgt.h"

QMap<int,IFunWidget*> WgtFactory::m_factoryWgt;
void WgtFactory::initWidget()
{
    //创建耗时的
    int procType = System::getInstance()->getProcessType();
    if(procType & PT_RightProc){
        //        CloudWebWgt::GetInstance();//new version2.0
        RightCameraWgt::GetInstance();//右摄像头界面
        //        VehicleInfoWgt::GetInstance();//车辆信息界面
        ForwardRightCameraWgt::GetInstance();//前右摄像头界面
    }
    if(procType & PT_MidProc){
        MainCameraWgt::GetInstance();//主界面相机界面
        MainMonitorWgt::GetInstance();//监视器界面
    }
    if(procType & PT_LeftProc){
        //                CloudWebWgt::GetInstance();//old version1.0
        LeftCameraWgt::GetInstance();
        DriveCameraWgt::GetInstance();
    }
    WgtFactory::m_factoryWgt.clear();
    WgtFactory::m_factoryWgt[MD_SystemInfo]=nullptr;
    WgtFactory::m_factoryWgt[MD_FaultInfo]=nullptr;
}

IFunWidget * WgtFactory::getFunWidget(ModuleType type)
{
    IFunWidget *pFunWidget = nullptr;
    switch (type) {
    case MD_FastStop: // 主摄像头提示信息
    {
        pFunWidget = FastStopWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_FastStop,pFunWidget);
    }
        break;
    case MD_MainCameraTip: // 主摄像头提示信息
    {
        pFunWidget = MainCameraTipWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_MainCameraTip,pFunWidget);
    }
        break;
    case MD_AcceptTaskWork: // 接受任务
    {
        pFunWidget = AcceptTaskWorkWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_AcceptTaskWork,pFunWidget);
    }
        break;
    case MD_CompleteOperEnd://结束接管提示
    {
        pFunWidget = CompleteOperEndWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_CompleteOperEnd,pFunWidget);
    }
        break;
    case MD_CompleteOperStart://开始接管提示
    {
        pFunWidget = CompleteOperStartWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_CompleteOperStart,pFunWidget);
    }
        break;
    case MD_GiveUpTakeOver://放弃接管提示
    {
        pFunWidget = GiveUpTakeOverWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_GiveUpTakeOver,pFunWidget);
    }
        break;
    case MD_NetworkInterruption://网络连接中断提示
    {
        //qInfo() << "MD_MainCamera";
        pFunWidget = NetworkInterruptionWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_NetworkInterruption,pFunWidget);
    }
        break;

    // --> BEGIN added by ZJZ, 2022/3/1
    case MD_TipsPopup://通用弹窗
    {
        //qInfo() << "MD_TipsPopup";
        pFunWidget = TipsPopupWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_TipsPopup,pFunWidget);
        break;
    }
    // <-- END
    case MD_SelfTest:
    {
        pFunWidget = selfTestWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_SelfTest,pFunWidget);
        break;
    }
    case MD_NotSatisfiedWithTakeover://接管条件不满足提示
    {
        pFunWidget = NotSatisfiedWithTakeoverWgt::GetInstance();
        System::getInstance()->setMsgWidgetMap(MD_NotSatisfiedWithTakeover,pFunWidget);
    }
        break;
    case MD_TaskWorkChange://接管目标变更提示
    {
        //qInfo() << "MD_TaskWorkChange";
        pFunWidget = TaskWorkChangeWgt::GetInstance();
//        System::getInstance()->setMsgWidgetMap(MD_TaskWorkChange,pFunWidget);
    }
        break;
    case MD_MainCamera:
    {
        //qInfo() << "MD_MainCamera";
        pFunWidget = MainCameraWgt::GetInstance();
    }
        break;
    case MD_MainMonitor:
    {
        //qInfo() << "MD_MainMonitor";
        pFunWidget = MainMonitorWgt::GetInstance();
    }
        break;
    case MD_RightCamera:
    {
        //qInfo() << "MD_RightCamera";
        pFunWidget = RightCameraWgt::GetInstance();
    }
        break;
    case MD_ForwardRightCamera:
    {
        //qInfo() << "MD_ForwardRightCamera";
        pFunWidget = ForwardRightCameraWgt::GetInstance();
    }
        break;
    case MD_LeftCamera:
    {
        //qInfo() << "MD_LeftCamera";
        pFunWidget = LeftCameraWgt::GetInstance();
    }
        break;
    case MD_DriveCamera:
    {
        //qInfo() << "MD_DriveCamera";
        pFunWidget = DriveCameraWgt::GetInstance();
    }
        break;
    case MD_CloudWeb:
    {
        //qInfo() << "MD_CloudWeb";
        pFunWidget = CloudWebWgt::GetInstance();
    }
        break;
    case MD_UserGuide:
    {
        //qInfo() << "MD_MD_UserGuide";
        pFunWidget = UserGuideWgt::GetInstance();
    }
        break;
    case MD_FaultInfo:
    {
        if( WgtFactory::m_factoryWgt[MD_FaultInfo]==nullptr)
        {
            WgtFactory::m_factoryWgt[MD_FaultInfo] = new InfoWgt();
            ((InfoWgt*)WgtFactory::m_factoryWgt[MD_FaultInfo])->setType(0);
        }
        pFunWidget = WgtFactory::m_factoryWgt[MD_FaultInfo];
    }
        break;
    case MD_SystemInfo:
    {
        if( WgtFactory::m_factoryWgt[MD_SystemInfo]==nullptr)
        {
            WgtFactory::m_factoryWgt[MD_SystemInfo] = new InfoWgt();
            ((InfoWgt*)WgtFactory::m_factoryWgt[MD_SystemInfo])->setType(1);
        }
        pFunWidget = WgtFactory::m_factoryWgt[MD_SystemInfo];
    }
        break;
    case MD_TakeOverInfo:
    {
        //qInfo() << "MD_MD_UserGuide";
        pFunWidget = TakeOverInfoWgt::GetInstance();
    }
        break;
    case MD_LoadInstruction:
    {
        //qInfo() << "MD_MD_UserGuide";
        pFunWidget = LoadInstructionWgt::GetInstance();
    }
        break;
    case MD_VehicleInfo:
    {
        //qInfo() << "MD_VehicleInfo";
//        pFunWidget = VehicleInfoWgt::GetInstance();
    }
        break;
    case MD_AllInfo:
    {
        //qInfo() << "MD_AllInfo";
//        pFunWidget = AllInfoWgt::GetInstance();
    }
        break;
    case MD_WarnInfo:
    {
        //qInfo() << "MD_WarnInfo";
        pFunWidget = WarnInfoWgt::GetInstance();
    }
        break;
    case MD_VehicleData:
    {
        pFunWidget = VehicleDataWgt::GetInstance();
    }
        break;
    default:
    {
        qWarning() << "can't find this ModuleType:"<<type;
        pFunWidget = nullptr;
        break;
    }
    }

    return pFunWidget;
}

