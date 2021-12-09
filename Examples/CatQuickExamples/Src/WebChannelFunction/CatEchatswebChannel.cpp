#include "CatEchatswebChannel.h"
#include <QDebug>

CatEchatswebChannel::CatEchatswebChannel()
{

}

CatEchatswebChannel::~CatEchatswebChannel()
{

}

void CatEchatswebChannel::sendMessage(const QJsonObject &message)
{
    QJsonDocument doc(message);
    emit messageChanged(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

void CatEchatswebChannel::textMessageReceive(const QString &messageData)
{
    QJsonParseError error;
    QJsonDocument message = QJsonDocument::fromJson(messageData.toUtf8(), &error);
    if (error.error)
    {
        qWarning() << "Failed to parse text message as JSON object:" << messageData
                   << "Error is:" << error.errorString();
        return;
    } else if (!message.isObject())
    {
        qWarning() << "Received JSON message that is not an object: " << messageData;
        return;
    }
    emit messageReceived(message.object(), this);
}
