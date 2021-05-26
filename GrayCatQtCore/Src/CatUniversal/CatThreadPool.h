#ifndef CATTHREADPOOL_H
#define CATTHREADPOOL_H

#include <QObject>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include "CatThread.h"

class CatThreadPool : public QObject
{
    Q_OBJECT
public:
    explicit CatThreadPool(QObject *parent = nullptr, int InitialThreadCount = QThread::idealThreadCount());
    ~CatThreadPool();

public:
    int GetThreadCount( void );
    int GetThreadWorkCount( void );

    template<class F, class... Args>
    void AddTask(F&& f, Args&&... args)
    {
        if(GetThreadCount() == GetThreadWorkCount())
        {
            CatThread *thread = new CatThread(this);
            m_pHandleMutex.lock();
            m_pThreadList.push_back(thread);
            thread->Start(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
            m_pHandleMutex.unlock();
            return;
        } else {
            for(auto thread : m_pThreadList)
            {
                if(!thread->GetWork())
                {
                    thread->Start(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
                    return;
                }
            }
        }
    }

private:
    void InitHandleNonWorkTimer( void );
    int HandleNonWork( void );

signals:
    // 定时发送处理不工作线程数
    void handthreadsed(int);

private:
    int m_iDefaultThreadCount;
    int m_iThreadWorkCount;
    QList<CatThread*> m_pThreadList;
    bool m_bHandle_NonWork_Threads;
    CatThread *m_pHandle_NonWork_Threads; //  处理不工作线程
    QMutex m_pHandleMutex;
    QMutex m_pWrokMutex;

};

#endif // CATTHREADPOOL_H
