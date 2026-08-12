#-------------------------------------------------
#
# Project created by QtCreator 2020-07-14T20:49:52
#
#-------------------------------------------------

QT -= gui
CONFIG += console
CONFIG -= app_bundle

QT += serialbus serialport network core

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++17

INCLUDEPATH += /usr/local/include/hidapi/
INCLUDEPATH += ../pubinc/
INCLUDEPATH += ./include/
INCLUDEPATH += ../pubQsLog/



SOURCES += ../pubQsLog/QsLog.cpp \
           ../pubQsLog/QsLogDest.cpp \
           ../pubQsLog/QsLogDestConsole.cpp \
           ../pubQsLog/QsLogDestFile.cpp \
           src/controlpub.cpp \
           src/fison.cpp \
           src/main.cpp

HEADERS += ../pubQsLog/QsLog.h \
           ../pubQsLog/QsLogDest.h \
           ../pubQsLog/QsLogDestConsole.h \
           ../pubQsLog/QsLogDestFile.h \
           ../pubQsLog/QsLogLevel.h \
           include/controlpub.h \
           include/fison.h \
           include/mydebug.h

HEADERS += ../pubinc/

LIBS += -L"/usr/local/lib/" -lhidapi-libusb -lusb-1.0
LIBS += -lzmq -lpthread


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ReadMe.md
