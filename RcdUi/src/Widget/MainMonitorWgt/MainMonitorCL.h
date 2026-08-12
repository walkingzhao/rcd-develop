#ifndef MainMonitorCL_H
#define MainMonitorCL_H

#include "Interface/IController.h"
#include "MainMonitorModel.h"
#include <QMessageBox>

class MainMonitorCL : public IController
{
    Q_OBJECT
public:
    explicit MainMonitorCL(QObject *parent = nullptr);
    ~MainMonitorCL() override;

    enum CLCmdType
    {
        CL_UpdateAll=0,
        CL_UpdateLoginStatus,
        CL_UpdateVehicle,
        CL_UpdateSelect,
        CL_UpdateOnlineState,
        CL_InputKey,
        CL_CloseTip,

        CL_Max
    };

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void getButton(int numb);
    void setModel(MainMonitorModel *model);
    void keyPress();
    void pageUpkeyPress();
    void keyEmpty();

private:
    void inputHandler(Qt::Key key);
    void vehicleStatusHandler(QVariant &data);
    void refreshDisplayData();
    void setMessageStyle(QMessageBox* m,QString text,QSize size);

    MainMonitorModel *m_pModel;
    bool _isAcceptTask = false;
    QMessageBox *m_msgBox = nullptr;// 系统提示框是否进入遥控驾驶舱/退出程序
    QMessageBox *m_msgEmergency = nullptr;// 系统提示框 emergcy button pressed

    // --> BEGIN added by ZJZ, 2022/3/1
//    QTimer *timer_checkCloudy = nullptr;
//    int iCloudyHeartCnt = 6;// data coming every two second
    QTime cloudyComingTime;


private slots:
    //void slot_timer_checkCloudy();
    // <-- END
};

#endif // MainMonitorCL_H
