/********************************************************************************
** Form generated from reading UI file 'BoundaryLineWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOUNDARYLINEWGT_H
#define UI_BOUNDARYLINEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoundaryLineWgt
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *BoundaryLineWgt)
    {
        if (BoundaryLineWgt->objectName().isEmpty())
            BoundaryLineWgt->setObjectName(QString::fromUtf8("BoundaryLineWgt"));
        BoundaryLineWgt->resize(679, 437);
        gridLayout = new QGridLayout(BoundaryLineWgt);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(BoundaryLineWgt);

        QMetaObject::connectSlotsByName(BoundaryLineWgt);
    } // setupUi

    void retranslateUi(QWidget *BoundaryLineWgt)
    {
        BoundaryLineWgt->setWindowTitle(QCoreApplication::translate("BoundaryLineWgt", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoundaryLineWgt: public Ui_BoundaryLineWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOUNDARYLINEWGT_H
