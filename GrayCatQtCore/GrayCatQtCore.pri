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
if(!contains(DEFINES,WEBASSEMBLY)) {
include($$PWD/Src/SingleApplication/singleapplication.pri)
}
if(!contains(DEFINES,WEBASSEMBLY)) {
include($$PWD/Src/CatNetWork/CatNetWork.pri)
}
include($$PWD/Src/CatUniversal/CatUniversal.pri)
include($$PWD/Src/CatLog/CatLog.pri)
if(!contains(DEFINES,IOS_APP)) {
if(!contains(DEFINES,WEBASSEMBLY)) {
include($$PWD/Src/CatSerial/CatSerial.pri)
}
}
