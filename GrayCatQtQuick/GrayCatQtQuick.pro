TEMPLATE = lib

QT += quick

CONFIG += c++11
#CONFIG += staticlib

TARGET = GrayCatQtQuick

DEFINES += QT_DEPRECATED_WARNINGS

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc

#判断Qt版本
lessThan(QT_MAJOR_VERSION, 6) {
    include($$PWD/imports/GrayCatQt5Compat/imports.pri)
} else {
    include($$PWD/imports/GrayCatQt6Compat/imports.pri)
}
#include($$PWD/imports/imports.pri)
include($$PWD/Src/CatModel/CatModel.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target