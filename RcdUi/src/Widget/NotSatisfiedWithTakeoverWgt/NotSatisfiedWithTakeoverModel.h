#ifndef NotSatisfiedWithTakeoverModel_H
#define NotSatisfiedWithTakeoverModel_H

#include "Interface/IModel.h"
#include "public/fbsstructure.h"
class NotSatisfiedWithTakeoverModel : public IModel
{
    Q_OBJECT
public:
    explicit NotSatisfiedWithTakeoverModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_Update=0,

        MC_Max
    };

    void setVehicleState(vehicleDataST st);

    vehicleDataST m_vehicleData;
};

#endif // NotSatisfiedWithTakeoverModel_H
