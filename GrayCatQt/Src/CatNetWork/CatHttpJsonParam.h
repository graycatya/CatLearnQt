#ifndef CatHttpJsonParam_H
#define CatHttpJsonParam_H

#include <QObject>
#include <QJsonObject>

class CatHttpJsonParam : public QObject
{
    Q_OBJECT
public:
    explicit CatHttpJsonParam(QObject *parent = nullptr);

    void AddHttpParam(const QString &key, const QJsonValue &value);
    void AddHttpParamObject(const QString &key, const QJsonObject &value);
    void AddHttpParamArray(const QString &key, const QJsonArray &value);
    QByteArray GetHttpParams();

private:
    QJsonObject m_yParamObject;
};

#endif // CatHttpJsonParam_H
