#ifndef GEARWIDGET_H
#define GEARWIDGET_H

#include <QWidget>
#include <QPixmap>
namespace Ui {
class gearWidget;
}

class gearWidget : public QWidget
{
    Q_OBJECT

public:
    enum GearWgtType {
        Gear_P = 0x2,
        Gear_D = 0x1,
        Gear_N = 0x0,
        Gear_R = -0x01
    };
    explicit gearWidget(QWidget *parent = nullptr);
    ~gearWidget();
    void setValue(int value);
protected:
    virtual void paintEvent(QPaintEvent *) override;
private:
    void clearStyle();
private:
    Ui::gearWidget *ui;
    //    QTimer         m_timer;
    QPixmap        m_gearWgtImage;
    GearWgtType    m_currentValue;
};

#endif // GEARWIDGET_H
