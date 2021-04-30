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
public:
    enum HTTPSTATE {
        NONE,
        DOWNLOAD,
        HTTPGET,
        HTTPOST,
        HTTPPUS
    };
    explicit CatNetWorkHttp(QObject *parent = nullptr);
    ~CatNetWorkHttp();

public:
    int DownLoad(QUrl url, QString downloaddir, bool ssl = false);
    int HttpGet(QUrl url);

protected:
    void run() override;

private:
    void InitHttpDownLoad(QNetworkAccessManager *m_pManager, QNetworkReply *m_pReply);

signals:
    void DownLoadFinished(QString filePath);
    void DownLoadError();
    void DownLoadProgress(qint64, qint64);

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
