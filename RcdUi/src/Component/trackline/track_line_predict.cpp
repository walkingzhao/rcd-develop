#include "track_line_predict.h"
#include <QDebug>
#include <stdlib.h>
#include <string>
#include <QTransform>
#include <QMatrix4x4>
/* @brief: 构造函数
  * @param [in]: config_file_str-配置文件路径,back_mode-倒车后轮轨迹true,前进前轮轨迹false
  * @param [out]: NONE
  * @return NONE
  */
TrackLinePredict::TrackLinePredict(std::string config_file_str)
{
    back_mode_ = true;
#if 0
    config_parser_ptr_.reset(new common::ConfigParser(config_file_str));//读取配置文件
    //前摄像头垂直可视角度
    FovFrontCamera = config_parser_ptr_->getDouble("FovFrontCamera");
    //后摄像头垂直可视角度
    FovBackCamera = config_parser_ptr_->getDouble("FovBackCamera");

    cameraAlphaFront = FovFrontCamera/2;
    cameraAlphaBack = FovBackCamera/2;

    //前摄像头中心线同水平面的夹角(度)
    inclinationAngleFrontCamera = config_parser_ptr_->getDouble("inclinationAngleFrontCamera");
    //后摄像头中心线同水平面的夹角(度)
    inclinationAngleBackCamera = config_parser_ptr_->getDouble("inclinationAngleBackCamera");

    //前摄像头距离地面距离
    heightFrontCamera = config_parser_ptr_->getDouble("heightFrontCamera");
    //后摄像头距离地面距离
    heightBackCamera = config_parser_ptr_->getDouble("heightBackCamera");

    //屏幕分辨率横向方向
    screenWidth = config_parser_ptr_->getDouble("screenWidth");
    //屏幕分辨率纵向方向
    screenHeight = config_parser_ptr_->getDouble("screenHeight");


    //前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）
    offsetFrontCamera = config_parser_ptr_->getDouble("offsetFrontCamera");
    //后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）
    offsetBackCamera = config_parser_ptr_->getDouble("offsetBackCamera");

    //车头摄像头到车前轮中心的距离
    distanceFrontCamera2Axles = config_parser_ptr_->getDouble("distanceFrontCamera2Axles");
    //车尾摄像头到车后轮中心的距离
    distanceBackCamera2Axles = config_parser_ptr_->getDouble("distanceBackCamera2Axles");

    //车前后轮的轴距
    distanceAxles = config_parser_ptr_->getDouble("distanceAxles");

    //前车轮轴长
    distanceFrontAxles = config_parser_ptr_->getDouble("distanceFrontAxles");
    //后车轮轴长
    distanceBackAxles = config_parser_ptr_->getDouble("distanceBackAxles");

    //方向盘最大转角
    steerMaxAngle = config_parser_ptr_->getDouble("steerMaxAngle");
    //车轮最大转角
    wheelMaxAngle = config_parser_ptr_->getDouble("wheelMaxAngle");

    //是否开启了后置摄像头镜像
    mirrorBackCameraFlag = config_parser_ptr_->getBool("mirrorBackCameraFlag");
#endif

#if 0
    qDebug()<<"前摄像头垂直可视角度(度):"<<FovFrontCamera;

    qDebug()<<"后摄像头垂直可视角度(度):"<<FovBackCamera;

    qDebug()<<"前摄像头中心线同水平面的夹角(度):"<<inclinationAngleFrontCamera;
    qDebug()<<"后摄像头中心线同水平面的夹角(度):"<<inclinationAngleBackCamera;

    qDebug()<<"前摄像头距离地面距离:"<<heightFrontCamera;
    qDebug()<<"后摄像头距离地面距离:"<<heightBackCamera;



    qDebug()<<"屏幕分辨率横向方向:"<<screenWidth;

    qDebug()<<"屏幕分辨率纵向方向:"<<screenHeight;


    qDebug()<<"前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<offsetFrontCamera;
    qDebug()<<"后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<offsetBackCamera;

    qDebug()<<"车头摄像头到车前轮中心的距离:"<<distanceFrontCamera2Axles;
    qDebug()<<"车尾摄像头到车后轮中心的距离:"<<distanceBackCamera2Axles;

    qDebug()<<"车前后轮的轴距:"<<distanceAxles;

    qDebug()<<"前车轮轴长:"<<distanceFrontAxles;
    qDebug()<<"后车轮轴长:"<<distanceBackAxles;
#endif
}

