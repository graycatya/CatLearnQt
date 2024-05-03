#ifndef SERIALSERVERREMOTE_H
#define SERIALSERVERREMOTE_H

#include "rep_CatSerialRemote_source.h"

class SerialServerRemote : public CatSerialRemoteSource
{
    Q_OBJECT
public:
    explicit SerialServerRemote(QObject *parent = nullptr);
    ~SerialServerRemote();
    virtual void SerialDevList();
    virtual void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    virtual void CloseSerialPort(QString port);
    virtual void WriteData(QString port, QByteArray data);

private:
    void InitConnect();

};

#endif // SERIALSERVERREMOTE_H
