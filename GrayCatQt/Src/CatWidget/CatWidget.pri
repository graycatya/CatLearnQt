include($$PWD/ImageTools/ImageTools.pri)
include($$PWD/QrenCode/QrenCode.pri)

if(!contains(DEFINES,IOS_APP)) {
#if(!contains(DEFINES,WEBASSEMBLY)) {
include($$PWD/CatQcustomplot/CatQcustomplot.pri)
#}
}

