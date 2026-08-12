#ifndef UserGuideCL_H
#define UserGuideCL_H

#include "Interface/IController.h"
#include "UserGuideModel.h"

class UserGuideCL : public IController
{
    Q_OBJECT
public:
    explicit UserGuideCL(QObject *parent = nullptr);
    ~UserGuideCL() override;

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void getButton(int numb);
    void setModel(UserGuideModel *model);

private:

    UserGuideModel *m_pModel;
};

#endif // UserGuideCL_H
