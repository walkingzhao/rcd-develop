#include "BoundaryLineWgt.h"
#include "ui_BoundaryLineWgt.h"
#include <QDebug>
#include <iostream>
BoundaryLineWgt::BoundaryLineWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoundaryLineWgt)
{
    ui->setupUi(this);
    center_path.clear();
    right_path.clear();
    left_path.clear();
    laneDisplay=nullptr;
}

BoundaryLineWgt::~BoundaryLineWgt()
{
    delete ui;
}
void BoundaryLineWgt::paintEvent(QPaintEvent *)
{
    m_painter.begin(this);
//    qDebug()<<"path size:"<<left_path.size()<<center_path.size()<<right_path.size();

    m_pen = QPen(Qt::gray);
    m_pen.setWidth(7);
    m_painter.setPen(m_pen);
    PlotLine(left_path);

    PlotLine(right_path);

    m_pen = QPen(Qt::blue);
    m_pen.setWidth(7);
    m_painter.setPen(m_pen);
    PlotLine(center_path);

    m_painter.end();

//    qDebug()<<"windows size:"<<this->width()<<this->height();
}

/* @brief: 在QLabel上显示预测车轮轨迹
  * @param [in]: rotate-旋转角度(-90~90度),正顺时针，负逆时针
  * @param [out]: NONE
  * @return NONE
  * @param [in]::backward:true R档，false D档
  */
void BoundaryLineWgt::boundaryComputer(GPSInfoST &gps)
{
    laneDisplay->computeLaneUV(gps,&left_path,&right_path,&center_path);
    return;

    qDebug()<<"boundaryComputer:"<<center_path.size();
    int count=0;
    for(int i=0;i<center_path.size();i++)
    {
        if((center_path.at(i).x>0 && center_path.at(i).x<1920)
            &&(center_path.at(i).y>0 && center_path.at(i).y<1080))
        {
            qDebug()<<center_path.at(i).x<<center_path.at(i).y;
            count++;
        }
    }
    qDebug()<<"show count:"<<count;
}
void BoundaryLineWgt::PlotLine(std::vector<XY> &plot_points)
{
    if(0 == plot_points.size())
        return;
    for(unsigned long i=0;i<plot_points.size()-1;i++)
    {
        QPointF left,right;
        left = QPointF(plot_points.at(i).x,plot_points.at(i).y);
        right= QPointF(plot_points.at(i+1).x,plot_points.at(i+1).y);
        if(left.x()>0 && left.x()<1920 &&left.y()>0 && left.y()<1080
            &&right.x()>0 && right.x()<1920 &&right.y()>0 && right.y()<1080)
        m_painter.drawLine(left,right);
//        qDebug()<<"drawline";
    }
//    qDebug()<<"plotline size:"<<plot_points.size();
    this->update();
}

void BoundaryLineWgt::newConnect(GPSInfoST &gps)
{
    qDebug()<<"new Connect";
    if(laneDisplay!=nullptr)
        delete laneDisplay;

    center_path.clear();
    right_path.clear();
    left_path.clear();

    laneDisplay = new LaneDisplay("laneData/calibration_config.txt");  //摄像头校准参数
    laneDisplay->initRelfPoint(gps);
}
