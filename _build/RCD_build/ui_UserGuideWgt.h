/********************************************************************************
** Form generated from reading UI file 'UserGuideWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERGUIDEWGT_H
#define UI_USERGUIDEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_UserGuideWgt
{
public:
    TGFrame *rightTitle;

    void setupUi(QWidget *UserGuideWgt)
    {
        if (UserGuideWgt->objectName().isEmpty())
            UserGuideWgt->setObjectName(QString::fromUtf8("UserGuideWgt"));
        UserGuideWgt->resize(800, 600);
        UserGuideWgt->setStyleSheet(QString::fromUtf8(""));
        rightTitle = new TGFrame(UserGuideWgt);
        rightTitle->setObjectName(QString::fromUtf8("rightTitle"));
        rightTitle->setGeometry(QRect(10, 10, 481, 311));

        retranslateUi(UserGuideWgt);

        QMetaObject::connectSlotsByName(UserGuideWgt);
    } // setupUi

    void retranslateUi(QWidget *UserGuideWgt)
    {
        UserGuideWgt->setWindowTitle(QCoreApplication::translate("UserGuideWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserGuideWgt: public Ui_UserGuideWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERGUIDEWGT_H
