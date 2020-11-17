#include "RimlessWindowBase.h"
#include "ProcessObject.h"
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QScreen>
#include <CatLog>
#include <QMouseEvent>

const QSize AngleRect(5, 5);
const int RectWidth = 2;


RimlessWindowBase::RimlessWindowBase(QWidget *parent)
    : QWidget(parent)
    , m_pScreen(nullptr)
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

    // 初始化 处理屏幕的对象 并初始化 可活动范围
    m_pScreen = new ProcessObject;

}

bool RimlessWindowBase::ZoomIsInArea(QRect rect, QPoint pos)
{
    if(pos.x() > rect.x()
            && pos.x() < rect.x() + rect.width()
            && pos.y() > rect.y()
            && pos.y() < rect.y() + rect.height())
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
    m_pZoom_Right.setRect(x+width-AngleRect.width(), y,
                          RectWidth, height);
    m_pZoom_Left_Bottom.setRect(x, y+height-AngleRect.height(),
                                AngleRect.width(), AngleRect.height());
    m_pZoom_Bottom.setRect(x, y+height-RectWidth,
                           width, RectWidth);
    m_pZoom_Right_Bottom.setRect(x+width-AngleRect.width(), y+height-AngleRect.height(),
                                 AngleRect.width(), AngleRect.height());
}

void RimlessWindowBase::mousePressEvent(QMouseEvent *event)
{
    if(ZoomIsInArea(m_pZoom_Left_Top, event->pos()))
    {
        // 左上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeFDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Right_Top, event->pos()))
    {
        // 右上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetRightBottomPos().y()));
        this->setCursor(Qt::SizeBDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Left_Bottom, event->pos()))
    {
        // 左下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetRightBottomPos().x(), m_pScreen->GetLeftTopPos().y()));
        this->setCursor(Qt::SizeBDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Right_Bottom, event->pos()))
    {
        // 右下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetLeftTopPos().y()));
        this->setCursor(Qt::SizeFDiagCursor);
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
    } else if(event->button() == Qt::LeftButton)
    {
        m_qMovePos = event->pos();
        if(m_pScreen->GetStart() == QPoint(-1, -1))
        {
            m_pScreen->SetState(ProcessObject::STATE::ZOOM);
            m_pScreen->SetStart(m_qMovePos);

        } else if(m_pScreen->IsInArea(event->pos()))
        {
            m_pScreen->SetState(ProcessObject::STATE::MOVE);
            this->setCursor(Qt::SizeAllCursor);
        }
    }
}

void RimlessWindowBase::mouseMoveEvent(QMouseEvent *event)
{

}

void RimlessWindowBase::mouseReleaseEvent(QMouseEvent *event)
{

}

void RimlessWindowBase::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    // QT5.6 获取主屏幕大小 - 全屏大小
    QScreen *screen = QApplication::primaryScreen();
    m_pScreen->SetMaxParentSize(screen->size());
    m_pScreen->SetMaxWidth(screen->size().width());
    m_pScreen->SetMaxHeight(screen->size().height());
    m_pScreen->SetMinWidth(400);
    m_pScreen->SetMinHeight(400);


    QString log = "RimlessWindowBase showEvent size: "
            + QString::number(screen->size().width())
            + " : "
            + QString::number(screen->size().height());
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
    QString log1 = "RimlessWindowBase showEvent this size: "
            + QString::number(this->width())
            + " : "
            + QString::number(this->height())
            + " x: "
            + QString::number(this->x())
            + " y: "
            + QString::number(this->y());
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log1.toStdString()));
    SetZoomGeometry(this->x(), this->y(), this->width(), this->height());
}

void RimlessWindowBase::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    SetZoomGeometry(this->x(), this->y(), this->width(), this->height());
}

void RimlessWindowBase::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)
    SetZoomGeometry(this->x(), this->y(), this->width(), this->height());
}
