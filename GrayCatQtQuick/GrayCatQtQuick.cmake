
function(find_graycatqtquick_pack)
if(ARGV0)
    set(GrayCatQtQuickPath ${ARGV0}/imports)

    if (CMAKE_BUILD_TYPE MATCHES "Release")
        set(GrayCatQtQuickRes ${GrayCatQtQuickPath}/GrayCatQtQuick/GrayCatQtQuick.qrc)
        set(GrayCatQtQuickImport "qrc:///" )
        set(GrayCatQtQuickImage "qrc:/GrayCatQtQuick/Images/")
    else()
        set(GrayCatQtQuickRes ${GrayCatQtQuickPath}/GrayCatQtQuick/GrayCatQtQuick.qrc)
        set(GrayCatQtQuickImport "file:///${GrayCatQtQuickPath}")
        set(GrayCatQtQuickImage "file:///${GrayCatQtQuickPath}/GrayCatQtQuick/Images/")
    endif()
    add_compile_definitions(GrayCatQtQuickRes="${GrayCatQtQuickRes}")
    add_compile_definitions(GrayCatQtQuickImport="${GrayCatQtQuickImport}")
    add_compile_definitions(GrayCatQtQuickImage="${GrayCatQtQuickImage}")

    add_compile_definitions(GrayCatQtQuickImportPath="${GrayCatQtQuickImport}")
    add_compile_definitions(GrayCatQtQuickImagePath="${GrayCatQtQuickImage}")

    add_compile_definitions(QML_IMPORT_PATH="${GrayCatQtQuickPath}")
    add_compile_definitions(QML2_IMPORT_PATH="${GrayCatQtQuickPath}")
    add_compile_definitions(QML_DESIGNER_IMPORT_PATH="${GrayCatQtQuickPath}")
    message(${ARGV0})
endif(ARGV0)
endfunction(find_graycatqtquick_pack)

