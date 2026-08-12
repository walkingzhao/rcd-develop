#ifndef TITLEDATEDRIVER_H
#define TITLEDATEDRIVER_H

#include <QWidget>
#include <QTimer>
namespace Ui {
class titleDateDriver;
}

class titleDateDriver : public QWidget
{
    Q_OBJECT

public:
    explicit titleDateDriver(QWidget *parent = nullptr);
    ~titleDateDriver();
    void setCurrentDateTime(QString strTime);
    void setDriverName(QString name);
private slots:
    void slotUpdateTime();
private:
    Ui::titleDateDriver *ui;
    QTimer _timerDate;
};

#endif // TITLEDATEDRIVER_H
