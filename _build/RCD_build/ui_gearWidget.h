/********************************************************************************
** Form generated from reading UI file 'gearWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GEARWIDGET_H
#define UI_GEARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gearWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *gear_P;
    QFrame *line;
    QLabel *gear_R;
    QFrame *line_2;
    QLabel *gear_N;
    QFrame *line_3;
    QLabel *gear_D;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *gearWidget)
    {
        if (gearWidget->objectName().isEmpty())
            gearWidget->setObjectName(QString::fromUtf8("gearWidget"));
        gearWidget->resize(530, 40);
        gearWidget->setStyleSheet(QString::fromUtf8("QWidget#gearWidget{\n"
"	background-color: transparent;\n"
"}"));
        horizontalLayout = new QHBoxLayout(gearWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(78, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gear_P = new QLabel(gearWidget);
        gear_P->setObjectName(QString::fromUtf8("gear_P"));
        gear_P->setMinimumSize(QSize(90, 40));
        gear_P->setMaximumSize(QSize(90, 40));
        QFont font;
        font.setPointSize(21);
        gear_P->setFont(font);
        gear_P->setStyleSheet(QString::fromUtf8("color: rgb(186, 189, 182);\n"
"background-color: rgb(32, 74, 135);\n"
"border-top-left-radius: 20px;\n"
"border-bottom-left-radius: 20px;"));
        gear_P->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_P);

        line = new QFrame(gearWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setMinimumSize(QSize(0, 20));
        line->setMaximumSize(QSize(16777215, 20));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        gear_R = new QLabel(gearWidget);
        gear_R->setObjectName(QString::fromUtf8("gear_R"));
        gear_R->setMinimumSize(QSize(90, 40));
        gear_R->setMaximumSize(QSize(90, 40));
        gear_R->setFont(font);
        gear_R->setStyleSheet(QString::fromUtf8("color: rgb(186, 189, 182);\n"
"background-color: rgb(32, 74, 135);\n"
""));
        gear_R->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_R);

        line_2 = new QFrame(gearWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMaximumSize(QSize(16777215, 20));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        gear_N = new QLabel(gearWidget);
        gear_N->setObjectName(QString::fromUtf8("gear_N"));
        gear_N->setMinimumSize(QSize(90, 40));
        gear_N->setMaximumSize(QSize(90, 40));
        gear_N->setFont(font);
        gear_N->setStyleSheet(QString::fromUtf8("color: rgb(186, 189, 182);\n"
"background-color: rgb(32, 74, 135);\n"
""));
        gear_N->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_N);

        line_3 = new QFrame(gearWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setMaximumSize(QSize(16777215, 20));
        line_3->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        gear_D = new QLabel(gearWidget);
        gear_D->setObjectName(QString::fromUtf8("gear_D"));
        gear_D->setMinimumSize(QSize(90, 40));
        gear_D->setMaximumSize(QSize(90, 40));
        gear_D->setFont(font);
        gear_D->setStyleSheet(QString::fromUtf8("color: rgb(186, 189, 182);\n"
"background-color: rgb(32, 74, 135);\n"
"border-top-right-radius: 20px;\n"
"border-bottom-right-radius: 20px;"));
        gear_D->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(gear_D);

        horizontalSpacer_2 = new QSpacerItem(77, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(gearWidget);

        QMetaObject::connectSlotsByName(gearWidget);
    } // setupUi

    void retranslateUi(QWidget *gearWidget)
    {
        gearWidget->setWindowTitle(QCoreApplication::translate("gearWidget", "Form", nullptr));
        gear_P->setText(QCoreApplication::translate("gearWidget", "P", nullptr));
        gear_R->setText(QCoreApplication::translate("gearWidget", "R", nullptr));
        gear_N->setText(QCoreApplication::translate("gearWidget", "N", nullptr));
        gear_D->setText(QCoreApplication::translate("gearWidget", "D", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gearWidget: public Ui_gearWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GEARWIDGET_H
