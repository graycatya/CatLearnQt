#include "CatDoubleSlider.h"
#include <QPainter>
#include <QPainterPath>

CatDoubleSlider::CatDoubleSlider(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
    InitProperty();
}

CatDoubleSlider::~CatDoubleSlider()
{

}

void CatDoubleSlider::InitUi()
{

}

void CatDoubleSlider::InitProperty()
{
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
}

void CatDoubleSlider::Painter_Background_Rect(QPainter *painter)
{
    Q_UNUSED(painter)
}

void CatDoubleSlider::Painter_BackgroundSlide_Rect(QPainter *painter)
{
    Q_UNUSED(painter)
}

void CatDoubleSlider::Painter_Slide_LeftOrTop(QPainter *painter)
{
    Q_UNUSED(painter)
}

void CatDoubleSlider::Painter_Slide_RightOrBottom(QPainter *painter)
{
    Q_UNUSED(painter)
}

void CatDoubleSlider::setSlideLeftOrTopWidth(int width)
{
    m_ySlide_LeftOrTop.setWidth(width);
    update();
}

void CatDoubleSlider::setSlideLeftOrTopHeight(int height)
{
    m_ySlide_LeftOrTop.setHeight(height);
    update();
}

void CatDoubleSlider::setSlideRightOrBottomWidth(int width)
{
    m_ySlide_RightOrBottom.setWidth(width);
    update();
}

void CatDoubleSlider::setSlideRightOrBottomHeight(int height)
{
    m_ySlide_RightOrBottom.setHeight(height);
    update();
}

void CatDoubleSlider::setSlideOrientationState(CatDoubleSlider::OrientationState state)
{
    m_ySlideOrientationState = state;
    update();
}

void CatDoubleSlider::setMySliderStyle(CatDoubleSlider::SliderStyle style)
{
    m_ySliderStyle = style;
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
    Q_UNUSED(event)
}

void CatDoubleSlider::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void CatDoubleSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void CatDoubleSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    Painter_Background_Rect(&painter);
    Painter_BackgroundSlide_Rect(&painter);
    Painter_Slide_LeftOrTop(&painter);
    Painter_Slide_RightOrBottom(&painter);
}
