#-------------------------------------------------
#
# Project created by QtCreator 2020-07-24T13:30:15
#
#-------------------------------------------------
include(QsLog.pri)

QT       += core gui multimedia texttospeech
#QMAKE_CXXFLAGS += /MP
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  opengl gui network webenginewidgets concurrent quick sql
TARGET = RCD
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES +=  QT_NO_WARNING_OUTPUT \
#            QT_NO_DEBUG_OUTPUT \
#            QT_MESSAGELOGCONTEXT
DEFINES +=  QT_DEPRECATED_WARNINGS

# 移植HMI的3+6.+        
#DCU_VERSION=V06.80.09.02.02.03
#DEFINES += DCU_VERSION=\"\\\"$$DCU_VERSION\\\"\"

DEFINES += MAINPATHEXCAVATORID_FEATURE
DEFINES += PROTOCAL_TYPE=2
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

INCLUDEPATH += $$PWD/../../pubinc/fbs
#INCLUDEPATH += $$PWD/../../zmq_interface/zmqmodule
#INCLUDEPATH += $$PWD/../../zmq_interface/zmqmodule/product
#INCLUDEPATH += $$PWD/../../zmq_interface/zmqmodule/factory
#INCLUDEPATH += $$PWD/../../zmq_interface/zmqmodule/thread
#INCLUDEPATH += $$PWD/../../zmq_interface/platform/framework/common/include
#INCLUDEPATH += $$PWD/../../zmq_interface/platform/framework/common/include
#INCLUDEPATH += $$PWD/../../zmq_interface/platform/framework/fbs/out
#INCLUDEPATH += $$PWD/../../zmq_interface/platform/framework/zmq_wrapper/include


#LIBS += -L$$PWD/../../zmq_interface/lib

#LIBS += -lgcov
#LIBS += -lzmq
#LIBS += -lboost_log_setup
#LIBS += -lboost_system
#LIBS += -lboost_log
#LIBS += -lboost_graph
#LIBS += -lzmq_wrapper
#LIBS += -lzmq_interface

SOURCES += \
        Component/AnalogClock.cpp \
        Component/Dashboard.cpp \
        Component/OpenglWidget.cpp \
        Component/PageWgt.cpp \
        Component/RingDial.cpp \
        Component/RingDialPro.cpp \
        Component/SteerWheel.cpp \
        Component/StreamThread.cpp \
        Component/TGFrame.cpp \
        Component/TitleWgt.cpp \
        Component/TriangleFill.cpp \
        Component/WebEngine.cpp \
        Component/audiodecode.cpp \
        Component/baseForm.cpp \
        Component/basemsgdialog.cpp \
        Component/boundary/BoundaryLineWgt.cpp \
        Component/boundary/lane_display.cpp \
        Component/boundary/map_common.cpp \
        Component/btnForm.cpp \
        Component/buttonForm.cpp \
        Component/gearWidget.cpp \
        Component/gearProWidget.cpp \
