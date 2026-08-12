#include "trankLineW.h"
#include "ui_trankLineW.h"
#include <QtDebug>
#include <iostream>
trankLineW::trankLineW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trankLineW)
{
    ui->setupUi(this);
    get_x_in_ = new double[POINTS_NUM];  //获取内侧轮在屏幕上的x坐标数组
    get_y_in_ = new double[POINTS_NUM];  //获取内侧轮在屏幕上的y坐标数组
    get_x_out_ = new double[POINTS_NUM]; //获取外侧轮在屏幕上的x坐标数组
    get_y_out_ = new double[POINTS_NUM]; //获取外侧轮在屏幕上的y坐标数组
    std::string path = QString(QApplication::applicationDirPath()+"/trackline_config.txt").toStdString();
    track_line_ptr_ = new TrackLinePredict(path);  //摄像头放置车头的情况
    track_line_ptr_->getCameraXaY(&cameraX_, &cameraY_);  //摄像头输出屏幕分辨率
    m_pen = QPen(QColor(239, 41, 41), 5);
//    trackLineShow(0); //绘制初始轨迹线

#if OPEN_CV_TRACK_LINE
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
#endif
}

trankLineW::~trankLineW()
{
    delete ui;
}
#if QT_PAINT_TRACK_LINE
void trankLineW::paintEvent(QPaintEvent *)
{

    m_painter.begin(this);
    if(track_line_ptr_->mode()){

        m_pen = QPen(Qt::red);
        m_pen.setWidth(7);
        m_painter.setPen(m_pen);

        if((!_red_left.isNull()) && (!_red_right.isNull()))
            m_painter.drawLine(_red_left,_red_right);
        m_pen = QPen(Qt::yellow);
        m_pen.setWidth(7);
        m_painter.setPen(m_pen);
        if((!_yellow_left.isNull()) && (!_yellow_right.isNull()))
            m_painter.drawLine(_yellow_left,_yellow_right);

        m_pen = QPen(Qt::green);
        m_pen.setWidth(7);
        m_painter.setPen(m_pen);
        if((!_green_left.isNull()) && (!_green_right.isNull()))
            m_painter.drawLine(_green_left,_green_right);
    }
    m_pen = QPen(Qt::red);
    m_pen.setWidth(7);
    m_painter.setPen(m_pen);
    PlotLine(_points_in_red);
    PlotLine(_points_out_red);
    m_pen = QPen(Qt::yellow);
    m_pen.setWidth(7);
    m_painter.setPen(m_pen);
    PlotLine(_points_in_yellow);
    PlotLine(_points_out_yellow);
    m_pen = QPen(Qt::green);
    m_pen.setWidth(7);
    m_painter.setPen(m_pen);
    PlotLine(_points_in_green);
    PlotLine(_points_out_green);
    m_painter.end();

}
#endif
/* @brief: 将opencv图像贴在QLable上显示
  * @param [in]: image-opencv图像,scaled-图像缩小比例
  * @param [out]: NONE
  * @return NONE
  */
