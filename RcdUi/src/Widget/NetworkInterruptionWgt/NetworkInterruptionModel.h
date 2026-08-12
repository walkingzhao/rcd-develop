#ifndef NetworkInterruptionModel_H
#define NetworkInterruptionModel_H

#include "Interface/IModel.h"
#include "../include/qtzmq.h"
#include "public/fbsstructure.h"

class NetworkInterruptionModel : public IModel
{
    Q_OBJECT
public:
    explicit NetworkInterruptionModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_Update=0,
        MC_UpdateSelf,

        MC_Max
    };

    void setState(VehicleStatus &st);
    void updateSelfState(SelfCheckStatusST &selfState);

    VehicleStatus m_vehicleState;
    SelfCheckStatusST m_selfState;
    bool _timerStatus = true;
};

#endif // NetworkInterruptionModel_H
