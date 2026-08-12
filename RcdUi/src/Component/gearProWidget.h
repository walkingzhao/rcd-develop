#ifndef GEARPROWIDGET_H
#define GEARPROWIDGET_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class gearProWidget;
}

class gearProWidget : public QWidget
{
    Q_OBJECT

public:
    enum GearProWgtType {
        Gear_R = -0x01,
        Gear_N = 0x0,
        Gear_D = 0x1
    };

    explicit gearProWidget(/*bool isRemote, */QWidget *parent = nullptr);
    ~gearProWidget();
    void setValue(int value);
    void setParking(int value);
    void setLoading(int value);
    void setmode(int value);

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    void resetStyle();

private:
    Ui::gearProWidget *ui;
    QPixmap        m_gearWgtImage;
    GearProWgtType m_currentValue;
    int imode = 0;
};

#endif // GEARPROWIDGET_H
