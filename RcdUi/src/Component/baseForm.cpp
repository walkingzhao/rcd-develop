#include "baseForm.h"
#include "ui_baseForm.h"
#include <QPainter>
baseForm::baseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::baseForm)
{
    ui->setupUi(this);
    m_penColor=QColor(0x00, 0xba, 0xff);//QColor(0xfa, 0x5a, 0x00)
}

baseForm::~baseForm()
{
    delete ui;
}
void baseForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::LosslessImageRendering);
    drawTip(painter);
    painter.end();
}
void baseForm::drawTip(QPainter &painter)
{
    painter.setPen(QPen(m_penColor,2));
    painter.setBrush(QColor/*(0,0x1d,0x33)*/(0x00, 0xba, 0xff,0x33));
    painter.drawRect(this->rect());

    painter.setBrush(m_penColor);
    int offset = qMin(width()/20.0, height()/5.0);

    QPolygon points;
    QPoint  point(0,0);
    points.append(point);
    points.append(point+QPoint(offset,0));
    points.append(point+QPoint(0,offset));
    painter.drawConvexPolygon(points);


    painter.translate(width()/2, height()/2);

    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    int size = 1;
    for(auto str : m_titleStr){
        ushort uni = str.unicode();
        if(uni >= 0x4E00 && uni <= 0x9FA5){
            size += 2;
        }else{
            size += 1;
        }
    }

    if(size > 0){
        point = QPoint(-5*size,5);
        painter.drawText(point,m_titleStr);

        point += QPoint(0,10);
        painter.setPen(QPen(QColor(0xfa, 0x5a, 0x00),2));

        painter.setPen(QPen(QColor(0,0x1d,0x33),2));
    }
}

void baseForm::setPenColor(QColor color)
{
    m_penColor=color;
    this->update();
}
