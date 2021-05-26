#include "CatHttpParam.h"
#include <QFile>


CatHttpParam::CatHttpParam(QObject *parent)
    : QObject(parent)
{
    m_yParts.clear();
}

QHttpPart CatHttpParam::AddHttpParam(const QString &key, const QString &value)
{
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(key)));
    part.setBody(value.toUtf8());
    m_yParts.push_back(part);
    return part;
}

QHttpPart CatHttpParam::AddHttpImageParam(QHttpMultiPart *multipart, const QString &key, const QString &imagepath, const QString &type)
{
    QHttpPart imagePart;
    if(multipart)
    {
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(type));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(QString("form-data; name=\"%1\"").arg(key)));
        QFile *file = new QFile(imagepath);
        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multipart);
    }
    m_yParts.push_back(imagePart);
    return imagePart;
}

QVector<QHttpPart> CatHttpParam::GetHttpParams()
{
    return m_yParts;
}

void CatHttpParam::ClearParams()
{
    m_yParts.clear();
}
