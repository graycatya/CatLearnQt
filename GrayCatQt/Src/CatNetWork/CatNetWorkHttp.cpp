#include "CatNetWorkHttp.h"
#include <QDir>
#include <QCoreApplication>

CatNetWorkHttp::CatNetWorkHttp(QObject *parent)
    : QThread(parent)
    , m_bStart(false)
    , m_bWork(false)
    , m_yState(NONE)
{
    m_pFile = nullptr;
    m_bStart = true;
    this->start();
}

CatNetWorkHttp::~CatNetWorkHttp()
{
    m_bStart = false;
    this->wait();
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
                return -1;
            }
        }
        QFileInfo info(url.path());
        QString fileName(info.fileName());
        fileName = downloaddir+fileName;
        m_pFile = new QFile(fileName);
        if(!m_pFile->open(QIODevice::WriteOnly))
        {
            m_bWork = false;
            m_pFile->deleteLater();
            m_pFile = nullptr;
            return -2;
        }
        QHash<QString, QVariant> hash;
        hash["url"] = url;
        hash["fileName"] = fileName;
        hash["ssl"] = ssl;
        m_pVar = hash;
        m_yState = DOWNLOAD;
        m_yWaitCondition.notify_one();
    }

    return 0;
}

void CatNetWorkHttp::run()
{
    QNetworkAccessManager *m_pManager = new QNetworkAccessManager;
    QNetworkReply *m_pReply = nullptr;
    while(m_bStart)
    {
        m_yMutex.lock();
        m_yWaitCondition.wait(&m_yMutex);
        m_yMutex.unlock();
        switch (m_yState) {
            case DOWNLOAD: {
                InitHttpDownLoad(m_pManager, m_pReply);
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
            QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
        }
    }
    m_pManager->deleteLater();
}

void CatNetWorkHttp::InitHttpDownLoad(QNetworkAccessManager *m_pManager, QNetworkReply *m_pReply)
{
    QHash<QString, QVariant> hash = m_pVar.toHash();
    if(hash["ssl"].toBool())
    {
        m_pReply = m_pManager->get(QNetworkRequest(hash["url"].toUrl()));
    } else {
        QNetworkRequest request;
        QSslConfiguration config;
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::TlsV1SslV3);
        request.setSslConfiguration(conf);
        request.setUrl(hash["url"].toUrl());
        m_pReply = m_pManager->get(request);
    }

    connect(m_pReply, SIGNAL(readyRead()), this, SLOT(httpDownReadyRead()));
    connect(m_pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateDataReadProgress(qint64, qint64)));
    connect(m_pReply, SIGNAL(finished()), this, SLOT(httpDownFinished()));
    connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(httpError(QNetworkReply::NetworkError)));
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
}

void CatNetWorkHttp::httpDownReadyRead()
{
    QNetworkReply *m_pReply =qobject_cast<QNetworkReply *>(sender());
    if(m_pFile)
    {
        m_pFile->write(m_pReply->readAll());
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
        default: {
            break;
        }
    }

    m_yState = NONE;
    m_bWork = false;
    m_pVar.clear();
}

void CatNetWorkHttp::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    emit DownLoadProgress(bytesRead, totalBytes);
}
