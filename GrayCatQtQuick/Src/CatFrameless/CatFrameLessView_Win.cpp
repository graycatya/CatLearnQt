#include "CatFrameLessView.h"

#include <QGuiApplication>

#include <QQuickItem>
#include <QScreen>
#include <QWindow>
#include <QTimer>



#include <WinUser.h> // Windows UI 相关的大部分 API 都是在 winuser.h 中定义的
#include <dwmapi.h> //dwmapi获得Areo效果
#include <objidl.h> // Fixes error C2504: 'IUnknown' : base class undefined
#include <windows.h>
#include <windowsx.h>
#include <atltypes.h>

static bool Titlecontains = false;


#pragma comment(lib, "Dwmapi.lib")  // Adds missing library, fixes error LNK2019: unresolved
#pragma comment(lib, "User32.lib")

// we cannot just use WS_POPUP style
// WS_THICKFRAME: without this the window cannot be resized and so aero snap, de-maximizing and minimizing won't work
// WS_SYSMENU: enables the context menu with the move, close, maximize, minize... commands (shift + right-click on the task bar item)
// WS_CAPTION: enables aero minimize animation/transition
// WS_MAXIMIZEBOX, WS_MINIMIZEBOX: enable minimize/maximize

enum class Style : DWORD {
    windowed = WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
    aero_borderless = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
    basic_borderless = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX
};

/*
 * 检测系统是否开启Aero Glass。
 * 使用 函数 DwmIsCompositionEnabled 检测系统当前是否开启了Aero Glass特效。
 * 它接受一个BOOL参数，并将当前状态存储到其中。
*/
static bool isCompositionEnabled()
{
    BOOL composition_enabled = FALSE;
    bool success = ::DwmIsCompositionEnabled(&composition_enabled) == S_OK;
    return composition_enabled && success;
}

static Style selectBorderLessStyle()
{
    return isCompositionEnabled() ? Style::aero_borderless : Style::basic_borderless;
}

