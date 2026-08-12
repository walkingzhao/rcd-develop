/********************************************************************************
** Form generated from reading UI file 'titleDateDriver.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEDATEDRIVER_H
#define UI_TITLEDATEDRIVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_titleDateDriver
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_data_icon;
    QLabel *label_date;
    QSpacerItem *horizontalSpacer;
    QLabel *label_driver_icon;
    QLabel *label_driver;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *titleDateDriver)
    {
        if (titleDateDriver->objectName().isEmpty())
            titleDateDriver->setObjectName(QString::fromUtf8("titleDateDriver"));
        titleDateDriver->resize(573, 51);
        gridLayout = new QGridLayout(titleDateDriver);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_data_icon = new QLabel(titleDateDriver);
        label_data_icon->setObjectName(QString::fromUtf8("label_data_icon"));
        label_data_icon->setMinimumSize(QSize(40, 40));
        label_data_icon->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(label_data_icon);

        label_date = new QLabel(titleDateDriver);
        label_date->setObjectName(QString::fromUtf8("label_date"));

        horizontalLayout->addWidget(label_date);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_driver_icon = new QLabel(titleDateDriver);
        label_driver_icon->setObjectName(QString::fromUtf8("label_driver_icon"));
        label_driver_icon->setMinimumSize(QSize(40, 40));
        label_driver_icon->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(label_driver_icon);

        label_driver = new QLabel(titleDateDriver);
        label_driver->setObjectName(QString::fromUtf8("label_driver"));

        horizontalLayout->addWidget(label_driver);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(titleDateDriver);

        QMetaObject::connectSlotsByName(titleDateDriver);
    } // setupUi

    void retranslateUi(QWidget *titleDateDriver)
    {
        titleDateDriver->setWindowTitle(QCoreApplication::translate("titleDateDriver", "Form", nullptr));
        label_data_icon->setText(QString());
        label_date->setText(QCoreApplication::translate("titleDateDriver", "2021/00/00 12:00:00", nullptr));
        label_driver_icon->setText(QString());
        label_driver->setText(QCoreApplication::translate("titleDateDriver", "\345\217\270\346\234\272\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class titleDateDriver: public Ui_titleDateDriver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEDATEDRIVER_H
