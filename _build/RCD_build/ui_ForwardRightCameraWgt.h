/********************************************************************************
** Form generated from reading UI file 'ForwardRightCameraWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORWARDRIGHTCAMERAWGT_H
#define UI_FORWARDRIGHTCAMERAWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "Component/OpenglWidget.h"
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_ForwardRightCameraWgt
{
public:
    TGFrame *leftVideoFrame1;
    OpenGLWidget *playWgt;

    void setupUi(QWidget *ForwardRightCameraWgt)
    {
        if (ForwardRightCameraWgt->objectName().isEmpty())
            ForwardRightCameraWgt->setObjectName(QString::fromUtf8("ForwardRightCameraWgt"));
        ForwardRightCameraWgt->resize(800, 600);
        ForwardRightCameraWgt->setStyleSheet(QString::fromUtf8(""));
        leftVideoFrame1 = new TGFrame(ForwardRightCameraWgt);
        leftVideoFrame1->setObjectName(QString::fromUtf8("leftVideoFrame1"));
        leftVideoFrame1->setGeometry(QRect(80, 90, 321, 211));
        leftVideoFrame1->setFocusPolicy(Qt::StrongFocus);
        leftVideoFrame1->setStyleSheet(QString::fromUtf8(""));
        playWgt = new OpenGLWidget(leftVideoFrame1);
        playWgt->setObjectName(QString::fromUtf8("playWgt"));
        playWgt->setGeometry(QRect(20, 20, 281, 171));
        playWgt->setFocusPolicy(Qt::NoFocus);
        playWgt->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(ForwardRightCameraWgt);

        QMetaObject::connectSlotsByName(ForwardRightCameraWgt);
    } // setupUi

    void retranslateUi(QWidget *ForwardRightCameraWgt)
    {
        ForwardRightCameraWgt->setWindowTitle(QCoreApplication::translate("ForwardRightCameraWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ForwardRightCameraWgt: public Ui_ForwardRightCameraWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORWARDRIGHTCAMERAWGT_H
