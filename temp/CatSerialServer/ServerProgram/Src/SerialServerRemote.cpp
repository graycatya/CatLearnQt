#include "SerialServerRemote.h"
#include "SerialDevList.h"
#include <CatLog>


SerialServerRemote::SerialServerRemote(QObject *parent) : CatSerialRemoteSource(parent)
{
    Q_UNUSED(parent)
    InitConnect();
}

SerialServerRemote::~SerialServerRemote()
{

}

void SerialServerRemote::SerialDevList()
{
    emit SerialDevListSign(SerialDevList::Instance()->GetSerialDevList());
}

void SerialServerRemote::OpenSerialPort(QString port, qint32 baudRate, int stopBits)
{
    SerialDevList::Instance()->OpenSerialPort(port, baudRate, stopBits);
}

void SerialServerRemote::CloseSerialPort(QString port)
{
    SerialDevList::Instance()->CloseSerialPort(port);
}

void SerialServerRemote::WriteData(QString port, QByteArray data)
{
    SerialDevList::Instance()->WriteData(port, data);
}

void SerialServerRemote::InitConnect()
{
    connect(SerialDevList::Instance(), &SerialDevList::AddDev, this, [=](QString port){
        QString log = "SerialServerRemote addDev: " + port;
        CATLOG::CatLog::Instance()->__Write_Log(INFO_LOG_T(log.toStdString()));
        CATLOG::CatLog::__Write_Log("./SerialServer", INFO_LOG_T(log.toStdString()));
        emit AddDev(port);
    });
    connect(SerialDevList::Instance(), &SerialDevList::DelDev, this, [=](QString port){
        QString log = "SerialServerRemote delDev: " + port;
        CATLOG::CatLog::Instance()->__Write_Log(INFO_LOG_T(log.toStdString()));
        CATLOG::CatLog::__Write_Log("./SerialServer", INFO_LOG_T(log.toStdString()));
        emit DelDev(port);
    });
    connect(SerialDevList::Instance(), &SerialDevList::SerialError, this, &CatSerialRemoteSource::SerialError);
    connect(SerialDevList::Instance(), &SerialDevList::ReadData, this, &CatSerialRemoteSource::ReadData);
    connect(SerialDevList::Instance(), &SerialDevList::SerialOpenSucceed, this, &CatSerialRemoteSource::SerialOpenSucceed);
    connect(SerialDevList::Instance(), &SerialDevList::SerialCloseSucceed, this, &CatSerialRemoteSource::SerialCloseSucceed);
    connect(SerialDevList::Instance(), &SerialDevList::SerialDisconnect, this, &CatSerialRemoteSource::SerialDisconnect);
}
