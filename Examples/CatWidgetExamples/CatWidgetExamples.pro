QT += core gui sql
if(!contains(DEFINES,WEBASSEMBLY)) {
QT -= sql
}
QT += quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = CatLearnQtWidget


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

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
DEFINES += APP_NAME=\\\"'CatWidgetExamples'\\\"

include($$PWD/CatWidgetExamples.pri)
include($$PWD/../../GrayCatQt/GrayCatQt.pri)

RESOURCES += \
    Resource/Resource.qrc

TRANSLATIONS = Resource/lang/language_en.ts \
               Resource/lang/language_zh_CN.ts

SOURCES += \
    main.cpp
