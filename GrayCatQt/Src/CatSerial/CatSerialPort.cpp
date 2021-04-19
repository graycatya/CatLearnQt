#include "CatSerialPort.h"
#include <CatLog>
#include <QAbstractSocket>
#include <QMetaEnum>

#if Q_CC_MSVC
    #include "CatWinMonitorSerial.h"
#endif


CatSerialPort::CatSerialPort(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
    InitProperty();
    InitConnect();
}

CatSerialPort::~CatSerialPort()
{
    if(m_pReadPortDataWork)
    {
        m_pReadPortDataWork->deleteLater();
        m_pReadPortDataWork = nullptr;
    }
    if(m_qPort.isOpen())
    {
        m_qPort.close();
    }
}

void CatSerialPort::InitProperty()
{
    m_yWriteData.clear();
    m_yReadData.clear();

    m_pReadPortDataWork = new ReadPortDataWork(this);

}

void CatSerialPort::InitConnect()
{
    connect(m_pReadPortDataWork, &ReadPortDataWork::UpdateReadWork, [=](){
        if(!m_yReadData.isEmpty())
        {
            emit ReadSerialPort(m_yReadData);
            m_yReadData.clear();
        }
    });

    connect(&m_qPort, &QSerialPort::readyRead, this, [=](){
        if(!m_pReadPortDataWork->GetWork())
        {
            m_pReadPortDataWork->Start(50);
        }
        m_yReadData += m_qPort.readAll();
    });

#ifdef Q_OS_WIN
    if(QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS7)
    {
        QObject::connect(CatWinMonitorSerial::Instance(), &CatWinMonitorSerial::DeleteSerial, this, [=](qint64 pid, qint64 vid){

            if(m_qPortInfo.vendorIdentifier() == vid && m_qPortInfo.productIdentifier() == pid)
            {
                if(m_qPort.isOpen())
                {
                    m_qPort.close();
                }
                emit DisconnectPort();
            }
        });
    }
#endif

    connect(&m_qPort, &QSerialPort::errorOccurred, this, [=](QSerialPort::SerialPortError error){
        if(error == QSerialPort::SerialPortError::ResourceError)
        {
            QString log = "QSerialPort::errorOccurred: " + QString::number(error);
            CATLOG::CatLog::__Write_Log("./log", ERROR_LOG_T(log.toStdString()));
            if(m_qPort.isOpen())
            {
                m_qPort.close();
            }
            emit DisconnectPort();
        }
    });
}

void CatSerialPort::SetSerialInfo(const QSerialPortInfo info)
{
    this->m_qPortInfo = info;
    this->m_sSerialPortName = info.portName();
}

void CatSerialPort::SetSerialPortName(const QString portname)
{
    this->m_sSerialPortName = portname;
}

QString CatSerialPort::GetPortName()
{
    return m_sSerialPortName;
}

bool CatSerialPort::OpenSerial(qint32 baudRate, QSerialPort::StopBits stopBits)
{
    // [0] 判断端口是否有效
    if(m_qPortInfo.isNull() && m_sSerialPortName.isEmpty())
    {
        CATLOG::CatLog::__Write_Log(_INFO_LOG("SerialPort PortName is Null!"));
        return false;
    } else if(m_sSerialPortName.isEmpty()) {
        m_sSerialPortName = m_qPortInfo.portName();
    }

    // [1] 端口操作 - 初始化
    m_qPort.close();
    QString port;
#ifdef Q_OS_LINUX
    port = "/dev/" + m_sSerialPortName;
#endif
    port = m_sSerialPortName;
    m_qPort.setPortName(port);
    m_qPort.setBaudRate(baudRate);
    m_qPort.setStopBits(stopBits);

    // [2] 端口打开
    if(!m_qPort.open(QIODevice::ReadWrite))
    {
        QString Error = QString("SerialPort Open %1, error code %2")
                .arg(m_sSerialPortName).arg(m_qPort.error());
        emit ErrorSerialPort(Error);
        return false;
    }
    emit OpenSuccess();
    return true;
}

bool CatSerialPort::IsOpen()
{
    return m_qPort.isOpen();
}

void CatSerialPort::Close()
{
    if(m_qPort.isOpen())
    {
        m_qPort.close();
        emit Closeed();
    }
}

QSerialPortInfo CatSerialPort::GetSerialProtInfo(QString port)
{
    QSerialPortInfo info;
    for(auto temp : QSerialPortInfo::availablePorts())
    {
        if(port == temp.portName())
        {
            info = temp;
        }
    }
    return info;
}

void CatSerialPort::WriteSerialPortSlot(QByteArray data, bool waitread, int msecs)
{
    if(m_qPort.isOpen())
    {
        QString log = QString("%1 Write: %2").arg(m_sSerialPortName).arg(QString(data.toHex()));
        CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
        m_qPort.write(data);
        if(waitread)
        {
            while(m_qPort.waitForReadyRead(msecs));
        }
    }
}

