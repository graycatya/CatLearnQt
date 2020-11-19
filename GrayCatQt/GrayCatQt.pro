QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11
# CONFIG += console
CONFIG -= qml_debug


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_QML_DEBUG_NO_WARNING

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui


DEFINES += APP_VERSION=\\\"'v1.0.0'\\\"
DEFINES += LOG_PATH=\\\"'Logs/'\\\"


INCLUDEPATH += Src

include(main/main.pri)
include(Src/SingleApplication/singleapplication.pri)
include(Src/CatUniversal/CatUniversal.pri)
include(Src/CatNetWork/CatNetWork.pri)
include(Src/CatLog/CatLog.pri)
include(Src/CatWidget/CatWidget.pri)
include(Src/CatGraphicsView/CatGraphicsView.pri)
include(Src/CatSerial/CatSerial.pri)

RESOURCES += \
    Resource/Resource.qrc

