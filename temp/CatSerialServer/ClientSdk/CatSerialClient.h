#ifndef CATSERIALCLIENT_H
#define CATSERIALCLIENT_H

#include <QObject>
#include <QThread>
#include <QRemoteObjectNode>
#include "rep_CatSerialRemote_replica.h"


class CatSerialClient : public QThread
{
    Q_OBJECT
public:
    explicit CatSerialClient(QObject* parent = nullptr);
    ~CatSerialClient();

private:
    void InitProperty();
    void InitConnect();

protected:
    void run() override;

signals:
    void SerialDevListSign(QList<QString> ports);
    void SerialOpenSucceed(QString port);
    void SerialCloseSucceed(QString port);
    void SerialDisconnect(QString port);
    void SerialError(QString port, quint64 error);
    void ReadData(QString port, QByteArray data);
    void AddDev(QString port);
    void DelDev(QString port);

public slots:
    void SerialDevList();
    void OpenSerialPort(QString port, qint32 baudRate, int stopBits);
    void CloseSerialPort(QString port);
    void WriteData(QString port, QByteArray data);

private:
    QRemoteObjectNode * m_pRemoteNode = nullptr;
    CatSerialRemoteReplica *m_pCatSerialRemoteReplica = nullptr;
};

#endif // CATSERIALCLIENT_H
