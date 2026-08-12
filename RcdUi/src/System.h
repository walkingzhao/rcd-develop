#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QMetaType>
#include <QDateTime>
#include <QMap>
#include <QWidget>
#include <QtDebug>
#include <set>

//#define RCD_VERSION "V06.80.09.02.01.08"


#ifndef INT_INVALID
#define INT_INVALID (-1) //无效值
#endif

#ifndef STR_INVALID
#define STR_INVALID ("") //无效值
#endif

typedef QList<uint> ModuleDir;
Q_DECLARE_METATYPE(ModuleDir);



enum ModuleType
{
    MD_None=-1,//隐藏窗口
    MD_MainProcessor=0,       //主处理模块
    MD_IPCManager,            //进程通信管理模块
    MD_InteractiveManager,    //输入交互管理模块

    MD_LeftCamera,            //左摄像头界面
    MD_DriveCamera,           //驾驶室摄像头界面
    MD_FaultInfo,             //故障信息界面
    MD_VehicleData,           //车辆数据
    MD_UserGuide,              //用户指南

    MD_MainCamera,            //主摄像头界面
    MD_AcceptTaskWork,        //接受新任务提示页面
    MD_CompleteOperEnd,       //结束接管提示
    MD_CompleteOperStart,     //开始接管提示
    MD_GiveUpTakeOver,        //放弃接管提示
    MD_NetworkInterruption,   //网络连接中断提示
    MD_NotSatisfiedWithTakeover,//接管条件不满足提示

    // --> BEGIN added by ZJZ, 2022/3/1
    MD_TipsPopup,   //common tips window
    // <-- END

    MD_SelfTest,

    MD_FastStop,           //fast stop
    MD_MainCameraTip,           //主摄像头提示信息
    MD_TaskWorkChange,        //接管目标变更提示
    MD_Msg_exit,              //是否退出程序
    MD_Msg_Init,              //是否进入遥控驾驶舱
    MD_MainMonitor,           //主监控界面

    MD_RightCamera,           //右摄像头界面
    MD_ForwardRightCamera,    //前右摄像头界面
    MD_VehicleInfo,           //车辆信息界面
    MD_CloudWeb,              //web界面
    MD_CloudWebSmall,         //web小界面
    MD_TakeOverInfo,               //接管信息界面
    MD_LoadInstruction,              //装载指令界面
    MD_RightFrontWgt,           //右屏幕的右前摄像头
    MD_SystemInfo,               //系统信息界面
    MD_AllInfo,               //所有信息界面
    MD_WarnInfo,              //警告信息界面
    //    MD_MapWeb,                //地图界面
    //MD_FunDialog,
    MD_MsgBox,               //弹出框
    MD_Max
};

// 屏幕功能区域类型
enum ScreenAreaType
{
    SA_MainScreen,          // 主屏幕区域
    SA_RightScreen,          //右屏幕区域
    SA_LeftScreen,           //左屏幕区域
    SA_RightScreenL,        // 右屏幕左区域
    SA_RightScreenR,        // 右屏幕右区域
    SA_RightScreenLTop,        // 右屏幕左区域 上
    SA_RightScreenLBottom,        // 右屏幕左区域 下
    SA_RightScreenRTop,        // 右屏幕右区域 上
    SA_RightScreenRMid,        // 右屏幕右区域 中
    SA_RightScreenRTopMid,         //右屏幕右区域 上中
    SA_RightScreenRBottom,        // 右屏幕右区域 下
    SA_LeftScreenTopL,      // 左屏幕上左区域
    SA_LeftScreenTopR,      // 左屏幕上右区域
    SA_LeftScreenBottom,    // 左屏幕下区域
    SA_LeftScreenBottomL,    // 左屏幕下区域左
    SA_LeftScreenBottomR,    // 左屏幕下区域右
    SA_MainScreenMsg,    // 主屏幕提示窗

};


// 布局类型
enum LayoutType
{
    LT_Monitor=0,           //监控时布局
    LT_RemoteControl,       //遥控时布局

    LT_Max
};

// 主处理模块支持的处理命令
enum MainProcessorCmdType
{
    MP_SwitchWgt=0,     //切换窗
    MP_SwitchLayout,    //切换布局
    MP_SoftKeyPress,    //软键盘按下
    MP_IpcForward,      //消息ipc进程转发
    MP_UpdateSysData,   //系统数据更新
    MP_Max
};

// 各模块通用命令
enum CommonCmdType
{
    CC_KeyPress = 0xA1,  //按键按下
    CC_StartPlay,
    CC_StopPlay,
    CC_Enter
};

