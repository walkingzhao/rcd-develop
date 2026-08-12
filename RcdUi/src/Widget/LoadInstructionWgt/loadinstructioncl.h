#ifndef LOADINSTRUCTIONCL_H
#define LOADINSTRUCTIONCL_H
#include "Interface/IController.h"
#include "loadinstructionmodel.h"

class LoadInstructionCL : public IController
{
    Q_OBJECT
public:
    explicit LoadInstructionCL(QObject *parent = nullptr);
    void setModel(LoadInstructionModel *model);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

private:
    LoadInstructionModel *m_pModel;
};

#endif // LOADINSTRUCTIONCL_H
