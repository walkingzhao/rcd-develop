#ifndef ForwardRightCameraCL_H
#define ForwardRightCameraCL_H

#include "Interface/IController.h"

class ForwardRightCameraCL : public IController
{
    Q_OBJECT
public:
    enum CLCmdType
    {
        CL_UpdateCamera,
        CL_StartPlay,

        CL_Max
    };
    explicit ForwardRightCameraCL(QObject *parent = nullptr);
    ~ForwardRightCameraCL() override;

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void getButton(int numb);

private:

};

#endif // ForwardRightCameraCL_H
