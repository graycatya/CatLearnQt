QT += core gui quick

msvc {
    QT += webengine webchannel websocket
}

mac {
    QT += webengine webchannel websocket
}

DEFINES += WEBRESOURCEPATH=\\\"file:///$$PWD/WebResource\\\"

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

minQtVersion(5, 15, 0) {
    QT += quick3d
}



CONFIG += c++11
# CONFIG += console

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
    DEFINES += QT_OS_WIN10
}

TARGET = CatQuickExamples

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

include($$PWD/../../GrayCatQtQuick/GrayCatQtQuick.pri)
include($$PWD/../../GrayCatQtCore/Src/CatUniversal/CatUniversal.pri)
include($$PWD/QrenCode/QrenCode.pri)
include($$PWD/QmlCatLog/QmlCatLog.pri)
include($$PWD/src/WebChannelFunction/WebChannelFunction.pri)

SOURCES += \
    CatConfig.cpp \
    main.cpp

RESOURCES += \
    QmlSrc/QmlSrc.qrc \
    Resource/Resource.qrc

TRANSLATIONS = $$PWD/Resource/Lang/language_en.ts \
                $$PWD/Resource/lang/language_zh_CN.ts

win32 {
    RC_ICONS += Resource\Images\applogo.ico
}

HEADERS += \
    CatConfig.h
