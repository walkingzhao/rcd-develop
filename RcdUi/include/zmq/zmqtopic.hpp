/**
 * @file zmqtopic.hpp
 * @author lujiefeng
 * @brief 
 * @version 0.1
 * @date 2020-08-21
 * 
 * @copyright Copyright () 2020
 * 
 */

#pragma once

#define ZMQ_TOPIC_ALL ""

#define ZMQ_TOPIC_CONTROL_RAW_DATA "ControlRawData"     //方向盘
#define ZMQ_TOPIC_CONTROL_DATA "ControlData"            //驾驶舱控制数据

#define ZMQ_TOPIC_CONTROL_DEVLINKSTATUS "ControlDevLinkStatus"
#define ZMQ_TOPIC_BUTTON    "ControlButton"
#define ZMQ_TOPIC_SELF_CHECK_STATUS "SelfCheckStatus"

#define ZMQ_TOPIC_TAKEOVER_TASK_GEVE_UP  "TakeoverTaskGiveUp" // ui -> platform
#define ZMQ_TOPIC_TAKEOVER_TASK_REQ     "TakeoverTaskReq"  // ui -> platform
#define ZMQ_TOPIC_TAKEOVER_TASK_REPLY "TakeoverTaskReply" // ui -> platform
#define ZMQ_TOPIC_TAKEOVER_TASK_CANCEL "TakeoverTaskCancel" // platform -> ui/vehicle
#define ZMQ_TOPIC_TAKEOVER_TASK_END    "TakeoverTaskEnd" // ui -> platform/vehicle
#define ZMQ_TOPIC_TAKEOVER_TASK_FAIL    "TakeoverTaskFail" // ui- > platform/vehicle
#define ZMQ_TOPIC_TAKEOVER_TASK_OPERATE "TakeoverTaskOperate"

#define ZMQ_TOPIC_REQ_REMOTE_CONTROL "ReqRemoteControl"     //请求遥控
#define ZMQ_TOPIC_RESP_REMOTE_CONTROL "RespRemoteControl"   //遥控返回结果

#define ZMQ_TOPIC_VEHICLE_STATUS "VehicleStatus"
#define ZMQ_TOPIC_VEHICLE_RAWDATA "VehicleRawData"

#define ZMA_TOPIC_VEHICLE_DELAY "Ping"

#define ZMQ_TOPIC_REPORT_GPS_DATA "GpsData"
#define ZMQ_TOPIC_REQ_SEND_HMIMSG "ReqSendHmiMsg"
#define ZMQ_TOPIC_REPORT_HMI_HINT_MSG "ReportHmiHintMsg"
#define ZMQ_TOPIC_REPORT_TRACK_LINE_MSG "ReportTrackLineMsg"
#define ZMQ_TOPIC_REPORT_TRACK_LINE_MSG_REQ "ReportTrackLineMsgReq"
#define ZMQ_TOPIC_REPORT_ROAD_TASK_INFO "ReportRoadTaskInfo"
#define ZMQ_TOPIC_REPORT_SPEED_WARNING_MSG "ReportSpeedWarningMsg"

#define ZMQ_TOPIC_CLOUD_FBS_MSG "CloudMsg"
#define ZMQ_TOPIC_CLOUD_SEND_TASK_AUTH_INFO "CloudSendTaskAuthInfo"
#define TOPIC_HMI_HINTMSG_TO_RCD            "HintMsgToRcd"

#define ZMQ_TOPIC_IC_CARD_STATUS "IcCardStatus"
#define ZMQ_TOPIC_REMOTE_ESTOP "RemoteEstop"
#define ZMQ_TOPIC_FAST_STOP_REQ "FastStopReq"
#define ZMQ_TOPIC_SAFE_DECELERATION "SafeDeceleration"

#define ZMQ_TOPIC_REQ_CONNECT "ReqConnect"
