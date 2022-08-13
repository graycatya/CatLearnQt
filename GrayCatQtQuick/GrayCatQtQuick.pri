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

#判断Qt版本
lessThan(QT_MAJOR_VERSION, 6) {

} else {

}

QT += qml quick widgets


INCLUDEPATH += $$PWD/Src
#判断Qt版本
lessThan(QT_MAJOR_VERSION, 6) {
    include($$PWD/imports/GrayCatQt5Compat/imports.pri)
} else {
    include($$PWD/imports/GrayCatQt6Compat/imports.pri)
}
#include($$PWD/imports/imports.pri)
include($$PWD/Src/CatModel/CatModel.pri)

#RESOURCES += \
#    $$PWD/GrayCatQtQuick.qrc
