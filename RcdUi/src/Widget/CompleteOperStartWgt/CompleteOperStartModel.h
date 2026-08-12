#ifndef CompleteOperStartModel_H
#define CompleteOperStartModel_H

#include "Interface/IModel.h"
#include "public/fbsstructure.h"
class CompleteOperStartModel : public IModel
{
    Q_OBJECT
public:
    explicit CompleteOperStartModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_Update=0,

        MC_Max
    };

    void updateState(SelfCheckStatusST st);

    SelfCheckStatusST m_selfState;
    bool _timerStatus = true;
};

#endif // CompleteOperStartModel_H