TrackLinePredict::~TrackLinePredict(){}

/* @brief: 计算内侧车轮轨迹的x坐标
  * @param [in]: angle-前轮同水平方向的夹角,y-外侧车轮轨迹的y坐标参考值
  * @param [out]: NONE
  * @return double-内侧车轮轨迹的x坐标
  */
double TrackLinePredict::ComputerXIn(double angle, double y)
{
    double alpha;
    double Y2;
    double R2;
    double X2;
    double X1;
    double x;


    if(back_mode_)
    {
//        if(0.1 > angle)
//        {
//            x= -distanceBackAxles/2;
//            return x;
//        }
        alpha = cameraAlphaBack;
        R2 = pow(distanceAxles * 1/tan(angle) - distanceBackAxles / 2,2);
        Y2 = pow(y + distanceBackCamera2Axles,2);
        X2 = R2 - Y2;
        X1 = (double) pow(X2, 0.5);
        x = X1 - distanceAxles * 1 / tan(angle);
    }
    else
    {
//        if(0.1 > angle)
//        {
//            x= -distanceFrontAxles/2;
//            return x;
//        }
        alpha = cameraAlphaFront;
        R2 = pow(distanceAxles * 1/tan(angle) - distanceFrontAxles / 2,2) + pow(distanceAxles,2);
        Y2 = pow(y + distanceFrontCamera2Axles + distanceAxles,2);
        X2 = R2 - Y2;
        X1 = (double) pow(X2, 0.5);
        x = X1 - distanceAxles * 1 / tan(angle);
    }

//    if(isnan(x))
//    {
//        if(back_mode_)
//        {
//            x=-distanceBackAxles/2;
//        }else
//        {
//            x=-distanceFrontAxles/2;
//        }
//    }
    return x;
//    return (double) ((x * screenWidth) / ((pow((pow(y,2) + pow(screenHeight,2)), 0.5) * tan(alpha) * 2)));
}

/* @brief: 计算外侧车轮轨迹的x坐标
  * @param [in]: angle-前轮同水平方向的夹角,y-内侧车轮轨迹的y坐标参考值
  * @param [out]: NONE
  * @return double-外侧车轮轨迹的x坐标
  */
double TrackLinePredict::ComputerXOut(double angle, double y)
{
    double alpha;
    double R2;
    double Y2;
    double X2;
    double X1;
    double x;
    if(back_mode_)
    {
//        if(0.1 > angle)
//        {
//            x= distanceBackAxles/2;
//            return x;
//        }
        alpha = cameraAlphaBack;
        R2 = pow(distanceAxles * 1/tan(angle) + distanceBackAxles / 2,2);
        Y2 = pow(y + distanceBackCamera2Axles,2);
        X2 = R2 - Y2;
        X1 = (double) pow(X2, 0.5);
        x = X1 - distanceAxles * 1 / tan(angle);
    }
    else
    {
//        if(0.1 > angle)
//        {
//            x= distanceFrontAxles/2;
//            return x;
//        }
        alpha = cameraAlphaFront;
        R2 = pow(distanceAxles * 1/tan(angle) + distanceFrontAxles / 2,2)+pow(distanceAxles,2);
        Y2 = pow(y + distanceFrontCamera2Axles + distanceAxles,2);
        X2 = R2 - Y2;
        X1 = (double) pow(X2, 0.5);
        x = X1 - distanceAxles * 1 / tan(angle);
    }
//    if(isnan(x))
//    {
//        if(back_mode_)
//        {
//            x=distanceBackAxles/2;
//        }else
//        {
//            x=distanceFrontAxles/2;
//        }
//    }
    return x;
//    return (double) ((x * screenWidth) / ((pow((pow(y,2) + pow(screenHeight,2)), 0.5) * tan(alpha) * 2)));
}

