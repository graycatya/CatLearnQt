#ifndef CATECHATSWEBCHANNEL_H
#define CATECHATSWEBCHANNEL_H

#include <QWebChannelAbstractTransport>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class CatEchatswebChannel : public QWebChannelAbstractTransport
{
    Q_OBJECT
public:
    CatEchatswebChannel();
    ~CatEchatswebChannel();


};

#endif // CATECHATSWEBCHANNEL_H
