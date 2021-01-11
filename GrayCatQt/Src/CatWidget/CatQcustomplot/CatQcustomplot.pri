QT += printsupport

contains(QT_CONFIG, opengl): QT += opengl

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
    #LIBS += -lGL #-lglut
}

macos {
    LIBS -= -lGL -lglut
}

#表示arm平台构建套件
contains(QT_ARCH, arm) {
    LIBS -= -lGL -lglut
}

greaterThan(QT_MAJOR_VERSION, 4) printsupport

HEADERS += \
    $$PWD/CatAxisTag.h \
    $$PWD/CatQcustomplot.h \
    $$PWD/qcustomplot.h

SOURCES += \
    $$PWD/CatAxisTag.cpp \
    $$PWD/CatQcustomplot.cpp \
    $$PWD/qcustomplot.cpp

include(CatQcustomplotCharts/CatQcustomplotCharts.pri)
