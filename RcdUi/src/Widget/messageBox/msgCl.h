#ifndef MSGCL_H
#define MSGCL_H
#include "Interface/IController.h"
#include "msgModel.h"
class msgCl : public IController
{
     Q_OBJECT
public:
    explicit msgCl(QObject *parent = nullptr);
    ~msgCl() override;

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void getButton(int numb);
    void setModel(msgModel *model);

private:

    void inputHandler(Qt::Key key);
    void vehicleStatusHandler(QVariant &data);
    void refreshDisplayData();

    msgModel *m_pModel;
    bool _isAcceptTask = false;





};


#endif // MSGCL_H