static void setShadow(HWND handle, bool enabled)
{
    if(isCompositionEnabled())
    {
        static const MARGINS shadow_state[2] { {0,0,0,0}, {1,1,1,1} };
        // 半透明窗体设置
        ::DwmExtendFrameIntoClientArea(handle, &shadow_state[enabled]);
        //SetWindowPos(handle, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    }
}

static long hitTest(RECT winrect, long x, long y, int borderWidth)
{
    // 鼠标区域位于窗体边框，进行缩放
    if ((x >= winrect.left) && (x < winrect.left + borderWidth) && (y >= winrect.top) && (y < winrect.top + borderWidth)) {
        return HTTOPLEFT;
    } else if (x < winrect.right && x >= winrect.right - borderWidth && y >= winrect.top && y < winrect.top + borderWidth) {
        return HTTOPRIGHT;
    } else if (x >= winrect.left && x < winrect.left + borderWidth && y < winrect.bottom && y >= winrect.bottom - borderWidth) {
        return HTBOTTOMLEFT;
    } else if (x < winrect.right && x >= winrect.right - borderWidth && y < winrect.bottom && y >= winrect.bottom - borderWidth) {
        return HTBOTTOMRIGHT;
    } else if (x >= winrect.left && x < winrect.left + borderWidth) {
        return HTLEFT;
    } else if (x < winrect.right && x >= winrect.right - borderWidth) {
        return HTRIGHT;
    } else if (y >= winrect.top && y < winrect.top + borderWidth) {
        return HTTOP;
    } else if (y < winrect.bottom && y >= winrect.bottom - borderWidth) {
        return HTBOTTOM;
    } else {
        return 0;
    }
}

static bool isMaxWin(QWindow *win)
{
    return win->windowState() == Qt::WindowMaximized;
}

static bool isFullWin(QQuickView *win)
{
    return win->windowState() == Qt::WindowFullScreen;
}

static QTimer *m_pTimer = nullptr;

class CatFrameLessViewPrivate
{
public:
    bool m_isMax;
    QQuickItem *m_titleItem = nullptr;
    bool borderless = true; // is the window currently borderless
    bool borderless_resize = true; // should the window allow resizing by dragging the borders while borderless
    bool borderless_drag = true; // should the window allow moving my dragging the client area
    bool borderless_shadow = true; // should the window display a native aero shadow while borderless

    void setBorderLess(HWND handle, bool enabled)
    {
        auto newStyle = enabled ? selectBorderLessStyle() : Style::windowed;
        //GetWindowLongPtr函数是在指定的窗口中获取信息
        auto oldStyle = static_cast<Style>(::GetWindowLongPtrW(handle, GWL_STYLE));
        if (oldStyle != newStyle) {
            borderless = enabled;
            //该函数改变指定窗口的属性。函数也将指定的一个值设置在窗口的额外存储空间的指定偏移位置。
            ::SetWindowLongPtrW(handle, GWL_STYLE, static_cast<LONG>(newStyle));

            // when switching between borderless and windowed, restore appropriate shadow state
            setShadow(handle, borderless_shadow && (newStyle != Style::windowed));

            // redraw frame
            ::SetWindowPos(handle, nullptr, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
            ::ShowWindow(handle, SW_SHOW);
        }
    }

    void setBorderLessShadow(HWND handle, bool enabled)
    {
        if (borderless) {
            borderless_shadow = enabled;
            setShadow(handle, enabled);
        }
    }

};

CatFrameLessView::CatFrameLessView(QWindow *parent)
    : QQuickView(parent)
    , m_pCatFrameLessViewPrivate(new CatFrameLessViewPrivate)
{

    setFlags(Qt::CustomizeWindowHint | Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    //setFrameStyle(QFrame::NoFrame);
    setResizeMode(SizeRootObjectToView);
    setColor(QColor(1, 0, 0, 0));
    m_bWork = true;
    m_pTimer = new QTimer;

    m_pCatFrameLessViewPrivate->setBorderLess((HWND)(winId()),
                                              m_pCatFrameLessViewPrivate->borderless);
    m_pCatFrameLessViewPrivate->setBorderLessShadow((HWND)(winId()), m_pCatFrameLessViewPrivate->borderless_shadow);

    setIsMax(isMaxWin(this));
    connect(this, &QWindow::windowStateChanged, this, [&](Qt::WindowState state) { setIsMax(state == Qt::WindowMaximized); });


    connect(m_pTimer, &QTimer::timeout, this, [=](){
        QCoreApplication::processEvents();
    });

    m_pTimer->start(10);
}

CatFrameLessView::~CatFrameLessView()
{
    if(m_pTimer->isActive())
    {
        m_pTimer->stop();
    }
    delete m_pTimer;
    delete m_pCatFrameLessViewPrivate;
}

bool CatFrameLessView::isMax() const
{
    return m_pCatFrameLessViewPrivate->m_isMax;
}

void CatFrameLessView::setWork(bool work)
{
    m_bWork = work;
}

QQuickItem *CatFrameLessView::titleItem() const
{
    return m_pCatFrameLessViewPrivate->m_titleItem;
}

void CatFrameLessView::setTitleItem(QQuickItem *item)
{
    m_pCatFrameLessViewPrivate->m_titleItem = item;
}

QRect CatFrameLessView::calcCenterGeo(const QRect &screenGeo, const QSize &normalSize)
{
    int w = normalSize.width();
    int h = normalSize.height();
    int x = screenGeo.x() + (screenGeo.width() - w) / 2;
    int y = screenGeo.y() + (screenGeo.height() - h) / 2;
    if (screenGeo.width() < w) {
        x = screenGeo.x();
        w = screenGeo.width();
    }
    if (screenGeo.height() < h) {
        y = screenGeo.y();
        h = screenGeo.height();
    }

    return { x, y, w, h };
}

void CatFrameLessView::moveToScreenCenter()
{
    auto geo = calcCenterGeo(screen()->availableGeometry(), size());
    if(minimumWidth() > geo.width() || minimumHeight() > geo.height())
    {
        setMinimumSize(geo.size());
    }
    setGeometry(geo);
    update();
}

void CatFrameLessView::setIsMax(bool isMax)
{
    if(m_pCatFrameLessViewPrivate->m_isMax == isMax)
    {
        return;
    }
    m_pCatFrameLessViewPrivate->m_isMax = isMax;

    emit isMaxChanged(m_pCatFrameLessViewPrivate->m_isMax);
}


void CatFrameLessView::moveUpdateSize()
{
    emit moveWindow();
    static int width = this->width();
    static int height = this->height();
    static int cursorwidth = QCursor::pos().x() - geometry().x();
    static int cursorheight = QCursor::pos().y() - geometry().y();
    //static QPoint lastPoint = QCursor::pos();
    //QPoint offetPoint = QCursor::pos() - lastPoint;
    //lastPoint = QCursor::pos();
    if(Titlecontains && width != this->width() && height != this->height())
    {
        if(!isMax())
        {
            if(!isMax())
            {
                this->setGeometry(QCursor::pos().x() - cursorwidth,
                                  QCursor::pos().y() - cursorheight,
                                  width, height);
            }
        }
        //this->setWidth(width);
        //this->setHeight(height);
    } else {
        if(!isMax())
        {
            if(!isMax())
            {
                cursorwidth = QCursor::pos().x() - geometry().x();
                cursorheight = QCursor::pos().y() - geometry().y();
                width = this->width();
                height = this->height();
            }
        }
    }

    //qDebug() << QCursor::pos();
}


#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool CatFrameLessView::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool CatFrameLessView::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
{

    const long border_width = 4;
    if(!m_bWork) {
        return false;
    }
    if (!result) {
        //防御式编程
        //一般不会发生这种情况，win7一些极端情况，会传空指针进来。解决方案是升级驱动、切换到basic主题。
        return false;
    }

#if (QT_VERSION == QT_VERSION_CHECK(5, 11, 1))
    // Work-around a bug caused by typo which only exists in Qt 5.11.1
    const auto msg = *reinterpret_cast<MSG **>(message);
#else
    const auto msg = static_cast<LPMSG>(message);
#endif

    if (!msg || !msg->hwnd) {
        return false;
    }

    switch (msg->message) {
    case WM_NCCALCSIZE: {
        const auto mode = static_cast<BOOL>(msg->wParam);
        const auto clientRect = mode ? &(reinterpret_cast<LPNCCALCSIZE_PARAMS>(msg->lParam)->rgrc[0]) : reinterpret_cast<LPRECT>(msg->lParam);
        if (mode == TRUE && m_pCatFrameLessViewPrivate->borderless) {
            *result = WVR_REDRAW;
            //规避 拖动border进行resize时界面闪烁

            if (!isMaxWin(this) && !isFullWin(this)) {
                if (clientRect->top != 0) {
                    clientRect->top -= 0.1;
                }
            } else {
                if (clientRect->top != 0) {
                    clientRect->top += 0.1;
                }
            }
            return true;
        }
        break;
    }
    case WM_NCACTIVATE: {
        if (!isCompositionEnabled()) {
            // Prevents window frame reappearing on window activation
            // in "basic" theme, where no aero shadow is present.
            *result = 1;

            return true;
        }
        break;
    }
    case WM_NCHITTEST: {
        if (m_pCatFrameLessViewPrivate->borderless) {
            //moveUpdateSize();
            RECT winrect;
            GetWindowRect(HWND(winId()), &winrect);

            long x = GET_X_LPARAM(msg->lParam);
            long y = GET_Y_LPARAM(msg->lParam);
            //qDebug() << "x , y : " + QString::number(x) + " " + QString::number(y);

            *result = 0;
            if (!isMaxWin(this) && !isFullWin(this)) { //非最大化、非全屏时，进行命中测试，处理边框拖拽
                Titlecontains = false;
                *result = hitTest(winrect, x, y, border_width);
                if (0 != *result) {
                    return true;
                }
            }

            if (m_pCatFrameLessViewPrivate->m_titleItem) {
                auto titlePos = m_pCatFrameLessViewPrivate->m_titleItem->mapToGlobal(m_pCatFrameLessViewPrivate->m_titleItem->position());
                titlePos = mapFromGlobal(titlePos.toPoint());
                auto titleRect = QRect(titlePos.x(), titlePos.y(),
                                       m_pCatFrameLessViewPrivate->m_titleItem->width(),
                                       m_pCatFrameLessViewPrivate->m_titleItem->height());
                double dpr = qApp->devicePixelRatio();
                QPoint pos = mapFromGlobal(QPoint(x / dpr, y / dpr));
                if (titleRect.contains(pos)) {
                    *result = HTCAPTION;
                    moveUpdateSize();
                    Titlecontains = true;
                    return true;
                } else {
                    Titlecontains = false;
                }
            }

            return false;
        }
        break;
    } // end case WM_NCHITTEST
    case WM_MOVE:
    {
        moveUpdateSize();
        break;
    }
    }

    return QQuickView::nativeEvent(eventType, message, result);
}

void CatFrameLessView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    emit updateSize();

    QQuickView::resizeEvent(event);
}

void CatFrameLessView::setTitlecontains(bool contain)
{
    Titlecontains = contain;
}
