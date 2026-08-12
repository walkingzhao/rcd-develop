#include "TGFrame.h"
#include <QPainter>
#include <QDebug>

TGFrame::TGFrame(QWidget *parent,TGFrameType type) : QWidget(parent),
    m_titleStr(QLatin1String("")),
    m_isShowTitle(false)
{
    setFrameType(type);
}

void TGFrame::setTitleString(QString str)
{
    m_titleStr = str;
    m_isShowTitle = true;
    this->update();
}

void TGFrame::setFrameType(TGFrameType type)
{
    m_frameType = type;
    if(m_frameType < Tip){
        m_frameImage.load(QString(QLatin1String(":/resource/frame/tgframe_%1.png"))
                          .arg(static_cast<int>(m_frameType)));
        this->update();
    }
}

TGFrame::TGFrameType TGFrame::frameType()
{
    return m_frameType;
}

void TGFrame::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::LosslessImageRendering);

    if(m_frameType < VideoFrame){
        drawInfoFrame(painter);
    }else if(m_frameType < Tip){
        drawFrame(painter);
    }else if(m_frameType < None){
        drawTip(painter);
    }
//    painter.translate(width()/2, height()/2);
//    qreal side = qMin(width()/WIDTH, height()/HEIGHT);

    painter.end();
}

void TGFrame::drawInfoFrame(QPainter &painter)
{
    QPixmap newPix = m_frameImage;
    if(TGFrame::InfoFrameRightPage2No8 == m_frameType)
        newPix = scaleByNinePatch(m_frameImage, 250, 50, 400, 50, this->rect().width(), this->rect().height());
    painter.drawPixmap(this->rect(),newPix,newPix.rect());
    if(m_isShowTitle){
        painter.setPen(Qt::white);
        QFont font = painter.font();
        font.setPixelSize(20);
        painter.setFont(font);
        QPoint point(25,28);
        painter.drawText(point,m_titleStr);

        point += QPoint(0,10);
        painter.setPen(QPen(QColor(0xfa, 0x5a, 0x00),2));
        QLine line(point,point + QPoint(100,0));
        painter.drawLine(line);
    }
}

void TGFrame::drawFrame(QPainter &painter)
{
    QPixmap newPix = m_frameImage;
    if(m_frameType == TGFrame::VideoFrameLeftPage2No1)
        newPix = scaleByNinePatch(m_frameImage, 500, 50, 50, 50, this->rect().width(), this->rect().height());
    else if(m_frameType == TGFrame::VideoFrameRightPage2No1)
        newPix = scaleByNinePatch(m_frameImage, 50, 50, 500, 50, this->rect().width(), this->rect().height());
    painter.drawPixmap(this->rect(),newPix,newPix.rect());
}

void TGFrame::drawTip(QPainter &painter)
{
    painter.setPen(QPen(QColor(0x00, 0xba, 0xff),2));
    painter.setBrush(QColor(0x00, 0xba, 0xff,0x33));
    painter.drawRect(this->rect());

    painter.setBrush(QColor(0x00, 0xba, 0xff));
    int offset = qMin(width()/20.0, height()/5.0);

    QPolygon points;
    QPoint  point(0,0);
    points.append(point);
    points.append(point+QPoint(offset,0));
    points.append(point+QPoint(0,offset));
    painter.drawConvexPolygon(points);

    points.clear();
    point = QPoint(width(),0);
    points.append(point);
    points.append(point-QPoint(offset,0));
    points.append(point+QPoint(0,offset));
    painter.drawConvexPolygon(points);

    points.clear();
    point = QPoint(0,height());
    points.append(point);
    points.append(point+QPoint(offset,0));
    points.append(point-QPoint(0,offset));
    painter.drawConvexPolygon(points);

    points.clear();
    point = QPoint(width(),height());
    points.append(point);
    points.append(point-QPoint(offset,0));
    points.append(point-QPoint(0,offset));
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
//        QLine line(point,point + QPoint(4*20,0));
//        painter.drawLine(line);

//        painter.setPen(QPen(QColor(0,0x1d,0x33),2));
//        line.setP1(point + QPoint(4*20,0));
//        line.setP2(point + QPoint(size*10,0));
//        painter.drawLine(line);
    }
}

QPixmap TGFrame::scaleByNinePatch(const QPixmap& pix, int x1, int y1, int x2, int y2, int iNewPixWidth, int iNewPixHeight)
{
    QPixmap pix_1 = pix.copy(0, 0, x1, y1);
    QPixmap pix_3 = pix.copy(pix.width() - x2, 0, x2, y1);
    QPixmap pix_7 = pix.copy(0, pix.height() - y2, x1, y2);
    QPixmap pix_9 = pix.copy(pix.width() - x2, pix.height() - y2, x2, y2);

    QPixmap pix_2 = pix.copy(x1, 0, pix.width() - x1 - x2, y1);
    QPixmap pix_4 = pix.copy(0, y1, x1, pix.height() - y1 - y2);
    QPixmap pix_6 = pix.copy(pix.width() - x2, y1, x2, pix.height() - y1 - y2);
    QPixmap pix_8 = pix.copy(x1, pix.height() - y2, pix.width() - x1 - x2, y2);

    QPixmap pix_5 = pix.copy(x1, y1, pix.width() - x1 - x2, pix.height() - y1 - y2);

    pix_2 = pix_2.scaled(iNewPixWidth- x1 - x2, y1, Qt::IgnoreAspectRatio);
    pix_4 = pix_4.scaled(x1, iNewPixHeight- y1 - y2, Qt::IgnoreAspectRatio);
    pix_5 = pix_5.scaled(iNewPixWidth- x1 - x2, iNewPixHeight- y1 - y2, Qt::IgnoreAspectRatio);
    pix_6 = pix_6.scaled(x2, iNewPixHeight- y1 - y2, Qt::IgnoreAspectRatio);
    pix_8 = pix_8.scaled(iNewPixWidth- x1 - x2, y2, Qt::IgnoreAspectRatio);

    QPixmap destPix(QSize(iNewPixWidth, iNewPixHeight));
    destPix.fill(Qt::transparent);
    QPainter painter(&destPix);

    if (!destPix.isNull())
    {
        painter.drawPixmap(0, 0, pix_1);
        painter.drawPixmap(x1, 0, pix_2);
        painter.drawPixmap(iNewPixWidth- x2, 0, pix_3);

        painter.drawPixmap(0, y1, pix_4);
        painter.drawPixmap(x1, y1, pix_5);
        painter.drawPixmap(iNewPixWidth- x2, y1, pix_6);

        painter.drawPixmap(0, iNewPixHeight- y2, pix_7);
        painter.drawPixmap(x1, iNewPixHeight- y2, pix_8);
        painter.drawPixmap(iNewPixWidth- x2, iNewPixHeight- y2, pix_9);
        painter.end();
    }

    return destPix;
}
