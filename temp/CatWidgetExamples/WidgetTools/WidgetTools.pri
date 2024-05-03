FORMS += \
    $$PWD/ImageTools.ui \
    $$PWD/InputTools.ui \
    $$PWD/PagingNavigationTools.ui \
    $$PWD/QrenCodeTool.ui \
    $$PWD/RimlessWindowTool.ui \
    $$PWD/SideColumnTool.ui \
    $$PWD/SliderTools.ui \
    $$PWD/TableViewTool.ui

HEADERS += \
    $$PWD/ImageTools.h \
    $$PWD/InputTools.h \
    $$PWD/PagingNavigationTools.h \
    $$PWD/QrenCodeTool.h \
    $$PWD/RimlessWindow.h \
    $$PWD/RimlessWindowTool.h \
    $$PWD/SideColumnTool.h \
    $$PWD/SliderTools.h \
    $$PWD/TableViewTool.h

SOURCES += \
    $$PWD/ImageTools.cpp \
    $$PWD/InputTools.cpp \
    $$PWD/PagingNavigationTools.cpp \
    $$PWD/QrenCodeTool.cpp \
    $$PWD/RimlessWindow.cpp \
    $$PWD/RimlessWindowTool.cpp \
    $$PWD/SideColumnTool.cpp \
    $$PWD/SliderTools.cpp \
    $$PWD/TableViewTool.cpp



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

include(InputTools/InputTools.pri)

include(CatTableViewTools/CatTableViewTools.pri)

INCLUDEPATH += $$PWD

