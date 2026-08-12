#ifndef TaskWorkChangeModel_H
#define TaskWorkChangeModel_H

#include "Interface/IModel.h"

class TaskWorkChangeModel : public IModel
{
    Q_OBJECT
public:
    explicit TaskWorkChangeModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_UpdateAll=0,
        MC_LoadUrl,

        MC_Max
    };

    void setUrl(QString &url);

    QString m_url;
};

#endif // TaskWorkChangeModel_H
