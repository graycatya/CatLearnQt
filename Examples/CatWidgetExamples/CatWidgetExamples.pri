SOURCES += \
    $$PWD/CatAbout.cpp \
    $$PWD/CatDrawingBoard.cpp \
    $$PWD/CatQuickWidget.cpp \
    $$PWD/CatSettings.cpp \
    $$PWD/CatWidget.cpp \
    $$PWD/WinWidget.cpp \
    $$PWD/WinMainWidget.cpp \

HEADERS += \
    $$PWD/CatAbout.h \
    $$PWD/CatDrawingBoard.h \
    $$PWD/CatQuickWidget.h \
    $$PWD/CatSettings.h \
    $$PWD/CatWidget.h \
    $$PWD/WinWidget.h \
    $$PWD/WinMainWidget.h \

FORMS += \
    $$PWD/CatAbout.ui \
    $$PWD/CatDrawingBoard.ui \
    $$PWD/CatQuickWidget.ui \
    $$PWD/CatSettings.ui \
    $$PWD/CatWidget.ui \
    $$PWD/WinWidget.ui \
    $$PWD/WinMainWidget.ui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}

!minQtVersion(5, 12, 0) {
    error("GrayCatQt minimum supported Qt5 version is 5.12.0")
}

include(CatConfig/CatConfig.pri)
include(WidgetTools/WidgetTools.pri)
include(QuickWidgetTools/QuickWidgetTools.pri)
