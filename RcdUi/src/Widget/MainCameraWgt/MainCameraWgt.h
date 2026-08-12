#ifndef MainCameraWgt_H
#define MainCameraWgt_H

#include "Interface/IFunWidget.h"
#include "MainCameraCL.h"
#include "MainCameraModel.h"
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "Component/gearProWidget.h"
#include <QFile>

// ---> START BAIYUN 2022/08/02
//#include "Component/TGFrame.h"
// <--- END

namespace Ui {
class MainCameraWgt;
}

class QStackedLayout;

class MainCameraWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit MainCameraWgt(QWidget *parent = nullptr);
    ~MainCameraWgt() override;

    static MainCameraWgt* GetInstance();
    virtual bool isQuit() override;
    virtual void initWidget() override;
    virtual void updateWidget() override;
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
    void  slotTimerTest();

// ---> START BAIYUN 2022/08/02
    bool get_net_usage();// show network speed
// <--- END

private:
    QString getRemoteStatusStr(MainCameraModel::RemoteStatus);
    void    changeLayout(int);
    void   clearLayout();
    Ui::MainCameraWgt *ui;
    static MainCameraWgt        *s_pInstance;
    MainCameraCL                *m_pCL;//控制类
    MainCameraModel             *m_pModel;//模型类
    QStackedLayout              *m_pSLayout;//布局
//    QGridLayout                 *_gridLayout = nullptr;
    int _isR = 0;

    QMap<ScreenAreaType,QWidget *>   m_pCurrentWgt;

    QTimer _testTimer;

    // --> BEGIN added by ZJZ, 2022/3/9
    QString strDriveMode = "";
    // <-- END

    QHBoxLayout *pHLayout = nullptr;
    QHBoxLayout *pHLayoutVideo = nullptr;
    bool isShowFrontLeftVideo = false;
    bool isShowFrontRightVideo = false;

    // ---> START BAIYUN 2022/08/02
    // show network speed
    QString strNetworkName = "";
    QTimer* _networkSpeedTimer;
    double m_timer_interval__ = 1000;
    double m_recv_bytes__ = 0;
    double m_send_bytes__ = 0;
    double m_recv_result__ = 0;
    QFile m_net_usage_file;
    QFile m_communication_delay_file;

    QHBoxLayout *pHLayoutNet = nullptr;
    // <--- END
};

#endif // MainCameraWgt_H
