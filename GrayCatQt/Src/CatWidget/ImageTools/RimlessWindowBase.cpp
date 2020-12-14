#include "RimlessWindowBase.h"
#include "ProcessObject.h"
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDebug>
#include <QTimer>

#ifdef Q_OS_LINUX
#include <X11/Xlib.h>
#include <QX11Info>
#endif



const QSize AngleRect(5, 5);
const int RectWidth = 2;


RimlessWindowBase::RimlessWindowBase(QWidget *parent)
    : QWidget(parent)
    , m_bMousePress(false)
    , m_pScreen(nullptr)
    , m_qCursorState(NONE)
{
    InitProperty();
}

RimlessWindowBase::~RimlessWindowBase()
{
   m_pScreen->deleteLater();
}

void RimlessWindowBase::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground);

    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    // 初始化 处理屏幕的对象 并初始化 可活动范围
    m_pScreen = new ProcessObject;
}

bool RimlessWindowBase::ZoomIsInArea(QRect rect, QPoint pos)
{
    if(rect.contains(pos))
    {
        return true;
    }
    return false;
}

void RimlessWindowBase::SetZoomGeometry(int x, int y, int width, int height)
{
    m_pZoom_Left_Top.setRect(x, y,
                             AngleRect.width(), AngleRect.height());
    m_pZoom_Top.setRect(x, y,
                        width, RectWidth);
    m_pZoom_Right_Top.setRect(x+width-AngleRect.width(), y,
                              AngleRect.width(), AngleRect.height());
    m_pZoom_Left.setRect(x, y,
                         RectWidth, height);
    m_pZoom_Right.setRect(x+width-RectWidth, y,
                          RectWidth, height);
    m_pZoom_Left_Bottom.setRect(x, y+height-AngleRect.height(),
                                AngleRect.width(), AngleRect.height());
    m_pZoom_Bottom.setRect(x, y+height-RectWidth,
                           width, RectWidth);
    m_pZoom_Right_Bottom.setRect(x+width-AngleRect.width(), y+height-AngleRect.height(),
                                 AngleRect.width(), AngleRect.height());
}

void RimlessWindowBase::SetProcessGeometry(int x, int y, int width, int height)
{
    m_pScreen->SetGeometry(x, y,
                           width,height);
}

#ifdef Q_OS_LINUX
void RimlessWindowBase::LinuxMoveWidget(int type, QString event)
{
    XEvent xevent;

    memset(&xevent, 0, sizeof(XEvent));
    //qDebug() << QCursor::pos();
    Display *display = QX11Info::display();
    xevent.xclient.type = type;
    //_NET_WM_ALLOWED_ACTIONS _NET_WM_MOVERESIZE
    xevent.xclient.message_type = XInternAtom(display, event.toStdString().data(), True);
    xevent.xclient.display = display;
    xevent.xclient.window = (XID)(this->winId());
    xevent.xclient.format = 32;
    xevent.xclient.data.l[0] = QCursor::pos().x();
    xevent.xclient.data.l[1] = QCursor::pos().y();
    xevent.xclient.data.l[2] = 8;
    xevent.xclient.data.l[3] = Button1;
    xevent.xclient.data.l[4] = 1;

    XUngrabPointer(display, CurrentTime);
    XSendEvent(display,
               QX11Info::appRootWindow(QX11Info::appScreen()),
               True,
               SubstructureNotifyMask | SubstructureRedirectMask,
               &xevent);
    XFlush(display);
}
#endif

void RimlessWindowBase::SetMoveRect(QRect rect)
{
    this->m_pMove_Rect = rect;
}

