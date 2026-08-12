#ifndef WARNNING_H
#define WARNNING_H
#include <vector>
#include <map>
#include <string>
#include <bitset>
#include <QMap>
using namespace std;
enum WarningBit
{
    frontMiddleRadarFault = 0,                //前激光雷达故障
    frontLidarFault = 1,                      //前左毫米波掉线
    rearRadarFault = 2,                       //前中毫米波故障
    rearLidarFault = 3,                       //前右毫米波掉线
    frontLeftRadarDisconnetion= 4,            //后激光雷达故障
    frontRightRadarDisconnetion = 5,          //后毫米波故障
    leftLidarDisconnetion = 6,                //左激光雷达掉线
    rightLidarDisconnetion = 7,               //右激光雷达掉线
    perceptualSystemFault = 8,                //感知系统模块故障
    rtkStatusAbnormal = 9,                    //定位状态异常
    imuStatusAbnormal = 10,                   //外置定位设备异常
    gpsStatusAbnormal = 11,                   //GPS信号质量差
    noSatelliteSignal = 12,                   //差分数据状态异常
//    gnssAge = 13,                             //前补盲激光雷达故障
//    gnssVariance = 14,                        //感知地图下载失败
    V2VDisconnection = 15,                    //车车通信异常
    V2NDisconnection = 16,                    //与平台通信中断
    VCUCommunicationAbnormal = 17,	          //VCU通信异常
    CGUCommunicationAbnormal = 18,            //网关通信异常
    SCUCommunicationAbnormal = 19,            //SCU通信异常
    CCUCommunicationAbnormal = 20,			  //主控通信异常
    HMICommunicationAbnormal = 21,            //HMI通信异常
    CCUAbnormalExit = 22,               //CCU异常退出
    MainInertialDifferWidely = 23,          //主从惯导航向差异过大
    //TBoxAbnormalCommunication = 24, 		 //与T-Box通信异常
    mainPowerFault = 25,                      //系统主电源故障
    bakPowerFault = 26,                       //系统备用电源故障
    MBoxV2NDrops = 27,                       //MBox V2N掉线
    TBoxV2NDrops = 28,                       //TBox V2N掉线
    takeOverAbnormal = 29,                    //与接管平台通信异常
    CCUReceiveCGUAbnormal = 30,                //主控接收网关定位异常
    CCUReceiveLocationAbnormal = 31,           //主控接收定位异常
    //    dynamicRoad = 32,                         //装卸载点动态规划故障
    dockingFailure = 33,                      //停靠失败
    taskFileFormat = 34,                      //任务文件异常
    taskFileNoKey = 35,                       //车辆航向与路径偏差大
    //    calibrationFileList = 36,                 //标定文件列表读取失败
    liftingStateAbnormal = 37,                //货斗举升异常
    trafficJam = 38,                          //道路长时间堵塞告警
    emptyStateReceivedUnloadTask = 39,        //空载状态卸载任务
    fullStateReceivedLoadTask = 40,           //满载状态装载任务
    gatewayDownLoadMapFailed = 41,            //地图文件下载失败
    gatewayDownLoadTaskFileFailed = 42,       //网关下载任务失败
    masterDownLoadTaskFileFailed = 43,        //主控下载任务失败
    rssiWarning = 44,                         //平台连接信号质量差
    fullLoadCloseCar = 45,                    //满载状态收车任务
    fallingStateAbnormal = 46,                    //货斗下降异常
    locationNoStopPoint = 47,                    //货斗位置非下止点告警
    frontComplementFault = 48,                    //前补盲激光雷达故障
    fisheyeCameraFault = 49,                    //鱼眼相机故障
    telephotoCameraFault = 50,                    //长焦相机故障
    perceptionMapFault = 51,                    //感知地图下载失败
    front_perception_timeout = 52,         //前感知处理超时
    back_perception_timeout = 53,          //后感知处理超时
    front_perception_input_error = 54,     //前感知输入数据异常
    back_perception_input_error = 55,      //后感知输入数据异常
    ControllerLosesHeartbeat = 56,        //线控丢失控制心跳
    gearFault = 57,                           //档位故障
    steeringFault = 58,                       //转向故障
    trolleyFault = 59,                        //溜车告警
    roadDeviation = 60,                       //偏离主路径告警
    collwarning = 61,                         //碰撞已发生报警
    rollWarning = 62,                         //车身姿态异常
    speedFastWarning = 63,                    //车速过快报警
    speedSlowWarning = 64,                    //车速过慢报警
    throttleDrivingAbnormal = 65,             //油门驱动力异常
    electricBrakingAbnormal = 66,             //电制动力异常
    mechanicalBrakingAbnormal = 67,           //机械制动力异常
    loadingBrakingWithExecutionDiff = 68,     //驻车命令与执行不符合
    vehicleDrawDragonWarning = 69,     //车辆画龙告警
    crossedFinishWarning = 70,     //越过路权终点告警
    vehicleSkidWarning = 71,        //轻微打滑告警
    enginePrimaryFault = 72,                  //发动机严重故障
    engineSecondaryFault = 73,               //发动机中等故障
    engineThreeFault = 74,                   //发动机一般故障
    transmissionPrimaryFault = 75,            //变速箱严重故障
    transmissionSecondaryFault = 76,          //变速箱中等故障
    transmissionThreeFault = 77,              //变速箱一般故障
    EBSFault = 78,                            //车辆电制动故障
    EPSFault = 79,                            //车辆电助力转向故障
    electricDriveSpeedLimit1 = 80,            //电驱动系统类异常
    electricDriveSpeedLimit2 = 81,            //电驱动系统类异常
    electricDriveSpeedLimit3 = 82,            //电驱动系统类异常
    electricDriveEngineLift  = 83,            //电驱动系统类异常
    electricDriveSystemEvents  = 84,          //电驱动系统类异常
    noTractio = 85,                           //车辆无牵引告警
    WithoutElectricityGoSlow = 86,            //车辆无电缓行告警
    liftingHardwareFault = 87,                //举升硬件故障
    suspensionCylinderPrimaryFault = 88,      //悬缸严重故障
    suspensionCylinderThreeFault = 89,        //悬缸一般故障
    tirePrimaryFault = 90,                    //轮胎严重故障
    tireThreeFault = 91,                      //轮胎一般故障
    tirePressureWarning = 92,                 //车辆胎压异常
    LowFuelOilLevel = 93,                     //燃油油位低告警
    automaticWeighingFault = 94,              //自动称重故障
    selfExtinguished = 95,                   //自主灭火系统故障
    turnLightShort = 96,                      //车辆转向灯短路
    nearLightOrHighBeamShort = 97,           //近光灯或远光灯短路
    circuitAlarmLampOrFrontFogLampShort = 98,    //报警灯或前雾灯短路
    gasHornOrReverseLampShort = 99,       //车辆喇叭短路
    workingLightShort = 100,                  //工作灯短路
    brakeOrSideLightShort = 101,              //制动灯或侧向灯短路
    positionLightShort = 102,                 //位置灯短路
    vehicleDeviceShort = 103,        //车辆设备短路
    shaftSolenoidShort = 104,                 //轴差电磁阀短路
    drierOrWaterHanbaoOrExhaustShort = 105,   //车辆排气制动故障
    steeringOilOrEmptyFilterJamAlarm = 106,   //车辆油滤堵塞告警
    handBrakeSolenoidValveShort = 107,        //手制动电磁阀短路
    mechanicalBrakeHardwareFault = 108,       //机械制动硬件故障
    leverSensorFault = 109,                   //前轮转角传感器故障
    oilTemperatureHigh = 110,            //车辆液压油温高告警
    coolingFluidTemperatureLow = 111,      //发动机冷却液液位低
    coolingFluidTemperatureHeight = 112,    //发动机冷却液温度高
    driveSystemFailure = 113,       //驱动系统严重故障
    brakePressureLow = 114,        //车辆制动压力低告警
    veerPressureLow = 115,         //车辆转向压力低告警
    engineOilPressureLow = 116,     //车辆机油压力低告警
    steeringValveAlarm = 117,       //转向阀反馈报警故障
    highOilPressureInTank = 118,       //液压油箱油压高
    wheelMotorSunexit = 119,       //轮马达太阳轮退出
    HydraulicTankLow = 120,     //液压油箱油位低
    RedundantBrakeAbnormal = 121,       //冗余制动自检状态异常
    RedundantBrakeBatteryPower = 122,       //冗余制动当前为蓄电池供电
    SteerExitGPS = 160,   //转向阀状态异常
    BlockedAtParking = 161,    //停靠受阻异常
    SlipSeriously = 162,    //严重打滑告警
    AbnormalLoadStatus = 163,    //载货状态异常
    SteerModeAbnormal = 164,    //转向阀状态异常
    FlatTire = 165,    //车辆爆胎

