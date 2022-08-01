include($$PWD/ImageTools/ImageTools.pri)
include($$PWD/QrenCode/QrenCode.pri)

if(!contains(DEFINES,IOS_APP)) {
#if(!contains(DEFINES,WEBASSEMBLY)) {
lessThan(QT_MAJOR_VERSION, 6) {
include($$PWD/CatQcustomplot/CatQcustomplot.pri)
} else {

}
#}
}

