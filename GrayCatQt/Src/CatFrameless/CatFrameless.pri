QT += core gui widgets

HEADERS += \
    $$PWD/CatFrameLessMainView.h \
    $$PWD/CatFramelessDialog.h \
    $$PWD/CatFramelessMainWindow.h \
    $$PWD/CatFramelessWidget.h

SOURCES += \
    $$PWD/CatFramelessDialog.cpp \
    $$PWD/CatFramelessMainWindow.cpp \
    $$PWD/CatFramelessWidget.cpp

win32 {
    #DEFINES += _X86_
    SOURCES += \
        $$PWD/CatFrameLessMainView_Win.cpp \
} else {
    SOURCES += \
        $$PWD/CatFrameLessMainView_Unix.cpp \
}
