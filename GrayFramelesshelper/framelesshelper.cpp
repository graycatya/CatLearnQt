/*
 * MIT License
 *
 * Copyright (C) 2021 by wangwenx190 (Yuhang Zhao)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "framelesshelper.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))

#include <QDateTime>
#include <QtCore/qdebug.h>
#include <QtGui/qevent.h>
#include <QtGui/qwindow.h>
#include "framelesswindowsmanager.h"
#include "utilities.h"

#include <QMouseEvent>
#include <QGuiApplication>

FRAMELESSHELPER_BEGIN_NAMESPACE

FramelessHelper::FramelessHelper(QObject *parent) : QObject(parent) {
#ifdef Q_OS_LINUX
    m_bLinuxWindowClicked = false;
#endif
}

/*!
    Resize non-client area
 */
void FramelessHelper::resizeWindow(const QSize& windowSize)
{
    if (windowSize == this->windowSize())
        return;

    setWindowSize(windowSize);
}

void FramelessHelper::removeWindowFrame(QWindow *window)
{
    Q_ASSERT(window);
    if (!window) {
        return;
    }
    m_window = window;

    QRect origRect = m_window->geometry();
#ifdef Q_OS_MAC
    window->setFlags(Qt::Window);
#endif // Q_OS_MAC
#ifdef Q_OS_LINUX
    window->setFlags(window->flags() | Qt::FramelessWindowHint);
#endif

    m_window->setGeometry(origRect);
    resizeWindow(origRect.size());

    window->installEventFilter(this);
    //window->setMouseTracking(this);
    window->setProperty(Constants::kFramelessModeFlag, true);


#ifdef Q_OS_MAC
    Utilities::setMacWindowHook(m_window);
    Utilities::setMacWindowFrameless(m_window);
#endif
}

void FramelessHelper::bringBackWindowFrame(QWindow *window)
{
    Q_ASSERT(window);
    if (!window) {
        return;
    }
    window->removeEventFilter(this);
    window->setFlags(window->flags() & ~Qt::FramelessWindowHint);
    window->setProperty(Constants::kFramelessModeFlag, false);

}

