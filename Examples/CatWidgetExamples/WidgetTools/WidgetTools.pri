FORMS += \
    $$PWD/ImageTools.ui \
    $$PWD/PagingNavigationTools.ui \
    $$PWD/QrenCodeTool.ui \
    $$PWD/RimlessWindowTool.ui \
    $$PWD/SideColumnTool.ui \
    $$PWD/SliderTools.ui

HEADERS += \
    $$PWD/ImageTools.h \
    $$PWD/PagingNavigationTools.h \
    $$PWD/QrenCodeTool.h \
    $$PWD/RimlessWindow.h \
    $$PWD/RimlessWindowTool.h \
    $$PWD/SideColumnTool.h \
    $$PWD/SliderTools.h

SOURCES += \
    $$PWD/ImageTools.cpp \
    $$PWD/PagingNavigationTools.cpp \
    $$PWD/QrenCodeTool.cpp \
    $$PWD/RimlessWindow.cpp \
    $$PWD/RimlessWindowTool.cpp \
    $$PWD/SideColumnTool.cpp \
    $$PWD/SliderTools.cpp


if(!contains(DEFINES,IOS_APP)) {

FORMS += \
    $$PWD/CatQcustomplotTools.ui
HEADERS += \
    $$PWD/CatQcustomplotTools.h
SOURCES += \
    $$PWD/CatQcustomplotTools.cpp

include(QcustomplotCharts/QcustomplotCharts.pri)

}

include(SideWidgetTools/SideWidgetTools.pri)

