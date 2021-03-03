#include "ScreenShot.h"
#include "ButtonTool.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>

#include "ProcessObject.h"

ScreenShot::ScreenShot(QWidget *parent)
    : ImageToolBase(parent)
    , m_pMousePress(false)
{
    InitUi();

    InitProperty();
}

ScreenShot::~ScreenShot()
{

}

void ScreenShot::InitUi()
{
    showFullScreen();
    m_pButtonTool = new ButtonTool(this);
    m_pButtonTool->InitButtons({"SaveButton", "CloseButton"});
    m_pButtonTool->setVisible(false);

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

void ScreenShot::InitProperty()
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    /*QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);*/
    /*setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);*/
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

    //获取程序当前运行目录
    //QString path = QCoreApplication::applicationDirPath();

    QFile resourceqss(":/ImageTools/qss/ScreenShot.qss");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    m_bLight = false;
    SetLightState("OpenLight");
    m_pButtonTool->SetLampToolTip(m_bLight);

    connect(m_pButtonTool, &ButtonTool::clicked, this, [=](ButtonTool::STATE state){
        switch (state) {
            case ButtonTool::STATE::SAVE: {
                Save();
                break;
            }

            case ButtonTool::STATE::CLOSE: {
                emit clicked(STATE::CLOSE);
                this->close();
                break;
            }
            default:{
                break;
            }
        }
    });

    // 初始化 处理屏幕的对象 并初始化 可活动范围
    m_pScreen = new ProcessObject;
    m_pScreen->SetMaxParentSize(QApplication::desktop()->size());
    m_pScreen->SetMaxWidth(QApplication::desktop()->size().width());
    m_pScreen->SetMaxHeight(QApplication::desktop()->size().height());
    m_pScreen->SetMinWidth(0);
    m_pScreen->SetMinHeight(0);
    this->setMinimumSize(QApplication::desktop()->size());


    m_pFullScreen = new QPixmap;
    m_bInit =true;
}

void ScreenShot::SetZoomVisible(bool visible)
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

void ScreenShot::SetZoomGeometry(int x, int y, int width, int height)
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

bool ScreenShot::ZoomIsInArea(QWidget *Zoom, QPoint pos)
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

void ScreenShot::Save()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", STRDATETIME + QString(".png"), "PNG (*.png);;JPEG (*.jpg *jpeg);;BMP (*.bmp)");
    if(!fileName.isEmpty())
    {
        int x = m_pScreen->GetLeftTopPos().x();
        int y = m_pScreen->GetLeftTopPos().y();
        int w = m_pScreen->GetRightBottomPos().x() - x;
        int h = m_pScreen->GetRightBottomPos().y() - y;

        m_pFullScreen->copy(x, y, w, h).save(fileName);

        close();
        emit clicked(STATE::CLOSE);
    }
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    m_pMousePress = true;
    //qDebug() << "press: " << event->pos();
    if(ZoomIsInArea(m_pZoom_Left_Top, event->pos()))
    {
        // 左上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeFDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Right_Top, event->pos()))
    {
        // 右上角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetRightBottomPos().y()));
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeBDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Left_Bottom, event->pos()))
    {
        // 左下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetRightBottomPos().x(), m_pScreen->GetLeftTopPos().y()));
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeBDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Right_Bottom, event->pos()))
    {
        // 右下角拖拽
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pScreen->SetStart(QPoint(m_pScreen->GetLeftTopPos().x(), m_pScreen->GetLeftTopPos().y()));
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeFDiagCursor);
    } else if(ZoomIsInArea(m_pZoom_Top, event->pos()))
    {
        // 上边拖拽
        m_pScreen->SetState(ProcessObject::STATE::TOP_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeVerCursor);
    } else if(ZoomIsInArea(m_pZoom_Bottom, event->pos()))
    {
        //下边拖拽
        m_pScreen->SetState(ProcessObject::STATE::BOTTOM_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeVerCursor);
    } else if(ZoomIsInArea(m_pZoom_Left, event->pos()))
    {
        // 左边拖拽
        m_pScreen->SetState(ProcessObject::STATE::LEFT_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetRightBottomPos());
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeHorCursor);
    } else if(ZoomIsInArea(m_pZoom_Right, event->pos()))
    {
        // 右边拖拽
        m_pScreen->SetState(ProcessObject::STATE::RIGHT_ZOOM);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeHorCursor);
    } else if(event->button() == Qt::LeftButton)
    {
        m_qMovePos = event->pos();
        if(m_pScreen->GetStart() == QPoint(-1, -1))
        {
            m_pScreen->SetState(ProcessObject::STATE::ZOOM);
            m_pScreen->SetStart(m_qMovePos);
            m_pButtonTool->setVisible(false);

        } else if(m_pScreen->IsInArea(event->pos()))
        {
            m_pScreen->SetState(ProcessObject::STATE::MOVE);
            m_pButtonTool->setVisible(false);
            this->setCursor(Qt::SizeAllCursor);
        }
    } else if(event->button() == Qt::RightButton)
    {
        if(m_pScreen->GetStart() == QPoint(-1, -1))
        {
            this->close();
            emit clicked(STATE::CLOSE);
        } else {
            m_pButtonTool->setVisible(false);
            m_pScreen->SetStart(QPoint(-1, -1));
            m_pScreen->SetGeometry(-1, -1, 0, 0);
            SetZoomVisible(false);
            update();
        }
    }

}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "Move: " << event;
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

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_pMousePress = false;
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        m_pButtonTool->setVisible(true);
    } if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::TOP_ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::BOTTOM_ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::RIGHT_ZOOM ||
         m_pScreen->GetState() == ProcessObject::STATE::LEFT_ZOOM)
    {
        m_pButtonTool->setVisible(true);
    }
    m_pScreen->SetState(ProcessObject::STATE::SELECT);
    this->setCursor(Qt::ArrowCursor);
}