// 主相机窗口命令类型
enum MainCameraWgtCmdType
{
    MC_PlayUrl,             //更新播放url
    MC_VehicleData,         //当前控制车辆设备信息
    MC_ThrottleBrakeWheel,  //当前控制车辆设备信息
    MC_Speed,               //当前控制车辆速度
    MC_Gear,                //当前控制车辆档位
    MC_VehicleDelay,        //当前控制车辆延迟
    MC_RemoteResule,        //6遥控返回结果
    MC_UpdateState,        //更新单车模式状态
    MC_UpdateCloudyState,   // 更新座舱与平台连接状态
    MC_UpdatePosition,        //更新单车位置信息
    MC_Throttle,            //加速百分比
    MC_Brake,               //刹车
    MC_Wheel,               //方向盘转角
    MC_Other,               //扩展数据
    MC_Speed_Gear,          //车速与档位
    MC_Throttle_RingDila,   //加速踏板百分比+发动机转速
    MC_MainCamera_Vehicle_data,// 主摄像头界面数据
    MC_Req_Task,                //主动请求任务连接
    MC_CameraCalibration,       //摄像头标定
    MC_UpdateLoginStatus,       //更新登陆状态
    MC_InputKey = CC_KeyPress  //输入按键
    //    MC_TEST
};

// 监控主界面命令
enum MainMonitorWgtCmdType
{
    MM_UpdateAll=0,         //更新界面
    MM_VehicleData,         //当前接入车辆设备信息
    MM_ThrottleBrakeWheel,  //当前接入车辆设备信息
    MM_Speed,               //当前接入车辆设备速度
    MM_Gear,                //当前接入车辆设备档位
    MM_VehicleStatus,       //当前接入车辆设备状态
    MM_UpdateLoginStatus,   //更新登陆状态
    MM_UpdateUI,       //更新ui
    MM_CloseTip,       //关闭提示
    MM_ShowEmergency,       //show emergency tip
    MM_UpdateOnlineState,       //更新车辆在线状态
    MM_InputKey = CC_KeyPress   //输入按键
};
// 接管信息页
enum TakeOverInfoWgtCmdType
{
    TakeOver_UpdateTask=0,         //更新接管信息
    TakeOver_UpdateDispatchTask,   //更新接管任务
    TakeOver_UpdateLoadStatus,   //更新装载状态

    TakeOver_MAX
};
// 装载指令页
enum LoadInstructionWgtCmdType
{
    LoadInstruction_Update=0,         //更新任务状态/装载状态

    LoadInstruction_MAX
};
// fast stop
enum FastStopWgtCmdType
{
    FastStop_Show=0,

    FastStop_MAX
};
// 主摄像头提示信息闪烁
enum MainCameraTipWgtCmdType
{
    MainCameraTip_Update=0,         //更新文本并显示
    MainCameraTip_Hide,

    MainCameraTip_MAX
};
enum MsgWgtCmdType  //弹出框
{
    M_msg_accept_task_work = 0, //接受任务
    M_msg_complete_oper_start,//完成坐舱以下操作开始接管
    M_msg_task_work_change,//接管目标已变更
    M_msg_network_interruption,//网络中断
    M_msg_complete_oper_end,//完成以下操作结束接管
    M_msg_not_satisfied_with_takeover,//不满足接管
    M_msg_give_up_take_over, // 放弃接管
    M_msg_hint // 提示框
};

enum RightCameraWgtCmdType
{
    RC_UpdateTitle=0,       //更新标题
    RC_UpdateForwardRihgtCamera,//更新右窗口显示模式

    RC_InputKey = CC_KeyPress
};

enum LeftCameraWgtCmdType   //更新标题
{
    LC_UpdateTitle=0,


    LC_Max
};

enum DriveCameraWgtCmdType
{
    DC_UpdateUrl=0,
    DC_UpdateCamera,


    DC_Max
};

enum CloudWebWgtCmdType
{
    CW_LoadNewUrl=0,
    CW_SwitchMapUrl,

    CW_Max
};
enum InfoWgtCmdType
{
    IF_InsertMsg=0,


    IF_Max
};


enum VehicleInfoWgtCmdType
{
    VI_LoadNewUrl=0,
    VI_G2HmiInfo,

    VI_Max,
    VI_Oil,
    VI_Map //地图
};

enum VehicleDataWgtCmdType
{
    VD_UpdateVehicleData=0,
    VD_Max
};
enum AllInfoWgtCmdType
{
    AI_LoadNewUrl=0,


