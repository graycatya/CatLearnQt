TEMPLATE = subdirs

message($$QT_ARCH)

#DEFINES += WEBASSEMBLY

OTHER_FILES += *.md \
    .qmake.conf \
    .github/workflows/* \

if(!contains(DEFINES,WEBASSEMBLY)) {
SUBDIRS += $$PWD/Examples/CatWidgetExamples/CatWidgetExamples.pro \
           $$PWD/GrayCatQt/GrayCatQt.pro \
           $$PWD/GrayCatQtCore/GrayCatQtCore.pro \
}

if(contains(DEFINES,WEBASSEMBLY)) {
SUBDIRS += $$PWD/Examples/CatWidgetWebAssEmblyExamples/CatWidgetWebAssEmblyExamples.pro
}
