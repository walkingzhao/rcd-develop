/********************************************************************************
** Form generated from reading UI file 'NotSatisfiedWithTakeoverWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTSATISFIEDWITHTAKEOVERWGT_H
#define UI_NOTSATISFIEDWITHTAKEOVERWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Component/baseForm.h"

QT_BEGIN_NAMESPACE

class Ui_NotSatisfiedWithTakeoverWgt
{
public:
    QGridLayout *gridLayout;
    baseForm *widget;
    QVBoxLayout *verticalLayout;
    QFrame *frame_title;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_title;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_checked;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *mode;
    QCheckBox *gear;
    QCheckBox *breakState;
    QCheckBox *speed;
    QSpacerItem *horizontalSpacer_8;
    QFrame *frame_btn;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_task_over;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *NotSatisfiedWithTakeoverWgt)
    {
        if (NotSatisfiedWithTakeoverWgt->objectName().isEmpty())
            NotSatisfiedWithTakeoverWgt->setObjectName(QString::fromUtf8("NotSatisfiedWithTakeoverWgt"));
        NotSatisfiedWithTakeoverWgt->resize(899, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NotSatisfiedWithTakeoverWgt->sizePolicy().hasHeightForWidth());
        NotSatisfiedWithTakeoverWgt->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(NotSatisfiedWithTakeoverWgt);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new baseForm(NotSatisfiedWithTakeoverWgt);
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
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_title = new QLabel(frame_title);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        QFont font;
        font.setFamily(QString::fromUtf8("Source Han Sans CN"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_title->setFont(font);
        label_title->setStyleSheet(QString::fromUtf8("/*font*/\n"
"QLabel{\n"
"color:white;\n"
"font:32px \"Source Han Sans CN\";\n"
"}"));
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_title);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_title);

        frame_checked = new QFrame(widget);
        frame_checked->setObjectName(QString::fromUtf8("frame_checked"));
        frame_checked->setFrameShape(QFrame::StyledPanel);
        frame_checked->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_checked);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(30);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        mode = new QCheckBox(frame_checked);
        mode->setObjectName(QString::fromUtf8("mode"));
        mode->setStyleSheet(QString::fromUtf8("/*font*/\n"
"QCheckBox{\n"
"color:white;\n"
"font:16px \"Source Han Sans CN\";\n"
"}\n"
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 26px;\n"
"	height: 50px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: url(:/resource/button/false.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/resource/button/true.png);\n"
"}"));

        horizontalLayout_8->addWidget(mode);

        gear = new QCheckBox(frame_checked);
        gear->setObjectName(QString::fromUtf8("gear"));
        gear->setStyleSheet(QString::fromUtf8("/*font*/\n"
"QCheckBox{\n"
"color:white;\n"
"font:16px \"Source Han Sans CN\";\n"
"}\n"
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 26px;\n"
"	height: 50px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: url(:/resource/button/false.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/resource/button/true.png);\n"
"}"));

        horizontalLayout_8->addWidget(gear);

        breakState = new QCheckBox(frame_checked);
        breakState->setObjectName(QString::fromUtf8("breakState"));
        breakState->setStyleSheet(QString::fromUtf8("/*font*/\n"
"QCheckBox{\n"
"color:white;\n"
"font:16px \"Source Han Sans CN\";\n"
"}\n"
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 26px;\n"
"	height: 50px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: url(:/resource/button/false.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/resource/button/true.png);\n"
"}"));

        horizontalLayout_8->addWidget(breakState);

        speed = new QCheckBox(frame_checked);
        speed->setObjectName(QString::fromUtf8("speed"));
        speed->setStyleSheet(QString::fromUtf8("/*font*/\n"
"QCheckBox{\n"
"color:white;\n"
"font:16px \"Source Han Sans CN\";\n"
"}\n"
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 26px;\n"
"	height: 50px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: url(:/resource/button/false.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/resource/button/true.png);\n"
"}"));

        horizontalLayout_8->addWidget(speed);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        gridLayout_4->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_checked);

        frame_btn = new QFrame(widget);
        frame_btn->setObjectName(QString::fromUtf8("frame_btn"));
        frame_btn->setFrameShape(QFrame::StyledPanel);
        frame_btn->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_btn);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButton_task_over = new QPushButton(frame_btn);
        pushButton_task_over->setObjectName(QString::fromUtf8("pushButton_task_over"));
        pushButton_task_over->setMinimumSize(QSize(120, 0));
        pushButton_task_over->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(pushButton_task_over);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_btn);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(NotSatisfiedWithTakeoverWgt);

        QMetaObject::connectSlotsByName(NotSatisfiedWithTakeoverWgt);
    } // setupUi

    void retranslateUi(QWidget *NotSatisfiedWithTakeoverWgt)
    {
        NotSatisfiedWithTakeoverWgt->setWindowTitle(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "Form", nullptr));
        label_title->setText(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "\350\275\246\350\276\206\345\255\230\345\234\250\344\270\215\346\273\241\350\266\263\346\216\245\347\256\241\347\232\204\346\203\205\345\206\265\357\274\214\346\227\240\346\263\225\345\220\257\345\212\250\346\216\245\347\256\241\357\274\201", nullptr));
        mode->setText(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "\350\207\252\345\212\250\351\251\276\351\251\266\346\250\241\345\274\217", nullptr));
        gear->setText(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "\346\241\243\344\275\215N\346\241\243", nullptr));
        breakState->setText(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "\351\251\273\350\275\246\345\210\266\345\212\250", nullptr));
        speed->setText(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "\350\275\246\351\200\237\344\270\2720", nullptr));
        pushButton_task_over->setText(QCoreApplication::translate("NotSatisfiedWithTakeoverWgt", "\347\273\223\346\235\237\344\273\273\345\212\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotSatisfiedWithTakeoverWgt: public Ui_NotSatisfiedWithTakeoverWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTSATISFIEDWITHTAKEOVERWGT_H
