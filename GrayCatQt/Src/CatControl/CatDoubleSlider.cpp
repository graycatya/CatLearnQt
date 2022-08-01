#include "CatDoubleSlider.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>
#include <QDateTime>

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

void CatDoubleSlider::SetFromTo(qreal from, qreal to)
{
    if(from != to)
    {
        m_nFrom = from;
        m_nTo = to;
        m_nFirst = m_nFrom;
        m_nSecond = m_nTo;
        UpdateSlideCoordinates();
        update();
        emit UpdateFirstSeconded(m_nFirst, m_nSecond);
    }
}

void CatDoubleSlider::SetFirst(qreal first)
{
    if(m_nFrom < m_nTo)
    {
        m_nFirst = first > m_nSecond ? m_nSecond : first;
    } else if(m_nFrom > m_nTo)
    {
        m_nFirst = first < m_nSecond ? m_nSecond : first;
    }
    UpdateSlideCoordinates();
    update();
    emit UpdateFirstSeconded(m_nFirst, m_nSecond);
}

void CatDoubleSlider::SetSecond(qreal second)
{
    if(m_nFrom < m_nTo)
    {
        m_nSecond = second < m_nFirst ? m_nFrom : second;
    } else if(m_nFrom > m_nTo)
    {
        m_nSecond = second > m_nFirst ? m_nFrom : second;
    }
    UpdateSlideCoordinates();
    update();
    emit UpdateFirstSeconded(m_nFirst, m_nSecond);
}

void CatDoubleSlider::SetFirstSecond(qreal first, qreal second)
{
    m_nFirst = first;
    m_nSecond = second;
    UpdateSlideCoordinates();
    update();
    emit UpdateFirstSeconded(m_nFirst, m_nSecond);
}

void CatDoubleSlider::SetFromToNotUpdate(qreal from, qreal to)
{
    if(from != to)
    {
        m_nFrom = from;
        m_nTo = to;
        UpdateSlideCoordinates();
        update();
    }
}

void CatDoubleSlider::InitUi()
{
}

void CatDoubleSlider::InitProperty()
{
    m_bMousePress = false;
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
    m_ySelectStyle = NotSelect;
    m_ySelectStyle = NotSelect;

    InitRectfProperty();

    this->setMouseTracking(true);
    this->installEventFilter(this->parent());

    SetFromTo(0, 100);
    SetFirst(10);
    SetSecond(30);
    //UpdateSlideCoordinates();
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

    m_cCurrentSlideLeftColor = m_cSlideLeftColor;
    m_cCurrentSlideRightColor = m_cSlideRightColor;
    m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
    m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
    m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
    m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
    m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
    m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;

    m_cHoverSlideLeftColor = m_cSlideLeftColor;
    m_cHoverSlideRightColor = m_cSlideRightColor;
    m_cHoverBackgroundRectColor = m_cBackgroundRectColor;
    m_cHoverBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
    m_cHoverSlideLeftBorderColor = m_cSlideLeftBorderColor;
    m_cHoverSlideRightBorderColor = m_cSlideRightBorderColor;
    m_cHoverBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
    m_cHoverBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;

    m_cPressSlideLeftColor = m_cSlideLeftColor;
    m_cPressSlideRightColor = m_cSlideRightColor;
    m_cPressBackgroundRectColor = m_cBackgroundRectColor;
    m_cPressBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
    m_cPressSlideLeftBorderColor = m_cSlideLeftBorderColor;
    m_cPressSlideRightBorderColor = m_cSlideRightBorderColor;
    m_cPressBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
    m_cPressBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;

    m_nSlideWidth = DEFINEWIDTH;
    m_nSlideHeight = DEFINEWIDTH;
    m_nBackgroundHeight = m_nSlideWidth/2.0;
    m_nBackgroundSlideHeight = m_nSlideWidth/2.0;

    UpdateOrientation();
    m_nSliderDistance = m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.left();
}


