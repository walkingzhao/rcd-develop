#ifndef selfTestModel_H
#define selfTestModel_H

#include "Interface/IModel.h"
#include "../include/qtzmq.h"
#include "public/fbsstructure.h"

class selfTestModel : public IModel
{
    Q_OBJECT
public:
    explicit selfTestModel(QObject *parent = nullptr);

    enum ModelCmdType {
        Self_Update_content,
        Self_Update_wheel_content,
        Self_Update_takeover_content,
        Self_Update_blind_content,
        Self_Update_empty_content
    };

    void setState(VehicleStatus &st);
    void updateContent(SelfTest_ControlData_St &content);
    void updateWheelValue(SelfTest_CtrlRawData_St &wheelData);
    void updateTakeoverStatus();
    void updateBlindStatus();
    void updateEmptyStatus();

    SelfTest_CtrlRawData_St m_wheelData;
    SelfTest_ControlData_St m_content;
    int curTipsType = 0;
};

#endif // selfTestModel_H
