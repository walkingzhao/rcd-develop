#ifndef TAKEOVERINFOMODEL_H
#define TAKEOVERINFOMODEL_H
#include "Interface/IModel.h"

class TakeOverInfoModel  : public IModel
{
    Q_OBJECT
public:
    explicit TakeOverInfoModel(QObject *parent = nullptr);
    enum ModelCmdType
    {
        MC_UpdateAll=0,
        MC_UpdateDest,
        MC_Max
    };
    void setAllInfo(QString dest,QString curName,QString orgDest);
    void setTargetInfo(QString dest);
    void setLoadStatus(uint8_t loadStatus);
    QString m_destName;
    QString m_orgDestName;
    QString m_curName;
    uint8_t m_loadStatus;
};

#endif // TAKEOVERINFOMODEL_H
