#ifndef TRACKLINEPREDICT_H
#define TRACKLINEPREDICT_H

#include <math.h>
#include "../common/config_parser.hpp"
#include "public/fbsstructure.h"


#define POINTS_NUM 48
#define COLOR_SCALE (POINTS_NUM/12)
#define PI  3.1415926535898
#define DISTANCE_STEP 0.25

class TrackLinePredict
{
public:
    /* @brief: 构造函数
      * @param [in]: config_file_str-配置文件路径,back_mode-摄像头在车尾时true,摄像头在车头时false
      * @param [out]: NONE
      * @return NONE
      */
    TrackLinePredict(std::string config_file_str);
    ~TrackLinePredict();
    //倒车true还是前进false
    bool mode();

    /* @brief: 根据前轮转角计算轨迹
      * @param [in]: steer_rotate-前轮同水平方向的夹角,
      *              forward - 前进/后退标志
      *              xu_in - 内侧轮在屏幕上的x坐标
      *              yv_in - 内侧轮在屏幕上的y坐标
      *              xu_out - 外侧轮在屏幕上的x坐标
      *              yv_out - 外侧轮在屏幕上的y坐标
      * @param [out]: NONE
      * @return NONE
      */
    void computeTrackLine(double steer_rotate, bool backward, double xu_in[], double yv_in[],
                          double xu_out[], double yv_out[]);


    /* @brief: 获取摄像头分辨率
      * @param [in]: x-摄像头输出屏幕分辨率x方向,y-摄像头输出屏幕分辨率y方向
      * @param [out]: NONE
      * @return NONE
      */
    void getCameraXaY(double* x, double* y);
    void setCameraCfg(TrackLineCalibrationST &st);

private:
    /* @brief: 计算内侧车轮轨迹的x坐标
      * @param [in]: angle-前轮同水平方向的夹角,y-外侧车轮轨迹的y坐标参考值
      * @param [out]: NONE
      * @return double-内外侧车轮轨迹的x坐标
      */
    double ComputerXIn(double angle, double y);

    /* @brief: 计算外侧车轮轨迹的x坐标
      * @param [in]: angle-前轮同水平方向的夹角,y-内侧车轮轨迹的y坐标参考值
      * @param [out]: NONE
      * @return double-外侧车轮轨迹的x坐标
      */
    double ComputerXOut(double angle, double y);

    /* @brief: camera坐标系(相机位置为(0,0))转换到opencv像素坐标系(左上角为(0,0))
      * @param [in]:
      * x-相机坐标系的x坐标,朝右为正(m)
      * y-相机坐标系的y坐标,朝上为正(m)
      * u-opencv像素坐标系的u坐标,朝右为正(ppi)
      * v-opencv像素坐标系的v坐标,朝下为正(ppi)
      * @param [out]: NONE
      * @return NONE
      */
    void cameraXY2imageUV(double x,double y,double* u, double* v);


private:
    common::ConfigParserPtr config_parser_ptr_;//配置文件获取

    bool back_mode_ = true; //倒车轨迹为true，前进轨迹为false
    //前摄像头垂直可视角度
    double FovFrontCamera;
    double cameraAlphaFront = 0.0f; //摄像头上下方向张角的二分之一(单位：度)
    //后摄像头垂直可视角度
    double FovBackCamera;
    double cameraAlphaBack = 0.0f; //摄像头上下方向张角的二分之一(单位：度)

    //前摄像头中心线同水平面的夹角(度)
    double inclinationAngleFrontCamera;
    //后摄像头中心线同水平面的夹角(度)
    double inclinationAngleBackCamera;

    //前摄像头距离地面距离
    double heightFrontCamera;
    //后摄像头距离地面距离
    double heightBackCamera;

    //屏幕分辨率横向方向
    double screenWidth = 1920.0;
    //屏幕分辨率纵向方向
    double screenHeight = 1080.0;


    //前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）
    double offsetFrontCamera;
    //后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）
    double offsetBackCamera;

    //车头摄像头到车前轮中心的距离
    double distanceFrontCamera2Axles;
    //车尾摄像头到车后轮中心的距离
    double distanceBackCamera2Axles;

    //车前后轮的轴距
    double distanceAxles;

    //前车轮轴长
    double distanceFrontAxles;
    //后车轮轴长
    double distanceBackAxles;

    //方向盘最大转角
    double steerMaxAngle;
    //车轮最大转角
    double wheelMaxAngle;

    //车轮转角
    double rotate;

    //是否开启了后置摄像头镜像
    bool mirrorBackCameraFlag = false;

};

#endif // TRACKLINEPREDICT_H
