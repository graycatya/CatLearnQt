#include "SerialDevList.h"
#include "ServerConfig.h"
#include <QCoreApplication>

SerialDevList* SerialDevList::_instance = nullptr;
QMutex* SerialDevList::m_pMutex = new QMutex;

class SerialState : public QObject {

public:
    QMetaObject::Connection SerialReadCon;
    QMetaObject::Connection ErrorCon;
    QMetaObject::Connection DisconnectCon;
    QMetaObject::Connection CloseCon;
    QMetaObject::Connection OpenCon;
    CatSerialPort serialPort;

    void DisConnect()
    {
        disconnect(SerialReadCon);
        disconnect(ErrorCon);
        disconnect(OpenCon);
        disconnect(DisconnectCon);
        disconnect(CloseCon);
    }
};


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
    QString log = "OpenSerialPort infos Size: " + QString::number(infos.size());
    CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    foreach (QSerialPortInfo info, infos)
    {
        QString log = QString("OpenSerialPort infoName %1, port %2").arg(info.portName()).arg(port);
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
        if(info.portName() == port)
        {
            if(!m_ySerials.contains(port))
            {
                CATLOG::CatLog::Instance()->__Write_Log(INFO_LOG_T("Serial contains"));
                SerialState *serialState = new SerialState;
                //serialState.serialPort = new CatSerialPort;
                serialState->serialPort.SetSerialInfo(info);
                serialState->SerialReadCon =
                connect(&serialState->serialPort, &CatSerialPort::ReadSerialPort, this, [=](QByteArray data){
                    emit ReadData(port, data);
                }, Qt::QueuedConnection);
                serialState->OpenCon =
                connect(&serialState->serialPort, &CatSerialPort::OpenSuccess, this, [=](){
                    emit SerialOpenSucceed(port);
                }, Qt::QueuedConnection);
                serialState->CloseCon =
                connect(&serialState->serialPort, &CatSerialPort::Closeed, this, [=](){
                    emit SerialCloseSucceed(port);
                }, Qt::QueuedConnection);
                serialState->ErrorCon =
                connect(&serialState->serialPort, &CatSerialPort::ErrorSerialPort, this, [=](QString error){
                    emit SerialError(port, 10004);
                }, Qt::QueuedConnection);
                serialState->DisconnectCon =
                connect(&serialState->serialPort, &CatSerialPort::DisconnectPort, this, [=](){
                    QString log = "Disconnect port: " + port;
                    CATLOG::CatLog::Instance()->__Write_Log(DEBUG_LOG_T(log.toStdString()));
                    if(m_ySerials.contains(port))
                    {
                        if(m_ySerials.contains(port))
                        {
                            if(m_ySerials[port] != nullptr)
                            {
                                m_ySerials[port]->DisConnect();
                                m_ySerials[port]->serialPort.Close();
                                delete m_ySerials[port];
                                m_ySerials[port] = nullptr;
                                QCoreApplication::processEvents();
                            }
                        }
                        m_ySerials.remove(port);
                    }

                }, Qt::QueuedConnection);
                m_ySerials[port] = serialState;
                if(serialState->serialPort.OpenSerial(baudRate, static_cast<QSerialPort::StopBits>(stopBits)))
                {
                    return;
                    //emit SerialOpenSucceed(port);
                } else {
                    emit SerialError(port, 10003);
                    return;
                }
                break;
            } else {
                if(m_ySerials[info.portName()]->serialPort.IsOpen())
                {
                    emit SerialError(port, 10002);
                    return;
                }
                if(m_ySerials[info.portName()]->serialPort.OpenSerial(baudRate, static_cast<QSerialPort::StopBits>(stopBits)))
                {
                    emit SerialOpenSucceed(port);
                    return;
                } else {
                    emit SerialError(port, 10003);
                    return;
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
        if(m_ySerials[port] != nullptr)
        {
            m_ySerials[port]->serialPort.Close();
        }
    } else {
        emit SerialError(port, 10005);
    }
}

void SerialDevList::WriteData(QString port, QByteArray data)
{
    if(m_ySerials.contains(port))
    {
        if(m_ySerials[port] != nullptr)
        {
            m_ySerials[port]->serialPort.WriteSerialPortSlot(data);
        }
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
            if(m_ySerials.contains(info.portName()))
            {
                if(m_ySerials.contains(info.portName()))
                {
                    if(m_ySerials[info.portName()] != nullptr)
                    {
                        m_ySerials[info.portName()]->DisConnect();
                        m_ySerials[info.portName()]->serialPort.Close();
                        delete m_ySerials[info.portName()];
                        m_ySerials[info.portName()] = nullptr;
                        QCoreApplication::processEvents();
                    }
                    m_ySerials.remove(info.portName());
                }
            }

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
