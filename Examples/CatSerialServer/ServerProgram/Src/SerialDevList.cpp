#include "SerialDevList.h"
#include "ServerConfig.h"

SerialDevList* SerialDevList::_instance = nullptr;
QMutex* SerialDevList::m_pMutex = new QMutex;


QList<QString> SerialDevList::GetSerialDevList()
{
    QList<QString> devs;
    QHash<QString, QSerialPortInfo> infos = MonitorSerial::Instance()->GetSerialPortInfo();
    foreach (QSerialPortInfo info, infos)
    {
        devs.push_back(info.portName());
    }
    return devs;
}

void SerialDevList::OpenSerialPort(QString port, qint32 baudRate, int stopBits)
{
    QHash<QString, QSerialPortInfo> infos = MonitorSerial::Instance()->GetSerialPortInfo();
    foreach (QSerialPortInfo info, infos)
    {
        if(info.portName() == port)
        {
            if(!m_ySerials.contains(port))
            {
                SERIALSTATE serialState;
                serialState.serialPort = new CatSerialPort;
                serialState.serialPort->SetSerialInfo(info);
                serialState.SerialReadCon = connect(serialState.serialPort, &CatSerialPort::ReadSerialPort, this, [=, &serialState](QByteArray data){
                    emit ReadData(serialState.serialPort->GetPortName(), data);
                });
                serialState.OpenCon = connect(serialState.serialPort, &CatSerialPort::OpenSuccess, this, [=, &serialState](){
                    emit SerialOpenSucceed(serialState.serialPort->GetPortName());
                });
                serialState.CloseCon = connect(serialState.serialPort, &CatSerialPort::Closeed, this, [=, &serialState](){
                    emit SerialCloseSucceed(serialState.serialPort->GetPortName());
                });
                serialState.ErrorCon = connect(serialState.serialPort, &CatSerialPort::ErrorSerialPort, this, [=, &serialState](QString error){
                    emit SerialError(serialState.serialPort->GetPortName(), 10004);
                });
                serialState.DisconnectCon = connect(serialState.serialPort, &CatSerialPort::DisconnectPort, this, [=, &serialState](){
                    serialState.DisConnect();
                    delete serialState.serialPort;
                    serialState.serialPort = nullptr;
                    m_ySerials.remove(serialState.serialPort->GetPortName());
                });
                if(serialState.serialPort->OpenSerial(baudRate, static_cast<QSerialPort::StopBits>(stopBits)))
                {
                    emit SerialOpenSucceed(port);
                } else {
                    emit SerialError(port, 10003);
                }
            } else {
                if(m_ySerials[info.portName()].serialPort->IsOpen())
                {
                    emit SerialError(port, 10002);
                }
                if(m_ySerials[info.portName()].serialPort->OpenSerial(baudRate, static_cast<QSerialPort::StopBits>(stopBits)))
                {
                    emit SerialOpenSucceed(port);
                } else {
                    emit SerialError(port, 10003);
                }
            }
            break;
        }

    }
    emit SerialError(port, 10001);
}

void SerialDevList::CloseSerialPort(QString port)
{
    if(m_ySerials.contains(port))
    {
        m_ySerials[port].serialPort->Close();
    } else {
        emit SerialError(port, 10005);
    }
}

void SerialDevList::WriteData(QString port, QByteArray data)
{
    if(m_ySerials.contains(port))
    {
        m_ySerials[port].serialPort->WriteSerialPortSlot(data);
    } else {
        emit SerialError(port, 10006);
    }
}

SerialDevList::SerialDevList()
{
    MonitorSerial::Instance();
    MonitorSerial::Instance()->Start(100, false);
    InitConnect();
}

SerialDevList::~SerialDevList()
{

}

void SerialDevList::InitConnect()
{
    m_ySerials.clear();

    // 设备插入后检测，是否为本公司设备，是的话加入新的设备列表
    connect(MonitorSerial::Instance(), &MonitorSerial::UpdateSerial,
            this, [=](QList<QSerialPortInfo> adds, QList<QSerialPortInfo> dels){
        QString log = "adds.size: " + QString::number(adds.size()) + " dels.size: " + QString::number(dels.size());
        CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
        CATLOG::CatLog::__Write_Log("./SerialServer", DEBUG_LOG_T(log.toStdString()));
        AddDevs(adds);
        DelDevs(dels);
    });
}

void SerialDevList::AddDevs(QList<QSerialPortInfo> devs)
{
    for(auto info : devs)
    {
        if(this->IsDev(info))
        {
            emit AddDev(info.portName());
        }
    }
}

void SerialDevList::DelDevs(QList<QSerialPortInfo> devs)
{
    for(auto info : devs)
    {
        if(this->IsDev(info))
        {
            emit DelDev(info.portName());
        }
    }
}

bool SerialDevList::IsDev(QSerialPortInfo &info)
{
    QVector<QVariant> filters = ServerConfig::Instance()->GetArrays("SerialFilter_Pid_Vid");
    for (int i = 0; i < filters.size(); ++i) {
        QString tempDev = filters.at(i).toString();
        QString strDev = QString(QString::number(info.productIdentifier())
                                 + "," +
                                 QString::number(info.vendorIdentifier()));
        if (tempDev == strDev)
        {
            return true;
        }
    }
    return false;
}
