#ifndef VEHICLEDATAFORM_H
#define VEHICLEDATAFORM_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "vehicledatacl.h"
#include "vehicledatamodel.h"
#include <QTimer>


enum VehicleType
{
    VehicleType_Unknown = 0,
    VehicleType_Electric = 1,
    VehicleType_Diesel = 2,
    VehicleType_Dust = 3,
};

namespace Ui {
class VehicleDataWgt;
}

class VehicleDataWgt : public IFunWidget
{
    Q_OBJECT

public:

    explicit VehicleDataWgt(QWidget *parent = nullptr);
    ~VehicleDataWgt();

    static VehicleDataWgt *GetInstance();
private slots:
    void updateUI();


private:
    Ui::VehicleDataWgt *ui;
    static VehicleDataWgt        *s_pInstance;
    VehicleDataCL                *m_pCL;
    VehicleDataModel             *m_pModel;
    QTimer                       *m_updateTimer;
    VehicleType                   m_vehicle_type;
};

#endif // VEHICLEDATAFORM_H
