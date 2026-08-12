/********************************************************************************
** Form generated from reading UI file 'baseForm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEFORM_H
#define UI_BASEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_baseForm
{
public:

    void setupUi(QWidget *baseForm)
    {
        if (baseForm->objectName().isEmpty())
            baseForm->setObjectName(QString::fromUtf8("baseForm"));
        baseForm->resize(698, 304);

        retranslateUi(baseForm);

        QMetaObject::connectSlotsByName(baseForm);
    } // setupUi

    void retranslateUi(QWidget *baseForm)
    {
        baseForm->setWindowTitle(QCoreApplication::translate("baseForm", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class baseForm: public Ui_baseForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEFORM_H
