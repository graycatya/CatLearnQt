TEMPLATE = subdirs

message($$QT_ARCH)

OTHER_FILES += *.md \
    .qmake.conf \
    .github/workflows/* \

SUBDIRS += $$PWD/Examples/Examples.pro \
           $$PWD/GrayCatQt/GrayCatQt.pro \
