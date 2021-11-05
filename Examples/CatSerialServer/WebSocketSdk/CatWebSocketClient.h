#ifndef CATWEBSOCKETCLIENK_H
#define CATWEBSOCKETCLIENK_H

#include <QObject>
#include <QThread>
#include <QWebSocket>

class CatWebSocketClient : public QThread
{
    Q_OBJECT
public:
    enum PROTOCOL_CMD {
        NEWCONNECTSOCKET = 1,
        ADDDEV,
        DELDEV,
        SERIALERROR,
        READDATA,
        SERIALOPENSUCCEED,
        SERIALCLOSESUCCEED,
        SERIALDISCONNECT,
        SERIALDEVLIST,
        OPENSERIALPORT,
        CLOSESERIALPORT,
        WRITEDATA
    };
    explicit CatWebSocketClient(QObject *parent = nullptr);
    ~CatWebSocketClient();

    void Open(QUrl url);
    void Close();

private:
    void InitProperty();
    void InitConnect();

    void DecodeData(QString data);

    void DecodeNewConnectSocket(QString data);
    void DecodeAddDev(QString data);
    void DecodeDelDev(QString data);
    void DecodeSerialError(QString data);
    void DecodeReadData(QString data);
    void DecodeSerialOpenSucceed(QString data);
    void DecodeSerialCloseSucceed(QString data);
    void DecodeSerialDisconnect(QString data);
    void DecodeSerialDevList(QString data);
    void DecodeOpenSerialPort(QString data);
    void DecodeCloseSerialPort(QString data);
    void DecodeWriteData(QString data);

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
    QWebSocket *m_pWebSocket = nullptr;
    QUrl m_qUrl;

};

#endif
