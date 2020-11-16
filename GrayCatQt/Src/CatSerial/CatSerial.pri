QT += serialport

include(SerialProtocol/SerialProtocol.pri)

HEADERS += \
    $$PWD/CatSerial \
    $$PWD/CatSerialPort.h \
    $$PWD/MonitorSerial.h \
    $$PWD/SerialDevFilter.h

SOURCES += \
    $$PWD/CatSerialPort.cpp \
    $$PWD/MonitorSerial.cpp \
    $$PWD/SerialDevFilter.cpp

INCLUDEPATH += $$PWD
