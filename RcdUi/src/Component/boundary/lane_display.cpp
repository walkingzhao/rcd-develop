#include "lane_display.h"

LaneDisplay::LaneDisplay(string config_str):config_file_str_(config_str)
{
    loadPara();
    path2UTM();
}

/* @brief:加载激光雷达-摄像头内外参,激光雷达-IMU/GPS外参
* @param [in]: NONE
* @param [out]: NONE
* @return NONE
*/
void LaneDisplay::loadPara()
{
    //激光雷达-IMU/GPS外参
    config_parser_ptr_.reset(new ConfigParser(config_file_str_));//读取配置文件
    //安装参数
    YPR_[0] = config_parser_ptr_->getDouble("Yaw");
    YPR_[1] = config_parser_ptr_->getDouble("Pitch");
    YPR_[2] = config_parser_ptr_->getDouble("Roll");
    T_[0]  =  config_parser_ptr_->getDouble("Tx");
    T_[1]  =  config_parser_ptr_->getDouble("Ty");
    T_[2]  =  config_parser_ptr_->getDouble("Tz");

    file_path_GPStrajectory1_ = config_parser_ptr_->getString("path_GPStrajectory1");
    file_path_GPStrajectory2_ = config_parser_ptr_->getString("path_GPStrajectory2");

    map_common_ptr_.reset(new MapCommon());

    cout<< "LaneDisplay:" << file_path_GPStrajectory1_ << endl;
}

void LaneDisplay::path2UTM()
{
    vector<GPSData> path_data1,path_data2;
    Eigen::Vector3d path_gps,path_utm;

    map_common_ptr_->readPathFromFile(file_path_GPStrajectory1_, &path_data1);
    map_common_ptr_->readPathFromFile(file_path_GPStrajectory2_, &path_data2);

    path_UTM1_.reserve(path_data1.size());//预留空间
    path_UTM2_.reserve(path_data2.size());

    for(int i=0;i<path_data1.size();i++)
    {
        path_gps<<path_data1[i].longitude,path_data1[i].latitude,path_data1[i].altitude;
        map_common_ptr_->convertWGS84ToUTM(path_gps[0],path_gps[1],path_gps[2],
                                           &path_utm[0],&path_utm[1],&path_utm[2]);
        path_UTM1_.push_back(path_utm);
    }
    for(int i=0;i<path_data2.size();i++)
    {
        path_gps<<path_data2[i].longitude,path_data2[i].latitude,path_data2[i].altitude;
        map_common_ptr_->convertWGS84ToUTM(path_gps[0],path_gps[1],path_gps[2],
                                           &path_utm[0],&path_utm[1],&path_utm[2]);

        path_UTM2_.push_back(path_utm);
    }

    R_lidar_ = map_common_ptr_->set_R_transform(YPR_); //计算旋转矩阵
}

void LaneDisplay::initRelfPoint(GPSInfoST gpsimu)
{
    Eigen::Vector3d gps;
    gps<<gpsimu.gps_lng,gpsimu.gps_lat,gpsimu.height;
    Eigen::Vector3d UTM_first;//车辆第一个UTM坐标
    map_common_ptr_->convertWGS84ToUTM(gps[0],gps[1],gps[2],
                                    &UTM_first[0],&UTM_first[1],&UTM_first[2]);

    double relf_x,relf_y,relf_z;
    double world_x, world_y, world_z;

    relf_x = UTM_first(0,0);
    relf_y = UTM_first(1,0);
    relf_z = UTM_first(2,0);

    map_common_ptr_->setUTMRelfPoint(relf_x, relf_y, relf_z);
}

void LaneDisplay::computeLaneUV(GPSInfoST gpsimu, vector<XY>* left_path,
                               vector<XY>* right_path, vector<XY>* center_path)
{
    Eigen::Vector3d gps,imu;
    Eigen::Vector3d UTM_now;//车辆当前UTM坐标
    Eigen::Matrix3d R_IMU_now;
    vector<Eigen::Vector3d> candidate_path; //左右路径点
    Eigen::Vector3d L;
    XYZI XYZI,XYZI_L,XYZI_R;

    left_path->clear();
    right_path->clear();
    center_path->clear();

    gps<<gpsimu.gps_lng,gpsimu.gps_lat,gpsimu.height;
    imu<<(-gpsimu.gps_heading),gpsimu.gps_pitch,gpsimu.gps_roll;

    map_common_ptr_->convertWGS84ToUTM(gps[0],gps[1],gps[2],
                                        &UTM_now[0],&UTM_now[1],&UTM_now[2]);
    R_IMU_now = map_common_ptr_->set_R_transform(imu);

    int count=0;
    int near_count=0;

    for (int j=0;j<path_UTM2_.size();j++)
    {
        if (abs(path_UTM2_[j][0]-UTM_now[0])<0.55&&abs(path_UTM2_[j][1]-UTM_now[1])<0.55)
        {
            near_count++;
        }
        if ( near_count!=0)//找到当前定位
        {
            candidate_path.push_back(path_UTM2_[j]);
            count++;
        }
    }

    for (int j=0; j<candidate_path.size();j++)
    {
        L = R_lidar_.transpose()*(R_IMU_now.transpose()*(candidate_path[j]-UTM_now)-T_);//轨迹的点云  转置=逆
        XYZI.x =L[0];
        XYZI.y =L[1];
        XYZI.z =L[2];
        XYZI.intensity =10000;//路径点云标识

        XYZI_L.x =L[0]-3;
        XYZI_L.y =L[1];
        XYZI_L.z =L[2];
        XYZI_L.intensity =20000;//边界点云标识

        XYZI_R.x =L[0]+3;
        XYZI_R.y =L[1];
        XYZI_R.z =L[2];
        XYZI_R.intensity =20000;//边界点云标识

        center_path->push_back(xyz2uv(XYZI));//添加路径点云
        left_path->push_back(xyz2uv(XYZI_L));//添加边界点点云
        right_path->push_back(xyz2uv(XYZI_R));//添加边界点点云
    }

}

XY LaneDisplay::xyz2uv(XYZI XYZI)
{
    XY uv;

    Eigen::MatrixXd inner_matx;
    inner_matx.resize(3,4);
    inner_matx << 1.8382801004280007e+03, 0, 3.2953681174273692e+02, 0,
                    0, 2.4448384227157680e+03, 2.8675479502629912e+02, 0,
                    0, 0, 1, 0;
    Eigen::MatrixXd outer_matx;
    outer_matx.resize(4,4);
    outer_matx <<     9.9880613734143409e-01, 0, -4.8849769795613264e-02, 0,
    -6.8204929541208412e-04, 9.9990252400930424e-01,
    -1.3945511413406204e-02, 8.9999999999999997e-02,
    4.8845008115907175e-02, 1.3962180339145272e-02, 9.9870877772368372e-01,
    2.7099999999999880e+00, 0, 0, 0, 1;

    Eigen::MatrixXd M_wordpoint;
    M_wordpoint.resize(4,1);
    M_wordpoint << XYZI.x,-XYZI.z,XYZI.y,1;
    Eigen::MatrixXd imagepoint = inner_matx*outer_matx*M_wordpoint;
    uv.x = imagepoint(0, 0)/XYZI.y;
    uv.y = imagepoint(1, 0)/XYZI.y;
    return uv;
}

LaneDisplay::~LaneDisplay()
{

}
