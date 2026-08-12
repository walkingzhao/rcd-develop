/********************************************************************************
** Form generated from reading UI file 'TipsPopupWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPSPOPUPWGT_H
#define UI_TIPSPOPUPWGT_H

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

class Ui_TipsPopupWgt
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
    QCheckBox *checkbox1;
    QCheckBox *checkbox2;
    QCheckBox *checkbox3;
    QCheckBox *checkbox4;
    QSpacerItem *horizontalSpacer_8;
    QFrame *frame_btn;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_ok;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *TipsPopupWgt)
    {
        if (TipsPopupWgt->objectName().isEmpty())
            TipsPopupWgt->setObjectName(QString::fromUtf8("TipsPopupWgt"));
        TipsPopupWgt->resize(818, 282);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TipsPopupWgt->sizePolicy().hasHeightForWidth());
        TipsPopupWgt->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(TipsPopupWgt);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new baseForm(TipsPopupWgt);
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

        checkbox1 = new QCheckBox(frame_checked);
        checkbox1->setObjectName(QString::fromUtf8("checkbox1"));
        checkbox1->setStyleSheet(QString::fromUtf8("/*font*/\n"
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

        horizontalLayout_8->addWidget(checkbox1);

        checkbox2 = new QCheckBox(frame_checked);
        checkbox2->setObjectName(QString::fromUtf8("checkbox2"));
        checkbox2->setStyleSheet(QString::fromUtf8("/*font*/\n"
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

        horizontalLayout_8->addWidget(checkbox2);

        checkbox3 = new QCheckBox(frame_checked);
        checkbox3->setObjectName(QString::fromUtf8("checkbox3"));
        checkbox3->setStyleSheet(QString::fromUtf8("/*font*/\n"
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

        horizontalLayout_8->addWidget(checkbox3);

        checkbox4 = new QCheckBox(frame_checked);
        checkbox4->setObjectName(QString::fromUtf8("checkbox4"));
        checkbox4->setStyleSheet(QString::fromUtf8("/*font*/\n"
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

        horizontalLayout_8->addWidget(checkbox4);

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

        pushButton_ok = new QPushButton(frame_btn);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(pushButton_ok);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        pushButton_cancel = new QPushButton(frame_btn);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(pushButton_cancel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_btn);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(TipsPopupWgt);

        QMetaObject::connectSlotsByName(TipsPopupWgt);
    } // setupUi

    void retranslateUi(QWidget *TipsPopupWgt)
    {
        TipsPopupWgt->setWindowTitle(QCoreApplication::translate("TipsPopupWgt", "Form", nullptr));
        label_title->setText(QCoreApplication::translate("TipsPopupWgt", "\345\272\247\350\210\261\346\216\247\345\210\266\345\215\225\345\205\203\346\216\211\347\272\277\357\274\201\350\257\267\345\244\215\344\275\215\345\272\247\350\210\261\345\220\216\347\273\223\346\235\237\344\273\273\345\212\241\343\200\202", nullptr));
        checkbox1->setText(QCoreApplication::translate("TipsPopupWgt", "\346\241\243\344\275\215P\346\241\243", nullptr));
        checkbox2->setText(QCoreApplication::translate("TipsPopupWgt", "\350\270\217\346\235\277\346\227\240\350\270\251\345\216\213", nullptr));
        checkbox3->setText(QCoreApplication::translate("TipsPopupWgt", "\346\226\271\345\220\221\347\233\230\345\233\236\346\255\243", nullptr));
        checkbox4->setText(QCoreApplication::translate("TipsPopupWgt", "\346\214\211\351\222\256\345\244\215\344\275\215", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("TipsPopupWgt", "\347\273\223\346\235\237\344\273\273\345\212\241", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("TipsPopupWgt", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TipsPopupWgt: public Ui_TipsPopupWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPSPOPUPWGT_H
