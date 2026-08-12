#ifndef TAKEOVERINFOCL_H
#define TAKEOVERINFOCL_H
#include "Interface/IController.h"
#include "takeoverinfomodel.h"

class TakeOverInfoCL : public IController
{
    Q_OBJECT
public:
    explicit TakeOverInfoCL(QObject *parent = nullptr);
    void setModel(TakeOverInfoModel *model);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

private:
    TakeOverInfoModel *m_pModel;
};

#endif // TAKEOVERINFOCL_H
