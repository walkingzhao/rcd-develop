#ifndef FastStopCL_H
#define FastStopCL_H
#include "Interface/IController.h"
#include "FastStopModel.h"

class FastStopCL : public IController
{
    Q_OBJECT
public:
    explicit FastStopCL(QObject *parent = nullptr);
    void setModel(FastStopModel *model);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;
    enum CLCmdType
    {
        CL_Show=0,
        CL_Hide,
        CL_Enter,

        CL_Max
    };
    void keyPress(QString keyStr);

private:
    FastStopModel *m_pModel;
};

#endif // FastStopCL_H
