QT += core gui quick

include(QrenCodeSrc/QrenCodeSrc.pri)

HEADERS += \
    $$PWD/QuickQrenCodeParentItem.h \
    $$PWD/QtQrenCode.h \

SOURCES += \
    $$PWD/QuickQrenCodeParentItem.cpp \
    $$PWD/QtQrenCode.cpp \
