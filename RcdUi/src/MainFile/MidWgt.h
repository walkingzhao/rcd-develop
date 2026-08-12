#ifndef MIDWGT_H
#define MIDWGT_H

#include <QMap>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include "System.h"
#include <QTimer>

namespace Ui {
class MidWgt;
}

// 中Widget背景
class MidWgt : public QWidget
{
    Q_OBJECT

public:
    explicit MidWgt(QWidget *parent = nullptr);
    ~MidWgt();

    void addShowWidget(int type ,QWidget *pWgt);

protected:

    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
public slots:
    void  timerOut();

private:
    Ui::MidWgt     *ui;
    //QPixmap        m_bgImage;
    QVBoxLayout    *m_pVLayout;
    QMap<ScreenAreaType,QWidget *>   m_pCurrentWgt;
    QTimer m_Timer;
};

#endif // MIDWGT_H
