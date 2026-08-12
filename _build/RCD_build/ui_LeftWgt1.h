/********************************************************************************
** Form generated from reading UI file 'LeftWgt1.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEFTWGT1_H
#define UI_LEFTWGT1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LeftWgt1
{
public:
    QWidget *logoWgt;
    QWidget *gridLayoutWidget;
    QGridLayout *m_pGridLayout;

    void setupUi(QWidget *LeftWgt1)
    {
        if (LeftWgt1->objectName().isEmpty())
            LeftWgt1->setObjectName(QString::fromUtf8("LeftWgt1"));
        LeftWgt1->resize(1280, 800);
        logoWgt = new QWidget(LeftWgt1);
        logoWgt->setObjectName(QString::fromUtf8("logoWgt"));
        logoWgt->setGeometry(QRect(90, 110, 371, 211));
        gridLayoutWidget = new QWidget(LeftWgt1);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(610, 150, 201, 161));
        m_pGridLayout = new QGridLayout(gridLayoutWidget);
        m_pGridLayout->setObjectName(QString::fromUtf8("m_pGridLayout"));
        m_pGridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(LeftWgt1);

        QMetaObject::connectSlotsByName(LeftWgt1);
    } // setupUi

    void retranslateUi(QWidget *LeftWgt1)
    {
        LeftWgt1->setWindowTitle(QCoreApplication::translate("LeftWgt1", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LeftWgt1: public Ui_LeftWgt1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEFTWGT1_H
