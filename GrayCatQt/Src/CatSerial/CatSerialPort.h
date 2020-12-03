#ifndef CATSERIALPORT_H
#define CATSERIALPORT_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSerialPort>
#include <QSerialPortInfo>

class CatSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit CatSerialPort(QObject *parent = nullptr);
    ~CatSerialPort();

    void InitProperty();

    void SetSerialInfo(const QSerialPortInfo info);

    void SetSerialPortName(const QString portname);

    bool OpenSerial();

    bool IsOpen();

    void Close();

signals:
    void ReadSerialPort(QByteArray);
    void ErrorSerialPort(QString);
    void DisconnectPort();

public slots:
    void WriteSerialPortSlot(QByteArray, bool waitread = false, int msecs = 1000);

private:
    QSerialPortInfo m_qPortInfo;
    QString m_sSerialPortName;
    QByteArray m_yWriteData;
    QSerialPort m_qPort;



};

#endif // CATSERIALPORT_H
