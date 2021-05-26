#include "CatHttpJsonParam.h"
#include <QJsonDocument>
#include <QJsonArray>

CatHttpJsonParam::CatHttpJsonParam(QObject *parent)
    : QObject(parent)
{

}

void CatHttpJsonParam::AddHttpParam(const QString &key, const QJsonValue &value)
{
    m_yParamObject.insert(key, value);
}

void CatHttpJsonParam::AddHttpParamObject(const QString &key, const QJsonObject &value)
{
    m_yParamObject.insert(key, value);
}

void CatHttpJsonParam::AddHttpParamArray(const QString &key, const QJsonArray &value)
{
    m_yParamObject.insert(key, value);
}

QByteArray CatHttpJsonParam::GetHttpParams()
{
    QJsonDocument document = QJsonDocument(m_yParamObject);
    QByteArray params = document.toJson();
    return params;
}
