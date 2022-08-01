#include "CatNetWorkHttp.h"
#include <QDir>
#include <QCoreApplication>
#include <QUrlQuery>
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#include <QTextCodec>
#endif
#include <QHttpMultiPart>
#include <QJsonParseError>

CatNetWorkHttp::CatNetWorkHttp(QObject *parent)
    : QThread(parent)
    , m_bStart(false)
    , m_bWork(false)
    , m_yState(NONE)
{
    moveToThread(this);
    m_pFile = nullptr;
    m_bStart = true;
    this->start();
    m_yStartMutex.lock();
    m_yWaitStartCondition.wait(&m_yStartMutex);
    m_yStartMutex.unlock();
}

CatNetWorkHttp::~CatNetWorkHttp()
{
    m_bStart = false;
    m_bWork = false;
    if(m_pFile)
    {
        m_pFile->flush();
        m_pFile->close();
        m_pFile->deleteLater();
        m_pFile = nullptr;
    }
    if(this->isRunning())
    {
        requestInterruption();
        this->quit();
        this->wait();
    }
}

int CatNetWorkHttp::DownLoad(QUrl url, QString downloaddir, bool ssl)
{
    if(m_bStart)
    {
        m_bWork = true;
        QDir dir;
        if(!dir.exists(downloaddir))
        {
            if(!dir.mkpath(downloaddir))
            {
                m_bWork = false;
                return DOWNLOADPATHERROR;
            }
        }
        QFileInfo info(url.path());
        QString fileName(info.fileName());
        if(downloaddir[downloaddir.size()-1] != "/")
        {
            downloaddir = downloaddir + "/";
        }
        fileName = downloaddir+fileName;
        QHash<QString, QVariant> hash;
        hash["url"] = url;
        hash["fileName"] = fileName;
        hash["ssl"] = ssl;
        m_pVar = hash;
        m_yState = DOWNLOAD;
        m_yWaitCondition.notify_one();
    }

    return NORMAL;
}

int CatNetWorkHttp::HttpGet(QUrl url, QVariantHash heads, QUrlQuery query, bool ssl)
{
    if(m_bStart)
    {
        m_bWork = true;
        if(url.isEmpty())
        {
            m_bWork = false;
            return URLERROR;
        }
        url.setQuery(query);
        QVariantHash hash;
        hash["url"] = url;
        hash["heads"] = heads;
        hash["ssl"] = ssl;
        m_pVar = hash;
        m_yState = HTTPGET;
        m_yWaitCondition.notify_one();
        return NORMAL;
    } else {
        return ISSTART;
    }
}

int CatNetWorkHttp::HttpPost(QUrl url, QVariantHash heads, QUrlQuery query, QByteArray &data, bool ssl)
{
    if(m_bStart)
    {
        m_bWork = true;
        if(url.isEmpty())
        {
            m_bWork = false;
            return URLERROR;
        }
        QUrl curUrl = url;
        curUrl.setQuery(query);
        QVariantHash hash;
        hash["url"] = curUrl;
        hash["heads"] = heads;
        hash["data"] = data;
        hash["ssl"] = ssl;
        m_pVar = hash;
        m_yState = HTTPPOST;
        m_yWaitCondition.notify_one();
        return NORMAL;
    } else {
        return ISSTART;
    }
}

int CatNetWorkHttp::HttpPost(QUrl url, QVariantHash heads, QUrlQuery query, QHttpMultiPart *data, bool ssl)
{
    if(m_bStart)
    {
        m_bWork = true;
        if(url.isEmpty())
        {
            m_bWork = false;
            return URLERROR;
        }
        QUrl curUrl = url;
        curUrl.setQuery(query);
        QVariantHash hash;
        hash["url"] = curUrl;
        hash["heads"] = heads;
        hash["data"] = QVariant::fromValue(reinterpret_cast<void*>(data));
        hash["ssl"] = ssl;
        m_pVar = hash;
        m_yState = HTTPMULTIPARTPOST;
        m_yWaitCondition.notify_one();
        return NORMAL;
    } else {
        return ISSTART;
    }
}


void CatNetWorkHttp::run()
{

    m_yMutex.lock();
    m_yWaitStartCondition.notify_all();
    m_yWaitCondition.wait(&m_yMutex);
    m_yMutex.unlock();
    QThread::msleep(1000);
    QNetworkAccessManager *m_pManager = new QNetworkAccessManager;
    switch (m_yState) {
        case DOWNLOAD: {
            InitHttpDownLoad(m_pManager);
            break;
        }
        case HTTPGET: {
            InitHttpGet(m_pManager);
            break;
        }
        case HTTPPOST: {
            InitHttpPost(m_pManager);
            break;
        }
        case HTTPMULTIPARTPOST: {
            InitHttpMultiPartPost(m_pManager);
            break;
        }
        default:{
            m_yState = NONE;
            m_bWork = false;
            break;
        }
    }
    while(m_bWork)
    {
        this->exec();
    }
    m_bStart = false;
    m_pManager->deleteLater();
    m_pManager = nullptr;
}



