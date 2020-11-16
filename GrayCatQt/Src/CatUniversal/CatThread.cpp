#include "CatThread.h"
#include <QTcpSocket>
#include <QHostAddress>

CatThread::CatThread(QObject *parent)
    : QThread(parent)
    , m_bStart(false)
    , m_bWork(false)
    , m_qThreadId(nullptr)
    , m_pFunction(nullptr)
{
    m_bStart = true;
    this->start();
}

CatThread::~CatThread()
{
    Stop();
}

void CatThread::Start(std::function<void ()> &&function)
{
    m_pFunction = function;
    m_bWork = true;
    m_qWaitCondition.notify_one();
}

void CatThread::Stop()
{
    m_bWork = false;
    m_bStart = false;
    m_pFunction = nullptr;
    m_qWaitCondition.notify_one();
    this->wait();
}

void CatThread::run()
{
    while(m_bStart)
    {
        m_qThreadId = QThread::currentThreadId();

        if(m_pFunction != nullptr)
        {
            m_bWork = true;
            emit worked();
            m_pFunction();
            m_bWork = false;
            emit quitworked();
        }

        m_qMutex.lock();
        m_qWaitCondition.wait(&m_qMutex);
        m_qMutex.unlock();
    }
    m_bStart = false;
}
