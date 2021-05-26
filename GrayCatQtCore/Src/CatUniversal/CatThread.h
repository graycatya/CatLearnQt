#ifndef CatTHREAD_H
#define CatTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>
#include <functional>

class QTcpSocket;

class CatThread : public QThread
{
    Q_OBJECT
public:
    explicit CatThread(QObject *parent = nullptr);
    ~CatThread();

public:
    template<class F, class... Args>
    void Start(F&& f, Args&&... args)
    {
        m_pFunction = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        m_bWork = true;
        m_qWaitCondition.notify_one();
    }

    void Start(std::function<void()> &&function);

    bool GetWork( void ) const
    {
        return m_bWork;
    }

    bool GetStart( void ) const
    {
        return m_bStart;
    }

    void Stop();

protected:
    void run();

signals:
    void worked();
    void quitworked();

private:
    bool m_bStart;  // 线程是否启动
    bool m_bWork;   // 线程是否工作

    QWaitCondition m_qWorkWaitCondition;

    QMutex m_qMutex;
    QWaitCondition m_qWaitCondition;

    Qt::HANDLE m_qThreadId; // 线程id

    std::function<void()> m_pFunction;

};

#endif // CatTHREAD_H