void CatNetWorkHttp::InitHttpDownLoad(QNetworkAccessManager *m_pManager)
{
    QNetworkReply *m_pReply = nullptr;
    QHash<QString, QVariant> hash = m_pVar.toHash();
    m_pFile = new QFile(hash["fileName"].toString());
    if(!m_pFile->open(QIODevice::WriteOnly))
    {
        m_bWork = false;
        m_pFile->deleteLater();
        m_pFile = nullptr;
        return;
    }
    if(hash["ssl"].toBool())
    {
        QNetworkRequest request;
        QSslConfiguration config;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1_0);
        request.setSslConfiguration(conf);
        request.setUrl(hash["url"].toUrl());
        m_pReply = m_pManager->get(request);
    } else {
        m_pReply = m_pManager->get(QNetworkRequest(hash["url"].toUrl()));
    }

    if(m_pReply != nullptr)
    {
        connect(m_pReply, &QNetworkReply::readyRead, this, &CatNetWorkHttp::httpDownReadyRead);
        connect(m_pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateDataReadProgress(qint64, qint64)));
        connect(m_pReply, SIGNAL(finished()), this, SLOT(httpDownFinished()));
        connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
    }
}

void CatNetWorkHttp::InitHttpGet(QNetworkAccessManager *m_pManager)
{
    QHash<QString, QVariant> hash = m_pVar.toHash();
    QNetworkRequest request;
    QHash<QString, QVariant>::const_iterator heads = hash["heads"].toHash().constBegin();
    while (heads != hash["heads"].toHash().constEnd() && !hash["heads"].toHash().isEmpty()) {
        request.setRawHeader(heads.key().toUtf8(), heads.value().toByteArray());
        ++heads;
    }

    connect(m_pManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        QNetworkReply *m_pReply = reply;
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Http Reply statusCode: " << statusCode;

        QNetworkReply::NetworkError error = reply->error();
        if(error == reply->NoError)
        {
            QByteArray datas = m_pReply->readAll();

            while (m_pReply->waitForReadyRead(50))
            {
                datas += m_pReply->readAll();
            }

            emit ReplyDataed(datas);
        } else {
            emit NetWorkError();
        }

        m_yState = NONE;
        m_pVar.clear();
        m_bWork = false;
        m_pReply->deleteLater();
        this->quit();
    });

    connect(m_pManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        qDebug() << "sslerror: " << errors;
        m_yState = NONE;
        m_pVar.clear();
        m_bWork = false;
        reply->deleteLater();
        this->quit();
    });

    if(hash["ssl"].toBool())
    {
        QSslConfiguration config;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1_0);
        request.setSslConfiguration(conf);
        request.setUrl(hash["url"].toUrl());
        m_pManager->get(request);
    } else {
        request.setUrl(hash["url"].toUrl());
        m_pManager->get(request);
    }
}

void CatNetWorkHttp::InitHttpPost(QNetworkAccessManager *m_pManager)
{
    QHash<QString, QVariant> hash = m_pVar.toHash();
    QNetworkRequest request;
    QHash<QString, QVariant>::const_iterator heads = hash["heads"].toHash().constBegin();
    while (heads != hash["heads"].toHash().constEnd() && !hash["heads"].toHash().isEmpty()) {
        request.setRawHeader(heads.key().toUtf8(), heads.value().toByteArray());
        ++heads;
    }

    connect(m_pManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        QNetworkReply *m_pReply = reply;
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "Http Reply statusCode: " << statusCode;

        QNetworkReply::NetworkError error = reply->error();
        if(error == reply->NoError)
        {
            QByteArray datas = m_pReply->readAll();

            while (m_pReply->waitForReadyRead(50))
            {
                datas += m_pReply->readAll();
            }

            emit ReplyDataed(datas);
        } else {
            emit NetWorkError();
        }

        m_yState = NONE;
        m_pVar.clear();
        m_bWork = false;
        m_pReply->deleteLater();
        this->quit();
    });

    connect(m_pManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        qDebug() << "sslerror: " << errors;
        m_yState = NONE;
        m_pVar.clear();
        m_bWork = false;
        reply->deleteLater();
        this->quit();
    });

    if(hash["ssl"].toBool())
    {
        QSslConfiguration config;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1_0);
        request.setSslConfiguration(conf);
        request.setUrl(hash["url"].toUrl());
        m_pManager->post(request, hash["data"].toByteArray());
    } else {
        request.setUrl(hash["url"].toUrl());
        m_pManager->post(request, hash["data"].toByteArray());
    }
}