void CatDoubleSlider::UpdateBackgroundSlide()
{
    switch (m_ySlideOrientationState) {
        case SliderHorizontal: {
            qreal x = static_cast<qreal>(m_nSlideWidth)/2.0 + m_ySlide_LeftOrTop.x();
            qreal w = this->width() - m_nSlideWidth - m_ySlide_LeftOrTop.x() - (this->width() - m_ySlide_RightOrBottom.right());
            m_yBackgroundSlide_Rect.setRect(x,
                                            (this->height() - m_nBackgroundHeight)/2.0,
                                            w,
                                            m_nBackgroundSlideHeight);
            break;
        }
        case SliderVertical: {
            qreal y = static_cast<qreal>(m_nSlideHeight)/2.0 + m_ySlide_LeftOrTop.y();
            qreal h = this->height() - m_nSlideHeight - m_ySlide_LeftOrTop.y() - (this->height() - m_ySlide_RightOrBottom.bottom());

            m_yBackgroundSlide_Rect.setRect((this->width() - m_nBackgroundHeight)/2.0,
                               y,
                               m_nBackgroundHeight,
                               h);
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
    pen.setBrush(m_cCurrentBackgroundRectBorderColor);
    QBrush brush = painter->brush();
    brush = m_cCurrentBackgroundRectColor;
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
    pen.setBrush(m_cCurrentBackgroundSlideRectBorderColor);
    QBrush brush = painter->brush();
    brush = m_cCurrentBackgroundSlideRectColor;
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
    pen.setBrush(m_cCurrentSlideLeftBorderColor);
    QBrush brush = painter->brush();
    brush = m_cCurrentSlideLeftColor;
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
    pen.setBrush(m_cCurrentSlideRightBorderColor);
    QBrush brush = painter->brush();
    brush = m_cCurrentSlideRightColor;
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
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
        } else if((m_ySlide_LeftOrTop.right() + movepos.rx()) < m_ySlide_RightOrBottom.right())
        {
            m_ySlide_LeftOrTop.setX(m_ySlide_LeftOrTop.x() + movepos.rx());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
        } else {
            m_ySlide_LeftOrTop.setX(m_ySlide_RightOrBottom.right() - m_ySlide_LeftOrTop.width());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
        }

        UpdateBackgroundSlide();

    } else if(m_ySlideOrientationState == SliderVertical) {
        if(m_ySlide_LeftOrTop.y() + movepos.ry() < 0)
        {
            m_ySlide_LeftOrTop.setY(0);
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
        } else if(m_ySlide_LeftOrTop.bottom() + movepos.ry() < m_ySlide_RightOrBottom.bottom())
        {
            m_ySlide_LeftOrTop.setY(m_ySlide_LeftOrTop.y() + movepos.ry());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
        } else {
            m_ySlide_LeftOrTop.setY(m_ySlide_RightOrBottom.top());
            m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
        }

        UpdateBackgroundSlide();
    }
}

void CatDoubleSlider::RightOrBottomSelectDisPose(QMouseEvent *event)
{
    QPointF movepos = event->pos() - m_pPressPoint;
    if(m_ySlideOrientationState == SliderHorizontal)
    {
        if(m_ySlide_RightOrBottom.x() + m_ySlide_RightOrBottom.width() + movepos.rx() > this->width())
        {
            m_ySlide_RightOrBottom.setX(this->width() - m_ySlide_RightOrBottom.width());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideHeight));
        } else if((m_ySlide_RightOrBottom.x() + movepos.rx()) > m_ySlide_LeftOrTop.x())
        {
            m_ySlide_RightOrBottom.setX(m_ySlide_RightOrBottom.x() + movepos.rx());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideHeight));
        } else {
            m_ySlide_RightOrBottom.setX(m_ySlide_LeftOrTop.x());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideHeight));
        }

        UpdateBackgroundSlide();
    } else if(m_ySlideOrientationState == SliderVertical) {

        if(m_ySlide_RightOrBottom.y() + m_ySlide_RightOrBottom.width() + movepos.ry() > this->height())
        {
            m_ySlide_RightOrBottom.setY(this->height() - m_ySlide_RightOrBottom.height());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideHeight));
        } else if(m_ySlide_RightOrBottom.y() + movepos.ry() > m_ySlide_LeftOrTop.top())
        {
            m_ySlide_RightOrBottom.setY(m_ySlide_RightOrBottom.y() + movepos.ry());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideHeight));
        } else {
            m_ySlide_RightOrBottom.setY(m_ySlide_LeftOrTop.top());
            m_ySlide_RightOrBottom.setSize(QSize(m_nSlideWidth, m_nSlideHeight));
        }

        UpdateBackgroundSlide();
    }
}

