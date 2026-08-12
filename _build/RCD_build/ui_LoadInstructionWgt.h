/********************************************************************************
** Form generated from reading UI file 'LoadInstructionWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINSTRUCTIONWGT_H
#define UI_LOADINSTRUCTIONWGT_H

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

class Ui_LoadInstructionWgt
{
public:
    TGFrame *Title;
    QFrame *frame_drive;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_drive_in;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_loading;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_drive_away;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_re_dock;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_re_dock;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *LoadInstructionWgt)
    {
        if (LoadInstructionWgt->objectName().isEmpty())
            LoadInstructionWgt->setObjectName(QString::fromUtf8("LoadInstructionWgt"));
        LoadInstructionWgt->resize(680, 304);
        Title = new TGFrame(LoadInstructionWgt);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(10, 10, 641, 271));
        frame_drive = new QFrame(Title);
        frame_drive->setObjectName(QString::fromUtf8("frame_drive"));
        frame_drive->setGeometry(QRect(81, 21, 148, 112));
        frame_drive->setStyleSheet(QString::fromUtf8("QFrame#frame_drive\n"
"{\n"
"background-color: rgb(32, 74, 135);\n"
"border-radius:10px;\n"
"}"));
        frame_drive->setFrameShape(QFrame::StyledPanel);
        frame_drive->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_drive);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_drive_in = new QLabel(frame_drive);
        label_drive_in->setObjectName(QString::fromUtf8("label_drive_in"));
        label_drive_in->setMinimumSize(QSize(0, 0));
        label_drive_in->setSizeIncrement(QSize(60, 0));
        label_drive_in->setStyleSheet(QString::fromUtf8(""));
        label_drive_in->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_drive_in);

        label = new QLabel(frame_drive);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_loading = new QLabel(frame_drive);
        label_loading->setObjectName(QString::fromUtf8("label_loading"));
        label_loading->setMinimumSize(QSize(0, 0));
        label_loading->setStyleSheet(QString::fromUtf8(""));
        label_loading->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_loading);

        label_2 = new QLabel(frame_drive);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_drive_away = new QLabel(frame_drive);
        label_drive_away->setObjectName(QString::fromUtf8("label_drive_away"));
        label_drive_away->setMinimumSize(QSize(0, 0));
        label_drive_away->setStyleSheet(QString::fromUtf8(""));
        label_drive_away->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_drive_away);

        label_3 = new QLabel(frame_drive);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        gridLayout_2->addLayout(verticalLayout_5, 0, 0, 1, 1);

        frame_re_dock = new QFrame(Title);
        frame_re_dock->setObjectName(QString::fromUtf8("frame_re_dock"));
        frame_re_dock->setGeometry(QRect(307, 21, 164, 157));
        frame_re_dock->setMaximumSize(QSize(200, 16777215));
        frame_re_dock->setStyleSheet(QString::fromUtf8("QFrame#frame_re_dock\n"
"{\n"
"background-color: rgb(32, 74, 135);\n"
"border-radius:10px;\n"
"}"));
        frame_re_dock->setFrameShape(QFrame::StyledPanel);
        frame_re_dock->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_re_dock);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_re_dock = new QLabel(frame_re_dock);
        label_re_dock->setObjectName(QString::fromUtf8("label_re_dock"));
        label_re_dock->setMinimumSize(QSize(0, 0));
        label_re_dock->setStyleSheet(QString::fromUtf8(""));
        label_re_dock->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_re_dock);

        label_4 = new QLabel(frame_re_dock);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_4);


        horizontalLayout_3->addLayout(verticalLayout_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        gridLayout_3->addLayout(verticalLayout_6, 0, 0, 1, 1);


        retranslateUi(LoadInstructionWgt);

        QMetaObject::connectSlotsByName(LoadInstructionWgt);
    } // setupUi

    void retranslateUi(QWidget *LoadInstructionWgt)
    {
        LoadInstructionWgt->setWindowTitle(QCoreApplication::translate("LoadInstructionWgt", "Form", nullptr));
        label_drive_in->setText(QString());
        label->setText(QCoreApplication::translate("LoadInstructionWgt", "\350\257\267\351\251\266\345\205\245", nullptr));
        label_loading->setText(QString());
        label_2->setText(QCoreApplication::translate("LoadInstructionWgt", "\350\243\205\350\275\275\344\270\255", nullptr));
        label_drive_away->setText(QString());
        label_3->setText(QCoreApplication::translate("LoadInstructionWgt", "\350\257\267\351\251\266\347\246\273", nullptr));
        label_re_dock->setText(QString());
        label_4->setText(QCoreApplication::translate("LoadInstructionWgt", "\351\207\215\346\226\260\345\201\234\351\235\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadInstructionWgt: public Ui_LoadInstructionWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINSTRUCTIONWGT_H
