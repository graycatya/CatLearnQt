#include "CatSerialPort.h"
#include <CatLog>

CatSerialPort::CatSerialPort(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QSerialPort::SerialPortError>("QSerialPort::SerialPortError");
    InitProperty();
}

CatSerialPort::~CatSerialPort()
{
    if(m_qPort.isOpen())
    {
        m_qPort.close();
    }
}

void CatSerialPort::InitProperty()
{
    connect(&m_qPort, &QSerialPort::readyRead, this, [=](){
        QByteArray readdate = m_qPort.readAll();
        while(m_qPort.waitForReadyRead(10))
        {
            readdate += m_qPort.readAll();
        }
        emit ReadSerialPort(readdate);
    });
    connect(&m_qPort, &QSerialPort::errorOccurred, this, [=](QSerialPort::SerialPortError error){
        if(error == QSerialPort::SerialPortError::ResourceError)
        {
            if(m_qPort.isOpen())
            {
                m_qPort.close();
                emit DisconnectPort();
            }
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

bool CatSerialPort::OpenSerial()
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
    m_qPort.setPortName(m_sSerialPortName);

    // [2] 端口打开
    if(!m_qPort.open(QIODevice::ReadWrite))
    {
        QString Error = QString("SerialPort Open %1, error code %2")
                .arg(m_sSerialPortName).arg(m_qPort.error());
        emit ErrorSerialPort(Error);
        return false;
    }
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
    }
}

void CatSerialPort::WriteSerialPortSlot(QByteArray data, bool waitread, int msecs)
{
    if(m_qPort.isOpen())
    {
        m_qPort.write(data);
        if(waitread)
        {
            while(m_qPort.waitForReadyRead(msecs));
        }
    }
}
