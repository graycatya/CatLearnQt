#include "CatGifTool.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QEvent>

#include <QDebug>
#include <QIcon>

#include "ProcessObject.h"
#include "GifButtonWidget.h"

CatGifTool::CatGifTool(QWidget *parent)
    : ImageToolBase(parent),
      m_bMove(true),
      m_bStart(false),
      m_bShow(true),
      m_bEnter(true),
      m_bResize(true)
{
    InitUi();

    InitProperty();

    setWindowIcon(QIcon(":/ImageTools/image/gif.png"));
}

CatGifTool::~CatGifTool()
{

}

void CatGifTool::SetGeometry(int x, int y, int width, int height)
{
    m_pScreen->SetStart(QPoint(x, y));
    m_pScreen->SetGeometry(x, y, width, height);
    update();
}

void CatGifTool::SetMoveState(QString state)
{
    m_pMoveWidget->setProperty("State", state);
    m_pMoveWidget->setStyle(QApplication::style());
}

void CatGifTool::InitUi()
{
    m_pMoveWidget = new QWidget(this);
    m_pMoveWidget->setObjectName("MoveWidget");
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
    m_pGifButtonWidget = new GifButtonWidget(this);
}

void CatGifTool::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    //setMouseTracking(true);

    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    //获取程序当前运行目录
    //QString path = QCoreApplication::applicationDirPath();


    //m_pGifButtonWidget->showFullScreen();
    m_pGifButtonWidget->show();

    QFile resourceqss(":/ImageTools/qss/CatGifTool.css");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    // 初始化 处理屏幕的对象 并初始化 可活动范围
    m_pScreen = new ProcessObject;
    m_pScreen->SetMaxParentSize(QApplication::desktop()->size());
    m_pScreen->SetMaxWidth(QApplication::desktop()->size().width());
    m_pScreen->SetMaxHeight(QApplication::desktop()->size().height());
    m_pScreen->SetMinWidth(0);
    m_pScreen->SetMinHeight(0);

    m_pGifButtonWidget->move(QApplication::desktop()->size().width() - m_pGifButtonWidget->width() - 20,
                             QApplication::desktop()->size().height() - m_pGifButtonWidget->height() - 50);

    this->setGeometry(0,0,
                      QApplication::desktop()->size().width(),
                      QApplication::desktop()->size().height());

    connect(this, &CatGifTool::gifgeometry, m_pGifButtonWidget, &GifButtonWidget::On_Gifgeometry);
    connect(m_pGifButtonWidget, &GifButtonWidget::gifmoveed, this, &CatGifTool::On_Move);
    connect(m_pGifButtonWidget, &GifButtonWidget::gifshowed, this, &CatGifTool::On_Show);
    connect(m_pGifButtonWidget, &GifButtonWidget::gifstarted, this, &CatGifTool::On_Start);
    connect(m_pGifButtonWidget, &GifButtonWidget::closeed, this, [=](){
        QApplication::exit(0);
    });

    int w = QApplication::desktop()->size().width() * 0.5;
    int h = QApplication::desktop()->size().height() * 0.5;
    int x = (QApplication::desktop()->size().width() - w)/2;
    int y = (QApplication::desktop()->size().height() - h)/2;
    m_pGifButtonWidget->SetGifSelect(true);
    SetGeometry(x, y, w, h);

    connect(m_pGifButtonWidget, &GifButtonWidget::gifgeometryed, this,
        [=](int x, int y, int w, int h){
        SetGeometry(x, y, w, h);
    });
    //m_pGifButtonWidget->SetGifSelect(false);

    m_bMove = true;
    On_Move(m_bMove);

}

void CatGifTool::SetZoomVisible(bool visible)
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

void CatGifTool::SetMoveWidgetVisible(bool visible)
{
    m_pMoveWidget->setVisible(visible);
}

void CatGifTool::SetZoomGeometry(int x, int y, int width, int height)
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

bool CatGifTool::ZoomIsInArea(QWidget *Zoom, QPoint pos)
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

