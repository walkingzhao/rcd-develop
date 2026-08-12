#ifndef VEHICLEDATACL_H
#define VEHICLEDATACL_H
#include "Interface/IController.h"
#include "vehicledatamodel.h"
class VehicleDataCL : public IController
{
    Q_OBJECT
public:
    explicit VehicleDataCL(QObject *parent = nullptr);

    void setModel(VehicleDataModel *model);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

private:
    VehicleDataModel *m_pModel;
};

#endif // VEHICLEDATACL_H