#        Component/hikvisioncamera.cpp \
        Component/soundplay.cpp \
        Component/titleDateDriver.cpp \
        Component/trackline/track_line_predict.cpp \
        Component/trackline/trankLineW.cpp \
        FunModule/InteractiveManager.cpp \
        FunModule/IpcManager.cpp \
        Interface/IController.cpp \
        Interface/IFunWidget.cpp \
        Interface/IModel.cpp \
        Interface/WgtFactory.cpp \
        MainFile/LeftWgt.cpp \
        MainFile/LeftWgt1.cpp \
        MainFile/MainProcessor.cpp \
        MainFile/RightWgt1.cpp \
        MainFile/MidWgt.cpp \
        MainFile/Mainwindow.cpp \
        Protocol/HmiCmdPackage.cpp \
        Protocol/ZmqMsgPackage.cpp \
        Protocol/warnning.cpp \
        System.cpp \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkCL.cpp \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkModel.cpp \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkWgt.cpp \
        Widget/CloudWebWgt/CloudWebCL.cpp \
        Widget/CloudWebWgt/CloudWebModel.cpp \
        Widget/CloudWebWgt/CloudWebWgt.cpp \
        Widget/CompleteOperEndWgt/CompleteOperEndCL.cpp \
        Widget/CompleteOperEndWgt/CompleteOperEndModel.cpp \
        Widget/CompleteOperEndWgt/CompleteOperEndWgt.cpp \
        Widget/CompleteOperStartWgt/CompleteOperStartCL.cpp \
        Widget/CompleteOperStartWgt/CompleteOperStartModel.cpp \
        Widget/CompleteOperStartWgt/CompleteOperStartWgt.cpp \
        Widget/DriveCameraWgt/DriveCameraCL.cpp \
        Widget/DriveCameraWgt/DriveCameraWgt.cpp \
        Widget/FastStopWgt/FastStopCL.cpp \
        Widget/FastStopWgt/FastStopModel.cpp \
        Widget/FastStopWgt/FastStopWgt.cpp \
        Widget/ForwardRightCameraWgt/ForwardRightCameraCL.cpp \
        Widget/ForwardRightCameraWgt/ForwardRightCameraWgt.cpp \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverCL.cpp \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverModel.cpp \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverWgt.cpp \
        Widget/InfoWgt/InfoWgt.cpp \
        Widget/InfoWgt/infocl.cpp \
        Widget/InfoWgt/infomodel.cpp \
        Widget/LeftCameraWgt/LeftCameraCL.cpp \
        Widget/LeftCameraWgt/LeftCameraModel.cpp \
        Widget/LeftCameraWgt/LeftCameraWgt.cpp \
        Widget/LoadInstructionWgt/LoadInstructionWgt.cpp \
        Widget/LoadInstructionWgt/loadinstructioncl.cpp \
        Widget/LoadInstructionWgt/loadinstructionmodel.cpp \
        Widget/MainCameraTipWgt/MainCameraTipCL.cpp \
        Widget/MainCameraTipWgt/MainCameraTipModel.cpp \
        Widget/MainCameraTipWgt/MainCameraTipWgt.cpp \
        Widget/MainCameraWgt/MainCameraCL.cpp \
        Widget/MainCameraWgt/MainCameraModel.cpp \
        Widget/MainCameraWgt/MainCameraWgt.cpp \
        Widget/MainMonitorWgt/MainMonitorCL.cpp \
        Widget/MainMonitorWgt/MainMonitorModel.cpp \
        Widget/MainMonitorWgt/MainMonitorWgt.cpp \
        Widget/NetworkInterruptionWgt/NetworkInterruptionCL.cpp \
        Widget/NetworkInterruptionWgt/NetworkInterruptionModel.cpp \
        Widget/NetworkInterruptionWgt/NetworkInterruptionWgt.cpp \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverCL.cpp \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverModel.cpp \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverWgt.cpp \
        Widget/RightCameraWgt/RightCameraCL.cpp \
        Widget/RightCameraWgt/RightCameraModel.cpp \
        Widget/RightCameraWgt/RightCameraWgt.cpp \
        Widget/TakeOverInfoWgt/TakeOverInfoWgt.cpp \
        Widget/TakeOverInfoWgt/takeoverinfocl.cpp \
        Widget/TakeOverInfoWgt/takeoverinfomodel.cpp \
        Widget/TaskWorkChangeWgt/TaskWorkChangeCL.cpp \
        Widget/TaskWorkChangeWgt/TaskWorkChangeModel.cpp \
        Widget/TaskWorkChangeWgt/TaskWorkChangeWgt.cpp \
        Widget/UserGuideWgt/UserGuideCL.cpp \
        Widget/UserGuideWgt/UserGuideModel.cpp \
        Widget/UserGuideWgt/UserGuideWgt.cpp \
        Widget/VehicleDataWgt/VehicleDataWgt.cpp \
        Widget/VehicleDataWgt/vehicledatacl.cpp \
        Widget/VehicleDataWgt/vehicledatamodel.cpp \
        Widget/WarnInfoWgt/WarnInfoCL.cpp \
        Widget/WarnInfoWgt/WarnInfoModel.cpp \
        Widget/WarnInfoWgt/WarnInfoWgt.cpp \
        Widget/messageBox/msgCl.cpp \
        Widget/messageBox/msgModel.cpp \
        Widget/messageBox/msgWgt.cpp \
        Widget/TipsPopupWgt/TipsPopupCL.cpp \
        Widget/TipsPopupWgt/TipsPopupModel.cpp \
        Widget/TipsPopupWgt/TipsPopupWgt.cpp \
        Widget/selfTestWgt/selfTestCL.cpp \
        Widget/selfTestWgt/selfTestModel.cpp \
        Widget/selfTestWgt/selfTestWgt.cpp \
        main.cpp \
        public/baseThread.cpp \
        public/jsonMethord.cpp \
        public/screenRecordThread.cpp

