QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

DEFINES += QCUSTOMPLOT_USE_OPENGL

win32 {

msvc {
    INCLUDEPATH += $$PWD/Freeglut/MSVC/include/
contains(QT_ARCH, i386) {
    LIBS += -L$$PWD/Freeglut/MSVC/lib/ -lfreeglut
} else {
    LIBS += -L$$PWD/Freeglut/MSVC/lib/x64 -lfreeglut
}
    LIBS += -lOpengl32
}

mingw {
    INCLUDEPATH += $$PWD/Freeglut/MinGW/include/
contains(QT_ARCH, i386) {
    LIBS += -L$$PWD/Freeglut/MinGW/lib/ -lfreeglut_static
} else {
    LIBS += -L$$PWD/Freeglut/MinGW/lib/x64 -lfreeglut_static
}
    LIBS += -lOpengl32
}

}

unix {
    LIBS += -lGL #-lglut
}

macos {
    LIBS -= -lGL -lglut
}

#表示arm平台构建套件
contains(DEFINES,ANDROID_APP) {
    LIBS -= -lGL -lglut
}



greaterThan(QT_MAJOR_VERSION, 4) printsupport

HEADERS += \
    $$PWD/CatAxisTag.h \
    $$PWD/CatBars.h \
    $$PWD/CatQcustomplot.h \
    $$PWD/qcustomplot.h

SOURCES += \
    $$PWD/CatAxisTag.cpp \
    $$PWD/CatBars.cpp \
    $$PWD/CatQcustomplot.cpp \
    $$PWD/qcustomplot.cpp

include(CatQcustomplotCharts/CatQcustomplotCharts.pri)
