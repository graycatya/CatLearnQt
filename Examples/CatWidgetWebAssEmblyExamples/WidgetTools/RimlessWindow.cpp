#include "RimlessWindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

#include "CatWidget/ImageTools/ProcessObject.h"

RimlessWindow::RimlessWindow(QWidget *parent)
    : ImageToolBase(parent)
    , m_pMousePress(false)
{
    InitUi();

    InitProperty();
}

RimlessWindow::~RimlessWindow()
{

}

void RimlessWindow::InitUi()
{
    m_pZoom_Left_Top = new QWidget(this);
    m_pZoom_Left_Top->setObjectName("Zoom");
    m_pZoom_Top = new QWidget(this);
    m_pZoom_Top->setObjectName("Zoom");
    m_pZoom_Right_Top = new QWidget(this);
    m_pZoom_Right_Top->setObjectName("Zoom");
    m_pZoom_Left = new QWidget(this);
    m_pZoom_Left->setObjectName("Zoom");
    m_pZoom_Right = new QWidget(this);
    m_pZoom_Right->setObjectName("Zoom");
    m_pZoom_Left_Bottom = new QWidget(this);
    m_pZoom_Left_Bottom->setObjectName("Zoom");
    m_pZoom_Right_Bottom = new QWidget(this);
    m_pZoom_Right_Bottom->setObjectName("Zoom");
    m_pZoom_Bottom = new QWidget(this);
    m_pZoom_Bottom->setObjectName("Zoom");
}

void RimlessWindow::InitProperty()
{
    setMouseTracking(true);
    m_pZoom_Top->installEventFilter(this);
    m_pZoom_Top->setMouseTracking(true);
    m_pZoom_Left->installEventFilter(this);
    m_pZoom_Left->setMouseTracking(true);
    m_pZoom_Right->installEventFilter(this);
    m_pZoom_Right->setMouseTracking(true);
    m_pZoom_Bottom->installEventFilter(this);
    m_pZoom_Bottom->setMouseTracking(true);
    m_pZoom_Left_Top->installEventFilter(this);
    m_pZoom_Left_Top->setMouseTracking(true);
    m_pZoom_Right_Top->installEventFilter(this);
    m_pZoom_Right_Top->setMouseTracking(true);
    m_pZoom_Left_Bottom->installEventFilter(this);
    m_pZoom_Left_Bottom->setMouseTracking(true);
    m_pZoom_Right_Bottom->installEventFilter(this);
    m_pZoom_Right_Bottom->setMouseTracking(true);

    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    // 初始化 处理屏幕的对象 并初始化 可活动范围
    m_pScreen = new ProcessObject;
    /*m_pScreen->SetMaxParentSize(QApplication::desktop()->size());
    m_pScreen->SetMaxWidth(QApplication::desktop()->size().width());
    m_pScreen->SetMaxHeight(QApplication::desktop()->size().height());
    m_pScreen->SetMinWidth(0);
    m_pScreen->SetMinHeight(0);*/
}

void RimlessWindow::SetZoomVisible(bool visible)
{
    m_pZoom_Top->setVisible(visible);
    m_pZoom_Bottom->setVisible(visible);
    m_pZoom_Left->setVisible(visible);
    m_pZoom_Right->setVisible(visible);
    m_pZoom_Left_Top->setVisible(visible);
    m_pZoom_Right_Top->setVisible(visible);
    m_pZoom_Left_Bottom->setVisible(visible);
    m_pZoom_Right_Bottom->setVisible(visible);
}

void RimlessWindow::SetZoomGeometry(int x, int y, int width, int height)
{
    m_pZoom_Left_Top->move(x - (m_pZoom_Left_Top->width() - 1)/2,
                           y - (m_pZoom_Left_Top->height() - 1)/2);

    m_pZoom_Top->move(x + width/2 - (m_pZoom_Top->width() - 1)/2,
                      y - (m_pZoom_Top->height() - 1)/2);

    m_pZoom_Right_Top->move(x + width - (m_pZoom_Right_Top->width() - 1)/2,
                            y - (m_pZoom_Right_Top->height() - 1)/2);

    m_pZoom_Left->move(x - (m_pZoom_Left->width() - 1)/2,
                       y + (height/2) - (m_pZoom_Left->height() - 1)/2);

    m_pZoom_Right->move(x + width - (m_pZoom_Right->width() - 1)/2,
                        y + (height/2) - (m_pZoom_Right->height() - 1)/2);

    m_pZoom_Left_Bottom->move(x - (m_pZoom_Left_Bottom->width() - 1)/2,
                              y + height - (m_pZoom_Left_Bottom->height() - 1)/2);

    m_pZoom_Bottom->move(x + width/2 - (m_pZoom_Bottom->width() - 1)/2,
                         y + height - (m_pZoom_Bottom->height() - 1)/2);

    m_pZoom_Right_Bottom->move(x + width - (m_pZoom_Right_Bottom->width() - 1)/2,
                               y + height - (m_pZoom_Right_Bottom->height() - 1)/2);
}