HEADERS += \
        Component/AnalogClock.h \
        Component/Dashboard.h \
        Component/OpenglWidget.h \
        Component/PageWgt.h \
        Component/RingDial.h \
        Component/RingDialPro.h \
        Component/SteerWheel.h \
        Component/StreamThread.h \
        Component/TGFrame.h \
        Component/TitleWgt.h \
        Component/TriangleFill.h \
        Component/WebEngine.h \
        Component/audiodecode.h \
        Component/baseForm.h \
        Component/basemsgdialog.h \
        Component/boundary/BoundaryLineWgt.h \
        Component/boundary/lane_display.h \
        Component/boundary/map_common.h \
        Component/boundary/object.h \
        Component/btnForm.h \
        Component/buttonForm.h \
        Component/common/config_parser.hpp \
        Component/gearWidget.h \
        Component/gearProWidget.h \
#        Component/hikvisioncamera.h \
        Component/soundplay.h \
        Component/titleDateDriver.h \
        Component/trackline/track_line_predict.h \
        Component/trackline/trankLineW.h \
        FunModule/InteractiveManager.h \
        FunModule/IpcManager.h \
        Interface/IController.h \
        Interface/IFunWidget.h \
        Interface/IModel.h \
        Interface/WgtFactory.h \
        MainFile/LeftWgt.h \
        MainFile/LeftWgt1.h \
        MainFile/MainProcessor.h \
        MainFile/Mainwindow.h \
        MainFile/RightWgt1.h \
        MainFile/MidWgt.h \
        Protocol/HmiCmdPackage.h \
        Protocol/ZmqMsgPackage.h \
        Protocol/warnning.h \
        System.h \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkCL.h \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkModel.h \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkWgt.h \
        Widget/CloudWebWgt/CloudWebCL.h \
        Widget/CloudWebWgt/CloudWebModel.h \
        Widget/CloudWebWgt/CloudWebWgt.h \
        Widget/CompleteOperEndWgt/CompleteOperEndCL.h \
        Widget/CompleteOperEndWgt/CompleteOperEndModel.h \
        Widget/CompleteOperEndWgt/CompleteOperEndWgt.h \
        Widget/CompleteOperStartWgt/CompleteOperStartCL.h \
        Widget/CompleteOperStartWgt/CompleteOperStartModel.h \
        Widget/CompleteOperStartWgt/CompleteOperStartWgt.h \
        Widget/DriveCameraWgt/DriveCameraCL.h \
        Widget/DriveCameraWgt/DriveCameraWgt.h \
        Widget/FastStopWgt/FastStopCL.h \
        Widget/FastStopWgt/FastStopModel.h \
        Widget/FastStopWgt/FastStopWgt.h \
        Widget/ForwardRightCameraWgt/ForwardRightCameraCL.h \
        Widget/ForwardRightCameraWgt/ForwardRightCameraWgt.h \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverCL.h \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverModel.h \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverWgt.h \
        Widget/InfoWgt/InfoWgt.h \
        Widget/InfoWgt/infocl.h \
        Widget/InfoWgt/infomodel.h \
        Widget/LeftCameraWgt/LeftCameraCL.h \
        Widget/LeftCameraWgt/LeftCameraModel.h \
        Widget/LeftCameraWgt/LeftCameraWgt.h \
        Widget/LoadInstructionWgt/LoadInstructionWgt.h \
        Widget/LoadInstructionWgt/loadinstructioncl.h \
        Widget/LoadInstructionWgt/loadinstructionmodel.h \
        Widget/MainCameraTipWgt/MainCameraTipCL.h \
        Widget/MainCameraTipWgt/MainCameraTipModel.h \
        Widget/MainCameraTipWgt/MainCameraTipWgt.h \
        Widget/MainCameraWgt/MainCameraCL.h \
        Widget/MainCameraWgt/MainCameraModel.h \
        Widget/MainCameraWgt/MainCameraWgt.h \
        Widget/MainMonitorWgt/MainMonitorCL.h \
        Widget/MainMonitorWgt/MainMonitorModel.h \
        Widget/MainMonitorWgt/MainMonitorWgt.h \
        Widget/NetworkInterruptionWgt/NetworkInterruptionCL.h \
        Widget/NetworkInterruptionWgt/NetworkInterruptionModel.h \
        Widget/NetworkInterruptionWgt/NetworkInterruptionWgt.h \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverCL.h \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverModel.h \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverWgt.h \
        Widget/RightCameraWgt/RightCameraCL.h \
        Widget/RightCameraWgt/RightCameraModel.h \
        Widget/RightCameraWgt/RightCameraWgt.h \
        Widget/TakeOverInfoWgt/TakeOverInfoWgt.h \
        Widget/TakeOverInfoWgt/takeoverinfocl.h \
        Widget/TakeOverInfoWgt/takeoverinfomodel.h \
        Widget/TaskWorkChangeWgt/TaskWorkChangeCL.h \
        Widget/TaskWorkChangeWgt/TaskWorkChangeModel.h \
        Widget/TaskWorkChangeWgt/TaskWorkChangeWgt.h \
        Widget/UserGuideWgt/UserGuideCL.h \
        Widget/UserGuideWgt/UserGuideModel.h \
        Widget/UserGuideWgt/UserGuideWgt.h \
        Widget/VehicleDataWgt/VehicleDataWgt.h \
        Widget/VehicleDataWgt/vehicledatacl.h \
        Widget/VehicleDataWgt/vehicledatamodel.h \
        Widget/WarnInfoWgt/WarnInfoCL.h \
        Widget/WarnInfoWgt/WarnInfoModel.h \
        Widget/WarnInfoWgt/WarnInfoWgt.h \
        Widget/messageBox/msgCl.h \
        Widget/messageBox/msgModel.h \
        Widget/messageBox/msgWgt.h \
        Widget/TipsPopupWgt/TipsPopupCL.h \
        Widget/TipsPopupWgt/TipsPopupModel.h \
        Widget/TipsPopupWgt/TipsPopupWgt.h \
        Widget/selfTestWgt/selfTestCL.h \
        Widget/selfTestWgt/selfTestModel.h \
        Widget/selfTestWgt/selfTestWgt.h \
        public/baseThread.h \
        public/fbsstructure.h \
        public/jsonMethord.h \
        public/screenRecordThread.h

