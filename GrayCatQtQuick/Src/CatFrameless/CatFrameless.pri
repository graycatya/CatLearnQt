QT += core gui quick

HEADERS += \
    $$PWD/CatFrameLessView.h

win32 {
    SOURCES += \
        $$PWD/CatFrameLessView_Win.cpp
} else {
    SOURCES += \
        $$PWD/CatFrameLessView_Unix.cpp
}