void CatDoubleSlider::BackgroundSlideRectPose(QMouseEvent *event)
{
    QPointF movepos = event->pos() - m_pPressPoint;

    if(m_ySlideOrientationState == SliderHorizontal)
    {
        if(movepos.rx() < 0)
        {
            if(m_ySlide_LeftOrTop.x() + movepos.rx() < 0)
            {
                m_ySlide_LeftOrTop.setRect(0, m_nSlideLeftBorderWidth/2.0,
                                           m_nSlideWidth, m_nSlideHeight);
            } else {
                m_ySlide_LeftOrTop.setRect(m_ySlide_LeftOrTop.x() + movepos.rx(), m_nSlideLeftBorderWidth/2.0,
                                           m_nSlideWidth, m_nSlideHeight);
            }
            m_ySlide_RightOrBottom.setRect(m_ySlide_LeftOrTop.left() + m_nSliderDistance - m_nSlideWidth,
                                           m_nSlideRightBorderWidth/2.0,
                                           m_nSlideWidth, m_nSlideHeight);

            UpdateBackgroundSlide();
        } else if(movepos.rx() > 0)
        {
            if(m_ySlide_RightOrBottom.right() + movepos.rx() > this->width())
            {
                m_ySlide_RightOrBottom.setRect(this->width() - m_ySlide_RightOrBottom.width(), m_nSlideRightBorderWidth/2.0,
                                               m_nSlideWidth, m_nSlideHeight);
            } else {
                m_ySlide_RightOrBottom.setRect(m_ySlide_RightOrBottom.x() + movepos.rx(), m_nSlideRightBorderWidth/2.0,
                                               m_nSlideWidth, m_nSlideHeight);
            }
            m_ySlide_LeftOrTop.setRect(m_ySlide_RightOrBottom.right() - m_nSliderDistance, m_nSlideLeftBorderWidth/2.0,
                                       m_nSlideWidth, m_nSlideHeight);

            UpdateBackgroundSlide();
        }
    } else if(m_ySlideOrientationState == SliderVertical) {
        if(movepos.ry() < 0)
        {
            if(m_ySlide_LeftOrTop.y() + movepos.ry() < 0)
            {
                m_ySlide_LeftOrTop.setRect(m_nSlideLeftBorderWidth/2.0, 0,
                                           m_nSlideWidth, m_nSlideHeight);
                m_ySlide_LeftOrTop.setY(0);
                m_ySlide_LeftOrTop.setSize(QSizeF(m_nSlideWidth, m_nSlideHeight));
            } else {
                m_ySlide_LeftOrTop.setRect(m_nSlideLeftBorderWidth/2.0, m_ySlide_LeftOrTop.y() + movepos.ry(),
                                           m_nSlideWidth, m_nSlideHeight);
            }
            m_ySlide_RightOrBottom.setRect(m_nSlideRightBorderWidth/2.0,
                                           m_ySlide_LeftOrTop.top() + m_nSliderDistance - m_nSlideHeight,
                                           m_nSlideWidth, m_nSlideHeight);

            UpdateBackgroundSlide();
        } else if(movepos.ry() > 0)
        {
            if(m_ySlide_RightOrBottom.y() + m_ySlide_RightOrBottom.width() + movepos.ry() > this->height())
            {
                m_ySlide_RightOrBottom.setRect(m_nSlideRightBorderWidth/2.0,
                                               this->height() - m_ySlide_RightOrBottom.height(),
                                               m_nSlideWidth, m_nSlideHeight);
            } else {
                m_ySlide_RightOrBottom.setRect(m_nSlideRightBorderWidth/2.0,
                                               m_ySlide_RightOrBottom.y() + movepos.ry(),
                                               m_nSlideWidth, m_nSlideHeight);
            }
            m_ySlide_LeftOrTop.setRect(m_nSlideLeftBorderWidth/2.0,
                                       m_ySlide_RightOrBottom.bottom() - m_nSliderDistance,
                                       m_nSlideWidth, m_nSlideHeight);

            UpdateBackgroundSlide();
        }
    }
}