/* @brief: camera坐标系(相机位置为(0,0))转换到opencv像素坐标系(左上角为(0,0))
  * @param [in]:
  * x-相机坐标系的x坐标,朝右为正(m)
  * y-相机坐标系的y坐标,朝上为正(m)
  * u-opencv像素坐标系的u坐标,朝右为正(ppi)
  * v-opencv像素坐标系的v坐标,朝下为正(ppi)
  * @param [out]: NONE
  * @return NONE
  */
void TrackLinePredict::cameraXY2imageUV(double x, double y, double *u, double *v)
{
#if 0
    double alpha;
    double beta;
    double h2;
    double actan;
    if(back_mode_)
    {
        alpha = cameraAlphaBack;
        beta = inclinationAngleBackCamera;
        actan = atan2(heightBackCamera,y);
        h2 = pow(heightBackCamera, 2);
    }
    else
    {
        alpha = cameraAlphaFront;
        beta = inclinationAngleFrontCamera;
        actan = atan2(heightFrontCamera,y);
        h2 = pow(heightFrontCamera, 2);
    }

    double y2 = pow(y, 2);

    double u_raw = x * screenWidth / pow(h2+y2, 0.5) / tan((alpha) * PI / 180) / 2;
    double v_raw = (sin((alpha +beta) * PI / 180 - actan)) * screenHeight / (cos((beta)* PI / 180 - actan)) / 2 / (sin((alpha) * PI / 180));

    *u = screenWidth/2 + u_raw;
    *v = screenHeight - v_raw;
#else
    double yaw = 0/180.0*M_PI;
    double pitch;
    if(back_mode_)
        pitch=-(90-inclinationAngleBackCamera)/180.0*M_PI;
    else
        pitch=-(90-inclinationAngleFrontCamera)/180.0*M_PI;
    double roll=0/180.0*M_PI;

    //构建旋转矩阵
    QVector<float> vec;
    vec<<1<< 0<<0<<
            0<< cos(pitch)<< -sin(pitch)<<
            0<< sin (pitch)<< cos (pitch);

    QMatrix3x3 transform_pitch(vec.data());
    transform_pitch=transform_pitch.transposed();

    vec.clear();
    vec<<cos (roll)<<  0<< sin(roll)<<
            0<<1<<0<<
            -sin (roll)<< 0<< cos (roll);
    QMatrix3x3 transform_roll(vec.data());
    transform_roll=transform_roll.transposed();

    vec.clear();
    vec<<cos (yaw)<< -sin(yaw)<< 0<<
            sin (yaw)<<  cos (yaw)<< 0<<
            0<<0<<1;
    QMatrix3x3 transform_yaw(vec.data());
    transform_yaw=transform_yaw.transposed();

    QMatrix3x3 transform_R = transform_pitch*transform_roll*transform_yaw;//transform_yaw*transform_roll*transform_pitch;

//    qDebug() <<"transform_pitch"<<transform_pitch;
//    qDebug() <<"transform_roll"<<transform_roll;
//    qDebug() <<"transform_yaw"<<transform_yaw;

//    qDebug()<<"transform_R"<<transform_R;

    //
    QMatrix4x4 O_matx(transform_R.transposed());
    QGenericMatrix<4,4,float> matrix4_R(O_matx.data());
//    qDebug()<<O_matx;
//    qDebug()<<"O_matx"<<matrix4_R;

    //inner com from camera.xml
//    1.1488178857055864e+03 0. 9.6555576380584660e+02 0.
//    1.1482078540815749e+03 5.3594470544776811e+02 0. 0. 1.
    vec.clear();
    vec <<1.1488178857055864e+03<< 0. <<9.6555576380584660e+02<<0
       <<0. <<1.1482078540815749e+03 <<5.3594470544776811e+02<<0
      <<0. <<0. <<1.<<0;

    QMatrix4x3 t(vec.data());
    QMatrix3x4 inner_matx_(t.data());
//    qDebug()<<"inner_matx31(3x4)"<<inner_matx_;

    //outer:1. 0. 0. 0. 0. 1. 0. 0. 0. 0. 1. 0. 0. 0. 0. 1.
    QGenericMatrix<4, 4, float> outer_matx_;
    outer_matx_.setToIdentity();
//    qDebug()<<"outer_matx_"<<outer_matx_;

    vec.clear();
    if(back_mode_)
        vec <<x<<-y<<heightBackCamera<<1;
    else
        vec <<x<<-y<<heightFrontCamera<<1;
    QGenericMatrix<4,1,float> M_workpoint(vec.data());
//    qDebug()<<"M_workpoint"<<M_workpoint;

    QGenericMatrix<3,1,float> imagepoint=M_workpoint*matrix4_R*outer_matx_*inner_matx_;
//    qDebug()<<"imagePoint"<<imagePoint;
    if(back_mode_)
    {
        *u = imagepoint.data()[0]/(-sin(pitch)*y+cos (pitch)*heightBackCamera);
        *v = imagepoint.data()[1]/(-sin(pitch)*y+cos (pitch)*heightBackCamera);
    }else
    {
        *u = imagepoint.data()[0]/(-sin(pitch)*y+cos (pitch)*heightFrontCamera);
        *v = imagepoint.data()[1]/(-sin(pitch)*y+cos (pitch)*heightFrontCamera);
    }
#endif
}

