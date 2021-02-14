#include "CatDoubleSlider.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>

#define DEFINEWIDTH 10

CatDoubleSlider::CatDoubleSlider(QWidget *parent)
    : QWidget(parent)
    , m_ySlideOrientationState(SliderHorizontal)
{
    InitUi();
    InitProperty();
    update();
}

CatDoubleSlider::~CatDoubleSlider()
{

}

void CatDoubleSlider::InitUi()
{
    this->setMinimumSize(QSize(100, DEFINEWIDTH));
    this->setMaximumSize(QSize(100, DEFINEWIDTH));
}

void CatDoubleSlider::InitProperty()
{
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
    m_ySelectStyle = NotSelect;
    InitRectfProperty();
}

void CatDoubleSlider::InitRectfProperty()
{
    m_nBackgroundRadius = 2;
    m_nSlideRadius = 5;
    m_nSlideLeftBorderWidth = 1;
    m_nSlideRightBorderWidth = 1;
    m_nBackgroundRectBorderWidth = 1;
    m_nBackgroundSlideRectBorderWidth = 1;
    m_cSlideLeftColor = QBrush(QColor(180, 180,180));
    m_cSlideRightColor = QBrush(QColor(180, 180,180));
    m_cBackgroundRectColor = QBrush(QColor(200, 200, 200));
    m_cBackgroundSlideRectColor = QBrush(QColor(119, 63, 114));
    m_cSlideLeftBorderColor = QBrush(QColor(30, 30, 30));
    m_cSlideRightBorderColor = QBrush(QColor(30, 30, 30));
    m_cBackgroundRectBorderColor = QBrush(QColor(30, 30, 30));
    m_cBackgroundSlideRectBorderColor = QBrush(QColor(30, 30, 30));
    m_nSlideWidth = DEFINEWIDTH;
    m_nBackgroundHeight = m_nSlideWidth/2.0;
    m_nBackgroundSlideHeight = m_nSlideWidth/2.0;

    UpdateOrientation();
    m_nSliderDistance = m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.left();
}

void CatDoubleSlider::UpdateProperty()
{
    switch (m_ySlideOrientationState) {
        case SliderHorizontal: {
            break;
        }
        case SliderVertical: {
            break;
        }
    }
}

void CatDoubleSlider::Painter_Background_Rect(QPainter *painter)
{
    //Q_UNUSED(painter)
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setWidthF(m_nBackgroundRectBorderWidth);
    pen.setBrush(m_cBackgroundRectBorderColor);
    QBrush brush = painter->brush();
    brush = m_cBackgroundRectColor;
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(m_yBackground_Rect, m_nBackgroundRadius , m_nBackgroundRadius);
    painter->restore();
}

void CatDoubleSlider::Painter_BackgroundSlide_Rect(QPainter *painter)
{
    //Q_UNUSED(painter)
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setWidthF(m_nBackgroundSlideRectBorderWidth);
    pen.setBrush(m_cBackgroundSlideRectBorderColor);
    QBrush brush = painter->brush();
    brush = m_cBackgroundSlideRectColor;
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(m_yBackgroundSlide_Rect, m_nBackgroundRadius , m_nBackgroundRadius);
    painter->restore();
}

void CatDoubleSlider::Painter_Slide_LeftOrTop(QPainter *painter)
{
    //Q_UNUSED(painter)
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setWidthF(m_nSlideLeftBorderWidth);
    pen.setBrush(m_cSlideLeftBorderColor);
    QBrush brush = painter->brush();
    brush = m_cSlideLeftColor;
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(m_ySlide_LeftOrTop, m_nSlideRadius , m_nSlideRadius);
    painter->restore();
}

void CatDoubleSlider::Painter_Slide_RightOrBottom(QPainter *painter)
{
    //Q_UNUSED(painter)
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setWidthF(m_nSlideRightBorderWidth);
    pen.setBrush(m_cSlideRightBorderColor);
    QBrush brush = painter->brush();
    brush = m_cSlideRightColor;
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(m_ySlide_RightOrBottom, m_nSlideRadius , m_nSlideRadius);
    painter->restore();
}

