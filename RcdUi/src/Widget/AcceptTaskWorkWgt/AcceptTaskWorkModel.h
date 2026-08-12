#ifndef AcceptTaskWorkModel_H
#define AcceptTaskWorkModel_H

#include "Interface/IModel.h"

class AcceptTaskWorkModel : public IModel
{
    Q_OBJECT
public:
    explicit AcceptTaskWorkModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_destStr=0,
        MC_Max
    };

    void setDest(QString &dest,unsigned short& taskId);

    QString m_dest;
    unsigned short m_taskId;
};

#endif // AcceptTaskWorkModel_H
