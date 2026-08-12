#ifndef RIGHTWGT1_H
#define RIGHTWGT1_H

#include <QMap>
#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include "System.h"

namespace Ui {
class RightWgt1;
}

// 右Widget背景

class RightWgt1 : public QWidget
{
    Q_OBJECT

public:
    explicit RightWgt1(QWidget *parent = nullptr);
    ~RightWgt1();

    void addShowWidget(int type ,QWidget *pWgt);
    void setLayoutMonitor();
    void setLayoutRemoteControl();

protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    Ui::RightWgt1    *ui;
    QMap<ScreenAreaType,QWidget *>   m_pCurrentWgt;

    QGridLayout    *m_pGridLayout;
//    QMap<ScreenAreaType,QWidget *>   m_pCurrentWgt;

};

#endif // RIGHTWGT1_H
