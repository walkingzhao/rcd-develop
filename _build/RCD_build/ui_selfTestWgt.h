/********************************************************************************
** Form generated from reading UI file 'selfTestWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELFTESTWGT_H
#define UI_SELFTESTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Component/SteerWheel.h"
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_selfTestWgt
{
public:
    QGridLayout *gridLayout;
    TGFrame *widget;
    QVBoxLayout *verticalLayout;
    QFrame *frame_title;
    QGridLayout *gridLayout_2;
    SteerWheel *testWheel;

    void setupUi(QWidget *selfTestWgt)
    {
        if (selfTestWgt->objectName().isEmpty())
            selfTestWgt->setObjectName(QString::fromUtf8("selfTestWgt"));
        selfTestWgt->resize(1128, 637);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selfTestWgt->sizePolicy().hasHeightForWidth());
        selfTestWgt->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(selfTestWgt);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new TGFrame(selfTestWgt);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_title = new QFrame(widget);
        frame_title->setObjectName(QString::fromUtf8("frame_title"));
        frame_title->setFrameShape(QFrame::StyledPanel);
        frame_title->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_title);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        testWheel = new SteerWheel(frame_title);
        testWheel->setObjectName(QString::fromUtf8("testWheel"));

        gridLayout_2->addWidget(testWheel, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_title);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(selfTestWgt);

        QMetaObject::connectSlotsByName(selfTestWgt);
    } // setupUi

    void retranslateUi(QWidget *selfTestWgt)
    {
        selfTestWgt->setWindowTitle(QCoreApplication::translate("selfTestWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class selfTestWgt: public Ui_selfTestWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFTESTWGT_H
