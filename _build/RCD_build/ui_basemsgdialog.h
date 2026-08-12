/********************************************************************************
** Form generated from reading UI file 'basemsgdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEMSGDIALOG_H
#define UI_BASEMSGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_baseMsgDialog
{
public:

    void setupUi(QDialog *baseMsgDialog)
    {
        if (baseMsgDialog->objectName().isEmpty())
            baseMsgDialog->setObjectName(QString::fromUtf8("baseMsgDialog"));
        baseMsgDialog->resize(400, 300);

        retranslateUi(baseMsgDialog);

        QMetaObject::connectSlotsByName(baseMsgDialog);
    } // setupUi

    void retranslateUi(QDialog *baseMsgDialog)
    {
        baseMsgDialog->setWindowTitle(QCoreApplication::translate("baseMsgDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class baseMsgDialog: public Ui_baseMsgDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEMSGDIALOG_H
