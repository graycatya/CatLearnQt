DEFINES += TEAHINGTOOL_VERSION=\\\"'v1.0.0'\\\"

QT       += svg

lessThan(QT_MAJOR_VERSION, 6) {

} else {
QT += svgwidgets
}

RESOURCES += \
    $$PWD/TeachingTool/TeachingTool.qrc

HEADERS += \
    $$PWD/AbsTeachingTool.h \
    $$PWD/CatMath.h \
    $$PWD/TeachingToolCompass.h \
    $$PWD/TeachingToolProtractor.h \
    $$PWD/TeachingToolRuler.h \
    $$PWD/TeachingToolTrangle.h

SOURCES += \
    $$PWD/CatMath.cpp \
    $$PWD/TeachingToolCompass.cpp \
    $$PWD/TeachingToolProtractor.cpp \
    $$PWD/TeachingToolRuler.cpp \
    $$PWD/TeachingToolTrangle.cpp
