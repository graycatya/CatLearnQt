#ifndef CATNETWORKHTTP_H
#define CATNETWORKHTTP_H

#include <QThread>
#include <QNetworkReply>
#include <QMutex>
#include <QWaitCondition>
#include <QFile>

class CatNetWorkHttp : public QThread
{
    Q_OBJECT
    Q_ENUMS(CATNETWORKERROR)
    Q_ENUMS(HTTPSTATE)
public:
    enum CATNETWORKERROR {
        NORMAL,
        ISSTART,
        DOWNLOADPATHERROR,
        FILEOPENERROR,
        URLERROR
    };
    enum HTTPSTATE {
        NONE,
        DOWNLOAD,
        HTTPGET,
        HTTPPOST,
        HTTPMULTIPARTPOST,
        HTTPPUS
    };
    explicit CatNetWorkHttp(QObject *parent = nullptr);
    ~CatNetWorkHttp();

public:
    int DownLoad(QUrl url, QString downloaddir, bool ssl = false);
    int HttpGet(QUrl url, QVariantHash heads, QUrlQuery query, bool ssl = false);
    int HttpPost(QUrl url, QVariantHash heads, QUrlQuery query, QByteArray& data, bool ssl = false);
    int HttpPost(QUrl url, QVariantHash heads, QUrlQuery query, QHttpMultiPart* data, bool ssl = false);

protected:
    void run() override;

private:
    void InitHttpDownLoad(QNetworkAccessManager *m_pManager);
    void InitHttpGet(QNetworkAccessManager *m_pManager);
    void InitHttpPost(QNetworkAccessManager *m_pManager);
    void InitHttpMultiPartPost(QNetworkAccessManager *m_pManager);

signals:
    void DownLoadFinished(QString filePath);
    void DownLoadError();
    void HttpPostError();
    void DownLoadProgress(qint64, qint64);
    void NetWorkError();
    void ReplyDataed(QByteArray data);
    void ExitTasked();

public slots:
    void ExitTask();

private slots:
    void httpDownFinished();
    void httpDownReadyRead();
    void httpError(QNetworkReply::NetworkError);
    void updateDataReadProgress(qint64, qint64);

private:
    bool m_bStart;
    bool m_bWork;
    QMutex m_yMutex;
    QWaitCondition m_yWaitCondition;
    QMutex m_yStartMutex;
    QWaitCondition m_yWaitStartCondition;


    QVariant m_pVar;

    QFile *m_pFile;
    HTTPSTATE m_yState;
};

#endif // CATNETWORKHTTP_H
