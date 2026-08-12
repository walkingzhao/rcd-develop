/********************************************************************************
** Form generated from reading UI file 'TakeOverInfoWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAKEOVERINFOWGT_H
#define UI_TAKEOVERINFOWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_TakeOverInfoWgt
{
public:
    TGFrame *Title;
    QFrame *frame;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_work_info;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_car_icon;
    QLabel *label_car_num;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_4;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_5;
    QLabel *label_load_area;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *TakeOverInfoWgt)
    {
        if (TakeOverInfoWgt->objectName().isEmpty())
            TakeOverInfoWgt->setObjectName(QString::fromUtf8("TakeOverInfoWgt"));
        TakeOverInfoWgt->resize(776, 262);
        Title = new TGFrame(TakeOverInfoWgt);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(9, 9, 771, 251));
        frame = new QFrame(Title);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 40, 106, 118));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 74, 135);\n"
"border-radius:10px"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(label);

        label_work_info = new QLabel(frame);
        label_work_info->setObjectName(QString::fromUtf8("label_work_info"));
        label_work_info->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_work_info);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        frame_2 = new QFrame(Title);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(410, 10, 245, 240));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 74, 135);\n"
"border-radius:10px"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 40));

        verticalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_6);

        label_car_icon = new QLabel(frame_2);
        label_car_icon->setObjectName(QString::fromUtf8("label_car_icon"));
        label_car_icon->setMinimumSize(QSize(0, 0));
        label_car_icon->setMaximumSize(QSize(16777215, 50));
        label_car_icon->setPixmap(QPixmap(QString::fromUtf8(":/resource/car/no_load.png")));
        label_car_icon->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_car_icon);

        label_car_num = new QLabel(frame_2);
        label_car_num->setObjectName(QString::fromUtf8("label_car_num"));
        label_car_num->setMinimumSize(QSize(0, 0));
        label_car_num->setMaximumSize(QSize(16777215, 30));
        label_car_num->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_car_num);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_7);

        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 0));
        label_4->setMaximumSize(QSize(16777215, 50));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/resource/car/route.png")));
        label_4->setScaledContents(false);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(0, 0));
        label_7->setMaximumSize(QSize(16777215, 30));
        label_7->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_3->addWidget(label_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_8);

        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setMaximumSize(QSize(16777215, 50));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/resource/car/Load_area.png")));
        label_5->setScaledContents(false);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_5);

        label_load_area = new QLabel(frame_2);
        label_load_area->setObjectName(QString::fromUtf8("label_load_area"));
        label_load_area->setMinimumSize(QSize(0, 0));
        label_load_area->setMaximumSize(QSize(16777215, 30));
        label_load_area->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_load_area);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_5);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(TakeOverInfoWgt);

        QMetaObject::connectSlotsByName(TakeOverInfoWgt);
    } // setupUi

    void retranslateUi(QWidget *TakeOverInfoWgt)
    {
        TakeOverInfoWgt->setWindowTitle(QCoreApplication::translate("TakeOverInfoWgt", "Form", nullptr));
        label->setText(QCoreApplication::translate("TakeOverInfoWgt", "\345\275\223\345\211\215\346\216\245\347\256\241\347\233\256\346\240\207", nullptr));
        label_work_info->setText(QCoreApplication::translate("TakeOverInfoWgt", "\350\241\214\351\251\266\350\207\263\350\243\205\350\275\275\345\214\272#2", nullptr));
        label_2->setText(QCoreApplication::translate("TakeOverInfoWgt", "\350\275\246\350\276\206\345\216\237\346\234\211\350\260\203\345\272\246\347\233\256\346\240\207", nullptr));
        label_car_icon->setText(QString());
        label_car_num->setText(QCoreApplication::translate("TakeOverInfoWgt", "1701", nullptr));
        label_4->setText(QString());
        label_7->setText(QString());
        label_5->setText(QString());
        label_load_area->setText(QCoreApplication::translate("TakeOverInfoWgt", "\350\243\205\350\275\275\345\214\272#2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TakeOverInfoWgt: public Ui_TakeOverInfoWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAKEOVERINFOWGT_H
