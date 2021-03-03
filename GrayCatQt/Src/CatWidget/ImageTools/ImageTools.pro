QT       += core svg widgets gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib

DEFINES += IMAGETOOL_VERSION=\\\"'v1.0.0'\\\"

unix {
    QT += x11extras
    LIBS += -lX11
}

macx {
    QT -= x11extras
    LIBS -= -lX11
}

android {
    QT -= x11extras
    LIBS -= -lX11
}

ios {
    QT -= x11extras
    LIBS -= -lX11
}

if(contains(DEFINES,WEBASSEMBLY)) {
    QT -= x11extras
    LIBS -= -lX11
}

HEADERS += \
    $$PWD/ButtonTool.h \
    $$PWD/CatGifTool.h \
    $$PWD/GifButtonWidget.h \
    $$PWD/ImageToolBase.h \
    $$PWD/ImageToolFactory.h \
    $$PWD/MagnifyingGlass.h \
    $$PWD/ProcessObject.h \
    $$PWD/RimlessWindowBase.h \
    $$PWD/ScreenShot.h \
    $$PWD/SpotLight.h \
    $$PWD/gif.h

SOURCES += \
    $$PWD/ButtonTool.cpp \
    $$PWD/CatGifTool.cpp \
    $$PWD/GifButtonWidget.cpp \
    $$PWD/ImageToolBase.cpp \
    $$PWD/ImageToolFactory.cpp \
    $$PWD/MagnifyingGlass.cpp \
    $$PWD/ProcessObject.cpp \
    $$PWD/RimlessWindowBase.cpp \
    $$PWD/ScreenShot.cpp \
    $$PWD/SpotLight.cpp

INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/ImageTools/ImageTools.qrc

FORMS += \
    $$PWD/GifButtonWidget.ui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
