#ifndef TRANKLINEW_H
#define TRANKLINEW_H

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/types_c.h>
#include "track_line_predict.h"
#include <qpainter.h>
#include <QPaintEvent>
#include <QWidget>
#include <QVector>

#include <math.h>
#include <unistd.h>

#include "public/fbsstructure.h"

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

#define FRONT_MODE false
#define BACK_MODE true
#define OPEN_CV_TRACK_LINE 0
#define QT_PAINT_TRACK_LINE 1

#define WHEEL_ANGLE_MAX 35
#define WHEEL_ANGLE_MIN -35
#define STEERING_WHEEL_MAX 540
#define STEERING_WHEEL_MIN -540

namespace Ui {
class trankLineW;
}

class trankLineW : public QWidget
{
    Q_OBJECT

public:
    explicit trankLineW(QWidget *parent = nullptr);
    ~trankLineW();
    /* @brief: 在QLabel上显示预测车轮轨迹
      * @param [in]: rotate-旋转角度(-90~90度),正顺时针，负逆时针
      * @param [out]: NONE
      * @return NONE
      * @param [in]::forward:true R档，false D档或其他
      */
    void trackLineShow(double rotate,bool backward,TrackLineCalibrationST &st);
protected:
#if QT_PAINT_TRACK_LINE
    void paintEvent(QPaintEvent *event) ;
#endif
private:
#if OPEN_CV_TRACK_LINE
    /* @brief: 将opencv图像贴在QLable上显示
      * @param [in]: image-opencv图像,scaled-图像缩小比例
      * @param [out]: NONE
      * @return NONE
      */
    void image2QImage(cv::Mat image,int scaled);
#endif
    /* @brief: 在opencv图像上绘制点
      * @param [in]: m-摄像头纵向距离,image_in-opencv输入图像,u-点的像素u坐标,v-点的像素v坐标,image_out-opencv输出图像
      * @param [out]: NONE
      * @return NONE
      */
    //    void PlotPoint(int y_m,cv::Mat image_in,double u,double v,cv::Mat* image_out);

#if OPEN_CV_TRACK_LINE
    void PlotLine(cv::Mat image_in,std::vector<cv::Point> plot_points,const cv::Scalar& color, cv::Mat* image_out);
    //    void addTransparency(cv::Mat &mat);
    //    QImage getTransImage(QImage image , QPoint ponit);
    //    cv::Mat QImage2cvMat(QImage image);
#endif
    void PlotLine(std::vector<QPointF> &plot_points);
private:
    Ui::trankLineW *ui;


    double cameraX_; //摄像头输出屏幕分辨率x方向
    double cameraY_; //摄像头输出屏幕分辨率y方向
    TrackLinePredict *track_line_ptr_; // 车道线输出点算法

    double *get_x_in_;  //获取内侧轮在屏幕上的x坐标数组
    double *get_y_in_;  //获取内侧轮在屏幕上的y坐标数组
    double *get_x_out_; //获取外侧轮在屏幕上的x坐标数组
    double *get_y_out_; //获取外侧轮在屏幕上的y坐标数组

    QPen m_pen;
    QPointF m_left[POINTS_NUM];
    QPointF m_right[POINTS_NUM];
    QPointF m_left_red[8];
    QPointF m_right_red[8];
    QPointF m_left_yellow[8];
    QPointF m_right_yellow[8];
    QPointF m_left_green[8];
    QPointF m_right_green[8];
    QPainter m_painter;
    QPointF _red_left,_red_right;
    QPointF _yellow_left,_yellow_right;
    QPointF _green_left,_green_right;
    std::vector<QPointF> _points_in_red,_points_out_red;
    std::vector<QPointF> _points_in_yellow,_points_out_yellow;
    std::vector<QPointF> _points_in_green,_points_out_green;
};

#endif // TRANKLINEW_H
