CONFIG(debug,debug|release){
    # debug mode use local file
    win32 {
        path=$$system("cd")
        path ~=s,\\\\,/,g
    } else {
        path=$$system("pwd")
    }
    RESOURCES += $$PWD/GrayCatQtQuick/GrayCatQtQuick.qrc
    GrayCatQtQuickImport=\"file:///$$path\"
    #GrayCatQtQuickImage=\"file:///$$path/GrayCatQtQuick/Images/\"
    DEFINES += GrayCatQtQuickImportPath=\\\"file:///$${path}\\\"
    #DEFINES += GrayCatQtQuickImagePath=\\\"file:///$${path}/GrayCatQtQuick/Images/\\\"
} else {
    # release mode use qrc file
    RESOURCES += $$PWD/GrayCatQtQuick/GrayCatQtQuick.qrc
    # release mode set importPath with 'qrc:///'
    GrayCatQtQuickImport=\"qrc:/\"
    #GrayCatQtQuickImage=\"qrc:/GrayCatQtQuick/Images/\"
    DEFINES += GrayCatQtQuickImportPath=\\\"qrc:///\\\"
    #DEFINES += GrayCatQtQuickImagePath=\\\"qrc:/GrayCatQtQuick/Images/\\\"
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH	+= $$PWD
QML2_IMPORT_PATH += $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH += $$PWD