void CatDoubleSlider::UpdateOrientation()
{
    if(m_ySlideOrientationState == OrientationState::SliderHorizontal)
    {
        m_yBackground_Rect.setRect(static_cast<qreal>(m_nSlideWidth)/2.0,
                           (this->height() - m_nBackgroundHeight)/2.0,
                           this->width() - m_nSlideWidth,
                           m_nBackgroundHeight);
        UpdateSlideCoordinates();
    } else if(m_ySlideOrientationState == OrientationState::SliderVertical)
    {
        m_yBackground_Rect.setRect((this->width() - m_nBackgroundHeight)/2.0,
                           static_cast<qreal>(m_nSlideHeight)/2.0,
                           m_nBackgroundHeight,
                           this->height() - m_nSlideHeight);
        UpdateSlideCoordinates();
    }
}

void CatDoubleSlider::UpdateFirstSecond()
{
    qreal width = 0;
    qreal first = 0;
    qreal second = 0;
    if(m_nFrom < m_nTo)
    {
        if(m_ySlideOrientationState == SliderHorizontal)
        {
            width = this->width() - m_nSlideWidth;
            first = (m_ySlide_LeftOrTop.left()/width)*(m_nTo - m_nFrom);
            second = (m_ySlide_RightOrBottom.left()/width)*(m_nTo - m_nFrom);
        } else {
            width = this->height() - m_nSlideHeight;
            first = (m_ySlide_LeftOrTop.top()/width)*(m_nTo - m_nFrom);
            second = (m_ySlide_RightOrBottom.top()/width)*(m_nTo - m_nFrom);
        }
    } else if(m_nFrom > m_nTo)
    {
        if(m_ySlideOrientationState == SliderHorizontal)
        {
            width = this->width() - m_nSlideWidth;
            first = m_nFrom - (m_ySlide_LeftOrTop.left()/width)*(m_nFrom - m_nTo);
            second = m_nFrom - (m_ySlide_RightOrBottom.left()/width)*(m_nFrom - m_nTo);
        } else {
            width = this->height() - m_nSlideHeight;
            first = m_nFrom - (m_ySlide_LeftOrTop.top()/width)*(m_nFrom - m_nTo);
            second = m_nFrom - (m_ySlide_RightOrBottom.top()/width)*(m_nFrom - m_nTo);
        }
    }

    if(m_nFirst != first || m_nSecond != second)
    {
        m_nFirst = first;
        m_nSecond = second;
        emit UpdateFirstSeconded(m_nFirst, m_nSecond);
    }
}

void CatDoubleSlider::UpdateSlideCoordinates()
{
    if(m_ySlideOrientationState == SliderHorizontal)
    {
        qreal width = this->width() - m_nSlideWidth;
        m_ySlide_LeftOrTop.setRect(m_nFirst/(m_nTo - m_nFrom)*width,
                                   (this->height() - m_nSlideHeight)/2.0,
                                   m_nSlideWidth, m_nSlideHeight);
        m_ySlide_RightOrBottom.setRect(m_nSecond/(m_nTo - m_nFrom)*width,
                                       (this->height() - m_nSlideHeight)/2.0,
                                       m_nSlideWidth, m_nSlideHeight);
    } else {
        qreal width = this->height() - m_nSlideHeight;
        m_ySlide_LeftOrTop.setRect((this->width() - m_nSlideWidth)/2.0,
                                   m_nFirst/(m_nTo - m_nFrom)*width,
                                   m_nSlideWidth, m_nSlideHeight);
        m_ySlide_RightOrBottom.setRect((this->width() - m_nSlideWidth)/2.0,
                                       m_nSecond/(m_nTo - m_nFrom)*width,
                                       m_nSlideWidth, m_nSlideHeight);
    }

    UpdateBackgroundSlide();
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
    m_cCurrentSlideLeftColor = m_cSlideLeftColor;
    update();
}