#if OPEN_CV_TRACK_LINE
void trankLineW::image2QImage(cv::Mat image,int scaled)
{
    QImage qimage = QImage((const uchar*)image.data,image.cols,image.rows,QImage::Format_ARGB32).rgbSwapped();

    QPixmap pixmap;
    pixmap = QPixmap::fromImage(qimage);
    pixmap = pixmap.scaled(cameraX_/scaled, cameraY_/scaled, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
    this->move(0,0);
    this->resize(cameraX_/scaled, cameraY_/scaled);
    //    this->setPixmap(pixmap);

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
    this->setPalette(palette);// 给widget加上背景图

}
#endif
/* @brief: 在QLabel上显示预测车轮轨迹
  * @param [in]: rotate-旋转角度(-90~90度),正顺时针，负逆时针
  * @param [out]: NONE
  * @return NONE
  * @param [in]::backward:true R档，false D档
  */
void trankLineW::trackLineShow(double rotate,bool backward,TrackLineCalibrationST &st)
{
    if(st.valid){
        track_line_ptr_->setCameraCfg(st);
    }else
    {
        return;
    }


    memset(get_x_in_,0,sizeof(double)*POINTS_NUM);
    memset(get_y_in_,0,sizeof(double)*POINTS_NUM);
    memset(get_x_out_,0,sizeof(double)*POINTS_NUM);
    memset(get_x_out_,0,sizeof(double)*POINTS_NUM);

    track_line_ptr_->computeTrackLine(rotate,backward,get_x_in_,get_y_in_,get_x_out_,get_y_out_);//计算轨迹线

//    std::cout<<"轨迹线:"<<std::endl;
//    for(int i=0;i<POINTS_NUM;i++)
//    {
//        std::cout<<get_x_in_[i]<<","<<get_y_in_[i]<<"    "<<get_x_out_[i]<<","<<get_y_out_[i]<<std::endl;
//    }

    _points_in_red.clear();
    _points_in_yellow.clear();
    _points_in_green.clear();
    _points_out_red.clear();
    _points_out_yellow.clear();
    _points_out_green.clear();

    _red_left =QPointF(0.0,0.0);
    _red_right=QPointF(0.0,0.0);
    _yellow_left=QPointF(0.0,0.0);
    _yellow_right=QPointF(0.0,0.0);
    _green_left=QPointF(0.0,0.0);
    _green_right=QPointF(0.0,0.0);
    for(int i=0;i<POINTS_NUM;i++)
    {

//        if(0 < get_x_in_[i] && get_x_in_[i] < cameraX_*3/2 &&
//                0 < get_y_in_[i] && get_y_in_[i] < cameraY_*3/2  )
        {
            if(COLOR_SCALE >= (i)*DISTANCE_STEP)
            {

                _points_in_red.push_back(QPointF(get_x_in_[i],get_y_in_[i]));


            }
            if(COLOR_SCALE*2 >= (i)*DISTANCE_STEP && COLOR_SCALE <= (i)*DISTANCE_STEP)
            {

                _points_in_yellow.push_back(QPointF(get_x_in_[i],get_y_in_[i]));

            }
            if(COLOR_SCALE*2 <= (i)*DISTANCE_STEP)
            {

                _points_in_green.push_back(QPointF(get_x_in_[i],get_y_in_[i]));
            }
        }
//        if(0 < get_x_out_[i] && get_x_out_[i] < cameraX_*3/2 &&
//                0 < get_y_out_[i] && get_y_out_[i] < cameraY_*3/2  )
        {
            if(COLOR_SCALE >= (i)*DISTANCE_STEP)
            {

                _points_out_red.push_back(QPointF(get_x_out_[i],get_y_out_[i]));
            }
            if(COLOR_SCALE*2 >= (i)*DISTANCE_STEP && COLOR_SCALE <= (i)*DISTANCE_STEP)
            {

                _points_out_yellow.push_back(QPointF(get_x_out_[i],get_y_out_[i]));
            }
            if(COLOR_SCALE*2 <= (i)*DISTANCE_STEP)
            {

                _points_out_green.push_back(QPointF(get_x_out_[i],get_y_out_[i]));
            }
        }
    }
    auto sizeV= _points_in_red.size();
    if(sizeV>0)
    {
        _red_left = _points_in_red.at(sizeV-1);
        _red_right = _points_out_red.at(sizeV-1);
    }

    sizeV= _points_in_yellow.size();
    if(sizeV>0)
    {
        _yellow_left = _points_in_yellow.at(sizeV-1);
        _yellow_right = _points_out_yellow.at(sizeV-1);
    }

    sizeV= _points_in_green.size();
    if(sizeV>0)
    {
        _green_left = _points_in_green.at(sizeV-1);
        _green_right = _points_out_green.at(sizeV-1);
    }
    #if 0
    qDebug()<<"size:"<<_points_in_red.size()<<_points_out_red.size()
           <<_points_in_yellow.size()<<_points_out_yellow.size()
          <<_points_in_green.size()<<_points_out_green.size();

    qDebug()<<"line:"<<_red_left<<_red_right<<_yellow_left<<_yellow_right<<_green_left<<_green_right;
    #endif
}
#if OPEN_CV_TRACK_LINE
void trankLineW::PlotLine(cv::Mat image_in, std::vector<cv::Point> plot_points, const cv::Scalar &color, cv::Mat *image_out)
{
#if OPEN_CV_TRACK_LINE
    if(0 == plot_points.size())
        return;
    for(int i=0;i<plot_points.size()-1;i++)
    {
        cv::line(image_in, plot_points.at(i), plot_points.at(i+1), color, 5,  16/*CV_AA*//*LINE_AA*/);
    }
    *image_out = image_in;
#endif
#if QT_PAINT_TRACK_LINE
    if(0 == plot_points.size())
        return;
    for(int i=0;i<plot_points.size()-1;i++)
    {
        QPointF left,right;
        left = QPointF(plot_points.at(i).x,plot_points.at(i).y);
        right= QPointF(plot_points.at(i+1).x,plot_points.at(i+1).y);
        m_painter.drawLine(left,right);
    }
    this->update();
#endif

}
#endif
void trankLineW::PlotLine(std::vector<QPointF> &plot_points)
{
    if(0 == plot_points.size())
        return;
    for(unsigned long i=0;i<plot_points.size()-1;i++)
    {
        QPointF left,right;
        left = plot_points.at(i);
        right= plot_points.at(i+1);
        m_painter.drawLine(left,right);
    }
    this->update();
}
