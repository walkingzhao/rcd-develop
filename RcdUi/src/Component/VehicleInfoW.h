#ifndef VEHICLEINFOW_H
#define VEHICLEINFOW_H

#include <QWidget>

namespace Ui {
class VehicleInfoW;
}

class VehicleInfoW : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleInfoW(QWidget *parent = nullptr);
    ~VehicleInfoW();

private:
    Ui::VehicleInfoW *ui;
};

#endif // VEHICLEINFOW_H
