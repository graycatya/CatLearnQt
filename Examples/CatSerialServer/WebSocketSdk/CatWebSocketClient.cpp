#include "CatWebSocketClient.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CatWebSocketClient::CatWebSocketClient(QObject *parent)
    : QThread(parent)
{
    //this->start();
}

CatWebSocketClient::~CatWebSocketClient()
{
    if(this->isRunning())
    {
        quit();
        wait();
    }
}

void CatWebSocketClient::Open(QUrl url)
{
    m_qUrl = url;
    this->start();
}

void CatWebSocketClient::Close()
{
    if(this->isRunning())
    {
        quit();
        wait();
    }
}

void CatWebSocketClient::InitProperty()
{
    m_pWebSocket = new QWebSocket;
    m_pWebSocket->open(m_qUrl);
}

void CatWebSocketClient::InitConnect()
{
    connect(m_pWebSocket, &QWebSocket::connected, this, [=](){

    });
    connect(m_pWebSocket, &QWebSocket::disconnected, this, [=](){
        quit();
    });
    connect(m_pWebSocket, &QWebSocket::textMessageReceived, this, [=](const QString &message){
        DecodeData(message);

    });
    connect(m_pWebSocket, &QWebSocket::binaryMessageReceived, this, [=](const QByteArray &message){
        DecodeData(message);
    });
}

void CatWebSocketClient::DecodeData(QString data)
{
    qDebug() << "read: " << data;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    if(!jsonDocument.isNull())
    {
        if(jsonDocument.isObject())
        {
            QJsonObject jsObject = jsonDocument.object();

            if(jsObject.value("Cmd").toInt() > 0 && (jsObject.value("State").toInt() == 200))
            {
                switch (jsObject.value("Cmd").toInt()) {
                    case NEWCONNECTSOCKET:{
                        qDebug() << "Decode NEWCONNECTSOCKET";
                        DecodeNewConnectSocket(data);
                        break;
                    }
                    case ADDDEV:{
                        qDebug() << "Decode ADDDEV";
                        DecodeAddDev(data);
                        break;
                    }
                    case DELDEV:{
                        qDebug() << "Decode DELDEV";
                        DecodeDelDev(data);
                        break;
                    }
                    case SERIALERROR:{
                        qDebug() << "Decode SERIALERROR";
                        DecodeSerialError(data);
                        break;
                    }
                    case READDATA:{
                        qDebug() << "Decode READDATA";
                        DecodeReadData(data);
                        break;
                    }
                    case SERIALOPENSUCCEED:{
                        qDebug() << "Decode SERIALOPENSUCCEED";
                        DecodeSerialOpenSucceed(data);
                        break;
                    }
                    case SERIALCLOSESUCCEED:{
                        qDebug() << "Decode SERIALCLOSESUCCEED";
                        DecodeSerialCloseSucceed(data);
                        break;
                    }
                    case SERIALDISCONNECT:{
                        qDebug() << "Decode SERIALDISCONNECT";
                        DecodeSerialDisconnect(data);
                        break;
                    }
                    case SERIALDEVLIST:{
                        qDebug() << "Decode SERIALDEVLIST";
                        DecodeSerialDevList(data);
                        break;
                    }
                    case OPENSERIALPORT:{
                        qDebug() << "Decode OPENSERIALPORT";
                        DecodeOpenSerialPort(data);
                        break;
                    }
                    case CLOSESERIALPORT:{
                        qDebug() << "Decode CLOSESERIALPORT";
                        DecodeCloseSerialPort(data);
                        break;
                    }
                    case WRITEDATA:{
                        qDebug() << "Decode WRITEDATA";
                        DecodeWriteData(data);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }
    }
}

void CatWebSocketClient::DecodeNewConnectSocket(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != NEWCONNECTSOCKET)
    {
        Close();
    }
}

void CatWebSocketClient::DecodeAddDev(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != ADDDEV)
    {
        if(!jsObject.value("Dev").toString().isEmpty())
        {
            emit AddDev(jsObject.value("Dev").toString());
        }
    }
}

void CatWebSocketClient::DecodeDelDev(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != DELDEV)
    {
        if(!jsObject.value("Dev").toString().isEmpty())
        {
            emit AddDev(jsObject.value("Dev").toString());
        }
    }
}

void CatWebSocketClient::DecodeSerialError(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != SERIALERROR)
    {
        if(!jsObject.value("Dev").toString().isEmpty() && jsObject.value("Error").toInt() != 0)
        {
            emit SerialError(jsObject.value("Dev").toString(), jsObject.value("Error").toInt());
        }
    }
}

void CatWebSocketClient::DecodeReadData(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != READDATA)
    {
        if(!jsObject.value("Dev").toString().isEmpty() && !jsObject.value("Data").toString().isEmpty())
        {
            emit ReadData(jsObject.value("Dev").toString(), jsObject.value("Data").toString().toLocal8Bit());
        }
    }
}

void CatWebSocketClient::DecodeSerialOpenSucceed(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != SERIALOPENSUCCEED)
    {
        if(!jsObject.value("Dev").toString().isEmpty())
        {
            emit SerialOpenSucceed(jsObject.value("Dev").toString());
        }
    }
}

void CatWebSocketClient::DecodeSerialCloseSucceed(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != SERIALCLOSESUCCEED)
    {
        if(!jsObject.value("Dev").toString().isEmpty())
        {
            emit SerialCloseSucceed(jsObject.value("Dev").toString());
        }
    }
}

void CatWebSocketClient::DecodeSerialDisconnect(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != SERIALDISCONNECT)
    {
        if(!jsObject.value("Dev").toString().isEmpty())
        {
            emit SerialDisconnect(jsObject.value("Dev").toString());
        }
    }
}

void CatWebSocketClient::DecodeSerialDevList(QString data)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLocal8Bit().data());
    QJsonObject jsObject = jsonDocument.object();
    if(jsObject.value("Cmd").toInt() != SERIALDEVLIST)
    {
        QList<QString> devs;
        
        /*if(!jsObject.value("Dev").toString().isEmpty())
        {
            emit SerialDisconnect(jsObject.value("Dev").toString());
        }*/
    }
}

void CatWebSocketClient::DecodeOpenSerialPort(QString data)
{

}

void CatWebSocketClient::DecodeCloseSerialPort(QString data)
{

}

void CatWebSocketClient::DecodeWriteData(QString data)
{

}

void CatWebSocketClient::run()
{
    InitProperty();
    InitConnect();
    exec();
    qDebug() << "exit client socket";
    m_pWebSocket->close();
    delete m_pWebSocket;
    m_pWebSocket = nullptr;
}

void CatWebSocketClient::SerialDevList()
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", SERIALDEVLIST);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    m_pWebSocket->sendTextMessage(json);
}

void CatWebSocketClient::OpenSerialPort(QString port, qint32 baudRate, int stopBits)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", OPENSERIALPORT);
    jsobject.insert("Dev", port);
    jsobject.insert("BaudRate", baudRate);
    jsobject.insert("StopBits", stopBits);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    m_pWebSocket->sendTextMessage(json);
}

void CatWebSocketClient::CloseSerialPort(QString port)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", CLOSESERIALPORT);
    jsobject.insert("Dev", port);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    m_pWebSocket->sendTextMessage(json);
}

void CatWebSocketClient::WriteData(QString port, QByteArray data)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", WRITEDATA);
    jsobject.insert("Dev", port);
    jsobject.insert("Data", data);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    m_pWebSocket->sendTextMessage(json);
}
