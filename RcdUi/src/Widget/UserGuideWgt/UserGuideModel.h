#ifndef UserGuideModel_H
#define UserGuideModel_H

#include "Interface/IModel.h"

class UserGuideModel : public IModel
{
    Q_OBJECT
public:
    explicit UserGuideModel(QObject *parent = nullptr);

    enum ModelCmdType
    {
        MC_UpdateAll=0,
        MC_LoadUrl,

        MC_Max
    };

    void setUrl(QString &url);

    QString m_url;
};

#endif // UserGuideModel_H
