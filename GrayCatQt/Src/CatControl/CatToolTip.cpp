#include "CatToolTip.h"
#include <QToolTip>

CatToolTip *CatToolTip::_instance = nullptr;
std::mutex* CatToolTip::m_pMutex = new std::mutex;


void CatToolTip::ShowToolTip(QString text, int sleep)
{
    std::unique_lock<std::mutex> lock(*m_pMutex);
    m_sShowText = text;
    m_pTimer->start(sleep);
}

void CatToolTip::HideToolTip()
{
    std::unique_lock<std::mutex> lock(*m_pMutex);
    if(m_pTimer->isActive())
    {
        m_pTimer->stop();
    }
    QToolTip::hideText();
}

CatToolTip::CatToolTip()
{
    m_pTimer = new QTimer(this);
    m_sShowText.clear();
    InitConnect();
}

CatToolTip::~CatToolTip()
{

}

void CatToolTip::InitConnect()
{
    connect(m_pTimer, &QTimer::timeout, this, [=](){
        QToolTip::showText(QCursor::pos(), m_sShowText);
    });
}