void CatDoubleSlider::setSlideRightColor(QBrush brush)
{
    m_cSlideRightColor = brush;
    m_cCurrentSlideRightColor = m_cSlideRightColor;
    update();
}

void CatDoubleSlider::setBackgroundRectColor(QBrush brush)
{
    m_cBackgroundRectColor = brush;
    m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
    update();
}

void CatDoubleSlider::setBackgroundSlideRectColor(QBrush brush)
{
    m_cBackgroundSlideRectColor = brush;
    m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
    update();
}

void CatDoubleSlider::setSlideLeftBorderColor(QBrush color)
{
    m_cSlideLeftBorderColor = color;
    m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
    update();
}

void CatDoubleSlider::setSlideRightBorderColor(QBrush color)
{
    m_cSlideRightBorderColor = color;
    m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
    update();
}

void CatDoubleSlider::setBackgroundRectBorderColor(QBrush color)
{
    m_cBackgroundRectBorderColor = color;
    m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
    update();
}

void CatDoubleSlider::setBackgroundSlideRectBorderColor(QBrush color)
{
    m_cBackgroundSlideRectBorderColor = color;
    m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
    update();
}

void CatDoubleSlider::setHoverSlideLeftColor(QBrush brush)
{
    m_cHoverSlideLeftColor = brush;
    update();
}

void CatDoubleSlider::setHoverSlideRightColor(QBrush brush)
{
    m_cHoverSlideRightColor = brush;
    update();
}

void CatDoubleSlider::setHoverBackgroundRectColor(QBrush brush)
{
    m_cHoverBackgroundRectColor = brush;
    update();
}

void CatDoubleSlider::setHoverBackgroundSlideRectColor(QBrush brush)
{
    m_cHoverBackgroundSlideRectColor = brush;
    update();
}

void CatDoubleSlider::setHoverSlideLeftBorderColor(QBrush color)
{
    m_cHoverSlideLeftBorderColor = color;
    update();
}

void CatDoubleSlider::setHoverSlideRightBorderColor(QBrush color)
{
    m_cHoverSlideRightBorderColor = color;
    update();
}

void CatDoubleSlider::setHoverBackgroundRectBorderColor(QBrush color)
{
    m_cHoverBackgroundRectBorderColor = color;
    update();
}

void CatDoubleSlider::setHoverBackgroundSlideRectBorderColor(QBrush color)
{
    m_cHoverBackgroundSlideRectBorderColor = color;
    update();
}

void CatDoubleSlider::setPressSlideLeftColor(QBrush brush)
{
    m_cPressSlideLeftColor = brush;
    update();
}

void CatDoubleSlider::setPressSlideRightColor(QBrush brush)
{
    m_cPressSlideRightColor = brush;
    update();
}

void CatDoubleSlider::setPressBackgroundRectColor(QBrush brush)
{
    m_cPressBackgroundRectColor = brush;
    update();
}

void CatDoubleSlider::setPressBackgroundSlideRectColor(QBrush brush)
{
    m_cPressBackgroundSlideRectColor = brush;
    update();
}

void CatDoubleSlider::setPressSlideLeftBorderColor(QBrush color)
{
    m_cPressSlideLeftBorderColor = color;
    update();
}

void CatDoubleSlider::setPressSlideRightBorderColor(QBrush color)
{
    m_cPressSlideRightBorderColor = color;
    update();
}

void CatDoubleSlider::setPressBackgroundRectBorderColor(QBrush color)
{
    m_cPressBackgroundRectBorderColor = color;
    update();
}

void CatDoubleSlider::setPressBackgroundSlideRectBorderColor(QBrush color)
{
    m_cPressBackgroundSlideRectBorderColor = color;
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
    emit SlideWidthChanged(width);
    update();
}

