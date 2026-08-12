/********************************************************************************
** Form generated from reading UI file 'msgWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGWGT_H
#define UI_MSGWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_msgWgt
{
public:

    void setupUi(QWidget *msgWgt)
    {
        if (msgWgt->objectName().isEmpty())
            msgWgt->setObjectName(QString::fromUtf8("msgWgt"));
        msgWgt->resize(400, 300);

        retranslateUi(msgWgt);

        QMetaObject::connectSlotsByName(msgWgt);
    } // setupUi

    void retranslateUi(QWidget *msgWgt)
    {
        msgWgt->setWindowTitle(QCoreApplication::translate("msgWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class msgWgt: public Ui_msgWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGWGT_H
