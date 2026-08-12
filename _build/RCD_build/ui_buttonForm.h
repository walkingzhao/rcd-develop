/********************************************************************************
** Form generated from reading UI file 'buttonForm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUTTONFORM_H
#define UI_BUTTONFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_buttonForm
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *buttonForm)
    {
        if (buttonForm->objectName().isEmpty())
            buttonForm->setObjectName(QString::fromUtf8("buttonForm"));
        buttonForm->resize(203, 25);
        gridLayout = new QGridLayout(buttonForm);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(buttonForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);


        retranslateUi(buttonForm);

        QMetaObject::connectSlotsByName(buttonForm);
    } // setupUi

    void retranslateUi(QWidget *buttonForm)
    {
        buttonForm->setWindowTitle(QCoreApplication::translate("buttonForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("buttonForm", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buttonForm: public Ui_buttonForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUTTONFORM_H
