TEMPLATE = lib

QT += core gui sql

QT += quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11
CONFIG += staticlib

TARGET = GrayCatQt
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS


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


INCLUDEPATH += Src
include(Src/SingleApplication/singleapplication.pri)
include(Src/CatUniversal/CatUniversal.pri)
include(Src/CatNetWork/CatNetWork.pri)
include(Src/CatLog/CatLog.pri)
include(Src/CatWidget/CatWidget.pri)
include(Src/CatGraphicsView/CatGraphicsView.pri)
if(!contains(DEFINES,IOS_APP)) {
include(Src/CatSerial/CatSerial.pri)
}
include(Src/CatControl/CatControl.pri)

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