bool FramelessHelper::eventFilter(QObject *object, QEvent *event)
{
    Q_ASSERT(object);
    Q_ASSERT(event);
    if (!object || !event) {
        return false;
    }

    // Only monitor window events.
    if (!object->isWindowType()) {
        return false;
    }
    const QEvent::Type type = event->type();
    const auto window = qobject_cast<QWindow *>(object);
#ifdef Q_OS_LINUX
        if(m_bLinuxWindowClicked)
        {
            m_bLinuxWindowClicked = false;
            Utilities::X11ButtonRelease(window->winId(), QPoint(0,0), QPoint(0,0));
            return false;
        }
#endif

    // We are only interested in mouse events.
    if ((type != QEvent::MouseButtonDblClick) && (type != QEvent::MouseButtonPress)
            && (type != QEvent::MouseMove)) {
        return false;
    }
    const int resizeBorderThickness = FramelessWindowsManager::getResizeBorderThickness(window);
    const int titleBarHeight = FramelessWindowsManager::getTitleBarHeight(window);
    const bool resizable = FramelessWindowsManager::getResizable(window);
    const int windowWidth = window->width();
    const auto mouseEvent = static_cast<QMouseEvent *>(event);
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    const QPoint localMousePosition = mouseEvent->position().toPoint();
#else
    const QPoint localMousePosition = mouseEvent->windowPos().toPoint();
#endif
    const Qt::Edges edges = [window, resizeBorderThickness, windowWidth, &localMousePosition, this] {
        const int windowHeight = window->height();
        if (localMousePosition.y() <= resizeBorderThickness) {
            if (localMousePosition.x() <= resizeBorderThickness) {
                return Qt::TopEdge | Qt::LeftEdge;
            }
            if (localMousePosition.x() >= (windowWidth - resizeBorderThickness)) {
                return Qt::TopEdge | Qt::RightEdge;
            }
            return Qt::Edges{Qt::TopEdge};
        }
        if (localMousePosition.y() >= (windowHeight - resizeBorderThickness)) {
            if (localMousePosition.x() <= resizeBorderThickness) {
                return Qt::BottomEdge | Qt::LeftEdge;
            }
            if (localMousePosition.x() >= (windowWidth - resizeBorderThickness)) {
                return Qt::BottomEdge | Qt::RightEdge;
            }
            return Qt::Edges{Qt::BottomEdge};
        }
        if (localMousePosition.x() <= resizeBorderThickness) {
            return Qt::Edges{Qt::LeftEdge};
        }
        if (localMousePosition.x() >= (windowWidth - resizeBorderThickness)) {
            return Qt::Edges{Qt::RightEdge};
        }
        return Qt::Edges{};
    } ();
    const bool hitTestVisible = Utilities::isHitTestVisible(window);
    bool isInTitlebarArea = false;
    if ((window->windowState() == Qt::WindowMaximized)
            || (window->windowState() == Qt::WindowFullScreen)) {
        isInTitlebarArea = (localMousePosition.y() >= 0)
                && (localMousePosition.y() <= titleBarHeight)
                && (localMousePosition.x() >= 0)
                && (localMousePosition.x() <= windowWidth)
                && !hitTestVisible;
    }
    if (window->windowState() == Qt::WindowNoState) {
        isInTitlebarArea = (localMousePosition.y() > resizeBorderThickness)
                && (localMousePosition.y() <= titleBarHeight)
                && (localMousePosition.x() > resizeBorderThickness)
                && (localMousePosition.x() < (windowWidth - resizeBorderThickness))
                && !hitTestVisible;
    }

    //qDebug() << "windows: "<< window->geometry();

    // Determine if the mouse click occurred in the title bar
    static bool titlebarClicked = false;
    if (type == QEvent::MouseButtonPress) {
        if (isInTitlebarArea)
        {
            titlebarClicked = true;
        }
        else
        {
            titlebarClicked = false;
        }
    }

    if (type == QEvent::MouseButtonDblClick) {
        if (mouseEvent->button() != Qt::MouseButton::LeftButton) {
            return false;
        }
        if (isInTitlebarArea) {
            if (window->windowState() == Qt::WindowState::WindowFullScreen) {
                return false;
            }
            if (window->windowState() == Qt::WindowState::WindowMaximized) {
                window->showNormal();
            } else {
                window->showMaximized();
            }
            window->setCursor(Qt::ArrowCursor);
        }
    } else if (type == QEvent::MouseMove) {
        // Display resize indicators
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);

        static bool cursorChanged = false;
        if ((window->windowState() == Qt::WindowState::WindowNoState) && resizable) {
            if (((edges & Qt::TopEdge) && (edges & Qt::LeftEdge))
                    || ((edges & Qt::BottomEdge) && (edges & Qt::RightEdge))) {
                window->setCursor(Qt::SizeFDiagCursor);
                cursorChanged = true;
            } else if (((edges & Qt::TopEdge) && (edges & Qt::RightEdge))
                       || ((edges & Qt::BottomEdge) && (edges & Qt::LeftEdge))) {
                window->setCursor(Qt::SizeBDiagCursor);
                cursorChanged = true;
            } else if ((edges & Qt::TopEdge) || (edges & Qt::BottomEdge)) {
                window->setCursor(Qt::SizeVerCursor);
                cursorChanged = true;
            } else if ((edges & Qt::LeftEdge) || (edges & Qt::RightEdge)) {
                window->setCursor(Qt::SizeHorCursor);
                cursorChanged = true;
            } else {
                if (cursorChanged) {
                    window->setCursor(Qt::ArrowCursor);
                    cursorChanged = false;
                }
            }
        }

        if ((mouseEvent->buttons() & Qt::LeftButton) && titlebarClicked) {
            if (edges == Qt::Edges{}) {
                if (isInTitlebarArea) {
#ifdef Q_OS_LINUX
            m_bLinuxWindowClicked = true;
#endif

                    if (!window->startSystemMove()) {
                        // ### FIXME: TO BE IMPLEMENTED!
                        qWarning() << "Current OS doesn't support QWindow::startSystemMove().";
                    }
                }
            }
        }

    } else if (type == QEvent::MouseButtonPress) {

        if (edges != Qt::Edges{}) {
            if ((window->windowState() == Qt::WindowState::WindowNoState) && !hitTestVisible && resizable) {
#ifdef Q_OS_LINUX
            m_bLinuxWindowClicked = true;
#endif
#ifndef Q_OS_MACOS
                if (!window->startSystemResize(edges)) {
                    // ### FIXME: TO BE IMPLEMENTED!
                    qWarning() << "Current OS doesn't support QWindow::startSystemResize().";
                }
#endif
            }
        }
    }
    //qDebug() << object->objectName() << " | " << event << " framelesshelper event filter";
    return QObject::eventFilter(object, event);
}

FRAMELESSHELPER_END_NAMESPACE

#endif
