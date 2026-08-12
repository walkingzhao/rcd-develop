#ifndef CompleteOperEndModel_H
#define CompleteOperEndModel_H

#include "Interface/IModel.h"
#include "public/fbsstructure.h"
class CompleteOperEndModel : public IModel
{
    Q_OBJECT
public:
    explicit CompleteOperEndModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_Show=0,
        MC_UpdateSelf,

        MC_Max
    };

    void updateSelfState(SelfCheckStatusST selfState);

    SelfCheckStatusST m_selfState;
    bool _timerStatus = true;
};

#endif // CompleteOperEndModel_H
