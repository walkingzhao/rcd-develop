/********************************************************************************
** Form generated from reading UI file 'trankLineW.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANKLINEW_H
#define UI_TRANKLINEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_trankLineW
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *trankLineW)
    {
        if (trankLineW->objectName().isEmpty())
            trankLineW->setObjectName(QString::fromUtf8("trankLineW"));
        trankLineW->resize(679, 437);
        gridLayout = new QGridLayout(trankLineW);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(trankLineW);

        QMetaObject::connectSlotsByName(trankLineW);
    } // setupUi

    void retranslateUi(QWidget *trankLineW)
    {
        trankLineW->setWindowTitle(QCoreApplication::translate("trankLineW", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class trankLineW: public Ui_trankLineW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANKLINEW_H
