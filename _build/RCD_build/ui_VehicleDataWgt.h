/********************************************************************************
** Form generated from reading UI file 'VehicleDataWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEHICLEDATAWGT_H
#define UI_VEHICLEDATAWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "Component/RingDialPro.h"
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_VehicleDataWgt
{
public:
    TGFrame *Title;
    QFrame *frame_dash_board;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *lowBeam;
    QLabel *highBeam;
    QLabel *emergencyFlash;
    QLabel *forwardLeft;
    QLabel *sideLamp;
    QLabel *forwardRight;
    QLabel *exhaustBrake;
    QLabel *tirePressureWarning;
    QLabel *bucketCtrl;
    QFrame *frame_info;
    QGridLayout *gridLayout_2;
    RingDialPro *widget_Coolant_temperature;
    RingDialPro *widget_coolant_level;
    RingDialPro *widget_oil_pressure;
    RingDialPro *widget_oil_volume;

    void setupUi(QWidget *VehicleDataWgt)
    {
        if (VehicleDataWgt->objectName().isEmpty())
            VehicleDataWgt->setObjectName(QString::fromUtf8("VehicleDataWgt"));
        VehicleDataWgt->resize(722, 410);
        Title = new TGFrame(VehicleDataWgt);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(30, 20, 651, 361));
        frame_dash_board = new QFrame(Title);
        frame_dash_board->setObjectName(QString::fromUtf8("frame_dash_board"));
        frame_dash_board->setGeometry(QRect(240, 0, 323, 348));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_dash_board->sizePolicy().hasHeightForWidth());
        frame_dash_board->setSizePolicy(sizePolicy);
        frame_dash_board->setMinimumSize(QSize(0, 0));
        frame_dash_board->setMaximumSize(QSize(323, 348));
        frame_dash_board->setAutoFillBackground(false);
        frame_dash_board->setStyleSheet(QString::fromUtf8("QFrame#frame_dash_board\n"
"{\n"
"border-image: url(:/resource/icon/fengexian.png);\n"
"background-color: rgb(32, 74, 135);\n"
"border-radius:10px;\n"
"}\n"
""));
        frame_dash_board->setFrameShape(QFrame::StyledPanel);
        frame_dash_board->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_dash_board);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lowBeam = new QLabel(frame_dash_board);
        lowBeam->setObjectName(QString::fromUtf8("lowBeam"));
        lowBeam->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lowBeam, 0, 0, 1, 1);

        highBeam = new QLabel(frame_dash_board);
        highBeam->setObjectName(QString::fromUtf8("highBeam"));
        highBeam->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(highBeam, 0, 1, 1, 1);

        emergencyFlash = new QLabel(frame_dash_board);
        emergencyFlash->setObjectName(QString::fromUtf8("emergencyFlash"));
        emergencyFlash->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(emergencyFlash, 0, 2, 1, 1);

        forwardLeft = new QLabel(frame_dash_board);
        forwardLeft->setObjectName(QString::fromUtf8("forwardLeft"));
        forwardLeft->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(forwardLeft, 1, 0, 1, 1);

        sideLamp = new QLabel(frame_dash_board);
        sideLamp->setObjectName(QString::fromUtf8("sideLamp"));
        sideLamp->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(sideLamp, 1, 1, 1, 1);

        forwardRight = new QLabel(frame_dash_board);
        forwardRight->setObjectName(QString::fromUtf8("forwardRight"));
        forwardRight->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(forwardRight, 1, 2, 1, 1);

        exhaustBrake = new QLabel(frame_dash_board);
        exhaustBrake->setObjectName(QString::fromUtf8("exhaustBrake"));
        exhaustBrake->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(exhaustBrake, 2, 0, 1, 1);

        tirePressureWarning = new QLabel(frame_dash_board);
        tirePressureWarning->setObjectName(QString::fromUtf8("tirePressureWarning"));
        tirePressureWarning->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(tirePressureWarning, 2, 1, 1, 1);

        bucketCtrl = new QLabel(frame_dash_board);
        bucketCtrl->setObjectName(QString::fromUtf8("bucketCtrl"));
        bucketCtrl->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(bucketCtrl, 2, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        frame_info = new QFrame(Title);
        frame_info->setObjectName(QString::fromUtf8("frame_info"));
        frame_info->setGeometry(QRect(9, 20, 191, 251));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_info->sizePolicy().hasHeightForWidth());
        frame_info->setSizePolicy(sizePolicy1);
        frame_info->setStyleSheet(QString::fromUtf8("QFrame#frame_info{\n"
"background-color: rgb(32, 74, 135);\n"
"border-radius:10px;\n"
"}\n"
""));
        frame_info->setFrameShape(QFrame::StyledPanel);
        frame_info->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_info);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_Coolant_temperature = new RingDialPro(frame_info);
        widget_Coolant_temperature->setObjectName(QString::fromUtf8("widget_Coolant_temperature"));
        sizePolicy1.setHeightForWidth(widget_Coolant_temperature->sizePolicy().hasHeightForWidth());
        widget_Coolant_temperature->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(widget_Coolant_temperature, 1, 0, 1, 1);

        widget_coolant_level = new RingDialPro(frame_info);
        widget_coolant_level->setObjectName(QString::fromUtf8("widget_coolant_level"));
        sizePolicy1.setHeightForWidth(widget_coolant_level->sizePolicy().hasHeightForWidth());
        widget_coolant_level->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(widget_coolant_level, 1, 1, 1, 1);

        widget_oil_pressure = new RingDialPro(frame_info);
        widget_oil_pressure->setObjectName(QString::fromUtf8("widget_oil_pressure"));
        sizePolicy1.setHeightForWidth(widget_oil_pressure->sizePolicy().hasHeightForWidth());
        widget_oil_pressure->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(widget_oil_pressure, 0, 1, 1, 1);

        widget_oil_volume = new RingDialPro(frame_info);
        widget_oil_volume->setObjectName(QString::fromUtf8("widget_oil_volume"));
        sizePolicy1.setHeightForWidth(widget_oil_volume->sizePolicy().hasHeightForWidth());
        widget_oil_volume->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(widget_oil_volume, 0, 0, 1, 1);


        retranslateUi(VehicleDataWgt);

        QMetaObject::connectSlotsByName(VehicleDataWgt);
    } // setupUi

    void retranslateUi(QWidget *VehicleDataWgt)
    {
        VehicleDataWgt->setWindowTitle(QCoreApplication::translate("VehicleDataWgt", "Form", nullptr));
        lowBeam->setText(QString());
        highBeam->setText(QString());
        emergencyFlash->setText(QString());
        forwardLeft->setText(QString());
        sideLamp->setText(QString());
        forwardRight->setText(QString());
        exhaustBrake->setText(QString());
        tirePressureWarning->setText(QString());
        bucketCtrl->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VehicleDataWgt: public Ui_VehicleDataWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEHICLEDATAWGT_H
