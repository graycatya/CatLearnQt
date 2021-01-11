TEMPLATE = subdirs

OTHER_FILES += *.md \
    .qmake.conf \
    .github/workflows/* \

CONFIG+= ordered

SUBDIRS += $$PWD/GrayCatQt/GrayCatQt.pro \
