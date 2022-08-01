if(!contains(DEFINES,WEBASSEMBLY)) {
QT += quick quickwidgets
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

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


INCLUDEPATH += $$PWD/Src
include($$PWD/Src/CatWidget/CatWidget.pri)
include($$PWD/Src/CatGraphicsView/CatGraphicsView.pri)
include($$PWD/Src/CatControl/CatControl.pri)
#include($$PWD/Src/CatWidgetFrameless/CatWidgetFrameless.pri)
