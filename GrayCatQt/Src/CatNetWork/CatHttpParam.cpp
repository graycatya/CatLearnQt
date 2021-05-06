#include "CatHttpParam.h"
#include <QJsonDocument>
#include <QJsonArray>

CatHttpParam::CatHttpParam(QObject *parent)
    : QObject(parent)
{

}

void CatHttpParam::AddHttpParam(const QString &key, const QJsonValue &value)
{
    m_yParamObject.insert(key, value);
}

void CatHttpParam::AddHttpParamObject(const QString &key, const QJsonObject &value)
{
    m_yParamObject.insert(key, value);
}

void CatHttpParam::AddHttpParamArray(const QString &key, const QJsonArray &value)
{
    m_yParamObject.insert(key, value);
}

QByteArray CatHttpParam::GetHttpParams()
{
    QJsonDocument document = QJsonDocument(m_yParamObject);
    QByteArray params = document.toJson();
    return params;
}
