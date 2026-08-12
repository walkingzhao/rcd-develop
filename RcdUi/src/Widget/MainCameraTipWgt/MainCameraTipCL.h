#ifndef MainCameraTipCL_H
#define MainCameraTipCL_H
#include "Interface/IController.h"
#include "MainCameraTipModel.h"

class MainCameraTipCL : public IController
{
    Q_OBJECT
public:
    explicit MainCameraTipCL(QObject *parent = nullptr);
    void setModel(MainCameraTipModel *model);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;
    enum CLCmdType
    {
        CL_UpdateText=0,
        CL_Hide,

        CL_Max
    };

private:
    MainCameraTipModel *m_pModel;
};

#endif // MainCameraTipCL_H