void RimlessWindowBase::mousePressEvent(QMouseEvent *event)
{
    m_bMousePress = true;
    if(ZoomIsInArea(m_pZoom_Left_Top, event->pos()))
    {
        // 左上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeFDiagCursor);
        m_qCursorState = TOPLEFT;
    } else if(ZoomIsInArea(m_pZoom_Right_Top, event->pos()))
    {
        // 右上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetRightBottomPos().y()));
        this->setCursor(Qt::SizeBDiagCursor);
        m_qCursorState = TOPRIGHT;
    } else if(ZoomIsInArea(m_pZoom_Left_Bottom, event->pos()))
    {
        // 左下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetRightBottomPos().x(), m_pScreen->GetLeftTopPos().y()));
        this->setCursor(Qt::SizeBDiagCursor);
        m_qCursorState = BOTTOMLEFT;
    } else if(ZoomIsInArea(m_pZoom_Right_Bottom, event->pos()))
    {
        // 右下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetLeftTopPos().y()));
        this->setCursor(Qt::SizeFDiagCursor);
        m_qCursorState = BOTTOMRIGHT;
    } else if(ZoomIsInArea(m_pZoom_Top, event->pos()))
    {
        // 上边拖拽
        m_pScreen->SetState(ProcessObject::STATE::TOP_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeVerCursor);
    } else if(ZoomIsInArea(m_pZoom_Bottom, event->pos()))
    {
        //下边拖拽
        m_pScreen->SetState(ProcessObject::STATE::BOTTOM_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        this->setCursor(Qt::SizeVerCursor);
    } else if(ZoomIsInArea(m_pZoom_Left, event->pos()))
    {
        // 左边拖拽
        m_pScreen->SetState(ProcessObject::STATE::LEFT_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeHorCursor);
    } else if(ZoomIsInArea(m_pZoom_Right, event->pos()))
    {
        // 右边拖拽
        m_pScreen->SetState(ProcessObject::STATE::RIGHT_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        this->setCursor(Qt::SizeHorCursor);
    } else if(m_pMove_Rect.contains(event->pos()))
    {
        m_pScreen->SetState(ProcessObject::STATE::MOVE);
        //this->setCursor(Qt::SizeAllCursor);
    }
    m_qMovePos = event->globalPos();
}

void RimlessWindowBase::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "event: " << event->globalPos();
    if(m_pScreen->GetState() != ProcessObject::STATE::MOVE && !m_bMousePress)
    {
        if(ZoomIsInArea(m_pZoom_Left_Top, event->pos()))
        {
            // 左上角拖拽
            this->setCursor(Qt::SizeFDiagCursor);
        } else if(ZoomIsInArea(m_pZoom_Right_Top, event->pos()))
        {
            // 右上角拖拽
            this->setCursor(Qt::SizeBDiagCursor);
        } else if(ZoomIsInArea(m_pZoom_Left_Bottom, event->pos()))
        {
            // 左下角拖拽
            this->setCursor(Qt::SizeBDiagCursor);
        } else if(ZoomIsInArea(m_pZoom_Right_Bottom, event->pos()))
        {
            // 右下角拖拽
            this->setCursor(Qt::SizeFDiagCursor);
        } else if(ZoomIsInArea(m_pZoom_Top, event->pos()))
        {
            // 上边拖拽
            this->setCursor(Qt::SizeVerCursor);
        } else if(ZoomIsInArea(m_pZoom_Bottom, event->pos()))
        {
            //下边拖拽
            this->setCursor(Qt::SizeVerCursor);
        } else if(ZoomIsInArea(m_pZoom_Left, event->pos()))
        {
            // 左边拖拽
            this->setCursor(Qt::SizeHorCursor);
        } else if(ZoomIsInArea(m_pZoom_Right, event->pos()))
        {
            // 右边拖拽
            this->setCursor(Qt::SizeHorCursor);
        } else if(m_pScreen->GetState() == ProcessObject::STATE::SELECT) {
            this->setCursor(Qt::ArrowCursor);
        }
    }


    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        m_pLast_Rect = QRect(m_pScreen->x(), m_pScreen->y(), m_pScreen->width(), m_pScreen->height());
        QPoint pos(event->globalX() - m_qMovePos.x(), event->globalY() - m_qMovePos.y());
        m_pScreen->Move(pos, true);
#ifdef Q_OS_LINUX
        LinuxMoveWidget(ClientMessage);
#endif
    } else if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        QRect temp;
        temp.setTopLeft(m_pScreen->GetLeftTopPos());
        temp.setBottomRight(m_pScreen->GetRightBottomPos());
        QPoint endpot;
        switch (m_qCursorState) {
            case TOPLEFT: {
                if(event->globalX() < temp.bottomRight().x() - this->minimumSize().width())
                {
                    endpot.setX(event->globalX());
                } else {
                    endpot.setX(temp.x());
                }
                if(event->globalY() < temp.bottomRight().y() - this->minimumSize().height())
                {
                    endpot.setY(event->globalY());
                } else {
                    endpot.setY(temp.y());
                }
                break;
            }
            case TOPRIGHT: {
                if(event->globalX() > temp.bottomLeft().x() + this->minimumSize().width())
                {
                    endpot.setX(event->globalX());
                } else {
                    endpot.setX(temp.topRight().x());
                }
                if(event->globalY() < temp.bottomLeft().y() - this->minimumSize().height())
                {
                    endpot.setY(event->globalY());
                } else {
                    endpot.setY(temp.topRight().y());
                }
                break;
            }
            case BOTTOMLEFT: {
                if(event->globalX() < temp.topRight().x() - this->minimumSize().width())
                {
                    endpot.setX(event->globalX());
                } else {
                    endpot.setX(temp.bottomLeft().x());
                }
                if(event->globalY() > temp.topRight().y() + this->minimumSize().height())
                {
                    endpot.setY(event->globalY());
                } else {
                    endpot.setY(temp.bottomLeft().y());
                }
                break;
            }
            case BOTTOMRIGHT: {
                if(event->globalX() > temp.topLeft().x() + this->minimumSize().width())
                {
                    endpot.setX(event->globalX());
                } else {
                    endpot.setX(temp.bottomRight().x());
                }
                if(event->globalY() > temp.topLeft().y() + this->minimumSize().height())
                {
                    endpot.setY(event->globalY());
                } else {
                    endpot.setY(temp.bottomRight().y());
                }
                break;
            }
            default:{
                break;
            }
        }
        m_pScreen->SetEnd(endpot);
        m_pLast_Rect = QRect(m_pScreen->x(), m_pScreen->y(), m_pScreen->width(), m_pScreen->height());

    } else if(m_pScreen->GetState() == ProcessObject::STATE::TOP_ZOOM) {
        if(event->globalY() < this->y() + this->height() - this->minimumSize().height())
        {
            m_pScreen->SetEnd(QPoint(m_pScreen->GetLeftTopPos().x(), event->globalY()));
            m_pLast_Rect = QRect(m_pScreen->x(), m_pScreen->y(), m_pScreen->width(), m_pScreen->height());
        }
    } else if(m_pScreen->GetState() == ProcessObject::STATE::BOTTOM_ZOOM) {
        if(event->globalY() > this->y() + this->minimumSize().height())
        {
            m_pScreen->SetEnd(QPoint(m_pScreen->GetRightBottomPos().x(), event->globalY()));
            m_pLast_Rect = QRect(m_pScreen->x(), m_pScreen->y(), m_pScreen->width(), m_pScreen->height());
        }
    } else if(m_pScreen->GetState() == ProcessObject::STATE::LEFT_ZOOM) {
        if(event->globalX() < this->x() + this->width() - this->minimumSize().width())
        {
            m_pScreen->SetEnd(QPoint(event->globalX(), m_pScreen->GetLeftTopPos().y()));
            m_pLast_Rect = QRect(m_pScreen->x(), m_pScreen->y(), m_pScreen->width(), m_pScreen->height());
        }
    } else if(m_pScreen->GetState() == ProcessObject::STATE::RIGHT_ZOOM) {
        if(event->globalX() > this->x() + this->minimumSize().width())
        {
            m_pScreen->SetEnd(QPoint(event->globalX(), m_pScreen->GetRightBottomPos().y()));
            m_pLast_Rect = QRect(m_pScreen->x(), m_pScreen->y(), m_pScreen->width(), m_pScreen->height());
        }
    }
    m_qMovePos = event->globalPos();
    if(m_pScreen->GetState() != ProcessObject::STATE::SELECT)
    {
#ifdef Q_OS_LINUX
        if(m_pScreen->GetState() != ProcessObject::STATE::MOVE)
        {
            this->setGeometry(m_pScreen->x(), m_pScreen->y(),
                              m_pScreen->width(), m_pScreen->height());
            this->move(m_pScreen->x(), m_pScreen->y());
        }

        if(m_pLast_Rect == this->geometry() &&
                m_pScreen->GetState() == ProcessObject::STATE::MOVE)
        {
            QApplication::mouseButtons().setFlag(Qt::NoButton, true);
            LinuxMoveWidget(ButtonRelease, "_NET_WM_ALLOWED_ACTIONS");
            m_bMousePress = false;
            m_pScreen->SetState(ProcessObject::STATE::SELECT);
            this->setCursor(Qt::ArrowCursor);
            //m_pScreen->SetGeometry(this->x(), this->y(), this->width(), this->height());
        }
#else
        this->setGeometry(m_pScreen->x(), m_pScreen->y(),
                          m_pScreen->width(), m_pScreen->height());
        this->move(m_pScreen->x(), m_pScreen->y());
#endif
    }
    emit mouseMoveed(event->pos());
}

