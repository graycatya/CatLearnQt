QT += core gui quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11

TARGET = CatSoftwareStarter

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
DEFINES += APP_NAME=\\\"'CatSoftwareStarter'\\\"

include($$PWD/../../GrayCatQt/GrayCatQt.pri)
include($$PWD/../../GrayCatQtCore/GrayCatQtCore.pri)
include($$PWD/../../GrayCatQtQuick/GrayCatQtQuick.pri)


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CatTitleWidget.cpp \
    MainWindow.cpp \
    main.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    MainWindow.ui

HEADERS += \
    CatTitleWidget.h \
    MainWindow.h
