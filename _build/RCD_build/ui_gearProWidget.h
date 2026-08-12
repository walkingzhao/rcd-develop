/********************************************************************************
** Form generated from reading UI file 'gearProWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEARPROWIDGET_H
#define UI_GEARPROWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gearProWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *brake1;
    QSpacerItem *horizontalSpacer;
    QLabel *gear_R;
    QLabel *lineSpace1;
    QLabel *gear_N;
    QLabel *lineSpace2;
    QLabel *gear_D;
    QSpacerItem *horizontalSpacer_2;
    QLabel *brake2;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *gearProWidget)
    {
        if (gearProWidget->objectName().isEmpty())
            gearProWidget->setObjectName(QString::fromUtf8("gearProWidget"));
        gearProWidget->resize(530, 40);
        gearProWidget->setStyleSheet(QString::fromUtf8("QWidget#gearProWidget{\n"
"	background-color: transparent;\n"
"}"));
        horizontalLayout = new QHBoxLayout(gearProWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        brake1 = new QLabel(gearProWidget);
        brake1->setObjectName(QString::fromUtf8("brake1"));

        horizontalLayout->addWidget(brake1);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gear_R = new QLabel(gearProWidget);
        gear_R->setObjectName(QString::fromUtf8("gear_R"));
        gear_R->setMinimumSize(QSize(90, 40));
        gear_R->setMaximumSize(QSize(90, 40));
        QFont font;
        font.setPointSize(21);
        gear_R->setFont(font);
        gear_R->setStyleSheet(QString::fromUtf8(""));
        gear_R->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_R);

        lineSpace1 = new QLabel(gearProWidget);
        lineSpace1->setObjectName(QString::fromUtf8("lineSpace1"));
        lineSpace1->setStyleSheet(QString::fromUtf8("color: rgb(0,18,31);\n"
"background-color: rgb(0, 44, 77);\n"
"border-top:1px solid rgb(0,18,31);\n"
"border-bottom:1px solid rgb(0,18,31);\n"
""));

        horizontalLayout->addWidget(lineSpace1);

        gear_N = new QLabel(gearProWidget);
        gear_N->setObjectName(QString::fromUtf8("gear_N"));
        gear_N->setMinimumSize(QSize(90, 40));
        gear_N->setMaximumSize(QSize(90, 40));
        gear_N->setFont(font);
        gear_N->setStyleSheet(QString::fromUtf8(""));
        gear_N->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_N);

        lineSpace2 = new QLabel(gearProWidget);
        lineSpace2->setObjectName(QString::fromUtf8("lineSpace2"));
        lineSpace2->setStyleSheet(QString::fromUtf8("color: rgb(0,18,31);\n"
"background-color: rgb(0, 44, 77);\n"
"border-top:1px solid rgb(0,18,31);\n"
"border-bottom:1px solid rgb(0,18,31);\n"
""));

        horizontalLayout->addWidget(lineSpace2);

        gear_D = new QLabel(gearProWidget);
        gear_D->setObjectName(QString::fromUtf8("gear_D"));
        gear_D->setMinimumSize(QSize(90, 40));
        gear_D->setMaximumSize(QSize(90, 40));
        gear_D->setFont(font);
        gear_D->setStyleSheet(QString::fromUtf8(""));
        gear_D->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_D);

        horizontalSpacer_2 = new QSpacerItem(27, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        brake2 = new QLabel(gearProWidget);
        brake2->setObjectName(QString::fromUtf8("brake2"));

        horizontalLayout->addWidget(brake2);

        horizontalSpacer_4 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        retranslateUi(gearProWidget);

        QMetaObject::connectSlotsByName(gearProWidget);
    } // setupUi

    void retranslateUi(QWidget *gearProWidget)
    {
        gearProWidget->setWindowTitle(QCoreApplication::translate("gearProWidget", "Form", nullptr));
        brake1->setText(QCoreApplication::translate("gearProWidget", "p", nullptr));
        gear_R->setText(QCoreApplication::translate("gearProWidget", "R", nullptr));
        lineSpace1->setText(QCoreApplication::translate("gearProWidget", "|", nullptr));
        gear_N->setText(QCoreApplication::translate("gearProWidget", "N", nullptr));
        lineSpace2->setText(QCoreApplication::translate("gearProWidget", "|", nullptr));
        gear_D->setText(QCoreApplication::translate("gearProWidget", "D", nullptr));
        brake2->setText(QCoreApplication::translate("gearProWidget", "p", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gearProWidget: public Ui_gearProWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEARPROWIDGET_H
