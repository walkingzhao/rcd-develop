#ifndef INFOMODEL_H
#define INFOMODEL_H
#include "Interface/IModel.h"

class InfoModel : public IModel
{
    Q_OBJECT
public:
    explicit InfoModel(QObject *parent = nullptr);
    enum ModelCmdType
    {
        MC_InsertMsg=0,

        MC_Max
    };
    void insertMsg(QString msg);
    QString newMsg;
};

#endif // INFOMODEL_H
