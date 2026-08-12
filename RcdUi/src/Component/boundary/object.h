#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>


namespace common {

typedef struct{
  long timestamp;
  double longitude;//经度
  double latitude;//纬度
  double altitude;//高程
  double heading;//航向角
}GPSData;

typedef struct{
  long timestamp;
  float yaw;//航向角
  float pitch;//俯仰角
  float roll;//翻滚角
}IMUData;

typedef struct{
  long timestamp;
  GPSData gps_data;
  IMUData imu_data;
}GpsImuData;

typedef struct{
  double x;
  double y;
  double z;
  int intensity;
}XYZI;

typedef struct{
  double x;
  double y;
}XY;





}//namespace common
#endif // OBJECT_H
