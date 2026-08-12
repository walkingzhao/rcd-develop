/********************************************************************************
** Form generated from reading UI file 'TaskWorkChangeWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKWORKCHANGEWGT_H
#define UI_TASKWORKCHANGEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Component/baseForm.h"

QT_BEGIN_NAMESPACE

class Ui_TaskWorkChangeWgt
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
    QFrame *frame_text;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_task;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame_btn;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *TaskWorkChangeWgt)
    {
        if (TaskWorkChangeWgt->objectName().isEmpty())
            TaskWorkChangeWgt->setObjectName(QString::fromUtf8("TaskWorkChangeWgt"));
        TaskWorkChangeWgt->resize(998, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TaskWorkChangeWgt->sizePolicy().hasHeightForWidth());
        TaskWorkChangeWgt->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(TaskWorkChangeWgt);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new baseForm(TaskWorkChangeWgt);
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
        font.setPointSize(18);
        label_title->setFont(font);
        label_title->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_title);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_title);

        frame_text = new QFrame(widget);
        frame_text->setObjectName(QString::fromUtf8("frame_text"));
        frame_text->setFrameShape(QFrame::StyledPanel);
        frame_text->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_text);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_task = new QLabel(frame_text);
        label_task->setObjectName(QString::fromUtf8("label_task"));
        QFont font1;
        font1.setPointSize(13);
        label_task->setFont(font1);

        horizontalLayout_2->addWidget(label_task);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_text);

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

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_btn);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(TaskWorkChangeWgt);

        QMetaObject::connectSlotsByName(TaskWorkChangeWgt);
    } // setupUi

    void retranslateUi(QWidget *TaskWorkChangeWgt)
    {
        TaskWorkChangeWgt->setWindowTitle(QCoreApplication::translate("TaskWorkChangeWgt", "Form", nullptr));
        label_title->setText(QString());
        label_task->setText(QCoreApplication::translate("TaskWorkChangeWgt", "\350\257\267\346\263\250\346\204\217\357\274\201\346\216\245\347\256\241\347\233\256\346\240\207\345\267\262\345\217\230\346\233\264\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskWorkChangeWgt: public Ui_TaskWorkChangeWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKWORKCHANGEWGT_H
