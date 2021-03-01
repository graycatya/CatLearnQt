QT += serialport
if(contains(DEFINES,WEBASSEMBLY)) {
QT -= serialport
}

if(!contains(DEFINES,WEBASSEMBLY)) {
HEADERS += \
    $$PWD/CatSerial \
    $$PWD/CatSerialPort.h \
    $$PWD/MonitorSerial.h

SOURCES += \
    $$PWD/CatSerialPort.cpp \
    $$PWD/MonitorSerial.cpp

INCLUDEPATH += $$PWD
}