void CatGifTool::mousePressEvent(QMouseEvent *event)
{
    QRect GifButtonR = QRect(m_pGifButtonWidget->x(),
                             m_pGifButtonWidget->y(),
                             m_pGifButtonWidget->width(),
                             m_pGifButtonWidget->height());
    if(GifButtonR.contains(event->pos()))
    {
        m_pGifButtonWidget->SetGifSelect(false);
        return;
    }
    if(ZoomIsInArea(m_pZoom_Left_Top, event->pos()) && m_bStart == false)
    {
        // 左上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeFDiagCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Right_Top, event->pos()) && m_bStart == false)
    {
        // 右上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetRightBottomPos().y()));
        this->setCursor(Qt::SizeBDiagCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Left_Bottom, event->pos()) && m_bStart == false)
    {
        // 左下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetRightBottomPos().x(), m_pScreen->GetLeftTopPos().y()));
        this->setCursor(Qt::SizeBDiagCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Right_Bottom, event->pos()) && m_bStart == false)
    {
        // 右下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetLeftTopPos().y()));
        this->setCursor(Qt::SizeFDiagCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Top, event->pos()) && m_bStart == false)
    {
        // 上边拖拽
        m_pScreen->SetState(ProcessObject::STATE::TOP_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeVerCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Bottom, event->pos()) && m_bStart == false)
    {
        //下边拖拽
        m_pScreen->SetState(ProcessObject::STATE::BOTTOM_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        this->setCursor(Qt::SizeVerCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Left, event->pos()) && m_bStart == false)
    {
        // 左边拖拽
        m_pScreen->SetState(ProcessObject::STATE::LEFT_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        this->setCursor(Qt::SizeHorCursor);
        m_bEnter = true;
    } else if(ZoomIsInArea(m_pZoom_Right, event->pos()) && m_bStart == false)
    {
        // 右边拖拽
        m_pScreen->SetState(ProcessObject::STATE::RIGHT_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        this->setCursor(Qt::SizeHorCursor);
        m_bEnter = true;
    } else if(event->button() == Qt::LeftButton)
    {
        m_qMovePos = event->pos();
        if(m_pScreen->GetStart() == QPoint(-1, -1) && m_bStart == false)
        {
            m_pScreen->SetState(ProcessObject::STATE::ZOOM);
            m_pScreen->SetStart(m_qMovePos);

        } else if(m_pScreen->IsInArea(event->pos()))
        {
            m_pScreen->SetState(ProcessObject::STATE::MOVE);
            this->setCursor(Qt::SizeAllCursor);
            m_bEnter = true;
        }
    }
    m_pGifButtonWidget->SetGifSelect(true);


}

void CatGifTool::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pScreen->GetState() != ProcessObject::STATE::MOVE && m_bStart == false)
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
    } else {
        this->setCursor(Qt::ArrowCursor);
    }
    m_qMovePos = event->pos();
    update();

}

void CatGifTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_pScreen->SetState(ProcessObject::STATE::SELECT);
    this->setCursor(Qt::ArrowCursor);
    m_pGifButtonWidget->SetGifSelect(false);
}

void CatGifTool::paintEvent(QPaintEvent *event)
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

    m_pMoveWidget->setGeometry(x, y, w, h);

    if(m_bEnter)
    {
        emit gifgeometry(x, y, w, h);
        //qDebug() << "x: " << x << " y: " << y << " w: " << w << " h: " << h;
    }

    if(w > 0 && h > 0 && m_bShow)
    {
        painter.drawRect(x, y, w, h);
        SetZoomGeometry(x, y, w, h);
        SetZoomVisible(m_bResize);
        SetMoveWidgetVisible(true);
        m_pMoveWidget->show();
    }
}

void CatGifTool::enterEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        QEnterEvent *enter = static_cast<QEnterEvent*>(event);
        if(m_pScreen->IsInArea(enter->pos()))
        {
            m_pGifButtonWidget->SetGifSelect(true);
            m_bEnter = true;
        } else {
            m_pGifButtonWidget->SetGifSelect(false);
            m_bEnter = false;
        }
    }
}

/*
void CatGifTool::leaveEvent(QEvent *event)
{
    m_bEnter = false;
    qDebug() << "leaveEvent: " << event;
    if(event->type() == QEvent::MouseMove)
    {
        qDebug() << "leaveEvent";
    }
}*/

void CatGifTool::On_Move(bool move)
{
    m_bMove = move;
    if(move)
    {
        SetMoveState("MoveON");
    } else {
        SetMoveState("MoveOFF");
    }
    //m_pMoveWidget->show();
    //update();
}

void CatGifTool::On_Show(bool show)
{
    m_bShow = show;
    SetZoomVisible(m_bShow);
    SetMoveWidgetVisible(m_bShow);
    update();
}

void CatGifTool::On_Start(bool start)
{
    m_bStart = start;
    m_bResize = !m_bStart;
}
