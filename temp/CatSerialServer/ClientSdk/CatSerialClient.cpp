#include "CatSerialClient.h"

CatSerialClient::CatSerialClient(QObject *parent)
    : QThread(parent)
{
    this->start();
}

CatSerialClient::~CatSerialClient()
{
    quit();
    wait();
}

void CatSerialClient::InitProperty()
{
    m_pRemoteNode = new QRemoteObjectNode();
    m_pRemoteNode->connectToNode(QUrl("local:interfaces"));
    m_pCatSerialRemoteReplica = m_pRemoteNode->acquire<CatSerialRemoteReplica>();
}

void CatSerialClient::InitConnect()
{
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::SerialDevListSign,
            this, &CatSerialClient::SerialDevListSign);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::SerialOpenSucceed,
            this, &CatSerialClient::SerialOpenSucceed);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::SerialCloseSucceed,
            this, &CatSerialClient::SerialCloseSucceed);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::SerialDisconnect,
            this, &CatSerialClient::SerialDisconnect);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::SerialError,
            this, &CatSerialClient::SerialError);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::ReadData,
            this, &CatSerialClient::ReadData);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::AddDev,
            this, &CatSerialClient::AddDev);
    connect(m_pCatSerialRemoteReplica, &CatSerialRemoteReplica::DelDev,
            this, &CatSerialClient::DelDev);
}

void CatSerialClient::run()
{
    InitProperty();
    InitConnect();
    exec();
    delete m_pRemoteNode;
    m_pRemoteNode = nullptr;
}

void CatSerialClient::SerialDevList()
{
    m_pCatSerialRemoteReplica->SerialDevList();
}

void CatSerialClient::OpenSerialPort(QString port, qint32 baudRate, int stopBits)
{
    m_pCatSerialRemoteReplica->OpenSerialPort(port, baudRate, stopBits);
}

void CatSerialClient::CloseSerialPort(QString port)
{
    m_pCatSerialRemoteReplica->CloseSerialPort(port);
}

void CatSerialClient::WriteData(QString port, QByteArray data)
{
    m_pCatSerialRemoteReplica->WriteData(port, data);
}