void CatDoubleSlider::LeftOrTopSelectDisPose(QMouseEvent *event)
{
    QPointF movepos = event->pos() - m_pPressPoint;
    if(m_ySlideOrientationState == SliderHorizontal)
    {
        if(m_ySlide_LeftOrTop.x() + movepos.rx() < 0)
        {
            m_ySlide_LeftOrTop.setX(0);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            return;
        }

        if((m_ySlide_LeftOrTop.x() + m_ySlide_LeftOrTop.width() + movepos.rx()) < m_ySlide_RightOrBottom.x())
        {
            m_ySlide_LeftOrTop.setX(m_ySlide_LeftOrTop.x() + movepos.rx());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_LeftOrTop.setX(m_ySlide_RightOrBottom.x() - m_ySlide_LeftOrTop.width());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        }

        qreal x = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.x();
        qreal w = this->width() - m_nSlideWidth - m_ySlide_LeftOrTop.x() - (this->width() - m_ySlide_RightOrBottom.right());
        m_yBackgroundSlide_Rect.setRect(x,
                                        static_cast<qreal>(m_nSlideWidth)/4.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                                        w,
                                        m_nBackgroundSlideHeight);

    } else if(m_ySlideOrientationState == SliderVertical) {
        if(m_ySlide_LeftOrTop.y() + movepos.ry() < 0)
        {
            m_ySlide_LeftOrTop.setY(0);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            return;
        }

        if(m_ySlide_LeftOrTop.y() + m_ySlide_LeftOrTop.height() + movepos.ry() < m_ySlide_RightOrBottom.y())
        {
            m_ySlide_LeftOrTop.setY(m_ySlide_LeftOrTop.y() + movepos.ry());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_LeftOrTop.setY(m_ySlide_RightOrBottom.y() - m_ySlide_LeftOrTop.height());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        }

        qreal y = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.y();
        qreal h = this->height() - m_nSlideWidth - m_ySlide_LeftOrTop.y() - (this->height() - m_ySlide_RightOrBottom.bottom());

        m_yBackgroundSlide_Rect.setRect(m_nBackgroundHeight/2.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                           y,
                           m_nBackgroundHeight,
                           h);
    }
}