FORMS += \
        Component/baseForm.ui \
        Component/basemsgdialog.ui \
        Component/boundary/BoundaryLineWgt.ui \
        Component/buttonForm.ui \
        Component/gearWidget.ui \
        Component/gearProWidget.ui \
        Component/titleDateDriver.ui \
        Component/trackline/trankLineW.ui \
        MainFile/LeftWgt.ui \
        MainFile/LeftWgt1.ui \
        MainFile/Mainwindow.ui \
        MainFile/RightWgt1.ui \
        MainFile/MidWgt.ui \
        Widget/AcceptTaskWorkWgt/AcceptTaskWorkWgt.ui \
        Widget/CloudWebWgt/CloudWebWgt.ui \
        Widget/CompleteOperEndWgt/CompleteOperEndWgt.ui \
        Widget/CompleteOperStartWgt/CompleteOperStartWgt.ui \
        Widget/DriveCameraWgt/DriveCameraWgt.ui \
        Widget/FastStopWgt/FastStopWgt.ui \
        Widget/ForwardRightCameraWgt/ForwardRightCameraWgt.ui \
        Widget/GiveUpTakeOverWgt/GiveUpTakeOverWgt.ui \
        Widget/InfoWgt/InfoWgt.ui \
        Widget/LeftCameraWgt/LeftCameraWgt.ui \
        Widget/LoadInstructionWgt/LoadInstructionWgt.ui \
        Widget/MainCameraTipWgt/MainCameraTipWgt.ui \
        Widget/MainCameraWgt/MainCameraWgt.ui \
        Widget/MainMonitorWgt/MainMonitorWgt.ui \
        Widget/NetworkInterruptionWgt/NetworkInterruptionWgt.ui \
        Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverWgt.ui \
        Widget/RightCameraWgt/RightCameraWgt.ui \
        Widget/TakeOverInfoWgt/TakeOverInfoWgt.ui \
        Widget/TaskWorkChangeWgt/TaskWorkChangeWgt.ui \
        Widget/UserGuideWgt/UserGuideWgt.ui \
        Widget/VehicleDataWgt/VehicleDataWgt.ui \
        Widget/WarnInfoWgt/WarnInfoWgt.ui \
        Widget/messageBox/msgWgt.ui \
        Widget/TipsPopupWgt/TipsPopupWgt.ui \
        Widget/selfTestWgt/selfTestWgt.ui \