bool TrackLinePredict::mode()
{
    return back_mode_;
}

/* @brief: 根据前轮转角计算轨迹
  * @param [in]: steer_rotate-前轮同水平方向的夹角,
  *              xu_in - 内侧轮在屏幕上的x坐标
  *              yv_in - 内侧轮在屏幕上的y坐标
  *              xu_out - 外侧轮在屏幕上的x坐标
  *              yv_out - 外侧轮在屏幕上的y坐标
  * @param [out]: NONE
  * @return NONE
  */
void TrackLinePredict::computeTrackLine(double steer_rotate,  bool backward, double xu_in[], double yv_in[],double xu_out[], double yv_out[])
{
    back_mode_ = backward;

    rotate = steer_rotate/steerMaxAngle*wheelMaxAngle;

//    qDebug()<<"车轮转角："<<rotate<<"向后："<<back_mode_;

    if(mirrorBackCameraFlag&&back_mode_)//后置摄像头左右镜像
    {
        rotate = -rotate;
    }else if(false==back_mode_)
    {
        rotate = -rotate;
    }
    if(rotate<0.001 && rotate>-0.001)
    {
        rotate = 0.001;
    }

    qDebug()<<"屏幕计算用车轮转角："<<rotate<<"向后："<<back_mode_;


//    for(int i=0;i<24+1;i++)
    for(int i=0;i<POINTS_NUM;i++)
    {
        double x_in =0.0,y_in=0.0,Xr_in=0.0,Yr_in=0.0;
        double x_out=0.0,y_out=0.0,Xr_out=0.0,Yr_out=0.0;

        //pre defined y
        y_in = y_out = + i*DISTANCE_STEP;
        //anti-clockwise
        if(rotate < 0.0)
        {
            //compute trajectory of inner wheel
            x_in = -ComputerXIn((-rotate) * PI / 180,y_in);

            //compute trajectory of outer wheel
            x_out = -ComputerXOut((-rotate) * PI / 180,y_out);
        }
        //clockwise
        else// if(rotate >= 0.0)
        {
            //compute trajectory of inner wheel
            x_in = ComputerXIn((rotate) * PI / 180,y_in);

            //compute trajectory of outer wheel
            x_out = ComputerXOut((rotate) * PI / 180,y_out);
        }

        //convert camera XYcoordinate to image UVcoordinate
        if(false == back_mode_)//前进
        {
            cameraXY2imageUV(x_in+offsetFrontCamera, y_in, &Xr_in, &Yr_in);
            cameraXY2imageUV(x_out+offsetFrontCamera, y_out, &Xr_out, &Yr_out);
        }
        else
        {
            cameraXY2imageUV(-x_in+offsetBackCamera, y_in, &Xr_in, &Yr_in);
            cameraXY2imageUV(-x_out+offsetBackCamera, y_out, &Xr_out, &Yr_out);
        }
        xu_in[i] = Xr_in;
        yv_in[i] =Yr_in;
        xu_out[i] =  Xr_out;
        yv_out[i] = Yr_out;
    }
}


