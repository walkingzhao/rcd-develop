#ifndef BoundaryLineWgt_H
#define BoundaryLineWgt_H

#include "lane_display.h"
#include <qpainter.h>
#include <QPaintEvent>
#include <QWidget>
#include <QVector>

#include <math.h>
#include <unistd.h>

//#include "public/fbsstructure.h"


#define FRONT_MODE false
#define BACK_MODE true
#define OPEN_CV_TRACK_LINE 0
#define QT_PAINT_TRACK_LINE 1

#define WHEEL_ANGLE_MAX 35
#define WHEEL_ANGLE_MIN -35
#define STEERING_WHEEL_MAX 540
#define STEERING_WHEEL_MIN -540

namespace Ui {
class BoundaryLineWgt;
}

class BoundaryLineWgt : public QWidget
{
    Q_OBJECT

public:
    explicit BoundaryLineWgt(QWidget *parent = nullptr);
    ~BoundaryLineWgt();
    void boundaryComputer(GPSInfoST &gpsInfo);
    void newConnect(GPSInfoST &gps);
protected:
    void paintEvent(QPaintEvent *event) ;
private:

    void PlotLine(std::vector<XY> &plot_points);
private:
    Ui::BoundaryLineWgt *ui;

    LaneDisplay *laneDisplay; // 车道中心线计算类
    vector<XY> left_path,right_path,center_path;


    QPen m_pen;
    QPainter m_painter;
};

#endif // BoundaryLineWgt_H