    AI_Max
};

enum WarnInfoWgtCmdType
{
    WI_LoadNewUrl=0,


    WI_Max
};
enum AcceptTaskWorkWgtCmdType
{
    AT_NewTask=0,


    AT_Max
};
enum CompleteOperEndWgtCmdType
{
    COE_Show=0,
    COE_Update,


    COE_Max
};
enum CompleteOperStartWgtCmdType
{
    COS_Show=0,
    COS_Update,


    COS_Max
};
enum GiveUpTakeOverWgtCmdType
{
    GU_Show=0,


    GU_Max
};
enum NetworkInterruptionWgtCmdType
{
    NI_Show=0,
    NI_Update,
    NI_Hide,

    NI_Max
};

// --> BEGIN added by ZJZ, 2022/3/1
enum TipsPopupWgtCmdType
{
    TP_Show = 0,
    TP_Update,
    TP_Hide,
    TP_Max
};
// <-- END

enum selfTestWgtCmdType
{
    selfTest_Show = 0,
    selfTest_Update,
    selfTest_Wheel_Update,
    selfTest_Hide,
    selfTest_Max,
    selfTest_empty_update,
    selfTest_takeover_update,
    selfTest_blind_update
};

enum NotSatisfiedWithTakeoverWgtCmdType
{
    NS_Update=0,
    NS_Show,


    NS_Max
};
enum TaskWorkChangeWgtCmdType
{
    TW_Show=0,
    TW_Max
};

// 进程通讯管理模块命令
enum IPCManagerCmdType
{
    IM_ReqRemoteStart=0,    //开始申请遥控
    IM_ReqRemoteEnd,        //结束遥控
    IM_ReqSendHmiMsg,       //发送HMI的消息命令包
    //    IM_Cloud, //发送给平台数据/
    IM_Cloud_Takeover_failed , //发送给平台接管失败数据
    IM_Cloud_Reply_Task , //是否接受任务回复
    IM_Cloud_GiveUp_Task,//放弃任务
    IM_Cloud_Request,// 主动请求
    IM_Cloud_Takeover_start,// 开始接管
    IM_Cloud_Takeover_end,// 结束接管
    IM_ReqCameraCfg,// 请求摄像头配置文件
    IM_FastStop,// 请求FastStop
    IM_ReqConnect,
    IM_Max
};

//交互管理支持的命令
enum InteractiveManagerCmdType
{
    IA_KeyPress=0,
    IA_SwitchLayout,
    IA_FocusToNextPage,      //更新焦点到右边焦点
    IA_FocusToPreviousPage,  //更新焦点到左边焦点
    IA_FocusToUpPage,        //更新焦点到上边焦点
    IA_FocusToDownPage,      //更新焦点到下边焦点

    IA_Max
};

enum ProcessType
{
    PT_All = 0x007,         // 非多进程运行
    PT_RightProc = 0x001,   // 右侧界面
    PT_MidProc = 0x002,     // 中间界面
    PT_LeftProc = 0x004,    // 左侧界面

    PT_Max
};

enum CabinModeType {
    CM_Monitor,         //0,全局模式
    CM_WaitTask,        //1,单车模式：等待连接（等待任务，已向平台申请任务，还没accept任务）
    CM_WaitTakeover,    //2,单车模式：监控中（已接受任务，已接受平台任务，还没按接管按键pageup）
    CM_Takeover,        //3,单车模式：远程接管中（接管中，已接受平台任务，已按下pageup，再按pageup，退出接管）
    CM_Max
};


#define IMEI_LENGTH 15

class QSharedMemory;

// 系统功能类
class System
{

public:
    ~System();

    typedef struct
    {
        uint8_t                  sysStatus;
        char                     vehicleImei[IMEI_LENGTH + 1];
        char                     none[4096 - (IMEI_LENGTH + 2)];
    } SharedDatas;

    static System           *getInstance();
    void             delayMsecTime(int msecTime,int delayModel = 0);
    ProcessType      belongTo(ModuleType mdType);
    bool             messageFilter(ModuleType module);
    bool             messageFilter(ModuleType module,QString &imei);
    void             setCurrentVehicle(QString &imei);
    std::atomic<LayoutType> showLayoutMode;
    QString          getCurrentVehicle();
    unsigned short   getCurrentTaskId();
    void             setCurrentTaskId(unsigned short &taskId);
    void             setShowEmergency(bool state);
    bool             getShowEmergency();//show or not show emergency window
    CabinModeType    getCurrentCabinMode();
    void             setCurrentCabinMode(CabinModeType mode);
    void             setProcessType(ProcessType);
    int              getProcessType();