void CatDoubleSlider::setSlideHeight(qreal height)
{
    m_nSlideHeight = height;
    emit SlideHeightChanged(height);
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

void CatDoubleSlider::setSliderDataType(CatDoubleSlider::SliderDataTypes type)
{
    m_ySliderDataType = type;
    emit SliderDataTypeChanged(type);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
void CatDoubleSlider::enterEvent(QEnterEvent *event)
#else
void CatDoubleSlider::enterEvent(QEvent *event)
#endif
{
    Q_UNUSED(event)
}

void CatDoubleSlider::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_cCurrentSlideLeftColor = m_cSlideLeftColor;
    m_cCurrentSlideRightColor = m_cSlideRightColor;
    m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
    m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
    m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
    m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
    m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
    m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
    update();
}

void CatDoubleSlider::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    update();
}

void CatDoubleSlider::mouseMoveEvent(QMouseEvent *event)
{
    QPainterPath slideLeftOrTopPath;
    QPainterPath slideRightOrBottomPath;
    QPainterPath backgroundSlideRectPath;
    slideLeftOrTopPath.addRoundedRect(m_ySlide_LeftOrTop, m_nSlideRadius, m_nSlideRadius);
    slideRightOrBottomPath.addRoundedRect(m_ySlide_RightOrBottom, m_nSlideRadius, m_nSlideRadius);
    backgroundSlideRectPath.addRoundedRect(m_yBackgroundSlide_Rect, m_nBackgroundRadius, m_nBackgroundRadius);

    if(m_ySelectStyle == NotSelect)
    {
        if(slideLeftOrTopPath == slideRightOrBottomPath &&
                (slideLeftOrTopPath.contains(event->pos()) ||
                 slideRightOrBottomPath.contains(event->pos()))
                )
        {
            if(m_yLastSelectStyle == LeftOrTopSelect)
            {
                m_cCurrentSlideLeftColor = m_cHoverSlideLeftColor;
                m_cCurrentSlideLeftBorderColor = m_cHoverSlideLeftBorderColor;
                m_cCurrentSlideRightColor = m_cSlideRightColor;
                m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
                m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
                m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
                m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
                m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
            } else if(m_yLastSelectStyle == RightOrBottomSelect){
                m_cCurrentSlideRightColor = m_cHoverSlideRightColor;
                m_cCurrentSlideRightBorderColor = m_cHoverSlideRightBorderColor;
                m_cCurrentSlideLeftColor = m_cSlideLeftColor;
                m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
                m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
                m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
                m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
                m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
            }
        } else if(slideLeftOrTopPath.contains(event->pos()))
        {
            m_cCurrentSlideLeftColor = m_cHoverSlideLeftColor;
            m_cCurrentSlideLeftBorderColor = m_cHoverSlideLeftBorderColor;
            m_cCurrentSlideRightColor = m_cSlideRightColor;
            m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
            m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
            m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
            m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
            m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
        } else if(slideRightOrBottomPath.contains(event->pos()))
        {
            m_cCurrentSlideRightColor = m_cHoverSlideRightColor;
            m_cCurrentSlideRightBorderColor = m_cHoverSlideRightBorderColor;
            m_cCurrentSlideLeftColor = m_cSlideLeftColor;
            m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
            m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
            m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
            m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
            m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
        } else if(backgroundSlideRectPath.contains(event->pos()))
        {
            m_cCurrentBackgroundSlideRectColor = m_cHoverBackgroundSlideRectColor;
            m_cCurrentBackgroundSlideRectBorderColor = m_cHoverBackgroundSlideRectBorderColor;
            m_cCurrentSlideLeftColor = m_cSlideLeftColor;
            m_cCurrentSlideRightColor = m_cSlideRightColor;
            m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
            m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
            m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
            m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
        } else {
            if(m_bMousePress == false)
            {
                m_cCurrentSlideLeftColor = m_cSlideLeftColor;
                m_cCurrentSlideRightColor = m_cSlideRightColor;
                m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
                m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
                m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
                m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
                m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
                m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
            }
        }
    } else {
        if(m_bMousePress == false)
        {
            m_cCurrentSlideLeftColor = m_cSlideLeftColor;
            m_cCurrentSlideRightColor = m_cSlideRightColor;
            m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
            m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
            m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
            m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
            m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
            m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
        }
    }

    if(m_nFrom != m_nTo)
    {
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

        if(m_ySelectStyle != NotSelect)
        {
            UpdateFirstSecond();
        }
    }

    m_pPressPoint = event->pos();
    update();
}

