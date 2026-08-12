#include "map_common.h"

bool MapCommon::relf_point_flag_ = false;

double MapCommon::utm_relf_x_ = 0;
double MapCommon::utm_relf_y_ = 0;
double MapCommon::utm_relf_z_ = 0;

double MapCommon::lld_relf_longitude_ = 0;
double MapCommon::lld_relf_latitude_ = 0;
double MapCommon::lld_relf_altitude_ = 0;

/* @brief:地图通用函数类
 * @param [in]: NONE
 * @param [out]: NONE
 * @return NONE
*/
MapCommon::MapCommon(void)
{
    std::cout<<"Create MapCommon"<<std::endl;

    //世界坐标系参考点，为第一个路径点
    relf_point_flag_ = false;
    utm_relf_x_ = 0;
    utm_relf_y_ = 0;
    utm_relf_z_ = 0;

    lld_relf_longitude_ = 0;
    lld_relf_latitude_ = 0;
    lld_relf_altitude_ = 0;

    //初始化LLA转UTM库
    initProj4();

    //点云和GPS/IMU输入循环缓冲区
    gps_imu_buffer_ptr_ = new boost::circular_buffer<GpsImuData> (GPS_IMU_QUE_LEN);

    gps_imu_buffer_ptr_->clear();

    max_time_syn_deta_ms_ = 80;
    time_syn_flag_ = false;
}

/* @brief:析构函数
 * @param [in]: NONE
 * @param [out]: NONE
 * @return NONE
*/
MapCommon::~MapCommon(void)
{
    pj_free(wgs84_);
    pj_free(utm_);
}


/* @brief:设置UTM坐标点为全局坐标系的参考点，全局坐标系内显示的其他坐标点由UTM坐标减去该参考点坐标
 * @param [in]: x,y,z-参考点的UTM坐标
 * @param [out]: NONE
 * @return NONE
 */
void MapCommon::setUTMRelfPoint(double x, double y, double z)
{
  if(true == relf_point_flag_)
  {
    std::cout<<"MapCommon: relf point has set."<<std::endl;
    return;
  }

  utm_relf_x_ = x;
  utm_relf_y_ = y;
  utm_relf_z_ = z;

  relf_point_flag_ = true;

  convertUTMToWGS84(x, y, z, &lld_relf_longitude_, &lld_relf_latitude_, &lld_relf_altitude_);
}

/* @brief:从文件中读取路径数据
 * @param [in]: path_str-路径数据路径及文件名
 * @param [out]: path_datas_ptr-读取的路径数据
 * @return:NONE
*/
void MapCommon::readPathFromFile(const string file_name_str, vector<GPSData> *out_datas_ptr)
{
  ifstream in_file(file_name_str.c_str(), ifstream::in);
  string line;
  
  string start_flag;
  int num;

  out_datas_ptr->clear();

  while (getline(in_file, line))
  {

    GPSData gps_data;

    for(int i=0;i<line.size();i++)
    {
      if(',' == line[i])
      {
        line[i] = ' ';
      }
    }

    istringstream iss(line);

    // reads first element from the current line
    iss >> start_flag;
    iss >> num;
    iss >> gps_data.heading;
    iss >> gps_data.latitude;
    iss >> gps_data.longitude;
    iss >> gps_data.altitude;

    out_datas_ptr->push_back(gps_data);
  }
}



/* @brief:proj4库初始化
 * @param [in]: NONE
 * @param [out]: NONE
 * @return NONE
*/
void MapCommon::initProj4(void)
{
	// 参数根据软件设置生成：http://epsg.io/32649
	wgs84_ = pj_init_plus("+proj=longlat +datum=WGS84 +no_defs ");
  utm_ = pj_init_plus("+proj=utm +zone=49 +datum=WGS84 +units=m +no_defs");
}

/* @brief:将WGS84地理坐标转换为UTM坐标
 * @param [in]: longitude latitude altitude-经纬高
 * @param [out]: ｘ y z－输入的UTM坐标
 * @return NONE
*/
void MapCommon::convertWGS84ToUTM(double longitude, double latitude, double altitude, double *x, double *y, double *z)
{
	longitude *= DEG_TO_RAD;
	latitude *= DEG_TO_RAD;

	pj_get_def(wgs84_, 0);
	pj_transform(wgs84_, utm_, 1, 1, &longitude, &latitude, &altitude);
	const char* strRelease = pj_get_release();

	char* strError = pj_strerrno(2);
	int iErrorNo = *pj_get_errno_ref();

	*x = longitude;
	*y = latitude;
	*z = altitude;
}

/* @brief:将UTM坐标转换为WGS84地理坐标
 * @param [in]: ｘ y z－输入的UTM坐标
 * @param [out]: longitude latitude altitude-经纬高
 * @return NONE
*/
void MapCommon::convertUTMToWGS84(double x, double y, double z, double *longitude, double *latitude, double *altitude)
{
	pj_get_def(wgs84_, 0);
	pj_transform(utm_, wgs84_, 1, 1, &x, &y, &z);
	const char* strRelease = pj_get_release();

	char* strError = pj_strerrno(2);
	int iErrorNo = *pj_get_errno_ref();

	*longitude = x*RAD_TO_DEG;
	*latitude = y*RAD_TO_DEG;
	*altitude = z;
}


/* @brief:计算相机旋转矩阵
 * @param [in]: ypr-yaw,pitch,roll 
 * @param [out]: NONE
 * @return Eigen::Matrix4d-旋转矩阵
 */
Eigen::Matrix3d MapCommon::set_R_transform(Eigen::Vector3d ypr)
{
    double yaw = ypr[0]/180.0*M_PI;
    double pitch=ypr[1]/180.0*M_PI;
    double roll=ypr[2]/180.0*M_PI;
    Eigen::Matrix3d transform_pitch;
    Eigen::Matrix3d transform_roll;
    Eigen::Matrix3d transform_yaw;
    //构建旋转矩阵
    transform_yaw << cos (yaw), -sin(yaw), 0, \
            sin (yaw),  cos (yaw), 0, \
            0,0,1;
    transform_pitch << 1, 0,0,  \
            0, cos(pitch), -sin(pitch),  \
            0, sin (pitch), cos (pitch);

    transform_roll << cos (roll),  0, sin(roll), \
            0,1,0,  \
            -sin (roll), 0, cos (roll);


    Eigen::Matrix3d transform_R = transform_yaw*transform_roll*transform_pitch;
    return transform_R;
}