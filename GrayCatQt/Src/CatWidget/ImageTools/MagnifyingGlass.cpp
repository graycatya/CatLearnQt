#include "MagnifyingGlass.h"
#include "ButtonTool.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
#include <QtMath>

#include "ProcessObject.h"

MagnifyingGlass::MagnifyingGlass(QWidget *parent)
    : ImageToolBase(parent)
    , m_qZoomRatio(2.0)
{
    InitUi();

    InitProperty();
}

MagnifyingGlass::~MagnifyingGlass()
{

}

void MagnifyingGlass::InitUi()
{
    showFullScreen();

    m_pZoom = new QWidget(this);
    m_pZoom->setObjectName("Zoom");

    m_pButtonTool = new ButtonTool(this);
    m_pButtonTool->InitButtons({"CutButton", "LampButton", "CloseButton"});
    m_pButtonTool->setVisible(false);


}

void MagnifyingGlass::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    //获取程序当前运行目录
    //QString path = QCoreApplication::applicationDirPath();

    QFile resourceqss(":/ImageTools/qss/ImageToolBase.qss");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    m_bLight = true;
    SetLightState("OpenLight");
    m_pButtonTool->SetLampToolTip(m_bLight);
    //SetLightState("CloseLight");

    connect(m_pButtonTool, &ButtonTool::clicked, this, [=](ButtonTool::STATE state){
        switch (state) {
            case ButtonTool::STATE::CUT: {
                m_bCut = !m_bCut;
                update();
                break;
            }
            case ButtonTool::STATE::LAMP: {
                m_bLight = !m_bLight;
                if(m_bLight)
                {
                    m_pButtonTool->SetLampToolTip(m_bLight);
                    SetLightState("OpenLight");
                    update();
                } else {
                    m_pButtonTool->SetLampToolTip(m_bLight);
                    SetLightState("CloseLight");
                    update();
                }

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


    m_pFullScreen = new QPixmap;
    m_bInit =true;
}

bool MagnifyingGlass::ZoomIsInArea(QPoint pos)
{
    if(pos.x() > m_pZoom->x()
            && pos.x() < m_pZoom->x() + m_pZoom->width()
            && pos.y() > m_pZoom->y()
            && pos.y() < m_pZoom->y() + m_pZoom->height())
    {
        return true;
    }
    return false;
}

void MagnifyingGlass::mousePressEvent(QMouseEvent *event)
{
    if(this->ZoomIsInArea(event->pos()))
    {
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if(m_pScreen->IsInArea(event->pos()))
    {
        m_pScreen->SetState(ProcessObject::STATE::MOVE);
        m_pZoom->setVisible(false);
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeAllCursor);
    }

    m_qMovePos = event->pos();
}

void MagnifyingGlass::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        m_pScreen->Move(pos);
        m_qMovePos = event->pos();
    } else if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        int w = m_pScreen->width() + pos.x();
        int h = m_pScreen->height() + pos.y();
        m_pScreen->SetGeometry(m_pScreen->x(),
                               m_pScreen->y(),
                               w, h);
        m_qMovePos = event->pos();
    }
    update();
}

void MagnifyingGlass::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        m_pScreen->SetState(ProcessObject::STATE::SELECT);
        m_pZoom->setVisible(true);
        m_pButtonTool->setVisible(true);
    } if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        m_pScreen->SetState(ProcessObject::STATE::SELECT);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        m_pScreen->SetEnd(m_pScreen->GetRightBottomPos());
        m_pButtonTool->setVisible(true);
    }
    this->setCursor(Qt::ArrowCursor);
}

