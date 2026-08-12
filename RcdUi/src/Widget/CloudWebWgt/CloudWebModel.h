#ifndef CloudWebModel_H
#define CloudWebModel_H

#include "Interface/IModel.h"

class CloudWebModel : public IModel
{
    Q_OBJECT
public:
    explicit CloudWebModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_UpdateAll=0,
        MC_LoadUrl,
        MC_SwitchMap,
        MC_Max
    };

    void setUrl(QString &url);
    void setCurrentMode(QString &data);
    QString m_url;
    QString _mapMode;
};

#endif // CloudWebModel_H
