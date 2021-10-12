QT += quick quickcontrols2

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += BENCHMARK
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/CatListModel.h \
    $$PWD/CatTreeModel.h \
    $$PWD/ModelTools.h

SOURCES += \
    $$PWD/CatListModel.cpp \
    $$PWD/CatTreeModel.cpp

