#ifndef SERIALSERVERINITIALIZE_H
#define SERIALSERVERINITIALIZE_H

#include <QObject>
#include "SerialServerRemote.h"
#include "SerialServerWebSocket.h"
#include <QRemoteObjectHost>

class SerialServerInitialize : public QObject
{
    Q_OBJECT
public:
    explicit SerialServerInitialize(QObject* parent = nullptr);
    ~SerialServerInitialize();

private:
    void InitServer();

private:

    SerialServerRemote* m_pSerialServerRemote = nullptr;
    SerialServerWebSocket* m_pSerialServerWebSocket = nullptr;
    QRemoteObjectHost *m_pHost = nullptr;
};

#endif // SERIALSERVERINITIALIZE_H