void CatNetWorkHttp::InitHttpMultiPartPost(QNetworkAccessManager *m_pManager)
{
    QHash<QString, QVariant> hash = m_pVar.toHash();
    QNetworkRequest request;
    QHash<QString, QVariant>::const_iterator heads = hash["heads"].toHash().constBegin();
    while (heads != hash["heads"].toHash().constEnd() && !hash["heads"].toHash().isEmpty()) {
        request.setRawHeader(heads.key().toUtf8(), heads.value().toByteArray());
        ++heads;
    }

    connect(m_pManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        QNetworkReply *m_pReply = reply;
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        qDebug() << "Http Reply statusCode: " << statusCode;

        QNetworkReply::NetworkError error = reply->error();
        if(error == reply->NoError)
        {
            QByteArray datas = m_pReply->readAll();

            while (m_pReply->waitForReadyRead(50))
            {
                datas += m_pReply->readAll();
            }

            emit ReplyDataed(datas);
        } else {
            emit NetWorkError();
        }

        m_yState = NONE;
        m_pVar.clear();
        m_bWork = false;
        QHttpMultiPart* part = reinterpret_cast<QHttpMultiPart*>(hash["data"].value<void*>());
        part->deleteLater();
        m_pReply->deleteLater();
        this->quit();
    });

    connect(m_pManager, &QNetworkAccessManager::sslErrors, this, [=](QNetworkReply *reply, const QList<QSslError> &errors){
        qDebug() << "sslerror: " << errors;
        m_yState = NONE;
        m_pVar.clear();
        m_bWork = false;
        QHttpMultiPart* part = reinterpret_cast<QHttpMultiPart*>(hash["data"].value<void*>());
        part->deleteLater();
        reply->deleteLater();
        this->quit();
    });

    if(hash["ssl"].toBool())
    {
        QSslConfiguration config;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1_0);
        request.setSslConfiguration(conf);
        request.setUrl(hash["url"].toUrl());
        hash["data"].value<void*>();
        QHttpMultiPart* part = reinterpret_cast<QHttpMultiPart*>(hash["data"].value<void*>());
        //part->moveToThread(this);
        m_pManager->post(request, part);
        //part->setParent(reply);
    } else {
        request.setUrl(hash["url"].toUrl());
        QHttpMultiPart* part = reinterpret_cast<QHttpMultiPart*>(hash["data"].value<void*>());
        //part->moveToThread(this);
        m_pManager->post(request, part);
        //part->setParent(reply);
    }
}

void CatNetWorkHttp::ExitTask()
{
    m_bStart = false;
    m_bWork = false;
    if(m_pFile)
    {
        m_pFile->flush();
        m_pFile->close();
        m_pFile->deleteLater();
        m_pFile = nullptr;
    }
    if(this->isRunning())
    {
        requestInterruption();
        this->quit();
        this->wait();
        emit ExitTasked();
    }
}


void CatNetWorkHttp::httpDownFinished()
{
    QNetworkReply *m_pReply =qobject_cast<QNetworkReply *>(sender());
    m_pReply->deleteLater();
    m_pReply = nullptr;
    if(m_pFile)
    {
        m_pFile->flush();
        m_pFile->close();
        m_pFile->deleteLater();
        m_pFile = nullptr;
    }

    m_yState = NONE;
    m_bWork = false;

    QString file = m_pVar.toHash()["fileName"].toString();
    emit DownLoadFinished(file);
    m_pVar.clear();
    this->quit();
}

void CatNetWorkHttp::httpDownReadyRead()
{
    QNetworkReply *m_pReply =qobject_cast<QNetworkReply *>(sender());
    if(m_pFile)
    {
        int available = m_pReply->bytesAvailable();
        if(available > 0)
        {
            QByteArray data = m_pReply->read(available);
            if(!data.isEmpty())
            {
                m_pFile->write(data);
            }
        }
    }
}

void CatNetWorkHttp::httpError(QNetworkReply::NetworkError)
{
    QNetworkReply *m_pReply =qobject_cast<QNetworkReply *>(sender());
    m_pReply->deleteLater();
    m_pReply = nullptr;
    switch (m_yState) {
        case DOWNLOAD: {
            if(m_pFile)
            {
                m_pFile->flush();
                m_pFile->close();
                m_pFile->deleteLater();
                m_pFile = nullptr;
            }
            emit DownLoadError();
            break;
        }
        case HTTPGET: {
            break;
        }
        case HTTPPOST: {
            emit HttpPostError();
            break;
        }
        default: {
            break;
        }
    }

    m_yState = NONE;
    m_bWork = false;
    m_pVar.clear();
    this->quit();
}

void CatNetWorkHttp::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    emit DownLoadProgress(bytesRead, totalBytes);
}
