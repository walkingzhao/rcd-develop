#ifndef GiveUpTakeOverModel_H
#define GiveUpTakeOverModel_H

#include "Interface/IModel.h"

class GiveUpTakeOverModel : public IModel
{
    Q_OBJECT
public:
    explicit GiveUpTakeOverModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_UpdateAll=0,

        MC_Max
    };
};

#endif // GiveUpTakeOverModel_H