void CatDoubleSlider::RightOrBottomSelectDisPose(QMouseEvent *event)
{
    QPointF movepos = event->pos() - m_pPressPoint;
    if(m_ySlideOrientationState == SliderHorizontal)
    {
        if(event->pos().x() <= 0 || event->pos().x() >= this->width())
        {
            return;
        }

        if(m_ySlide_RightOrBottom.x() + m_ySlide_RightOrBottom.width() + movepos.rx() > this->width())
        {
            m_ySlide_RightOrBottom.setX(this->width() - m_ySlide_RightOrBottom.width());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else if((m_ySlide_RightOrBottom.x() + movepos.rx()) > m_ySlide_LeftOrTop.x() + m_ySlide_LeftOrTop.width())
        {
            m_ySlide_RightOrBottom.setX(m_ySlide_RightOrBottom.x() + movepos.rx());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_RightOrBottom.setX(m_ySlide_LeftOrTop.x() + m_ySlide_LeftOrTop.width());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        }

        qreal x = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.x();
        qreal w = this->width() - m_nSlideWidth - m_ySlide_LeftOrTop.x() - (this->width() - m_ySlide_RightOrBottom.right());
        m_yBackgroundSlide_Rect.setRect(x,
                                        static_cast<qreal>(m_nSlideWidth)/4.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                                        w,
                                        m_nBackgroundSlideHeight);

    } else if(m_ySlideOrientationState == SliderVertical) {
        if(event->pos().y() <= 0 || event->pos().y() >= this->height())
        {
            return;
        }

        if(m_ySlide_RightOrBottom.y() + m_ySlide_RightOrBottom.width() + movepos.ry() > this->height())
        {
            m_ySlide_RightOrBottom.setY(this->height() - m_ySlide_RightOrBottom.height());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else if(m_ySlide_RightOrBottom.y() + movepos.ry() > m_ySlide_LeftOrTop.y() + m_ySlide_LeftOrTop.height())
        {
            m_ySlide_RightOrBottom.setY(m_ySlide_RightOrBottom.y() + movepos.ry());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_RightOrBottom.setY(m_ySlide_LeftOrTop.y() + m_ySlide_LeftOrTop.height());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        }

        qreal y = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.y();
        qreal h = this->height() - m_nSlideWidth - m_ySlide_LeftOrTop.y() - (this->height() - m_ySlide_RightOrBottom.bottom());

        m_yBackgroundSlide_Rect.setRect(m_nBackgroundHeight/2.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                           y,
                           m_nBackgroundHeight,
                           h);

    }
}

void CatDoubleSlider::BackgroundSlideRectPose(QMouseEvent *event)
{
    QPointF movepos = event->pos() - m_pPressPoint;
    qDebug() << "SliderDistance: " << m_nSliderDistance;
    if(m_ySlideOrientationState == SliderHorizontal)
    {
        /*if(event->pos().x() <= 0 || event->pos().x() >= this->width())
        {
            return;
        }*/

        if(m_ySlide_LeftOrTop.left() + movepos.rx() <= 0)
        {
            qDebug() << "SliderDistance1: " << m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.left();
            m_ySlide_LeftOrTop.setLeft(0);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            qDebug() << "m_ySlide_LeftOrTop: " << m_ySlide_LeftOrTop;
            m_ySlide_RightOrBottom.setRight(m_nSliderDistance);
            m_ySlide_RightOrBottom.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            qDebug() << "m_ySlide_RightOrBottom: " << m_ySlide_RightOrBottom;
            qDebug() << "SliderDistance2: " << m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.left();
            goto updateslide;
        } else if(m_ySlide_RightOrBottom.right() + movepos.rx() >= this->width())
        {
            m_ySlide_RightOrBottom.setRight(this->width());
            m_ySlide_RightOrBottom.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            qDebug() << "m_ySlide_RightOrBottom.right() - m_nSliderDistance: " << m_ySlide_RightOrBottom.right() - m_nSliderDistance;
            m_ySlide_LeftOrTop.setLeft(m_ySlide_RightOrBottom.right() - m_nSliderDistance);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            qDebug() << "SliderDistance2: " << m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.left();
            goto updateslide;
        }


        if(m_ySlide_RightOrBottom.x() + m_ySlide_RightOrBottom.width() + movepos.rx() > this->width())
        {
            m_ySlide_RightOrBottom.setX(this->width() - m_ySlide_RightOrBottom.width());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else if((m_ySlide_RightOrBottom.x() + movepos.rx()) > m_ySlide_LeftOrTop.x() + m_ySlide_LeftOrTop.width())
        {
            m_ySlide_RightOrBottom.setX(m_ySlide_RightOrBottom.x() + movepos.rx());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_RightOrBottom.setX(m_ySlide_LeftOrTop.x() + m_ySlide_LeftOrTop.width());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        }

        if((m_ySlide_LeftOrTop.x() + m_ySlide_LeftOrTop.width() + movepos.rx()) < m_ySlide_RightOrBottom.x())
        {
            m_ySlide_LeftOrTop.setX(m_ySlide_LeftOrTop.x() + movepos.rx());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_LeftOrTop.setX(m_ySlide_RightOrBottom.x() - m_ySlide_LeftOrTop.width());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        }

        updateslide:
        qreal x = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.x();
        qreal w = this->width() - m_nSlideWidth - m_ySlide_LeftOrTop.x() - (this->width() - m_ySlide_RightOrBottom.right());
        m_yBackgroundSlide_Rect.setRect(x,
                                        static_cast<qreal>(m_nSlideWidth)/4.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                                        w,
                                        m_nBackgroundSlideHeight);

    } else if(m_ySlideOrientationState == SliderVertical) {
        /*if(event->pos().y() <= 0 || event->pos().y() >= this->height())
        {
            return;
        }*/

        if(m_ySlide_LeftOrTop.y() + movepos.ry() < 0)
        {
            m_ySlide_LeftOrTop.setY(0);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            m_ySlide_RightOrBottom.setBottom(m_nSliderDistance);
            m_ySlide_RightOrBottom.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            return;
        } else if(m_ySlide_RightOrBottom.bottom() + movepos.ry() > this->height())
        {
            m_ySlide_RightOrBottom.setBottom(this->height());
            m_ySlide_RightOrBottom.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            m_ySlide_LeftOrTop.setY(m_ySlide_RightOrBottom.bottom() - m_nSliderDistance);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
            return;
        }

        if(m_ySlide_RightOrBottom.y() + m_ySlide_RightOrBottom.width() + movepos.ry() > this->height())
        {
            m_ySlide_RightOrBottom.setY(this->height() - m_ySlide_RightOrBottom.height());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else if(m_ySlide_RightOrBottom.y() + movepos.ry() > m_ySlide_LeftOrTop.y() + m_ySlide_LeftOrTop.height())
        {
            m_ySlide_RightOrBottom.setY(m_ySlide_RightOrBottom.y() + movepos.ry());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_RightOrBottom.setY(m_ySlide_LeftOrTop.y() + m_ySlide_LeftOrTop.height());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideWidth));
        }

        if(m_ySlide_LeftOrTop.y() + m_ySlide_LeftOrTop.height() + movepos.ry() < m_ySlide_RightOrBottom.y())
        {
            m_ySlide_LeftOrTop.setY(m_ySlide_LeftOrTop.y() + movepos.ry());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        } else {
            m_ySlide_LeftOrTop.setY(m_ySlide_RightOrBottom.y() - m_ySlide_LeftOrTop.height());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideWidth));
        }

        qreal y = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.y();
        qreal h = this->height() - m_nSlideWidth - m_ySlide_LeftOrTop.y() - (this->height() - m_ySlide_RightOrBottom.bottom());

        m_yBackgroundSlide_Rect.setRect(m_nBackgroundHeight/2.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                           y,
                           m_nBackgroundHeight,
                           h);

    }
}

