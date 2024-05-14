#ifndef CATECHATSWEBCHANNEL_H
#define CATECHATSWEBCHANNEL_H

#include <QtWebChannel/QtWebChannel>
#include <QtWebChannel/QWebChannelAbstractTransport>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class CatEchatswebChannel : public QWebChannelAbstractTransport
{
    Q_OBJECT
public:
    CatEchatswebChannel();
    ~CatEchatswebChannel();

    Q_INVOKABLE void sendMessage(const QJsonObject &message) override;

    Q_INVOKABLE void textMessageReceive(const QString &messageData);

signals:
    void messageChanged(const QString &message);

};

#endif // CATECHATSWEBCHANNEL_H
