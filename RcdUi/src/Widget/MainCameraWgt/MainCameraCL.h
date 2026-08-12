#ifndef MainCameraCL_H
#define MainCameraCL_H

#include "Interface/IController.h"
#include "MainCameraModel.h"
#include <QTimer>
#include <QThread>
#include "public/screenRecordThread.h"
#include "FunModule/IpcManager.h"

// ---> START BAIYUN 2022/08/02
//#include "../../Component/common/config_parser.hpp"
// <--- END

class MainCameraCL : public IController
{
    Q_OBJECT
public:
    explicit MainCameraCL(QObject *parent = nullptr);
    ~MainCameraCL() override;

    enum CLCmdType
    {
        CL_InputKey,
        CL_UpdateLoginStatus,
        CL_UpdateState,
        CL_UpdateCloudyState,
        CL_UpdatePosition,
        CL_UpdateFrontLeftRightCamera,
        CL_StartPlay,

        CL_Max
    };

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(MainCameraModel *model);

// ---> START BAIYUN 2022/08/02
private:
//    void readTrackLineCfgFile();
//    common::ConfigParserPtr config_parser_ptr_;//配置文件获取
// <--- END

private:
    void inputHandler(Qt::Key key);

    MainCameraModel *m_pModel;
    int _flag = 1;
    screenRecordThread * _screenThread = nullptr;
    QThread * _thread = nullptr;

    // --> BEGIN added by ZJZ, 2022/3/3
    QTimer *timer_checkSelfMode = nullptr;
    int iSelfModeCnt = 15;// data coming every two second
private slots:
    void slot_timer_checkSelfMode();
    // <-- END
};

#endif // MainCameraCL_H
