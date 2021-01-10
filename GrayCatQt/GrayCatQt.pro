QT += core gui sql

QT += quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
contains(QT_CONFIG, opengl): QT += opengl

CONFIG += c++11
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui

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
    error("CatLearnQt minimum supported Qt5 version is 5.12.0")
}


DEFINES += APP_VERSION=\\\"'v1.0.0'\\\"
DEFINES += LOG_PATH=\\\"'Logs/'\\\"
DEFINES += APP_NAME=\\\"'CatLearnQt'\\\"


INCLUDEPATH += Src

include(main/main.pri)
include(Src/SingleApplication/singleapplication.pri)
include(Src/CatUniversal/CatUniversal.pri)
include(Src/CatNetWork/CatNetWork.pri)
include(Src/CatLog/CatLog.pri)
include(Src/CatWidget/CatWidget.pri)
include(Src/CatGraphicsView/CatGraphicsView.pri)
include(Src/CatSerial/CatSerial.pri)
include(Src/CatControl/CatControl.pri)

RESOURCES += \
    Resource/Resource.qrc

TRANSLATIONS = Resource/lang/language_en.ts \
               Resource/lang/language_zh_CN.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


