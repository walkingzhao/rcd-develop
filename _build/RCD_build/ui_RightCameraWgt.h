/********************************************************************************
** Form generated from reading UI file 'RightCameraWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIGHTCAMERAWGT_H
#define UI_RIGHTCAMERAWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "Component/OpenglWidget.h"
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_RightCameraWgt
{
public:
    TGFrame *rightVideoFrame1;
    OpenGLWidget *playWgt;

    void setupUi(QWidget *RightCameraWgt)
    {
        if (RightCameraWgt->objectName().isEmpty())
            RightCameraWgt->setObjectName(QString::fromUtf8("RightCameraWgt"));
        RightCameraWgt->resize(800, 600);
        RightCameraWgt->setStyleSheet(QString::fromUtf8(""));
        rightVideoFrame1 = new TGFrame(RightCameraWgt);
        rightVideoFrame1->setObjectName(QString::fromUtf8("rightVideoFrame1"));
        rightVideoFrame1->setGeometry(QRect(90, 50, 291, 211));
        playWgt = new OpenGLWidget(rightVideoFrame1);
        playWgt->setObjectName(QString::fromUtf8("playWgt"));
        playWgt->setGeometry(QRect(21, 21, 249, 169));

        retranslateUi(RightCameraWgt);

        QMetaObject::connectSlotsByName(RightCameraWgt);
    } // setupUi

    void retranslateUi(QWidget *RightCameraWgt)
    {
        RightCameraWgt->setWindowTitle(QCoreApplication::translate("RightCameraWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RightCameraWgt: public Ui_RightCameraWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIGHTCAMERAWGT_H
