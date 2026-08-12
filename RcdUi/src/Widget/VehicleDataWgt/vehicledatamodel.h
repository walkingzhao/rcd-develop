#ifndef VEHICLEDATAMODEL_H
#define VEHICLEDATAMODEL_H
#include "Interface/IModel.h"
#include "public/fbsstructure.h"
class VehicleDataModel : public IModel
{
    Q_OBJECT
public:
    explicit VehicleDataModel(QObject *parent = nullptr);
    enum ModelCmdType
    {
        MC_UpdateVehicleData=0,

        MC_Max
    };
    void setVehicleState(vehicleDataST st);
    vehicleDataST m_VehicleData;
};

#endif // VEHICLEDATAMODEL_H
