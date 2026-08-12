/********************************************************************************
** Form generated from reading UI file 'MainCameraWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCAMERAWGT_H
#define UI_MAINCAMERAWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Component/OpenglWidget.h"
#include "Component/RingDial.h"
#include "Component/SteerWheel.h"
#include "Component/TGFrame.h"
#include "Component/TriangleFill.h"
#include "Component/boundary/BoundaryLineWgt.h"
#include "Component/gearProWidget.h"
#include "Component/titleDateDriver.h"
#include "Component/trackline/trankLineW.h"

QT_BEGIN_NAMESPACE

class Ui_MainCameraWgt
{
public:
    QWidget *cameraTitle;
    QVBoxLayout *CVLayout;
    TGFrame *modelWgt;
    QWidget *widget;
    TGFrame *pingWgt;
    QGridLayout *gridLayout;
    SteerWheel *wheelWgt;
    gearProWidget *gearWgt;
    TriangleFill *throttleWgt;
    TriangleFill *brakeWgt;
    RingDial *tachometerWgt;
    RingDial *speedWgt;
    QWidget *zero_2;
    TGFrame *midVideoFrame1;
    QHBoxLayout *minPLayout;
    QWidget *widget_back;
    QGridLayout *gridLayout_5;
    OpenGLWidget *backPlayWgt;
    QGridLayout *gridLayout_3;
    titleDateDriver *widget_date_dirver;
    QWidget *widget_front;
    QGridLayout *gridLayout_4;
    OpenGLWidget *frontPlayWgt;
    QGridLayout *gridLayout_2;
    QWidget *widget_msg;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_msg;
    QWidget *trackLineWgt;
    QGridLayout *gridLayout_7;
    trankLineW *widget_TrackLine;
    QWidget *laneBoundaryWgt;
    QGridLayout *gridLayout_8;
    BoundaryLineWgt *widget_LaneBoundary;
    TGFrame *cloudyStatueWgt;
    QLabel *label_rcd_version;
    TGFrame *frontLeftVideoFrame;
    QHBoxLayout *minPLayout_2;
    QWidget *widget_font_left;
    QGridLayout *gridLayout_9;
    OpenGLWidget *front_leftPlayWgt;
    QGridLayout *gridLayout_10;
    TGFrame *front_rightVideoFrame;
    QHBoxLayout *minPLayout_3;
    QWidget *widget_front_right;
    QGridLayout *gridLayout_11;
    OpenGLWidget *front_rightPlayWgt;
    QGridLayout *gridLayout_12;
    TGFrame *netSpeedWgt;

    void setupUi(QWidget *MainCameraWgt)
    {
        if (MainCameraWgt->objectName().isEmpty())
            MainCameraWgt->setObjectName(QString::fromUtf8("MainCameraWgt"));
        MainCameraWgt->resize(1024, 768);
        MainCameraWgt->setStyleSheet(QString::fromUtf8(""));
        cameraTitle = new QWidget(MainCameraWgt);
        cameraTitle->setObjectName(QString::fromUtf8("cameraTitle"));
        cameraTitle->setGeometry(QRect(10, 10, 961, 391));
        CVLayout = new QVBoxLayout(cameraTitle);
        CVLayout->setSpacing(0);
        CVLayout->setObjectName(QString::fromUtf8("CVLayout"));
        CVLayout->setContentsMargins(-1, 0, -1, 0);
        modelWgt = new TGFrame(cameraTitle);
        modelWgt->setObjectName(QString::fromUtf8("modelWgt"));
        widget = new QWidget(modelWgt);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(420, 40, 120, 80));

        CVLayout->addWidget(modelWgt);

        pingWgt = new TGFrame(cameraTitle);
        pingWgt->setObjectName(QString::fromUtf8("pingWgt"));

        CVLayout->addWidget(pingWgt);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        wheelWgt = new SteerWheel(cameraTitle);
        wheelWgt->setObjectName(QString::fromUtf8("wheelWgt"));

        gridLayout->addWidget(wheelWgt, 0, 5, 2, 1);

        gearWgt = new gearProWidget(cameraTitle);
        gearWgt->setObjectName(QString::fromUtf8("gearWgt"));

        gridLayout->addWidget(gearWgt, 2, 4, 1, 3);

        throttleWgt = new TriangleFill(cameraTitle);
        throttleWgt->setObjectName(QString::fromUtf8("throttleWgt"));

        gridLayout->addWidget(throttleWgt, 1, 7, 2, 1);

        brakeWgt = new TriangleFill(cameraTitle);
        brakeWgt->setObjectName(QString::fromUtf8("brakeWgt"));

        gridLayout->addWidget(brakeWgt, 1, 2, 2, 1);

        tachometerWgt = new RingDial(cameraTitle);
        tachometerWgt->setObjectName(QString::fromUtf8("tachometerWgt"));

        gridLayout->addWidget(tachometerWgt, 1, 6, 1, 1);

        speedWgt = new RingDial(cameraTitle);
        speedWgt->setObjectName(QString::fromUtf8("speedWgt"));

        gridLayout->addWidget(speedWgt, 1, 4, 1, 1);

        zero_2 = new QWidget(cameraTitle);
        zero_2->setObjectName(QString::fromUtf8("zero_2"));

        gridLayout->addWidget(zero_2, 0, 8, 3, 2);

        midVideoFrame1 = new TGFrame(cameraTitle);
        midVideoFrame1->setObjectName(QString::fromUtf8("midVideoFrame1"));
        minPLayout = new QHBoxLayout(midVideoFrame1);
        minPLayout->setSpacing(0);
        minPLayout->setObjectName(QString::fromUtf8("minPLayout"));
        minPLayout->setContentsMargins(20, 15, 20, 15);
        widget_back = new QWidget(midVideoFrame1);
        widget_back->setObjectName(QString::fromUtf8("widget_back"));
        widget_back->setStyleSheet(QString::fromUtf8(""));
        gridLayout_5 = new QGridLayout(widget_back);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        backPlayWgt = new OpenGLWidget(widget_back);
        backPlayWgt->setObjectName(QString::fromUtf8("backPlayWgt"));
        backPlayWgt->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(backPlayWgt);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);

        gridLayout_5->addWidget(backPlayWgt, 0, 0, 1, 1);


        minPLayout->addWidget(widget_back);


        gridLayout->addWidget(midVideoFrame1, 0, 0, 2, 2);


        CVLayout->addLayout(gridLayout);

        CVLayout->setStretch(0, 1);
        CVLayout->setStretch(1, 1);
        CVLayout->setStretch(2, 1);
        widget_date_dirver = new titleDateDriver(MainCameraWgt);
        widget_date_dirver->setObjectName(QString::fromUtf8("widget_date_dirver"));
        widget_date_dirver->setGeometry(QRect(70, 440, 131, 81));
        widget_front = new QWidget(MainCameraWgt);
        widget_front->setObjectName(QString::fromUtf8("widget_front"));
        widget_front->setGeometry(QRect(780, 410, 201, 91));
        gridLayout_4 = new QGridLayout(widget_front);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        frontPlayWgt = new OpenGLWidget(widget_front);
        frontPlayWgt->setObjectName(QString::fromUtf8("frontPlayWgt"));
        gridLayout_2 = new QGridLayout(frontPlayWgt);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);

        gridLayout_4->addWidget(frontPlayWgt, 0, 0, 1, 1);

        widget_msg = new QWidget(MainCameraWgt);
        widget_msg->setObjectName(QString::fromUtf8("widget_msg"));
        widget_msg->setGeometry(QRect(60, 570, 201, 126));
        widget_msg->setStyleSheet(QString::fromUtf8("QWidget#widget_msg{\n"
" background-color:transparent;\n"
"}"));
        gridLayout_6 = new QGridLayout(widget_msg);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_msg = new QGridLayout();
        gridLayout_msg->setObjectName(QString::fromUtf8("gridLayout_msg"));

        gridLayout_6->addLayout(gridLayout_msg, 0, 0, 1, 1);

        trackLineWgt = new QWidget(MainCameraWgt);
        trackLineWgt->setObjectName(QString::fromUtf8("trackLineWgt"));
        trackLineWgt->setGeometry(QRect(399, 460, 231, 151));
        gridLayout_7 = new QGridLayout(trackLineWgt);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        widget_TrackLine = new trankLineW(trackLineWgt);
        widget_TrackLine->setObjectName(QString::fromUtf8("widget_TrackLine"));

        gridLayout_7->addWidget(widget_TrackLine, 0, 0, 1, 1);

        laneBoundaryWgt = new QWidget(MainCameraWgt);
        laneBoundaryWgt->setObjectName(QString::fromUtf8("laneBoundaryWgt"));
        laneBoundaryWgt->setGeometry(QRect(630, 550, 231, 151));
        gridLayout_8 = new QGridLayout(laneBoundaryWgt);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        widget_LaneBoundary = new BoundaryLineWgt(laneBoundaryWgt);
        widget_LaneBoundary->setObjectName(QString::fromUtf8("widget_LaneBoundary"));
        widget_LaneBoundary->setStyleSheet(QString::fromUtf8("border-image:url(:/resource/car/car.png)"));

        gridLayout_8->addWidget(widget_LaneBoundary, 0, 0, 1, 1);

        cloudyStatueWgt = new TGFrame(MainCameraWgt);
        cloudyStatueWgt->setObjectName(QString::fromUtf8("cloudyStatueWgt"));
        cloudyStatueWgt->setGeometry(QRect(540, 150, 943, 10));
        label_rcd_version = new QLabel(MainCameraWgt);
        label_rcd_version->setObjectName(QString::fromUtf8("label_rcd_version"));
        label_rcd_version->setGeometry(QRect(350, 480, 67, 17));
        frontLeftVideoFrame = new TGFrame(MainCameraWgt);
        frontLeftVideoFrame->setObjectName(QString::fromUtf8("frontLeftVideoFrame"));
        frontLeftVideoFrame->setGeometry(QRect(330, 540, 206, 83));
        minPLayout_2 = new QHBoxLayout(frontLeftVideoFrame);
        minPLayout_2->setSpacing(0);
        minPLayout_2->setObjectName(QString::fromUtf8("minPLayout_2"));
        minPLayout_2->setContentsMargins(20, 15, 20, 15);
        widget_font_left = new QWidget(frontLeftVideoFrame);
        widget_font_left->setObjectName(QString::fromUtf8("widget_font_left"));
        widget_font_left->setStyleSheet(QString::fromUtf8(""));
        gridLayout_9 = new QGridLayout(widget_font_left);
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        front_leftPlayWgt = new OpenGLWidget(widget_font_left);
        front_leftPlayWgt->setObjectName(QString::fromUtf8("front_leftPlayWgt"));
        front_leftPlayWgt->setStyleSheet(QString::fromUtf8(""));
        gridLayout_10 = new QGridLayout(front_leftPlayWgt);
        gridLayout_10->setSpacing(0);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);

        gridLayout_9->addWidget(front_leftPlayWgt, 0, 0, 1, 1);


        minPLayout_2->addWidget(widget_font_left);

        front_rightVideoFrame = new TGFrame(MainCameraWgt);
        front_rightVideoFrame->setObjectName(QString::fromUtf8("front_rightVideoFrame"));
        front_rightVideoFrame->setGeometry(QRect(310, 590, 206, 83));
        minPLayout_3 = new QHBoxLayout(front_rightVideoFrame);
        minPLayout_3->setSpacing(0);
        minPLayout_3->setObjectName(QString::fromUtf8("minPLayout_3"));
        minPLayout_3->setContentsMargins(20, 15, 20, 15);
        widget_front_right = new QWidget(front_rightVideoFrame);
        widget_front_right->setObjectName(QString::fromUtf8("widget_front_right"));
        widget_front_right->setStyleSheet(QString::fromUtf8(""));
        gridLayout_11 = new QGridLayout(widget_front_right);
        gridLayout_11->setSpacing(0);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        front_rightPlayWgt = new OpenGLWidget(widget_front_right);
        front_rightPlayWgt->setObjectName(QString::fromUtf8("front_rightPlayWgt"));
        front_rightPlayWgt->setStyleSheet(QString::fromUtf8(""));
        gridLayout_12 = new QGridLayout(front_rightPlayWgt);
        gridLayout_12->setSpacing(0);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);

        gridLayout_11->addWidget(front_rightPlayWgt, 0, 0, 1, 1);


        minPLayout_3->addWidget(widget_front_right);

        netSpeedWgt = new TGFrame(MainCameraWgt);
        netSpeedWgt->setObjectName(QString::fromUtf8("netSpeedWgt"));
        netSpeedWgt->setGeometry(QRect(0, 0, 943, 10));

        retranslateUi(MainCameraWgt);

        QMetaObject::connectSlotsByName(MainCameraWgt);
    } // setupUi

    void retranslateUi(QWidget *MainCameraWgt)
    {
        MainCameraWgt->setWindowTitle(QCoreApplication::translate("MainCameraWgt", "Form", nullptr));
        label_rcd_version->setText(QCoreApplication::translate("MainCameraWgt", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainCameraWgt: public Ui_MainCameraWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCAMERAWGT_H
