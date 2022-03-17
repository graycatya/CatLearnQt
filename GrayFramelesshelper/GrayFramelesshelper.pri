qtHaveModule(widgets): SUBDIRS += widget mainwindow
qtHaveModule(quick): SUBDIRS += quick
CONFIG -= ordered

QT += core gui
QT += core-private gui-private

CONFIG += c++17 strict_c++ utf8_source warn_on

DEFINES += \
    #QT_NO_CAST_FROM_ASCII \
    #QT_NO_CAST_TO_ASCII \
    #QT_NO_KEYWORDS \
    #QT_DEPRECATED_WARNINGS \
    #QT_DISABLE_DEPRECATED_BEFORE=0x060100 \
    FRAMELESSHELPER_BUILD_LIBRARY

HEADERS += \
    $$PWD/framelesshelper_global.h \
    $$PWD/framelesshelper.h \
    $$PWD/framelesswindowsmanager.h \
    $$PWD/utilities.h
SOURCES += \
    $$PWD/framelesshelper.cpp \
    $$PWD/framelesswindowsmanager.cpp \
    $$PWD/utilities.cpp
qtHaveModule(quick) {
    QT += quick
    HEADERS += $$PWD/framelessquickhelper.h
    SOURCES += $$PWD/framelessquickhelper.cpp
}
win32 {
    HEADERS += \
        $$PWD/framelesshelper_windows.h \
        $$PWD/framelesshelper_win32.h \
        $$PWD/qwinregistry_p.h
    SOURCES += \
        $$PWD/utilities_win32.cpp \
        $$PWD/framelesshelper_win32.cpp \
        $$PWD/qwinregistry.cpp
    LIBS += -luser32 -lshell32 -ladvapi32
}
linux* {
    QT += x11extras
    SOURCES += $$PWD/utilities_linux.cpp
    LIBS += -lX11
}

macx {
    OBJECTIVE_HEADERS += \
        $$PWD/nswindow_proxy.h \
        $$PWD/scoped_nsobject.h \
        $$PWD/window_buttons_proxy.h
    OBJECTIVE_SOURCES += \
        $$PWD/utilities_macos.mm \
        $$PWD/nswindow_proxy.mm \
        $$PWD/window_buttons_proxy.mm
    LIBS += -framework CoreServices
    LIBS += -framework Foundation
    LIBS += -framework CoreFoundation
    LIBS += -framework Carbon
    LIBS += -lobjc
    LIBS += -framework AppKit
    DEFINES += OBJC_OLD_DISPATCH_PROTOTYPES
}

INCLUDEPATH += $$PWD

