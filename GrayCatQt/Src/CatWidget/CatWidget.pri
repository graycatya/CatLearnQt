include($$PWD/ImageTools/ImageTools.pri)
include($$PWD/QrenCode/QrenCode.pri)

if(!contains(DEFINES,IOS_APP)) {
include($$PWD/CatQcustomplot/CatQcustomplot.pri)
}