void CatDoubleSlider::UpdateOrientation()
{
    if(m_ySlideOrientationState == OrientationState::SliderHorizontal)
    {
        m_ySlide_LeftOrTop.setRect(0.0, m_nSlideLeftBorderWidth/2.0, m_nSlideWidth, m_nSlideWidth);
        m_ySlide_RightOrBottom.setRect(this->width() - m_nSlideWidth, m_nSlideRightBorderWidth/2.0,
                                       m_nSlideWidth, m_nSlideWidth);

        m_yBackground_Rect.setRect(static_cast<qreal>(m_nSlideWidth)/2.0,
                           static_cast<qreal>(m_nSlideWidth)/4.0 + m_nBackgroundRectBorderWidth/2.0,
                           this->width() - m_nSlideWidth,
                           m_nBackgroundHeight);
        qreal x = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.x();
        qreal w = this->width() - m_nSlideWidth - m_ySlide_LeftOrTop.x() - (this->width() - m_ySlide_RightOrBottom.right());
        m_yBackgroundSlide_Rect.setRect(x,
                                        static_cast<qreal>(m_nSlideWidth)/4.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                                        w,
                                        m_nBackgroundSlideHeight);
    } else if(m_ySlideOrientationState == OrientationState::SliderVertical)
    {
        m_ySlide_LeftOrTop.setRect(m_nSlideLeftBorderWidth/2.0, 0.0, m_nSlideWidth, m_nSlideWidth);
        m_ySlide_RightOrBottom.setRect(m_nSlideRightBorderWidth/2.0, this->height() - m_nSlideWidth,
                                       m_nSlideWidth, m_nSlideWidth);
        m_yBackground_Rect.setRect(m_nBackgroundHeight/2.0 + m_nBackgroundRectBorderWidth/2.0,
                           static_cast<qreal>(m_nSlideWidth)/2.0,
                           m_nBackgroundHeight,
                           this->height() - m_nSlideWidth);

        qreal y = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.y();
        qreal h = this->height() - m_nSlideWidth - m_ySlide_LeftOrTop.y() - (this->height() - m_ySlide_RightOrBottom.bottom());

        m_yBackgroundSlide_Rect.setRect(m_nBackgroundHeight/2.0 + m_nBackgroundSlideRectBorderWidth/2.0,
                           y,
                           m_nBackgroundHeight,
                           h);

    }
}

void CatDoubleSlider::setSlideLeftOrTopWidth(int width)
{
    m_ySlide_LeftOrTop.setWidth(width);
    emit SlideLeftOrTopWidthChanged(width);
    update();
}

void CatDoubleSlider::setSlideLeftOrTopHeight(int height)
{
    m_ySlide_LeftOrTop.setHeight(height);
    emit SlideLeftOrTopHeightChanged(height);
    update();
}

void CatDoubleSlider::setSlideRightOrBottomWidth(int width)
{
    m_ySlide_RightOrBottom.setWidth(width);
    emit SlideRightOrBottomWidthChanged(width);
    update();
}

void CatDoubleSlider::setSlideRightOrBottomHeight(int height)
{
    m_ySlide_RightOrBottom.setHeight(height);
    emit SlideRightOrBottomHeightChanged(height);
    update();
}

void CatDoubleSlider::setSlideOrientationState(CatDoubleSlider::OrientationState state)
{
    m_ySlideOrientationState = state;
    emit SlideOrientationStateChanged(state);
    UpdateOrientation();
    update();
}

void CatDoubleSlider::setSlideLeftColor(QBrush brush)
{
    m_cSlideLeftColor = brush;
    update();
}

void CatDoubleSlider::setSlideRightColor(QBrush brush)
{
    m_cSlideRightColor = brush;
    update();
}

void CatDoubleSlider::setBackgroundRectColor(QBrush brush)
{
    m_cBackgroundRectColor = brush;
    update();
}

