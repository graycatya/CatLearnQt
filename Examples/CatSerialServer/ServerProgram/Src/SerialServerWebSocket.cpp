#include "SerialServerWebSocket.h"
#include <QCoreApplication>
#include <CatLog>
#include "../ServerConfig.h"
#include "SerialDevList.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


SerialServerWebSocket::SerialServerWebSocket(QObject *parent)
    : QObject(parent)
{
    InitProperty();
    InitConnect();
}

SerialServerWebSocket::~SerialServerWebSocket()
{

}

void SerialServerWebSocket::InitProperty()
{
    m_pSockets.clear();
    m_pWebSocketServer = new QWebSocketServer(QCoreApplication::applicationName(), QWebSocketServer::NonSecureMode, this);
    quint16 port = 10024;

    if(ServerConfig::Instance()->getValue("WebSocketServer_Port").toInt() != 0)
    {
        port = ServerConfig::Instance()->getValue("WebSocketServer_Port").toInt();
    }
    if(m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        QString log = QString("Start webSocket %1 url %4")
                .arg(m_pWebSocketServer->serverName())
                .arg(m_pWebSocketServer->serverUrl().toString());
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &SerialServerWebSocket::onNewConnection);
    } else {
        QString log = QString("Start webSocketServer Error");
        CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    }
}

void SerialServerWebSocket::InitConnect()
{
    connect(SerialDevList::Instance(), &SerialDevList::AddDev, this, [=](QString port){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(AddDev(port));
            }
        }
    }, Qt::QueuedConnection);
    connect(SerialDevList::Instance(), &SerialDevList::DelDev, this, [=](QString port){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(DelDev(port));
            }
        }
    }, Qt::QueuedConnection);
    connect(SerialDevList::Instance(), &SerialDevList::SerialError, this, [=](QString port, quint64 error){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(SerialError(port, error));
            }
        }
    }, Qt::QueuedConnection);
    connect(SerialDevList::Instance(), &SerialDevList::ReadData, this, [=](QString port, QByteArray data){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(ReadData(port, data));
            }
        }
    }, Qt::QueuedConnection);
    connect(SerialDevList::Instance(), &SerialDevList::SerialOpenSucceed, this, [=](QString port){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(SerialOpenSucceed(port));
            }
        }
    }, Qt::QueuedConnection);
    connect(SerialDevList::Instance(), &SerialDevList::SerialCloseSucceed, this, [=](QString port){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(SerialCloseSucceed(port));
            }
        }
    }, Qt::QueuedConnection);
    connect(SerialDevList::Instance(), &SerialDevList::SerialDisconnect, this, [=](QString port){
        if(m_pWebSocketServer->isListening())
        {
            foreach(auto socket , m_pSockets)
            {
                socket->sendTextMessage(SerialDisconnect(port));
            }
        }
    }, Qt::QueuedConnection);
}

QString SerialServerWebSocket::NewConnectSocket()
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", NEWCONNECTSOCKET);
    jsobject.insert("ServerName", m_pWebSocketServer->serverName());
    jsobject.insert("ServerPort", m_pWebSocketServer->serverPort());
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::AddDev(QString port)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", ADDDEV);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::DelDev(QString port)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", DELDEV);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::SerialError(QString port, quint64 error)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", SERIALERROR);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("Error", static_cast<qint64>(error));
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::ReadData(QString port, QByteArray data)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", READDATA);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("Data", QString(data));
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::SerialOpenSucceed(QString port)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", SERIALOPENSUCCEED);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::SerialCloseSucceed(QString port)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", SERIALCLOSESUCCEED);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

QString SerialServerWebSocket::SerialDisconnect(QString port)
{
    QString json;
    QJsonDocument doc;
    QJsonObject jsobject;
    jsobject.insert("Cmd", SERIALDISCONNECT);
    jsobject.insert("ServerUrl", m_pWebSocketServer->serverUrl().toString());
    jsobject.insert("Dev", port);
    jsobject.insert("State", 200);
    doc.setObject(jsobject);
    json = doc.toJson();
    return json;
}

void SerialServerWebSocket::onNewConnection()
{
    QWebSocket *socket = m_pWebSocketServer->nextPendingConnection();
    QString log = QString("connect %1 %2:%3")
            .arg(socket->peerName())
            .arg(socket->peerAddress()
            .toString()).arg(socket->peerPort());
    CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    connect(socket, &QWebSocket::binaryMessageReceived, this, &SerialServerWebSocket::ontextFrameReceived);
    connect(socket, &QWebSocket::textMessageReceived, this, &SerialServerWebSocket::ontextMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &SerialServerWebSocket::onDisconnected);

    m_pSockets.append(socket);
    socket->sendTextMessage(NewConnectSocket());
}

void SerialServerWebSocket::ontextMessageReceived(const QString &message)
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    QString log = QString("receive text %1 %2:%3 | %4")
            .arg(socket->peerName())
            .arg(socket->peerAddress().toString())
            .arg(socket->peerPort())
            .arg(message);
    CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    DecodeData(message);
}

void SerialServerWebSocket::ontextFrameReceived(const QByteArray &message)
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    QString log = QString("receive byte %1 %2:%3 | %4")
            .arg(socket->peerName())
            .arg(socket->peerAddress().toString())
            .arg(socket->peerPort())
            .arg(QString(message));
    CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    DecodeData(message);
}

void SerialServerWebSocket::onDisconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket*>(sender());
    QString log = QString("disconnect %1 %2:%3")
            .arg(socket->peerName())
            .arg(socket->peerAddress().toString())
            .arg(socket->peerPort());
    CATLOG::CatLog::__Write_Log(INFO_LOG_T(log.toStdString()));
    m_pSockets.removeOne(socket);
    qDebug() << "sockets: " << m_pSockets.size();
}

void SerialServerWebSocket::DecodeData(QString data)
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
                        break;
                    }
                    case ADDDEV:{
                        qDebug() << "Decode ADDDEV";
                        break;
                    }
                    case DELDEV:{
                        qDebug() << "Decode DELDEV";
                        break;
                    }
                    case SERIALERROR:{
                        qDebug() << "Decode SERIALERROR";
                        break;
                    }
                    case READDATA:{
                        qDebug() << "Decode READDATA";
                        break;
                    }
                    case SERIALOPENSUCCEED:{
                        qDebug() << "Decode SERIALOPENSUCCEED";
                        break;
                    }
                    case SERIALCLOSESUCCEED:{
                        qDebug() << "Decode SERIALCLOSESUCCEED";
                        break;
                    }
                    case SERIALDISCONNECT:{
                        qDebug() << "Decode SERIALDISCONNECT";
                        break;
                    }
                    case SERIALDEVLIST:{
                        qDebug() << "Decode SERIALDEVLIST";
                        break;
                    }
                    case OPENSERIALPORT:{
                        qDebug() << "Decode OPENSERIALPORT";
                        break;
                    }
                    case CLOSESERIALPORT:{
                        qDebug() << "Decode CLOSESERIALPORT";
                        break;
                    }
                    case WRITEDATA:{
                        qDebug() << "Decode WRITEDATA";
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
