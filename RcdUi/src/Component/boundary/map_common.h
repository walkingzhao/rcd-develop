#ifndef MAP_COMMON_HEAD_
#define MAP_COMMON_HEAD_


#include <iostream>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <boost/circular_buffer.hpp> 
#include <fstream>
#include <vector>
#define ACCEPT_USE_OF_DEPRECATED_PROJ_API_H
#include <proj_api.h>

#include "object.h"

using namespace std;
using namespace common;

#define CLOUD_QUE_LEN       5
#define GPS_IMU_QUE_LEN     50//GPS IMU数据缓冲区长度

class MapCommon{
public:
    /* @brief:地图相关通用函数类
     * @param [in]: NONE
     * @param [out]: NONE
     * @return NONE
    */
    MapCommon(void);

    /* @brief:析构函数
     * @param [in]: NONE
     * @param [out]: NONE
     * @return NONE
    */
    ~MapCommon(void);
    
    /* @brief:设置UTM坐标点为全局坐标系的参考点，全局坐标系内显示的其他坐标点由UTM坐标减去该参考点坐标
     * @param [in]: x,y,z-参考点的UTM坐标
     * @param [out]: NONE
     * @return NONE
     */
    void setUTMRelfPoint(double x, double y, double z);

   /* @brief:从文件中读取路径数据
    * @param [in]: path_str-路径数据路径及文件名
    * @param [out]: path_datas_ptr-读取的路径数据
    * @return:NONE
    */
    void readPathFromFile(const string file_name_str, vector<GPSData> *out_datas_ptr);

    /* @brief:proj4库初始化
     * @param [in]: NONE
     * @param [out]: NONE#include <thread>
    */
    void initProj4(void);

    /* @brief:将WGS84地理坐标转换为UTM坐标
     * @param [in]: longitude latitude altitude-经纬高
     * @param [out]: ｘ y z－输入的UTM坐标
     * @return NONE
    */
    void convertWGS84ToUTM(double longitude, double latitude, double altitude, double *x, double *y, double *z);

    /* @brief:将UTM坐标转换为WGS84地理坐标
     * @param [in]: ｘ y z－输入的UTM坐标
     * @param [out]: longitude latitude altitude-经纬高
     * @return NONE
    */
    void convertUTMToWGS84(double x, double y, double z, double *longitude, double *latitude, double *altitude);

    /* @brief:计算相机旋转矩阵
    * @param [in]: ypr-yaw,pitch,roll 
    * @param [out]: NONE
    * @return Eigen::Matrix4d-旋转矩阵
    */
    Eigen::Matrix3d set_R_transform(Eigen::Vector3d ypr);


private:
    //世界坐标参考点，以装载区->卸载区第一个点为参考点
    static bool relf_point_flag_;
    static double utm_relf_x_;
    static double utm_relf_y_;
    static double utm_relf_z_;

    static double lld_relf_longitude_;
    static double lld_relf_latitude_;
    static double lld_relf_altitude_;

    projPJ wgs84_;
    projPJ utm_;

    std::mutex in_cloud_mutex_;//设置输出点云和输入点云读取时的互斥锁
    std::mutex in_gps_imu_mutex_;//设置GPS/IMU输入和读取时的互斥锁

    //输入的点云和GPS/IMU数据循环缓冲区
    boost::circular_buffer<GpsImuData> *gps_imu_buffer_ptr_;//输入的GPS/IMU循环缓冲区

    int max_time_syn_deta_ms_;//时间同步，时间差最大值，ms单位

    std::condition_variable time_syn_condvar_;
    bool time_syn_flag_;
};

typedef boost::shared_ptr<MapCommon>  MapCommonPtr;
#endif