    void             setVehicleStatus(int type);
    int              getVehicleStatus();

    // --> BEGIN added by ZJZ, 2022/3/22
    void             setVehicleTakeoverPurpose(int purpose);
    int              getVehicleTakeoverPurpose();
    // <-- END


    SharedDatas*     getSharedDatas();
    ModuleType       getCurrentMsg();
    void             setCurrentDriverLogin(const QString &data);//司机登录
    QString          getCurrentDriverLoginStatus();//司机登录返回结果
    void             setCurrentImeiList(const QList<QString> &listIMei){
        _vehicleImeiList = listIMei;
    }
    QList<QString>   getCurrentImeiList(){ return _vehicleImeiList;}
    void             setCurrentMsg(ModuleType wgt);
    void             setCurrentLayoutType(const LayoutType &type){
        _layout = type;
    }
    LayoutType       getCurrentLayoutType(){
        return  _layout;
    }
//    void clearMsgWidgetMap(){
//        if(_mapMsgMap.keys().contains(MD_Msg_exit)){
//            _mapMsgMap.remove(MD_Msg_exit);
//        }
//        if(_mapMsgMap.keys().contains(MD_Msg_Init)){
//            _mapMsgMap.remove(MD_Msg_Init);//系统弹出框
//        }
//    }
    void setMsgWidgetMap(ModuleType type, QWidget *w) {
        _mapMsgMap[type] = w;
    }

    void setAllMsgHide() {
        _mapMsgMap.value(MD_AcceptTaskWork)->hide();        //接受新任务提示页面
        _mapMsgMap.value(MD_CompleteOperEnd)->hide();       //结束接管提示
        _mapMsgMap.value(MD_CompleteOperStart)->hide();     //开始接管提示
        _mapMsgMap.value(MD_GiveUpTakeOver)->hide();       //放弃接管提示
        _mapMsgMap.value(MD_NetworkInterruption)->hide();   //网络连接中断提示

        // --> BEGIN added by ZJZ, 2022/3/1
        _mapMsgMap.value(MD_TipsPopup)->hide();   //common tips window
        // <-- END

        _mapMsgMap.value(MD_SelfTest)->hide();

        _mapMsgMap.value(MD_NotSatisfiedWithTakeover)->hide();//接管条件不满足提示
        _mapMsgMap.value(MD_FastStop)->hide();//接管条件不满足提示
        //           _mapMsgMap.value(MD_TaskWorkChange)->hide();       //接管目标变更提示
//        if(_mapMsgMap.keys().contains(MD_Msg_exit)){
//            _mapMsgMap.value(MD_Msg_exit)->hide();//系统弹出框
//        }
//        if(_mapMsgMap.keys().contains(MD_Msg_Init)){
//            _mapMsgMap.value(MD_Msg_Init)->hide();//系统弹出框
//        }
        setCurrentMsg(MD_None);
    }

    bool getShowFlag(){
        return showTipFlag;
    }
    void setShowFlag(bool flag){
        showTipFlag=flag;
    }

    int                      currentTakeoverPurpose=-1;


private:
    System();
    void                     createSharedMemory();
    void                     readSharedMemory();
    void                     writeSharedMemory();

    static System            *m_pInstance;
    SharedDatas              m_sysShareData;
    ProcessType              m_processType;
    QSharedMemory            *m_pSharedMemory;
    unsigned short           m_taskId;
    CabinModeType            m_CarbinMode;//0:全局界面，1：单车界面，尚未接管，2：单车界面，接管中
    ModuleType               m_currentMsg;
    LayoutType               _layout;//当前布局类型
    QMap<ModuleType,QWidget*> _mapMsgMap;
    QString                  _variantDriverInfo;
    QList<QString>           _vehicleImeiList;//当前配置文件里的imei
    bool                     showTipFlag=false;
    bool                     emergencyState=false;
    int                      currentVehicleStatus;

    // --> BEGIN added by ZJZ, 2022/3/22
    int                      currentVehiclePurpose;
    // <-- END

public:
    std::set<QString> onlineVehicle;
    uint warningSpeed=100;
    uint reduceSpeed=100;
    bool forwardLeft_forwardRight_Big = false;//左前和右前摄像头是否处于放大状态
    bool showSelfTestWnd = false;// self test window
};

#if defined(pSharedDatas)
#undef pSharedDatas
#endif
#define pSharedDatas System::getSharedDatas()

#endif // SYSTEM_H
