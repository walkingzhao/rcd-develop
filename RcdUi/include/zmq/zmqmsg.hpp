/**
 * @file zmqmsg.hpp
 * @author lujiefeng
 * @brief
 * @version 0.1
 * @date 2020-08-21
 *
 * @copyright Copyright () 2020
 *
 */
#include <cstdint>

#pragma once

#define IMEI_LENGTH 15

//控制设备连接状态 ControlDevLinkStatus
//断开
#define DEV_LINKSTATUS_DISCONNECTED 0
//已连接,无数据
#define DEV_LINKSTATUS_CONNECTED_NO_DATA 1
//已连接,有数据
#define DEV_LINKSTATUS_CONNECTED_DATA 2

//请求遥控命令 ReqRemoteControl.opt
//未知命令
#define REQ_REMOTE_CONTROL_UNKNOWN 0
//遥控开始
#define REQ_REMOTE_CONTROL_START 1
//遥控结束
#define REQ_REMOTE_CONTROL_END 2

//遥控请求响应结果 RespRemoteControl.result
//未知
#define RESP_REMOTE_CONTROL_UNKNOWN             0
//车辆未连接
#define RESP_REMOTE_CONTROL_VEHICLE_DISCONNECT  1
//车辆已接受
#define RESP_REMOTE_CONTROL_VEHICLE_RECV        2
//车辆接受超时
#define RESP_REMOTE_CONTROL_VEHICLE_TIMEOUT     3
//车辆拒绝
#define RESP_REMOTE_CONTROL_VEHICLE_REJECT      4

//车辆状态 VehicleStatus.status
#define VEHICLE_STATUS_UNKNOWN          0//未知
#define VEHICLE_STATUS_CONNECTED        1//车辆已连接
#define VEHICLE_STATUS_DISCONNECTED     2//车辆断开连接
#define VEHICLE_STATUS_NO_CAN           3//车辆CAN无数据

//远程控制数据中档位定义
#define GEARSHIFT_CTRL_N                3
#define GEARSHIFT_CTRL_D                2
#define GEARSHIFT_CTRL_R                4

//远程控制数据中货箱控制
#define BUCKET_CTRL_HOLDON              0
#define BUCKET_CTRL_UP                  1
#define BUCKET_CTRL_DOWN                2

#pragma pack(1)

typedef struct
{
    uint16_t clutch;        //离合
    uint16_t brake;         //刹车
    uint16_t accelerator;   //油门
    uint16_t handbrake;     //手刹
    int16_t steeringwheel; //方向盘
    uint8_t gear;           //挡位
    uint8_t mirror;         //后视镜按键
    uint8_t key_1;          //
    uint8_t key_2;          //
    uint8_t unused[5];
} MainCtrlMsg;

typedef struct{
    uint8_t clutch;         //离合
    uint8_t brake;          //刹车
    uint8_t accelerator;    //油门
    uint8_t handbrake;      //手刹
    int8_t steeringwheel;  //方向盘
}CtrlRawDataST;

typedef struct
{
    uint64_t utcTime;
    uint16_t steeringWheelAngle; //方向盘角度
    uint16_t throttlePedal;      //油门踏板开度百分比
    uint16_t brakePedal;         //电制动踏板开度百分比
    uint16_t hydraulicBrake;     //机械制动制动控制
    uint16_t retarderCtrl;       //缓速器控制
    uint8_t exhuastBrake;       //气压制动控制    0:气压制动失效，1:气压制动使能
    uint8_t parkCtrl;           //停车制动控制    0:解除驻车，1:驻车  //手刹
    uint8_t bucketCtrl;         //货箱控制  0:保持 1:上升 2:下降
    uint8_t trumpetCtrl;        //转向灯控制
    uint8_t gearShiftCtrl;      //档位控制 2:D, 3:N, 4:R
    uint8_t eStop;              //紧急停车
    uint8_t loadingCtrl;        //装载制动 0:解除驻车，1:驻车      //P档
} ControlData;

// light control, 0x00:close, 0x01:open
typedef struct {
    uint8_t left : 2;                //左转向
    uint8_t right : 2;               //右转向
    uint8_t lowBeam : 2;             //近光灯
    uint8_t heighBeam : 2;           //远光灯

    uint8_t rotatingWarningLight : 2;    //旋转警示灯
    uint8_t speaker : 2;             //气喇叭
    uint8_t frontFog : 2;            //前雾灯
    uint8_t frontStatus : 2;         //前工作灯

    uint8_t side : 2;                //侧照灯
    uint8_t rearPosition : 2;        //后位置灯
    uint8_t emergency : 2;          //紧急双闪
    uint8_t brake : 2;              //制动灯

    uint8_t back : 2;               //倒车灯
    uint8_t rearStatus : 2;          //后工作灯
    uint8_t unused : 4;
}ControlLight;