void CatDoubleSlider::mousePressEvent(QMouseEvent *event)
{
    m_bMousePress = true;
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

    if(slideLeftOrTopPath == slideRightOrBottomPath &&
            (slideLeftOrTopPath.contains(event->pos()) ||
             slideRightOrBottomPath.contains(event->pos()))
            )
    {
        if(m_yLastSelectStyle == NotSelect)
        {
            m_ySelectStyle = LeftOrTopSelect;
        } else {
            m_ySelectStyle = m_yLastSelectStyle;
        }
    } else if(slideLeftOrTopPath.contains(event->pos()))
    {
        m_ySelectStyle = LeftOrTopSelect;
        m_yLastSelectStyle = m_ySelectStyle;
    } else if(slideRightOrBottomPath.contains(event->pos()))
    {
        m_ySelectStyle = RightOrBottomSelect;
        m_yLastSelectStyle = m_ySelectStyle;
    } else if(backgroundSlideRectPath.contains(event->pos()))
    {
        m_ySelectStyle = BackgroundSlideSelect;
    }

    switch (m_ySelectStyle) {
        case LeftOrTopSelect: {
            m_cCurrentSlideLeftColor = m_cPressSlideLeftColor;
            m_cCurrentSlideLeftBorderColor = m_cPressSlideLeftBorderColor;
            break;
        }
        case RightOrBottomSelect: {
            m_cCurrentSlideRightColor = m_cPressSlideRightColor;
            m_cCurrentSlideRightBorderColor = m_cPressSlideRightBorderColor;
            break;
        }
        case BackgroundSlideSelect: {
            m_cCurrentBackgroundSlideRectColor = m_cPressBackgroundSlideRectColor;
            m_cCurrentBackgroundSlideRectBorderColor = m_cPressBackgroundSlideRectBorderColor;
            break;
        }
        default:{
            m_cCurrentSlideLeftColor = m_cSlideLeftColor;
            m_cCurrentSlideRightColor = m_cSlideRightColor;
            m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
            m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
            m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
            m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
            m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
            m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
            break;
        }
    }
    emit SliderPress();
    update();
}

void CatDoubleSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_bMousePress = false;
    m_ySelectStyle = NotSelect;
    m_cCurrentSlideLeftColor = m_cSlideLeftColor;
    m_cCurrentSlideRightColor = m_cSlideRightColor;
    m_cCurrentBackgroundRectColor = m_cBackgroundRectColor;
    m_cCurrentBackgroundSlideRectColor = m_cBackgroundSlideRectColor;
    m_cCurrentSlideLeftBorderColor = m_cSlideLeftBorderColor;
    m_cCurrentSlideRightBorderColor = m_cSlideRightBorderColor;
    m_cCurrentBackgroundRectBorderColor = m_cBackgroundRectBorderColor;
    m_cCurrentBackgroundSlideRectBorderColor = m_cBackgroundSlideRectBorderColor;
    this->mouseMoveEvent(event);

    emit SliderRelease();
    update();
}

void CatDoubleSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    UpdateOrientation();
    QPainter painter(this);
    Painter_Background_Rect(&painter);
    Painter_BackgroundSlide_Rect(&painter);
    switch (m_yLastSelectStyle) {
    case LeftOrTopSelect: {
        Painter_Slide_RightOrBottom(&painter);
        Painter_Slide_LeftOrTop(&painter);

        break;
    }
    case RightOrBottomSelect: {
        Painter_Slide_LeftOrTop(&painter);
        Painter_Slide_RightOrBottom(&painter);
        break;
    }
    default:{
        Painter_Slide_LeftOrTop(&painter);
        Painter_Slide_RightOrBottom(&painter);
        break;
    }
    }
}

bool CatDoubleSlider::eventFilter(QObject *o, QEvent *e)
{
    qDebug() << o->objectName();
    return QWidget::eventFilter(o, e);
}