void ScreenShot::paintEvent(QPaintEvent *event)
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

    QPixmap backgroundscreen(m_pScreen->GetMaxParentWidget(), m_pScreen->GetMaxParentHeight());
    //用给定的颜色填充像素图
    backgroundscreen.fill(MaskLayerColor);
    painter.drawPixmap(0,0, *m_pBackgroundScreen);
    painter.drawPixmap(0,0, backgroundscreen);

    if(w > 0 && h > 0)
    {
        QPixmap pix = m_pFullScreen->copy(x,y,w,h);
        /*QScreen *screen = QApplication::primaryScreen();
        QPixmap pix = screen->grabWindow(
                                           QApplication::desktop()->winId(),
                                           x,
                                           y,
                                           w,
                                           h);*/
        painter.drawPixmap(x, y, pix);
        painter.drawRect(x, y, w, h);

        // 动态变更按钮组位置
        int maxheight = m_pScreen->GetMaxParentHeight();
        int distance_y_bottom = maxheight - (y+h);
        int distance_y_top = m_pScreen->y();
        if(distance_y_bottom <= m_pButtonTool->height() + 10 && distance_y_top <= m_pButtonTool->height() + 10)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width() - 5, y+h-m_pButtonTool->height()-10);
        } else if(distance_y_bottom<= m_pButtonTool->height() + 10)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width() , y - m_pButtonTool->height() - 10);
        } else {
            m_pButtonTool->move(x+w-m_pButtonTool->width() , y+h+10);
        }
        if(distance_y_top <= 20)
        {
            pen.setColor(Qt::white);
            painter.setPen(pen);
            painter.drawText(x + 2, y + 14, tr("( %1 , %2 ) - ( %3 x %4 )")
                             .arg(x).arg(y).arg(w).arg(h));
        } else {

            pen.setColor(Qt::white);
            painter.setPen(pen);

            painter.drawText(x + 2, y - 7, tr("( %1 , %2 ) - ( %3 x %4 )")
                             .arg(x).arg(y).arg(w).arg(h));
        }
        SetZoomGeometry(x, y, w, h);
        SetZoomVisible(true);



    }
}

void ScreenShot::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    if(m_bInit)
    {

        // QT5.6 获取主屏幕大小 - 全屏大小
        QScreen *screen = QApplication::primaryScreen();
        *m_pFullScreen = screen->grabWindow(
                                           QApplication::desktop()->winId(),
                                           0,
                                           0,
                                           m_pScreen->GetMaxParentWidget(),
                                           m_pScreen->GetMaxParentHeight()
                                       );

        m_pBackgroundScreen = new QPixmap(*m_pFullScreen);

        update();
        m_pButtonTool->setVisible(false);
        SetZoomVisible(false);

    }
}

bool ScreenShot::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}
