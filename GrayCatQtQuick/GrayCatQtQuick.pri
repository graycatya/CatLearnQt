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


INCLUDEPATH += $$PWD/Src

include($$PWD/Src/CatFrameless/CatFrameless.pri)
include($$PWD/imports/imports.pri)

#RESOURCES += \
#    $$PWD/GrayCatQtQuick.qrc
