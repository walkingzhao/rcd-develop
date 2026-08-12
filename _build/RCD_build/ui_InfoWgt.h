/********************************************************************************
** Form generated from reading UI file 'InfoWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWGT_H
#define UI_INFOWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "Component/TGFrame.h"

QT_BEGIN_NAMESPACE

class Ui_InfoWgt
{
public:
    TGFrame *Title;
    QTextBrowser *messageBrowser;

    void setupUi(QWidget *InfoWgt)
    {
        if (InfoWgt->objectName().isEmpty())
            InfoWgt->setObjectName(QString::fromUtf8("InfoWgt"));
        InfoWgt->resize(838, 510);
        Title = new TGFrame(InfoWgt);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(0, 0, 838, 510));
        messageBrowser = new QTextBrowser(Title);
        messageBrowser->setObjectName(QString::fromUtf8("messageBrowser"));
        messageBrowser->setGeometry(QRect(9, 9, 501, 341));
        messageBrowser->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(InfoWgt);

        QMetaObject::connectSlotsByName(InfoWgt);
    } // setupUi

    void retranslateUi(QWidget *InfoWgt)
    {
        InfoWgt->setWindowTitle(QCoreApplication::translate("InfoWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoWgt: public Ui_InfoWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWGT_H