RESOURCES += \
    res.qrc

#        -lSDL2
#    INCLUDEPATH += $$PWD/third/libsqlite3/include
#    LIBS += -L$$PWD/third/libsqlite3/lib
#    INCLUDEPATH += /usr/local/include/libsqlite3
#    LIBS += = /usr/local/lib/libsqlite3
#    -lsqlite3

#LIBS +=-L$$PWD/third/libsqlite3/lib
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/map/
INCLUDEPATH += $$PWD/map/model

# deleted by zjz, 2022/6/15
#INCLUDEPATH += $$PWD/map/osg
#INCLUDEPATH += $$PWD/map/osg/poly2tri
#INCLUDEPATH += $$PWD/map/osg/poly2tri/common
#INCLUDEPATH += $$PWD/map/osg/poly2tri/sweep
#INCLUDEPATH += $$PWD/map/osg/proj

#QMAKE_CXXFLAGS_RELEASE = -Od -ZI -MD
#QMAKE_LFLAGS_RELEASE = /DEBUG /INCREMENTAL:NO

#INCLUDEPATH += /usr/local/include \
#        /usr/local/include/opencv2 \
#        /usr/local/include/osg
#INCLUDEPATH += /usr/include \

#LIBS += /usr/local/lib/libopencv_calib3d.so \
#/usr/local/lib/libopencv_core.so \
#/usr/local/lib/libopencv_features2d.so \
#/usr/local/lib/libopencv_flann.so \
#/usr/local/lib/libopencv_highgui.so \
#/usr/local/lib/libopencv_imgcodecs.so \
#/usr/local/lib/libopencv_imgproc.so \
#/usr/local/lib/libopencv_ml.so \
#/usr/local/lib/libopencv_objdetect.so \
#/usr/local/lib/libopencv_photo.so \
#/usr/local/lib/libopencv_shape.so \
#/usr/local/lib/libopencv_stitching.so \
#/usr/local/lib/libopencv_superres.so \
#/usr/local/lib/libopencv_videoio.so \
#/usr/local/lib/libopencv_video.so \
#/usr/local/lib/libopencv_videostab.so
#/usr/local/lib/libopencv_calib3d.so \

