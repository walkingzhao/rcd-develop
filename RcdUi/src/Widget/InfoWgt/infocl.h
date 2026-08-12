#ifndef INFOCL_H
#define INFOCL_H
#include "Interface/IController.h"
#include "infomodel.h"
class InfoCL : public IController
{
    Q_OBJECT
public:
    explicit InfoCL(QObject *parent = nullptr);
    ~InfoCL() override;
    void setModel(InfoModel *model);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;
private:
    InfoModel *m_pModel;
};

#endif // INFOCL_H
