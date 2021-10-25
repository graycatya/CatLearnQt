QT += core remoteobjects websockets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += COREAPP

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/../../../GrayCatQtCore/GrayCatQtCore.pri)

SOURCES += \
    main.cpp 

REPC_SOURCE = \
    ../RepResource/CatSerialRemote.rep