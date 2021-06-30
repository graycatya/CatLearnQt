QT += core gui quick quick3d

CONFIG += c++11
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_OS_WIN10

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
include($$PWD/QrenCode/QrenCode.pri)
include($$PWD/QmlCatLog/QmlCatLog.pri)

SOURCES += \
    main.cpp

RESOURCES += \
    QmlSrc/QmlSrc.qrc \
    Resource/Resource.qrc

TRANSLATIONS = $$PWD/Resource/Lang/language_en.ts \
                $$PWD/Resource/lang/language_zh_CN.ts

win32 {
    RC_ICONS += Resource\Images\applogo.ico
}
