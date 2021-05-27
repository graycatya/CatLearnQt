TEMPLATE = lib

QT += core gui
if(!contains(DEFINES,WEBASSEMBLY)) {
QT += sql
}

#QT += quick quickwidgets


#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11
#CONFIG += staticlib

TARGET = GrayCatQtCore
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += ANDROID_APP

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
include($$PWD/Src/CatNetWork/CatNetWork.pri)
}
include(Src/CatUniversal/CatUniversal.pri)
include(Src/CatLog/CatLog.pri)
if(!contains(DEFINES,IOS_APP)) {
if(!contains(DEFINES,WEBASSEMBLY)) {
include(Src/CatSerial/CatSerial.pri)
}
}