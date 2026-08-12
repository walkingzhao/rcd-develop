QT -= gui

CONFIG += console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    ../pubQsLog/QsLog.cpp \
    ../pubQsLog/QsLogDest.cpp \
    ../pubQsLog/QsLogDestConsole.cpp \
    ../pubQsLog/QsLogDestFile.cpp \
    src/cloudamqpserver.cpp \
    src/main.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../pubQsLog/QsLog.h \
    ../pubQsLog/QsLogDest.h \
    ../pubQsLog/QsLogDestConsole.h \
    ../pubQsLog/QsLogDestFile.h \
    ../pubQsLog/QsLogLevel.h \
    inc/cloudamqpserver.h \
    inc/download.hpp \
    inc/queueMsg.hpp

HEADERS += ../pubinc/

INCLUDEPATH += ./inc/
INCLUDEPATH += ../pubQsLog/
INCLUDEPATH += ../pubinc/

unix|win32: LIBS += -L/usr/local/lib/ -lSimpleAmqpClient

unix|win32: LIBS += -lzmq

unix|win32: LIBS += -lcurl
