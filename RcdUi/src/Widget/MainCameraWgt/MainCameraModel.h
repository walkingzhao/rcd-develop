#ifndef MainCameraModel_H
#define MainCameraModel_H

#include "Interface/IModel.h"
#include <QVariant>
#include "public/fbsstructure.h"
class MainCameraModel : public IModel
{
    Q_OBJECT
public:
    explicit MainCameraModel(QObject *parent = nullptr);

    //void setVehicleRawData(VehicleRawData data);
    void setCameraUrl(const QString &front,const QString &back, const QString &front_left, const QString &front_right);
    void setCameraName(const QString &front,const QString &back);
    void setThrottleBrakeWheel(float throttle,float brake,float wheel);
    void setThrottle(float throttle);//加速踏板百分比
    void setBrake(int type, float brake);//刹车
    void setWheel(float wheel);//方向盘转角
    void setSpeedRaw(float wheel);//发动机转速
    void setSpeed(float speed);
    void setGear(float gear);
    void setParkingBrake(int brake);
    void setLoadingBrake(int brake);
    void setVehicleDelay(uint);
    void setRemoteStatus(uint);
    void setFlag(int flag);
    enum ModelCmdType
    {
        MC_UpdateAll=0,
        MC_ThrottleBrakeWheel,
        MC_Speed,
        MC_Gear,
        MC_Delay,
        MC_RemoteStatus,
        MC_Max,
        MC_Throttle,
        MC_Brake,
        MC_Wheel,
        MC_Throttle_RingDila,
        MC_Keyboard_msg, //弹出框键盘焦点
        MC_Parking,
        MC_Loading,
    };

    enum RemoteStatus{
        RS_Monitoring = 0,              //0,监控中
        RS_RemoteControl,               //1,远程控制
        RS_RemoteControlUnknownVehicle, //2,车辆未知 （找不到车）
        RS_RemoteControlDisconnect,     //3
        RS_RemoteConnectionRefused,     //4,车辆拒绝连接
        RS_RemoteConnectionTimedOut,    //5,车辆连接超时
        RS_RemoteControlFail            //6,控制失败
    };

    typedef struct
    {
        float   current;
        float   max;
        float   min;
    } CtrlType;

    CtrlType    m_throttle{0,0,0};
    CtrlType    m_brake{0,0,0};
    CtrlType    m_wheel{0,0,0};

    CtrlType    m_speed{0,0,0};

    int         m_gear{0};
    int         m_parking{0};
    int         m_loading{0};

    CtrlType    m_tachometer{0,0,0};
    CtrlType    m_speed_raw{0,0,0};//发动机转速
    QString     m_frontCameraUrl;
    QString     m_backCameraUrl;

    QString     m_front_left_CameraUrl;
    QString     m_front_right_cameraUrl;

    QString     m_frontCameraName;
    QString     m_backCameraName;

    uint        m_vehicleDelay{0};
    RemoteStatus        m_remoteStatus{RS_Monitoring};
    int _testKey;

    TrackLineCalibrationST m_TrackLineCfg;
    QString vehicleName;
    GPSInfoST m_GpsInfo;
    bool gpsAvailable=false;

    // --> BEGIN added by ZJZ, 2022/5/10
    int brakeType = 1;
    // <-- END
};

#endif // MainCameraModel_H