bool RimlessWindow::ZoomIsInArea(QWidget *Zoom, QPoint pos)
{
    if(pos.x() > Zoom->x()
            && pos.x() < Zoom->x() + Zoom->width()
            && pos.y() > Zoom->y()
            && pos.y() < Zoom->y() + Zoom->height())
    {
        return true;
    }
    return false;
}

void RimlessWindow::mousePressEvent(QMouseEvent * event)
{
    m_pMousePress = true;
    //qDebug() << "press: " << event->pos();
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
    } else if(event->button() == Qt::RightButton)
    {
        if(m_pScreen->GetStart() == QPoint(-1, -1))
        {
            this->close();
            emit clicked(STATE::CLOSE);
        } else {
            m_pScreen->SetStart(QPoint(-1, -1));
            m_pScreen->SetGeometry(-1, -1, 0, 0);
            SetZoomVisible(false);
            update();
        }
    }
}

void RimlessWindow::mouseMoveEvent(QMouseEvent * event)
{
    if(m_pScreen->GetState() != ProcessObject::STATE::MOVE)
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
        } else if(!m_pMousePress) {
            this->setCursor(Qt::ArrowCursor);
        }
    }

    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        m_pScreen->Move(pos);

    } else if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        m_pScreen->SetEnd(event->pos());
    } else if(m_pScreen->GetState() == ProcessObject::STATE::TOP_ZOOM) {
        m_pScreen->SetEnd(QPoint(m_pScreen->GetLeftTopPos().x(), event->y()));
    } else if(m_pScreen->GetState() == ProcessObject::STATE::BOTTOM_ZOOM) {
        m_pScreen->SetEnd(QPoint(m_pScreen->GetRightBottomPos().x(), event->y()));
    } else if(m_pScreen->GetState() == ProcessObject::STATE::LEFT_ZOOM) {
        m_pScreen->SetEnd(QPoint(event->x(), m_pScreen->GetLeftTopPos().y()));
    } else if(m_pScreen->GetState() == ProcessObject::STATE::RIGHT_ZOOM) {
        m_pScreen->SetEnd(QPoint(event->x(), m_pScreen->GetRightBottomPos().y()));
    } /*else {
        //this->setCursor(Qt::ArrowCursor);
    }*/
    m_qMovePos = event->pos();

    update();
}

void RimlessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_pMousePress = false;
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
    } /*if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::TOP_ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::BOTTOM_ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::RIGHT_ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::LEFT_ZOOM)
    {
        m_pButtonTool->setVisible(true);
    }*/
    m_pScreen->SetState(ProcessObject::STATE::SELECT);
    this->setCursor(Qt::ArrowCursor);
}

void RimlessWindow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    int x = m_pScreen->x();
    int y = m_pScreen->y();
    int w = m_pScreen->width();
    int h = m_pScreen->height();
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(1);
    painter.setPen(pen);
    if(w > 0 && h > 0)
    {
        painter.drawRect(x, y, w, h);
        SetZoomGeometry(x, y, w, h);
        SetZoomVisible(true);
    }
}

void RimlessWindow::showEvent(QShowEvent *)
{
    m_pScreen->SetMaxParentSize(this->size());
    m_pScreen->SetMaxWidth(this->width());
    m_pScreen->SetMaxHeight(this->height());
    m_pScreen->SetMinWidth(0);
    m_pScreen->SetMinHeight(0);
    SetZoomVisible(false);
    int x = (this->width() - 200) / 2;
    int y = (this->height() - 200) / 2;
    m_pScreen->SetStart(QPoint(x, y));
    m_pScreen->SetEnd(QPoint(x + 200, y + 200));
    update();
}

void RimlessWindow::resizeEvent(QResizeEvent *)
{
    m_pScreen->SetMaxParentSize(this->size());
    m_pScreen->SetMaxWidth(this->width());
    m_pScreen->SetMaxHeight(this->height());
    m_pScreen->SetMinWidth(0);
    m_pScreen->SetMinHeight(0);
    SetZoomVisible(false);
    int x = (this->width() - 200) / 2;
    int y = (this->height() - 200) / 2;
    m_pScreen->SetStart(QPoint(x, y));
    m_pScreen->SetEnd(QPoint(x + 200, y + 200));
    update();
}

bool RimlessWindow::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}
