#ifndef LEFTWGT1_H
#define LEFTWGT1_H

#include <QMap>
#include <QWidget>
#include <QPixmap>
#include <QGridLayout>
#include "System.h"
#include <QTimer>
namespace Ui {
class LeftWgt1;
}

// 左Widget背景
class LeftWgt1 : public QWidget
{
    Q_OBJECT

public:
    explicit LeftWgt1(QWidget *parent = nullptr);
    ~LeftWgt1();
    void addShowWidget(int type ,QWidget *pWgt);
    void setLayoutMonitor();
    void setLayoutRemoteControl();
protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
private slots:
//    void slotUpdateSwitch();
private:

    Ui::LeftWgt1    *ui;

    //    QGridLayout    *m_pGridLayout;
    QHBoxLayout    *m_pLogoLayout;
    QMap<ScreenAreaType,QWidget *>   m_pCurrentWgt;
//    QTimer _timerSwitch;
//    int _switchId = 0;
};

#endif // LEFTWGT1_H
