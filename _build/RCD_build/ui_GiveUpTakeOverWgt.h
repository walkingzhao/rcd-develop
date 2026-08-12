/********************************************************************************
** Form generated from reading UI file 'GiveUpTakeOverWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GIVEUPTAKEOVERWGT_H
#define UI_GIVEUPTAKEOVERWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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

class Ui_GiveUpTakeOverWgt
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
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *GiveUpTakeOverWgt)
    {
        if (GiveUpTakeOverWgt->objectName().isEmpty())
            GiveUpTakeOverWgt->setObjectName(QString::fromUtf8("GiveUpTakeOverWgt"));
        GiveUpTakeOverWgt->resize(843, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GiveUpTakeOverWgt->sizePolicy().hasHeightForWidth());
        GiveUpTakeOverWgt->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(GiveUpTakeOverWgt);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new baseForm(GiveUpTakeOverWgt);
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
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButton_ok = new QPushButton(frame_btn);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(frame_btn);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(120, 0));

        horizontalLayout_3->addWidget(pushButton_cancel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        gridLayout_5->addLayout(horizontalLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_btn);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(GiveUpTakeOverWgt);

        QMetaObject::connectSlotsByName(GiveUpTakeOverWgt);
    } // setupUi

    void retranslateUi(QWidget *GiveUpTakeOverWgt)
    {
        GiveUpTakeOverWgt->setWindowTitle(QCoreApplication::translate("GiveUpTakeOverWgt", "Form", nullptr));
        label_title->setText(QCoreApplication::translate("GiveUpTakeOverWgt", "\347\241\256\350\256\244\346\224\276\345\274\203\346\216\245\347\256\241\344\273\273\345\212\241\357\274\237", nullptr));
        label_task->setText(QString());
        pushButton_ok->setText(QCoreApplication::translate("GiveUpTakeOverWgt", "\347\241\256\350\256\244", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("GiveUpTakeOverWgt", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GiveUpTakeOverWgt: public Ui_GiveUpTakeOverWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GIVEUPTAKEOVERWGT_H
