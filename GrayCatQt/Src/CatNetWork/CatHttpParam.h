#ifndef CATHTTPPARAM_H
#define CATHTTPPARAM_H

#include <QObject>
#include <QJsonObject>

class CatHttpParam : public QObject
{
    Q_OBJECT
public:
    explicit CatHttpParam(QObject *parent = nullptr);

    void AddHttpParam(const QString &key, const QJsonValue &value);
    void AddHttpParamObject(const QString &key, const QJsonObject &value);
    void AddHttpParamArray(const QString &key, const QJsonArray &value);
    QByteArray GetHttpParams();

private:
    QJsonObject m_yParamObject;
};

#endif // CATHTTPPARAM_H