void MagnifyingGlass::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    int x = m_pScreen->x();
    int y = m_pScreen->y();
    int w = m_pScreen->width();
    int h = m_pScreen->height();

    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    painter.setPen(pen);

    QPixmap backgroundscreen(m_pScreen->GetMaxParentWidget(), m_pScreen->GetMaxParentHeight());
    //用给定的颜色填充像素图
    backgroundscreen.fill(MaskLayerColor);
    painter.drawPixmap(0,0, *m_pBackgroundScreen);
    painter.drawPixmap(0,0, backgroundscreen);



    if(w != 0 && h != 0)
    {
        if(m_bCut)
        {
            int side = qMin(w, h);
            // x,y 的坐标换算比例
            float scale_x = float(x)/float(m_pScreen->GetMaxParentWidget()-side);
            float scale_y = float(y)/float(m_pScreen->GetMaxParentHeight()-side);
            m_pScreen->SetGeometry(m_pScreen->x(), m_pScreen->y(), side, side);
            QTransform transform;
            transform.translate(x, y);
            transform.scale(m_qZoomRatio, m_qZoomRatio);
            QPixmap pix = m_pFullScreen->copy(x + static_cast<int>(float(side)/float(m_qZoomRatio)*scale_x),
                                              y + static_cast<int>(float(side)/float(m_qZoomRatio)*scale_y),
                                              static_cast<int>(float(side)/float(m_qZoomRatio)),
                                              static_cast<int>(float(side)/float(m_qZoomRatio)));
            QBrush brush(pix);
            brush.setTransform(transform);
            painter.setBrush(brush);
            painter.drawEllipse(x, y, side, side);

            int circle_centerx = x + side/2;
            int circle_centery = y + side/2;
            int r = side/2;
            int x1 = static_cast<int>(double(circle_centerx) + double(r) * qCos(45.0));
            int y1 = static_cast<int>(double(circle_centery) + double(r) * qSin(45.0));
            m_pZoom->move(x1-m_pZoom->width()/2, y1-m_pZoom->height()/2);
            //m_pZoom->show();

        } else {
            // x,y 的坐标换算比例
            float scale_x = float(x)/float(m_pScreen->GetMaxParentWidget()-w);
            float scale_y = float(y)/float(m_pScreen->GetMaxParentHeight()-h);
            QTransform transform;
            transform.translate(x, y);
            transform.scale(m_qZoomRatio, m_qZoomRatio);
            QPixmap pix = m_pFullScreen->copy(x + static_cast<int>(float(w)/float(m_qZoomRatio)*scale_x),
                                              y + static_cast<int>(float(h)/float(m_qZoomRatio)*scale_y),
                                              static_cast<int>(float(w)/float(m_qZoomRatio)),
                                              static_cast<int>(float(h)/float(m_qZoomRatio)));
            QBrush brush(pix);
            brush.setTransform(transform);
            painter.setBrush(brush);
            painter.drawPixmap(x, y, m_pFullScreen->copy(x, y, w, h));
            painter.drawRect(x, y, w, h);

            m_pZoom->move(x+w-m_pZoom->width()/2, y+h-m_pZoom->height()/2);
            //m_pZoom->show();

        }
        // 动态变更按钮组位置
        int maxheight = m_pScreen->GetMaxParentHeight();
        int distance_y_bottom = maxheight - (y+h);
        int distance_y_top = m_pScreen->y();
        if(distance_y_bottom <= m_pButtonTool->height() + 7 && distance_y_top <= m_pButtonTool->height() + 7)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y+h-m_pButtonTool->height()-7);
        } else if(distance_y_bottom<= m_pButtonTool->height() + 7)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y - m_pButtonTool->height() - 7);
        } else {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y+h+7);
        }
    }
}

void MagnifyingGlass::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    if(m_bInit)
    {
        int wide = m_pScreen->GetMaxParentHeight()/3;
        int x = (m_pScreen->GetMaxParentWidget() - wide)/2;
        int y = (m_pScreen->GetMaxParentHeight() - wide)/2;
        m_pScreen->SetStart(QPoint(x,y));
        m_pScreen->SetGeometry(x, y, wide, wide);

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
        m_pZoom->show();
        m_pButtonTool->setVisible(true);

    }
}
