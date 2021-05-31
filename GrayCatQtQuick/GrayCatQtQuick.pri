QT += quick gui core

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
    error("GrayCatQtQuick minimum supported Qt5 version is 5.12.0")
}

CONFIG(debug,debug|release){
    # debug mode use local file
    win32{
        path=$$system("cd")
        path ~=s,\\\\,/,g
    } else {
        path=$$system("pwd")
    }
    GrayCatQtQuickImport=\"file:///$$path\"
    #GrayCatQtQuickImage=\"file:///$$path/GrayCatQtQuick/Images/\"
    DEFINES += GrayCatQtQuickImportPath=\\\"file:///$${path}\\\"
    #DEFINES += GrayCatQtQuickImagePath=\\\"file:///$${path}/GrayCatQtQuick/Images/\\\"
} else {
    # release mode use qrc file
    RESOURCES += $$PWD/GrayCatQtQuick.qrc
    # release mode set importPath with 'qrc:///'
    GrayCatQtQuickImport=\"qrc:/\"
    #GrayCatQtQuickImage=\"qrc:/GrayCatQtQuick/Images/\"
    DEFINES += GrayCatQtQuickImportPath=\\\"qrc:///GrayCatQtQuick///\\\"
    #DEFINES += GrayCatQtQuickImagePath=\\\"qrc:/GrayCatQtQuick/Images/\\\"
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH	= $$PWD
QML2_IMPORT_PATH = $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD


INCLUDEPATH += $$PWD/Src

include($$PWD/Src/CatFrameless/CatFrameless.pri)

#RESOURCES += \
#    $$PWD/GrayCatQtQuick.qrc
