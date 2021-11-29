#include "CatFramelessMainWindow.h"


CatFramelessMainWindow::CatFramelessMainWindow(QWidget *parent)
{

}

void CatFramelessMainWindow::showEvent(QShowEvent *event)
{

}

void CatFramelessMainWindow::doWindowStateChange(QEvent *event)
{

}

void CatFramelessMainWindow::doResizeEvent(QEvent *event)
{

}

bool CatFramelessMainWindow::eventFilter(QObject *watched, QEvent *event)
{

}


#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool CatFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
    bool CatFramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
{

}
