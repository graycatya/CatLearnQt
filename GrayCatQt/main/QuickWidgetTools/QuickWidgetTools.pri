QT += quick quickwidgets

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_QML_DEBUG_NO_WARNING

FORMS += \
    $$PWD/QuickQrenCode.ui \
    $$PWD/QuickSliders.ui

HEADERS += \
    $$PWD/QuickQrenCode.h \
    $$PWD/QuickSliders.h

SOURCES += \
    $$PWD/QuickQrenCode.cpp \
    $$PWD/QuickSliders.cpp
