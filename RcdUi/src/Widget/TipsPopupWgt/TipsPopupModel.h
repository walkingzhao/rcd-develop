#ifndef TipsPopupModel_H
#define TipsPopupModel_H

#include "Interface/IModel.h"
#include "../include/qtzmq.h"
#include "public/fbsstructure.h"

class TipsPopupModel : public IModel
{
    Q_OBJECT
public:
    explicit TipsPopupModel(QObject *parent = nullptr);

    enum ModelCmdType {
//        MC_Update=0,
//        MC_UpdateSelf,
        TP_Update_content,
//        MC_Max
    };

    void updateContent(popContent &content);
    popContent m_content;
    int curTipsType = 0;
    int curFirstPriority = 0;
    int curSecondPriority = 0;

    void setState(VehicleStatus &st);
    VehicleStatus m_vehicleState;
    bool _timerStatus = true;
};

#endif // TipsPopupModel_H