    EBR_response_timeout = 166,          //冗余制动响应超时
    R_box_process_exception = 167,       //R-Box冗余制动进程通信异常
    EBR_offline = 168,                   //冗余制动离线
    change_mode_manual_in_loaddump = 169,   //装卸载区切人工模式致任务失败
    park_brake_exception = 170,         //驻车制动/停车制动执行异常
    engine_kill_failure = 171,         //发动机熄火失败
    abnormal_switch_2_manual = 172,         //运行状态下驾驶模式异常切换
    main_path_error = 173,        //启动时不在主路径上
    AbnormalTireTemp = 208,    //车辆胎温异常
    BatteryVoltageLow = 209,    //电池电压低
    TransOilTempHigh = 211,   //变速箱油温高
    BrakeCoolantTempHigh = 212   //制动冷却液温度高
};

const QMap<int, std::pair<std::string, std::string>> warningMap = {
    /*报警位序号,文字提示,语音播放路径*/
    {frontMiddleRadarFault, {"前激光雷达掉线", "systemFaultDeal.wav"}},
    {frontLidarFault, {"前左毫米波掉线", "systemFaultDeal.wav"}},
    {rearRadarFault, {"前中毫米波掉线", "systemFaultDeal.wav"}},
    {rearLidarFault, {"前右毫米波掉线", "systemFaultDeal.wav"}},
    {frontLeftRadarDisconnetion, {"后激光雷达掉线", "takeOver.wav"}},
    {frontRightRadarDisconnetion, {"后毫米波掉线", "systemFaultDeal.wav"}},
    {leftLidarDisconnetion, {"左激光雷达掉线", "systemFaultDeal.wav"}},
    {rightLidarDisconnetion, {"右激光雷达掉线", "systemFaultDeal.wav"}},
    {perceptualSystemFault, {"感知系统模块故障", "takeOver.wav"}},
    {rtkStatusAbnormal, {"定位状态异常", "takeOver.wav"}},
    {imuStatusAbnormal, {"外置定位设备异常", "systemFaultDeal.wav"}},
    {gpsStatusAbnormal, {"GPS信号质量差", "systemFaultDeal.wav"}},
    {noSatelliteSignal, {"差分数据状态异常", "systemFaultDeal.wav"}},
//    {gnssAge, {"前补盲激光雷达故障", "takeOver.wav"}},
//    {gnssVariance, {"感知地图下载失败", "takeOver.wav"}},
    {V2VDisconnection, {"车车通信异常", "systemFaultAttention.wav"}},
    {V2NDisconnection, {"与平台通信中断", "systemFaultDeal.wav"}},
    {VCUCommunicationAbnormal, {"VCU通信异常", "takeOver.wav"}},
    {CGUCommunicationAbnormal, {"网关通信异常", "systemFaultDeal.wav"}},
    {SCUCommunicationAbnormal, {"SCU通信异常", "takeOver.wav"}},
    {CCUCommunicationAbnormal, {"主控通信异常", "takeOver.wav"}},
    {HMICommunicationAbnormal, {"HMI通信异常", "systemFaultDeal.wav"}},
    {CCUAbnormalExit, {"主控异常退出", "takeOver.wav"}},
    {MainInertialDifferWidely, {"主从惯导航向差异过大", "takeOver.wav"}},
    //{TBoxAbnormalCommunication, {"MBox与TBox通信异常", "systemFaultAttention.wav"}},
    {mainPowerFault, {"系统主电源故障", "systemFaultDeal.wav"}},
    {bakPowerFault, {"系统备用电源故障", "systemFaultDeal.wav"}},
    {MBoxV2NDrops, {"MBox V2N掉线", "systemFaultAttention.wav"}},
    {TBoxV2NDrops, {"TBox V2N掉线", "systemFaultAttention.wav"}},
    {takeOverAbnormal, {"与接管平台通信异常", "systemFaultAttention.wav"}},
    {CCUReceiveCGUAbnormal, {"主控接收网关定位异常", "systemFaultDeal.wav"}},
    {CCUReceiveLocationAbnormal, {"主控接收定位异常", "takeOver.wav"}},
//    {dynamicRoad, {"路径规划失败", "pathPlanningFailure.wav"}},
    {dockingFailure, {"停靠失败", "takeOver.wav"}},
    {taskFileFormat, {"任务文件异常", "systemFaultDeal.wav"}},
    {taskFileNoKey, {"车辆航向与路径偏差大", "takeOver.wav"}},
//    {calibrationFileList, {"标定文件异常", "calibrationFileReadFailure.wav"}},
    {liftingStateAbnormal, {"货斗举升异常", "takeOver.wav"}},
    {trafficJam, {"道路长时间堵塞告警", "systemFaultAttention.wav"}},
    {emptyStateReceivedUnloadTask, {"空载状态卸载任务", "systemFaultAttention.wav"}},
    {fullStateReceivedLoadTask, {"满载状态装载任务", "takeOver.wav"}},
    {gatewayDownLoadMapFailed, {"地图文件下载失败", "systemFaultDeal.wav"}},
    {gatewayDownLoadTaskFileFailed, {"网关下载任务失败", "systemFaultDeal.wav"}},
    {masterDownLoadTaskFileFailed, {"主控下载任务失败", "systemFaultDeal.wav"}},
    {rssiWarning, {"平台连接信号质量差", "systemFaultAttention.wav"}},
    {fullLoadCloseCar, {"满载状态收车任务", "takeOver.wav"}},
    {fallingStateAbnormal, {"货斗下降异常", "takeOver.wav"}},
    {locationNoStopPoint, {"货斗位置非下止点告警", "takeOver.wav"}},
    {frontComplementFault, {"前补盲激光雷达掉线", "systemFaultDeal.wav"}},
    {fisheyeCameraFault, {"鱼眼相机掉线", "systemFaultAttention.wav"}},
    {telephotoCameraFault, {"长焦相机掉线", "systemFaultAttention.wav"}},
    {perceptionMapFault, {"感知地图下载失败", "systemFaultAttention.wav"}},

    {front_perception_timeout, {"前感知处理超时", "systemFaultAttention.wav"}},
    {back_perception_timeout, {"后感知处理超时", "systemFaultAttention.wav"}},
    {front_perception_input_error, {"前感知输入数据异常", "takeOver.wav"}},
    {back_perception_input_error, {"后感知输入数据异常", "takeOver.wav"}},

    {ControllerLosesHeartbeat, {"CCU控制心跳异常", "takeOver.wav"}},
    {gearFault, {"档位故障", "takeOver.wav"}},
    {steeringFault, {"转向故障", "takeOver.wav"}},
    {trolleyFault, {"溜车告警", "takeOver.wav"}},
    {roadDeviation, {"偏离主路径告警", "takeOver.wav"}},
    {collwarning, {"碰撞已发生报警", "takeOver.wav"}},
    {rollWarning , {"车身姿态异常", "takeOver.wav"}},
    {speedFastWarning, {"车速过快报警", "takeOver.wav"}},
    {speedSlowWarning, {"车速过慢报警", "systemFaultAttention.wav"}},
    {throttleDrivingAbnormal, {"油门驱动力异常", "takeOver.wav"}},
    {electricBrakingAbnormal, {"电制动力异常", "takeOver.wav"}},
    {mechanicalBrakingAbnormal, {"机械制动力异常", "takeOver.wav"}},
    {loadingBrakingWithExecutionDiff, {"装载制动执行异常", "takeOver.wav"}},
    {vehicleDrawDragonWarning, {"车辆画龙告警", "systemFaultDeal.wav"}},
    {crossedFinishWarning, {"越过路权终点告警", "takeOver.wav"}},
    {vehicleSkidWarning, {"轻微打滑告警", "systemFaultDeal.wav"}},
    {enginePrimaryFault, {"发动机严重故障", "takeOver.wav"}},
    {engineSecondaryFault, {"发动机中等故障", "systemFaultDeal.wav"}},
    {engineThreeFault, {"发动机一般故障", "systemFaultAttention.wav"}},
    {transmissionPrimaryFault, {"变速箱严重故障", "takeOver.wav"}},
    {transmissionSecondaryFault, {"变速箱中等故障", "systemFaultDeal.wav"}},
    {transmissionThreeFault, {"变速箱一般故障", "systemFaultAttention.wav"}},
    {EBSFault, {"车辆电制动故障", "takeOver.wav"}},
    {EPSFault, {"车辆电助力转向故障", "takeOver.wav"}},
    {electricDriveSpeedLimit1, {"电驱动系统类异常", "systemFaultDeal.wav"}},
    {electricDriveSpeedLimit2, {"电驱动系统类异常", "systemFaultDeal.wav"}},
    {electricDriveSpeedLimit3, {"电驱动系统类异常", "systemFaultDeal.wav"}},
    {electricDriveEngineLift, {"电驱动系统类异常", "systemFaultAttention.wav"}},
    {electricDriveSystemEvents, {"电驱动系统类异常", "systemFaultAttention.wav"}},
    {noTractio, {"车辆无牵引告警", "takeOver.wav"}},
    {WithoutElectricityGoSlow, {"车辆无电缓行告警", "takeOver.wav"}},
    {liftingHardwareFault, {"举升硬件故障", "takeOver.wav"}},
    {suspensionCylinderPrimaryFault, {"悬缸严重故障", "takeOver.wav"}},
    {suspensionCylinderThreeFault , {"悬缸一般故障", "systemFaultAttention.wav"}},
    {tirePrimaryFault, {"轮胎严重故障", "takeOver.wav"}},
    {tireThreeFault, {"轮胎一般故障", "systemFaultAttention.wav"}},
    {tirePressureWarning, {"车辆胎压异常", "systemFaultDeal.wav"}},
    {LowFuelOilLevel, {"燃油油位低告警", "systemFaultAttention.wav"}},
    {automaticWeighingFault, {"自动称重故障", "systemFaultAttention.wav"}},
    {selfExtinguished, {"自主灭火系统故障", "systemFaultDeal.wav"}},
    {turnLightShort, {"车辆转向灯短路", "systemFaultAttention.wav"}},
    {nearLightOrHighBeamShort, {"近光灯或远光灯短路", "systemFaultAttention.wav"}},
    {circuitAlarmLampOrFrontFogLampShort, {"报警灯或前雾灯短路", "systemFaultAttention.wav"}},
    {gasHornOrReverseLampShort, {"车辆喇叭短路", "systemFaultAttention.wav"}},
    {workingLightShort, {"工作灯短路", "systemFaultAttention.wav"}},
    {brakeOrSideLightShort , {"制动灯或侧向灯短路", "systemFaultAttention.wav"}},
    {positionLightShort, {"位置灯短路", "systemFaultAttention.wav"}},
    {vehicleDeviceShort, {"车辆设备短路", "systemFaultAttention.wav"}},
    {shaftSolenoidShort, {"轴差电磁阀短路", "systemFaultAttention.wav"}},
    {drierOrWaterHanbaoOrExhaustShort, {"车辆排气制动故障", "systemFaultAttention.wav"}},
    {steeringOilOrEmptyFilterJamAlarm, {"车辆油滤堵塞告警", "systemFaultDeal.wav"}},
    {handBrakeSolenoidValveShort, {"手制动电磁阀短路", "takeOver.wav"}},
    {mechanicalBrakeHardwareFault, {"机械制动硬件故障", "takeOver.wav"}},
    {leverSensorFault, {"前轮转角传感器故障", "takeOver.wav"}},
    {oilTemperatureHigh, {"车辆液压油温高告警", "systemFaultAttention.wav"}},
    {coolingFluidTemperatureLow, {"发动机冷却液液位低", "systemFaultAttention.wav"}},
    {coolingFluidTemperatureHeight, {"发动机冷却液温度高", "systemFaultDeal.wav"}},
    {driveSystemFailure, {"驱动系统严重故障", "takeOver.wav"}},
    {brakePressureLow, {"车辆制动压力低告警", "systemFaultDeal.wav"}},
    {veerPressureLow, {"车辆转向压力低告警", "systemFaultDeal.wav"}},
    {engineOilPressureLow, {"车辆机油压力低告警", "systemFaultDeal.wav"}},
    {steeringValveAlarm, {"转向阀反馈报警故障", "takeOver.wav"}},
    {highOilPressureInTank, {"液压油箱油压高", "systemFaultDeal.wav"}},
    {wheelMotorSunexit, {"轮马达太阳轮退出", "takeOver.wav"}},
    {HydraulicTankLow, {"液压油箱油位低", "systemFaultDeal.wav"}},
    {RedundantBrakeAbnormal, {"冗余制动自检状态异常", "systemFaultDeal.wav"}},
    {RedundantBrakeBatteryPower, {"冗余制动供电异常", "systemFaultDeal.wav"}},
    {SteerExitGPS, {"转向阀状态异常", "takeOver.wav"}},
    {BlockedAtParking, {"停靠受阻异常", "takeOver.wav"}},
    {SlipSeriously, {"严重打滑告警", "takeOver.wav"}},
    {AbnormalLoadStatus, {"载货状态异常", "systemFaultDeal.wav"}},
    {SteerModeAbnormal, {"转向模式异常切换", "takeOver.wav"}},
    {FlatTire, {"车辆爆胎", "takeOver.wav"}},

    {EBR_response_timeout, {"冗余制动执行异常", "takeOver.wav"}},
    {R_box_process_exception, {"冗余制动进程通讯异常", "systemFaultDeal.wav"}},
    {EBR_offline, {"冗余制动离线", "systemFaultDeal.wav"}},
    {change_mode_manual_in_loaddump, {"装卸载区切人工模式致任务失败", "systemFaultDeal.wav"}},
    {park_brake_exception, {"停车制动执行异常", "takeOver.wav"}},
    {engine_kill_failure, {"发动机熄火失败", "systemFaultDeal.wav"}},
    {abnormal_switch_2_manual, {"运行状态下驾驶模式异常切换", "takeOver.wav"}},
    {main_path_error, {"启动时不在主路径上", "systemFaultDeal.wav"}},
    {AbnormalTireTemp, {"车辆胎温异常", "takeOver.wav"}},
    {BatteryVoltageLow, {"电池电压低", "systemFaultDeal.wav"}},
    {TransOilTempHigh, {"变速箱油温高", "systemFaultDeal.wav"}},
    {BrakeCoolantTempHigh, {"制动冷却液温度高", "systemFaultDeal.wav"}},
};