typedef struct{
    float throttlePedal;            //实际踩踏板百分比 0~100%
    float brakePedal;               //电制动踏板位置百分比 0~100
    float hydraulicBrake;           //机械制动踏板反馈百分比 0~100
    float steeringWheelAngle;       //方向盘当前转角 -540~540
    float engineSpeed;              //1rpm 发动机转速
    float speed;                    //km/h 车速

    float batteryLevel;       //电池电量
    float cellTemperature;    //电芯温度
    float fuelLevel;            //油量
    float engineOilPressure;    //发动机油压
    float engineCoolantTemperature; //发动机冷却液温度
    float exhaustPortEmperature; //排气口温度
    float frontAxleBrakePressure; //前桥制动压力
    float rearAxleBrakePressure; //后桥制动压力

    int8_t gear;                    //挡位 -1:R 0:N 1:D
    uint8_t mode;                   // 车辆驾驶模式 0x00手动/0x01自动
//    uint8_t handBrake;            //手制动电磁阀 0x01: open 0x00: close
    uint8_t bucketCtrl;             //举升 0x00/0x01/0x02/0x03/0x04 下止点/上止点/下降/上升/保持
    uint8_t tirePressureWarning;    //胎压故障告警 0 no error, >0 error
    uint8_t exhaustBrake;           //排气制动0x01: enable 0x00: disable
    uint8_t parkingBrake;           //停车制动 手制动电磁阀 0x01: open 0x00: close
    uint8_t loadingBrake;           //装载制动 0:解除 1:实施 FF:无效
} VehicleBodyData;

typedef struct {
    uint8_t emergencyFlash; //紧急双闪 00关/01开
    uint8_t left;           //左转灯
    uint8_t right;          //右转灯
    uint8_t lowBeam;        //近光灯
    uint8_t highBeam;       //远光灯
    uint8_t rotateAlarm;    //旋转报警灯
    uint8_t airHorns;       //气喇叭
    uint8_t frontFogLamp;   //前雾灯
    uint8_t frontWorkLamp;  //前工作灯
    uint8_t sideLamp;       //侧照灯
    uint8_t positoinLamp;   //位置灯
} VehicleLightsData;

//typedef union {
typedef struct {
    VehicleBodyData bodyData;
    VehicleLightsData lightsData;
}FeedbackData;

// cabin device
typedef struct
{
    uint8_t wheel;      // 方向盘等控制器连接状态
    uint8_t io;         // IO控制器状态
    uint8_t vehicle;    // 车端状态
} ControlDevLinkStatus;

typedef struct
{
    uint8_t imei[IMEI_LENGTH]; //设备IMEI
    uint8_t opt;               //遥控命令
    uint16_t taskId;           //任务ID
} ReqRemoteControl;

typedef struct
{
    uint8_t imei[IMEI_LENGTH]; //设备IMEI
    uint8_t cmd;               // start or finish
    uint8_t result;            //遥控命令请求响应结果
    uint16_t taskId;            //taskId
} RespRemoteControl;

typedef struct
{
    uint8_t imei[IMEI_LENGTH]; //设备IMEI
    uint8_t type;              //车辆类型
    uint8_t status;            //车辆状态
} VehicleStatus;

typedef struct
{
    uint32_t canId;
    uint8_t data[8];
} CanRawData;

typedef struct
{
    uint8_t imei[IMEI_LENGTH]; //设备IMEI
    uint8_t type;              //车辆类型
    uint8_t length;            //CanRawData 长度
    CanRawData rawData[0];     //车身数据
} VehicleRawData;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint32_t delayUs;
}VehicleDelay;

typedef struct
{
    uint32_t key;
}KeyButton;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint16_t bodyLen;
    uint8_t body[256];
}HmiMsg;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint16_t bodyLen;
    uint8_t body[256];
}HmiHintMsg;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint16_t bodyLen;
    uint8_t body[256];
}GpsMsg;

typedef struct {
    uint16_t taskId;
    uint8_t result;
    uint8_t refuseReason[256];
}TaskReply;

typedef struct {
    uint16_t taskId;
}TaskGiveUp;

typedef struct {
    uint16_t taskId;
}TaskCancel;

typedef struct {
    uint8_t imei[IMEI_LENGTH];
}TaskReq;

typedef struct {
    uint16_t taskId;
    uint8_t reason; //add task end reason
}TaskEnd;

typedef struct {
    uint16_t taskId;
}TaskFail;

typedef enum : uint8_t {
    TakeoverTask_Reply = 0,
    TakeoverTask_GiveUp,
    TakeoverTask_Cancel,
    TakeoverTask_Request,
    TakeoverTask_End,
    TakeoverTask_Fail
}TakeoverTaskType;

typedef struct {
    TakeoverTaskType taskType;
    union {
        TaskReply taskReply;
        TaskGiveUp taskGiveUp;
        TaskCancel taskCancel;
        TaskReq taskReq;
        TaskEnd taskEnd;
        TaskFail taskFail;
    }TaskUnion;
}TaskOperSt;

typedef struct {
    bool isParking;
    bool isNoPedal;
    bool isCenterSteeringWheel;
    bool isButtonReset;
}SelfCheckStatus;

typedef struct {
    uint8_t status;
    uint8_t CardSn[8]; // 8 bytes always
} IcCardStatus;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint16_t bodyLen;
    uint8_t body[256];
}TrackLineMsg;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint16_t bodyLen;
    uint8_t body[256];
}SpeedWarningMsg;

typedef struct
{
    uint8_t imei[IMEI_LENGTH];
    uint16_t bodyLen;
    uint8_t body[256];
}RoadTaskInfo;

#pragma pack()
