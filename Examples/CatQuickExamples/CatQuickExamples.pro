QT += core gui quick 

CONFIG += c++11
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = CatQuickExamples

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

include($$PWD/../../GrayCatQtQuick/GrayCatQtQuick.pri)

SOURCES += \
    main.cpp

RESOURCES += \
    QmlSrc/QmlSrc.qrc