void CatDoubleSlider::setBackgroundSlideRectColor(QBrush brush)
{
    m_cBackgroundSlideRectColor = brush;
    update();
}

void CatDoubleSlider::setSlideLeftBorderColor(QBrush color)
{
    m_cSlideLeftBorderColor = color;
    update();
}

void CatDoubleSlider::setSlideRightBorderColor(QBrush color)
{
    m_cSlideRightBorderColor = color;
    update();
}

void CatDoubleSlider::setBackgroundRectBorderColor(QBrush color)
{
    m_cBackgroundRectBorderColor = color;
    update();
}

void CatDoubleSlider::setBackgroundSlideRectBorderColor(QBrush color)
{
    m_cBackgroundSlideRectBorderColor = color;
    update();
}

void CatDoubleSlider::setBackgroundRadius(int radius)
{
    m_nBackgroundRadius = radius;
    update();
}

void CatDoubleSlider::setSlideRadius(int radius)
{
    m_nSlideRadius = radius;
    update();
}

void CatDoubleSlider::setSlideWidth(qreal width)
{
    m_nSlideWidth = width;
    update();
}

void CatDoubleSlider::setBackgroundHeight(qreal height)
{
    m_nBackgroundHeight = height;
    update();
}

void CatDoubleSlider::setBackgroundSlideHeight(qreal height)
{
    m_nBackgroundSlideHeight = height;
    update();
}

void CatDoubleSlider::setSlideLeftBorderWidth(qreal width)
{
    m_nSlideLeftBorderWidth = width;
    update();
}

void CatDoubleSlider::setSlideRightBorderWidth(qreal width)
{
    m_nSlideRightBorderWidth = width;
    update();
}

void CatDoubleSlider::setBackgroundRectBorderWidth(qreal width)
{
    m_nBackgroundRectBorderWidth = width;
    update();
}

void CatDoubleSlider::setBackgroundSlideRectBorderWidth(qreal width)
{
    m_nBackgroundSlideRectBorderWidth = width;
    update();
}

void CatDoubleSlider::setSliderStyle(CatDoubleSlider::SliderStyles style)
{
    m_ySliderStyle = style;
    emit SliderStyleChanged(style);
    update();
}

void CatDoubleSlider::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
}

void CatDoubleSlider::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
}

void CatDoubleSlider::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
}

void CatDoubleSlider::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << event->pos();
    switch (m_ySelectStyle) {
        case LeftOrTopSelect: {
            LeftOrTopSelectDisPose(event);
            break;
        }
        case RightOrBottomSelect: {
            RightOrBottomSelectDisPose(event);
            break;
        }
        case BackgroundSlideSelect: {
            BackgroundSlideRectPose(event);
            break;
        }
        default:{
            break;
        }
    }

    m_pPressPoint = event->pos();
    update();
}

void CatDoubleSlider::mousePressEvent(QMouseEvent *event)
{
    m_pPressPoint = event->pos();

    QPainterPath slideLeftOrTopPath;
    QPainterPath slideRightOrBottomPath;
    QPainterPath backgroundSlideRectPath;

    slideLeftOrTopPath.addRoundedRect(m_ySlide_LeftOrTop, m_nSlideRadius, m_nSlideRadius);
    slideRightOrBottomPath.addRoundedRect(m_ySlide_RightOrBottom, m_nSlideRadius, m_nSlideRadius);
    backgroundSlideRectPath.addRoundedRect(m_yBackgroundSlide_Rect, m_nBackgroundRadius, m_nBackgroundRadius);

    if(m_ySlideOrientationState == OrientationState::SliderHorizontal)
    {
        m_nSliderDistance = m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.left();
    } else if(m_ySlideOrientationState == OrientationState::SliderVertical)
    {
        m_nSliderDistance = m_ySlide_RightOrBottom.bottom() - m_ySlide_LeftOrTop.top();
    }

    if(slideLeftOrTopPath.contains(event->pos()))
    {
        m_ySelectStyle = LeftOrTopSelect;
    } else if(slideRightOrBottomPath.contains(event->pos()))
    {
        m_ySelectStyle = RightOrBottomSelect;
    } else if(backgroundSlideRectPath.contains(event->pos()))
    {
        m_ySelectStyle = BackgroundSlideSelect;
    }
}

void CatDoubleSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_ySelectStyle = NotSelect;
}

void CatDoubleSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    UpdateProperty();
    Painter_Background_Rect(&painter);
    Painter_BackgroundSlide_Rect(&painter);
    Painter_Slide_LeftOrTop(&painter);
    Painter_Slide_RightOrBottom(&painter);
}
