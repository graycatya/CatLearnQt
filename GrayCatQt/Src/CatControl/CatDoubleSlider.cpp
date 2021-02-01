#include "CatDoubleSlider.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDebug>

#define DEFINEWIDTH 10

CatDoubleSlider::CatDoubleSlider(QWidget *parent)
    : QWidget(parent)
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
    m_ySlide_LeftOrTop.setRect(0.0, 0.0, DEFINEWIDTH, DEFINEWIDTH);
    m_ySlide_RightOrBottom.setRect(this->width() - DEFINEWIDTH, 0,
                                   DEFINEWIDTH, DEFINEWIDTH);
    m_yBackground_Rect.setRect(static_cast<qreal>(DEFINEWIDTH)/2.0,
                       static_cast<qreal>(DEFINEWIDTH)/4.0 + 0.5,
                       this->width() - DEFINEWIDTH,
                       static_cast<qreal>(DEFINEWIDTH)/2.0);
    m_yBackgroundSlide_Rect.setRect(static_cast<qreal>(DEFINEWIDTH)/2.0,
                                    static_cast<qreal>(DEFINEWIDTH)/4.0 + 0.5,
                                    this->width() - DEFINEWIDTH,
                                    static_cast<qreal>(DEFINEWIDTH)/2.0);
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
    QBrush brush = painter->brush();
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
    QBrush brush = painter->brush();
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
    QBrush brush = painter->brush();
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
    QBrush brush = painter->brush();
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(m_ySlide_RightOrBottom, m_nSlideRadius , m_nSlideRadius);
    painter->restore();
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
    update();
}

void CatDoubleSlider::setMySliderStyle(CatDoubleSlider::SliderStyle style)
{
    m_ySliderStyle = style;
    emit MySliderStyleChanged(style);
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
    QPointF movepos = event->pos() - m_pPressPoint;
    qDebug() << movepos;
    switch (m_ySelectStyle) {
        case LeftOrTopSelect: {
            m_ySlide_LeftOrTop.setX(m_ySlide_LeftOrTop.x() + movepos.rx());
            m_ySlide_LeftOrTop.setSize(QSizeF(DEFINEWIDTH, DEFINEWIDTH));
            break;
        }
        case RightOrBottomSelect: {
            m_ySlide_RightOrBottom.setX(m_ySlide_RightOrBottom.x() + movepos.rx());
            m_ySlide_RightOrBottom.setSize(QSize(DEFINEWIDTH, DEFINEWIDTH));
            break;
        }
        case BackgroundSlideSelect: {
            break;
        }
        default:{
            break;
        }
    }
    qDebug() << m_ySlide_LeftOrTop;
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
