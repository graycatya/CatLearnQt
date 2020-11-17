DEFINES += IMAGETOOL_VERSION=\\\"'v1.0.0'\\\"

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