/* @brief: 获取摄像头分辨率
  * @param [in]: x-摄像头输出屏幕分辨率x方向,y-摄像头输出屏幕分辨率y方向
  * @param [out]: NONE
  * @return NONE
  */
void TrackLinePredict::getCameraXaY(double *x, double *y)
{
    *x = screenWidth;
    *y = screenHeight;
}

void TrackLinePredict::setCameraCfg(TrackLineCalibrationST &st)
{
    qDebug()<<"setCameraCfg:"<<st.valid<<st.counter;
    if(st.valid && (st.counter==0))
    {
        st.counter++;
        //前摄像头垂直可视角度
        FovFrontCamera = st.FovFrontCamera;
        //后摄像头垂直可视角度
        FovBackCamera = st.FovBackCamera;

        cameraAlphaFront = FovFrontCamera/2;
        cameraAlphaBack = FovBackCamera/2;


        //前摄像头中心线同水平面的夹角(度)
        inclinationAngleFrontCamera = st.inclinationAngleFrontCamera;
        //后摄像头中心线同水平面的夹角(度)
        inclinationAngleBackCamera = st.inclinationAngleBackCamera;

        //前摄像头距离地面距离
        heightFrontCamera = st.heightFrontCamera;
        //后摄像头距离地面距离
        heightBackCamera = st.heightBackCamera;

        //屏幕分辨率横向方向
        screenWidth = st.screenWidth;
        //屏幕分辨率纵向方向
        screenHeight = st.screenHeight;


        //前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）
        offsetFrontCamera = st.offsetFrontCamera;
        //后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）
        offsetBackCamera = st.offsetBackCamera;

        //车头摄像头到车前轮中心的距离
        distanceFrontCamera2Axles = st.distanceFrontCamera2Axles;
        //车尾摄像头到车后轮中心的距离
        distanceBackCamera2Axles = st.distanceBackCamera2Axles;

        //车前后轮的轴距
        distanceAxles = st.distanceAxles;

        //前车轮轴长
        distanceFrontAxles = st.distanceFrontAxles;
        //后车轮轴长
        distanceBackAxles = st.distanceBackAxles;

        //方向盘最大转角
        steerMaxAngle = st.steerMaxAngle;
        //车轮最大转角
        wheelMaxAngle = st.wheelMaxAngle;

        //是否开启了后置摄像头镜像
        mirrorBackCameraFlag = st.mirrorBackCameraFlag;

#if 1
    qDebug()<<"方向盘最大转角："<<steerMaxAngle;
    qDebug()<<"车轮最大转角："<<wheelMaxAngle;
    if(wheelMaxAngle>=steerMaxAngle)
        qDebug()<<"请查看方向盘/车轮最大转角参数是否正确";


    qDebug()<<"前摄像头垂直可视角度(度):"<<FovFrontCamera;

    qDebug()<<"后摄像头垂直可视角度(度):"<<FovBackCamera;

    qDebug()<<"前摄像头中心线同水平面的夹角(度):"<<inclinationAngleFrontCamera;
    qDebug()<<"后摄像头中心线同水平面的夹角(度):"<<inclinationAngleBackCamera;

    qDebug()<<"前摄像头距离地面距离:"<<heightFrontCamera;
    qDebug()<<"后摄像头距离地面距离:"<<heightBackCamera;



    qDebug()<<"屏幕分辨率横向方向:"<<screenWidth;

    qDebug()<<"屏幕分辨率纵向方向:"<<screenHeight;


    qDebug()<<"前摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<offsetFrontCamera;
    qDebug()<<"后摄像头相对于车头中心横向偏移（镜头视角，左负，右正）:"<<offsetBackCamera;

    qDebug()<<"车头摄像头到车前轮中心的距离:"<<distanceFrontCamera2Axles;
    qDebug()<<"车尾摄像头到车后轮中心的距离:"<<distanceBackCamera2Axles;

    qDebug()<<"车前后轮的轴距:"<<distanceAxles;

    qDebug()<<"前车轮轴长:"<<distanceFrontAxles;
    qDebug()<<"后车轮轴长:"<<distanceBackAxles;
#endif
    }
}