#LIBS +=/usr/local/lib
#LIBS += -lproj

# deleted by zjz, 2022/6/15
#LIBS +=/usr/local/lib/libosg.so
#LIBS +=/usr/local/lib/libosgDB.so
#LIBS +=/usr/local/lib/libosgFX.so
#LIBS +=/usr/local/lib/libosgGA.so
#LIBS +=/usr/local/lib/libosgUI.so
#LIBS +=/usr/local/lib/libosgViewer.so
#LIBS +=/usr/local/lib/libosgText.so
#LIBS +=/usr/local/lib/libosgUtil.so

#LIBS +=/usr/local/lib/libosgSim.so
#LIBS +=/usr/local/lib/libosgShadow.so
#LIBS +=/usr/local/lib/libproj.so
#LIBS +=/usr/local/lib/libproj.so.12
#LIBS +=/usr/local/lib/libproj.so.12.0.0
# 勿写死 libproj.so.12 全路径：不同发行版 SONAME 不同；用 -lproj 由系统解析
unix:!macx:LIBS += -lproj
LIBS +=/usr/local/lib/libOpenThreads.so

# --> BEGIN modify by ZJZ, 2022/3/21
DEFINES += HIK_INTERFACE
DEFINES += USE_LIBDATACHANNEL_RTC

INCLUDEPATH += /usr/local/include
LIBS += -lzmq -lboost_system
LIBS += -L/usr/local/lib -ldatachannel

if(contains(DEFINES,HIK_INTERFACE)) {# 海康
    SOURCES += \
            Component/hikvisioncamera.cpp \
            Component/RtcPlayer.cpp

    HEADERS += \
            Component/hikvisioncamera.h \
            Component/RtcPlayer.h

    CONFIG += link_pkgconfig
    PKGCONFIG += gstreamer-1.0 gstreamer-app-1.0 gstreamer-video-1.0 gstreamer-webrtc-1.0
    unix:!macx {
        INCLUDEPATH += /usr/include/gstreamer-1.0
        INCLUDEPATH += /usr/include/glib-2.0
        exists(/usr/lib/x86_64-linux-gnu/glib-2.0/include) {
            INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include
        }
        exists(/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include) {
            INCLUDEPATH += /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
        }
        exists(/usr/lib/aarch64-linux-gnu/glib-2.0/include) {
            INCLUDEPATH += /usr/lib/aarch64-linux-gnu/glib-2.0/include
        }
        exists(/usr/lib/aarch64-linux-gnu/gstreamer-1.0/include) {
            INCLUDEPATH += /usr/lib/aarch64-linux-gnu/gstreamer-1.0/include
        }
        LIBS += -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstapp-1.0 -lgstvideo-1.0 \
                 -lgstbase-1.0 -lgstwebrtc-1.0 -lgstsdp-1.0
    }

    LIBS += -L/usr/local/lib -lavcodec -lavdevice -lavfilter \
            -lavformat -lavutil -lpostproc \
            -lswresample -lswscale #-lzmq -lsqlite3

    LIBS += -L$$PWD/lib/ -lcrypto\
                 -lHCNetUtils\
                 -lhlog\
                 -lHttpUtil\
                 -lCsfTraceChain\
                 -lHikCsf\
                 -lhpr\
                 -lssl
} else {# 清流
    LIBS += -L$$PWD/libs/ -lPI_MediaCore\
                 -lPI_iLiveBase\
                 -lUAC\
                 -lPI_MediaPlayer\
                 -lPIAudioProcessing\
                 -lSDL2-2.0\
                 -lavcodec\
                 -lavformat\
                 -lavutil\
                 -lswresample\
                 -lswscale\
                 -lpi_ws
}
# <-- END
