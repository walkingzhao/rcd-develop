#include "MainCameraModel.h"
//#include "../include/can/canraw.hpp"
#include <QDebug>

MainCameraModel::MainCameraModel(QObject *parent) : IModel(parent)
{
    m_frontCameraUrl = QLatin1String("");
    m_backCameraUrl = QLatin1String("");
    m_front_left_CameraUrl = QLatin1String("");
    m_front_right_cameraUrl = QLatin1String("");
    m_frontCameraName="";
    m_backCameraName="";

    m_TrackLineCfg.valid = false;
    m_TrackLineCfg.counter = 0;

    m_throttle.max = 100;
    m_throttle.min = 0;

    m_brake.max = 100;
    m_brake.min = 0;

    m_wheel.max = 800;
    m_wheel.min = -800;
//    m_wheel.max = 720;
//    m_wheel.min = -720;

    //    m_speed.max = 50;
    //    m_speed.min = 0;
    m_speed.max = 45;
    m_speed.min = 0;
}


void MainCameraModel::setCameraUrl(const QString &front,const QString &back, const QString &front_left, const QString &front_right)
{
    m_frontCameraUrl = front;
    m_backCameraUrl = back;

    m_front_left_CameraUrl = front_left;
    m_front_right_cameraUrl = front_right;
}

void MainCameraModel::setCameraName(const QString &front, const QString &back)
{
    m_frontCameraName = front;
    m_backCameraName = back;

}

void MainCameraModel::setThrottleBrakeWheel(float throttle,float brake,float wheel)
{
    m_throttle.current = throttle;
    m_brake.current = brake;
    m_wheel.current = wheel;
    emit sendModelUpdate(MC_ThrottleBrakeWheel);
}
void MainCameraModel::setThrottle(float throttle)//加速踏板百分比
{
    m_throttle.current = throttle;
    emit sendModelUpdate(MC_Throttle);
}
void MainCameraModel::setBrake(int type, float brake)//刹车
{
    // --> BEGIN added by ZJZ, 2022/5/10
    brakeType = type;
    // <-- END

    m_brake.current = brake;
    emit sendModelUpdate(MC_Brake);
}
void MainCameraModel::setWheel(float wheel)//方向盘转角
{
    m_wheel.current = wheel;
    emit sendModelUpdate(MC_Wheel);
}
void MainCameraModel::setSpeed(float speed)
{
    m_speed.current = speed;
    emit sendModelUpdate(MC_Speed);
}
void MainCameraModel::setSpeedRaw(float speed)
{
    m_speed_raw.current = speed;
    emit sendModelUpdate(MC_Throttle_RingDila);
}

void MainCameraModel::setParkingBrake(int brake)
{
    m_parking = brake;
    emit sendModelUpdate(MC_Parking);
}

void MainCameraModel::setLoadingBrake(int brake)
{
    m_loading = brake;
    emit sendModelUpdate(MC_Loading);
}

void MainCameraModel::setGear(float gear)
{
//    if(m_gear != static_cast<int>(gear))
    {
        m_gear = gear;
        emit sendModelUpdate(MC_Gear);
    }
}

void MainCameraModel::setVehicleDelay(uint delay)
{
    m_vehicleDelay = delay;
    emit sendModelUpdate(MC_Delay);
}

void MainCameraModel::setRemoteStatus(uint status)
{
    m_remoteStatus = static_cast<RemoteStatus>(status);
    emit sendModelUpdate(MC_RemoteStatus);
}

