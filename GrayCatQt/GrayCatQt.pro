TEMPLATE = lib

QT += core gui
if(!contains(DEFINES,WEBASSEMBLY)) {
QT += sql
}

QT += quick quickwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11
CONFIG += staticlib

TARGET = GrayCatQt
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc


INCLUDEPATH += Src
if(!contains(DEFINES,WEBASSEMBLY)) {
include($$PWD/Src/SingleApplication/singleapplication.pri)
include($$PWD/Src/CatNetWork/CatNetWork.pri)
}
include(Src/CatUniversal/CatUniversal.pri)
include(Src/CatLog/CatLog.pri)
include(Src/CatWidget/CatWidget.pri)
include(Src/CatGraphicsView/CatGraphicsView.pri)
if(!contains(DEFINES,IOS_APP)) {
if(!contains(DEFINES,WEBASSEMBLY)) {
include(Src/CatSerial/CatSerial.pri)
}
}
include(Src/CatControl/CatControl.pri)

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