void RimlessWindowBase::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_bMousePress = false;
    m_pScreen->SetState(ProcessObject::STATE::SELECT);
    this->setCursor(Qt::ArrowCursor);
}

void RimlessWindowBase::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    // QT5.6 获取主屏幕大小 - 全屏大小
    QScreen *screen = QApplication::primaryScreen();
    m_pScreen->SetMaxParentSize(screen->size());
    m_pScreen->SetMinSize(QSize(400, 400));
    m_pScreen->SetMaxWidth(screen->size().width());
    m_pScreen->SetMaxHeight(screen->size().height());
    m_pScreen->SetMinWidth(400);
    m_pScreen->SetMinHeight(400);

    SetZoomGeometry(0, 0, this->width(), this->height());
}

void RimlessWindowBase::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    SetZoomGeometry(0, 0, this->width(), this->height());
}

void RimlessWindowBase::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)
    //qDebug() << "QApp: " << QApplication::mouseButtons();
    if(m_pScreen->GetState() == ProcessObject::STATE::SELECT)
    {
        m_pScreen->SetGeometry(this->x(), this->y(),
                               this->width(),
                               this->height());
        SetZoomGeometry(0, 0, this->width(), this->height());
    } /*else {
        qDebug() << "m_pScreen->GetState(): No Select";
        m_pScreen->SetGeometry(this->x(), this->y(),
                               this->width(),
                               this->height());
    }*/
    emit moveEvented();
}

void RimlessWindowBase::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

}

void RimlessWindowBase::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(!m_bMousePress)
    {
        m_qCursorState = NONE;
        this->setCursor(Qt::ArrowCursor);
    }
}