const std::map<int, std::pair<std::string, std::string>> warningCloseMap = {
    /*报警位序号,文字提示,语音播放路径*/
    //    {frontMiddleRadarFault, {"前中毫米波故障", "systemFaultDeal.wav"}},
    //    {frontLidarFault, {"前激光雷达故障", "systemFaultDeal.wav"}},
    //    {rearRadarFault, {"后毫米波故障", "systemFaultDeal.wav"}},
    //    {rearLidarFault, {"后激光雷达故障", "systemFaultDeal.wav"}},
    //    {frontLeftRadarDisconnetion, {"前左毫米波通信中断", "systemFaultDeal.wav"}},
    //    {frontRightRadarDisconnetion, {"前右毫米波通信中断", "systemFaultDeal.wav"}},
    //    {leftLidarDisconnetion, {"左激光雷达通信中断", "systemFaultDeal.wav"}},
    //    {rightLidarDisconnetion, {"右激光雷达通信中断", "systemFaultDeal.wav"}},
    {perceptualSystemFault, {"感知系统模块故障检测已关闭", "perceptualSystemFaultClose.wav"}},//感知检测已关闭
    //    {rtkStatusAbnormal, {"差分定位状态异常", "takeOver.wav"}},
    //    {imuStatusAbnormal, {"IMU状态异常", "takeOver.wav"}},
    //    {gpsStatusAbnormal, {"GPS状态异常", "takeOver.wav"}},
    //    {noSatelliteSignal, {"GPS状态异常", "takeOver.wav"}},
    //    {gnssAge, {"系统导航状态异常", "takeOver.wav"}},
    //    {gnssVariance, {"系统导航状态异常", "takeOver.wav"}},
    //    {V2NDisconnection, {"与平台通信中断", "takeOver.wav"}},
    //    {VCUCommunicationAbnormal, {"控制单元通信异常", "takeOver.wav"}},
    //    {CGUCommunicationAbnormal, {"网关通信异常", "systemFaultDeal.wav"}},
    //    {SCUCommunicationAbnormal, {"SCU通信异常", "takeOver.wav"}},
    //    {CCUCommunicationAbnormal, {"主控通信异常检测已关闭", "takeOver.wav"}},
    //    {HMICommunicationAbnormal, {"HMI通信异常", "systemFaultDeal.wav"}},
    //    {CGURebootFault, {"网关重启故障", "systemFaultDeal.wav"}},
    //    {CCURebootFault, {"主控重启故障", "takeOver.wav"}},
    //    {HMIRebootFault, {"HMI重启故障", "systemFaultDeal.wav"}},
    //    {mainPowerFault, {"主电源故障", "takeOver.wav"}},
    //    {bakPowerFault, {"备用电源故障", "takeOver.wav"}},
    //    {dynamicRoad, {"路径规划失败", "pathPlanningFailure.wav"}},
    //    {dockingFailure, {"停靠失败", "dockingFailure.wav"}},
    //    {taskFileFormat, {"任务文件异常", "taskFileAbnormal.wav"}},
    //    {taskFileNoKey, {"路径文件异常", "pathFileAbnormal.wav"}},
    //    {calibrationFileList, {"标定文件异常", "calibrationFileReadFailure.wav"}},
    {liftingStateAbnormal, {"举升状态异常检测已关闭", "liftingStateAbnormalClose.wav"}},
    //    {trafficJam, {"道路堵塞异常", "trafficJam.wav"}},
    {emptyStateReceivedUnloadTask, {"载货状态异常检测已关闭", "loadStatusAbnormalClose.wav"}},
    {fullStateReceivedLoadTask, {"载货状态异常检测已关闭", "loadStatusAbnormalClose.wav"}},
    //    {gatewayDownLoadMapFailed, {"地图文件下载失败", "downLoadMapFailed.wav"}},
    //    {gatewayDownLoadTaskFileFailed, {"任务文件下载失败", "downLoadTaskFileFailed.wav"}},
    //    {masterDownLoadTaskFileFailed, {"任务文件下载失败", "downLoadTaskFileFailed.wav"}},
    //    {rssiWarning, {"无线通信异常", "rssiWarning.wav"}},
    //{inertialNavigationDriftFault, {"惯导漂移故障检测已关闭", "inertialNavigationDriftFaultClose.wav"}},
    {gearFault, {"档位故障检测已关闭", "gearFaultClose.wav"}},
    {steeringFault, {"转向故障检测已关闭", "steeringFaultClose.wav"}},
    {trolleyFault, {"溜车故障检测已关闭", "trolleyFaultClose.wav"}},
    {roadDeviation, {"道路偏离告警检测已关闭", "roadDeviationClose.wav"}},
    //    {collwarning, {"碰撞告警", "takeOver.wav"}},
    {rollWarning , {"车身姿态异常检测已关闭", "rollWarningClose.wav"}},
    {speedFastWarning, {"车速过快报警检测已关闭", "speedFastWarningClose.wav"}},
    //    {speedSlowWarning, {"车速过慢报警", "takeOver.wav"}},
    {throttleDrivingAbnormal, {"油门驱动力异常检测已关闭", "throttleDrivingAbnormalClose.wav"}},
    {electricBrakingAbnormal, {"电制动力异常检测已关闭", "electricBrakingAbnormalClose.wav"}},
    {mechanicalBrakingAbnormal, {"机械制动力异常检测已关闭", "mechanicalBrakingAbnormalClose.wav"}},
    {loadingBrakingWithExecutionDiff, {"制动执行异常检测已关闭", "loadingBrakingWithExecutionDiffClose.wav"}},
    //    {enginePrimaryFault, {"车辆发动机故障", "takeOver.wav"}},
    //    {engineSecondaryFault, {"车辆发动机故障", "systemFaultDeal.wav"}},
    //    {engineThreeFault, {"车辆发动机故障", "systemFaultAttention.wav"}},
    //    {transmissionPrimaryFault, {"车辆变速箱故障", "takeOver.wav"}},
    //    {transmissionSecondaryFault, {"车辆变速箱故障", "systemFaultDeal.wav"}},
    //    {transmissionThreeFault, {"车辆变速箱故障", "systemFaultAttention.wav"}},
    //    {EBSFault, {"车辆电制动故障", "takeOver.wav"}},
    //    {EPSFault, {"车辆电助力转向故障", "takeOver.wav"}},
    //    {electricDriveSpeedLimit1, {"车辆电驱动系统故障", "systemFaultDeal.wav"}},
    //    {electricDriveSpeedLimit2, {"车辆电驱动系统故障", "systemFaultDeal.wav"}},
    //    {electricDriveSpeedLimit3, {"车辆电驱动系统故障", "systemFaultDeal.wav"}},
    //    {electricDriveEngineLift, {"车辆电驱动系统故障", "systemFaultAttention.wav"}},
    //    {electricDriveSystemEvents, {"车辆电驱动系统故障", "systemFaultAttention.wav"}},
    {noTractio, {"车辆电驱动系统故障检测已关闭", "noTractioClose.wav"}},
    {WithoutElectricityGoSlow, {"车辆电驱动系统故障检测已关闭", "noTractioClose.wav"}},
    //    {liftingHardwareFault, {"车辆举升系统故障", "takeOver.wav"}},
    //    {suspensionCylinderPrimaryFault, {"车辆悬缸故障", "takeOver.wav"}},
    //    {suspensionCylinderThreeFault , {"车辆悬缸故障", "systemFaultAttention.wav"}},
    //    {tirePrimaryFault, {"车辆轮胎故障", "takeOver.wav"}},
    //    {tireThreeFault, {"车辆轮胎故障", "systemFaultAttention.wav"}},
    //    {LowFuelOilLevel, {"车辆燃油油位低", "systemFaultAttention.wav"}},
    //    {automaticWeighingFault, {"车辆自动称重故障", "systemFaultAttention.wav"}},
    //    {selfExtinguished, {"车辆自主灭火系统故障", "takeOver.wav"}},
    //    {turnLightShort, {"车辆转向灯短路", "systemFaultAttention.wav"}},
    //    {nearLightOrHighBeamShort, {"车辆车灯短路", "systemFaultAttention.wav"}},
    //    {circuitAlarmLampOrFrontFogLampShort, {"车辆车灯短路", "systemFaultAttention.wav"}},
    //    {gasHornOrReverseLampOrReversingHornShort, {"车辆喇叭短路", "systemFaultAttention.wav"}},
    //    {workingLightShort, {"车辆车灯短路", "systemFaultAttention.wav"}},
    //    {brakeOrSideLightShort , {"车辆车灯短路", "systemFaultAttention.wav"}},
    //    {positionLightShort, {"车辆车灯短路", "systemFaultAttention.wav"}},
    //    {WiperOrAirPressureOrAuxiliaryShort, {"车辆设备短路", "systemFaultAttention.wav"}},
    //    {shaftSolenoidShort, {"车辆轴差电磁阀短路", "systemFaultAttention.wav"}},
    //    {drierOrWaterHanbaoOrExhaustShort, {"车辆排气制动故障", "systemFaultAttention.wav"}},
    //    {steeringOilOrEmptyFilterJamAlarm, {"车辆油滤故障", "systemFaultDeal.wav"}},
    //    {handBrakeSolenoidValveShort, {"车辆手制动故障", "takeOver.wav"}},
    {mechanicalBrakeHardwareFault, {"车辆机械制动故障检测已关闭", "mechanicalBrakeHardwareFaultClose.wav"}},
    //    {leverSensorFault, {"车辆拉杆传感器故障", "systemFaultAttention.wav"}}
};

#define BITSET_LENGTH 8
#define BITSET_BYTE_LEN 32

class warnning
{
public:
    warnning();

    std::vector<std::bitset<BITSET_LENGTH>> warningVector = std::vector<std::bitset<BITSET_LENGTH>>(BITSET_BYTE_LEN);
    uint32_t status = 0;

private:
    int _getWarningBit(const std::bitset<BITSET_LENGTH> &_warn, std::vector<size_t> &outResult, int offset);

public:
    std::vector<size_t> getWarningBit();

    bool testWarning(enum WarningBit _bit);

    int loadFromRawData(QVector<unsigned char> rawData, int len);
};

#endif // WARNNING_H
