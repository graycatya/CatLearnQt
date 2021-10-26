#include "SerialServerInitialize.h"
#include "SerialDevList.h"

SerialServerInitialize::SerialServerInitialize(QObject *parent)
{
    InitServer();
}

SerialServerInitialize::~SerialServerInitialize()
{
    delete m_pSerialServerRemote;
    m_pSerialServerRemote = nullptr;
    delete m_pSerialServerWebSocket;
    m_pSerialServerWebSocket = nullptr;
    delete m_pHost;
    m_pHost = nullptr;
}

void SerialServerInitialize::InitServer()
{
    m_pHost = new QRemoteObjectHost(this);
    m_pHost->setHostUrl(QUrl("local:interfaces"));
    m_pSerialServerRemote = new SerialServerRemote(this);
    m_pHost->enableRemoting(m_pSerialServerRemote);


    m_pSerialServerWebSocket = new SerialServerWebSocket;
}
