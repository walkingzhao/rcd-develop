#ifndef LaneDisplay_H
#define LaneDisplay_H

#include "object.h"
#include "map_common.h"
#include "../common/config_parser.hpp"
#include "public/fbsstructure.h"

using namespace std;
using namespace common;

class LaneDisplay
{
public:
     LaneDisplay(string config_str);
    ~LaneDisplay();

    /* @brief:加载激光坐标系转GPS坐标系的相关参数
     * @param [in]: NONE
     * @param [out]: NONE
     * @return NONE
     */
    void loadPara();

    void path2UTM();

    void initRelfPoint(GPSInfoST gpsimu);

    void computeLaneUV(GPSInfoST gpsimu, vector<XY>* left_path,
                      vector<XY>* right_path, vector<XY>* center_path);

    XY xyz2uv(XYZI XYZI);


private:
    string config_file_str_;
    Eigen::Vector3d YPR_,T_;//lidar与GPS坐标转换的外参
    ConfigParserPtr config_parser_ptr_;//配置文件获取
    string file_path_lidar_,file_path_image_,file_path_GNSS_IMU_,file_path_GPStrajectory1_,file_path_GPStrajectory2_;//配置文件路径
    vector<GPSData> path_data1_,path_data2_; //左右行驶路径点
    vector<Eigen::Vector3d> path_UTM1_,path_UTM2_;
    Eigen::Matrix3d R_lidar_;

    MapCommonPtr map_common_ptr_;
};


#endif // LaneDisplay_H
