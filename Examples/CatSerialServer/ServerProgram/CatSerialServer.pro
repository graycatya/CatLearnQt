QT += core remoteobjects websockets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += COREAPP

#CONFIG +=console

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/../../../GrayCatQtCore/GrayCatQtCore.pri)

SOURCES += \
    ServerConfig.cpp \
    Src/SerialDevList.cpp \
    Src/SerialServerInitialize.cpp \
    Src/SerialServerRemote.cpp \
    Src/SerialServerWebSocket.cpp \
    main.cpp 

REPC_SOURCE += \
    ../RepResource/CatSerialRemote.rep

HEADERS += \
    ServerConfig.h \
    Src/SerialDevList.h \
    Src/SerialServerInitialize.h \
    Src/SerialServerRemote.h \
    Src/SerialServerWebSocket.h


win32 {
#QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\" #以管理员运行

#QMAKE_LFLAGS += /SUBSYSTEM:WINDOWS,\"5.01\" #VS2013 在XP运行
}
