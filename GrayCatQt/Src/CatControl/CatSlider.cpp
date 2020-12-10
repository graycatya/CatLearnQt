#include "CatSlider.h"
#include <QPushButton>

CatSlider::CatSlider(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
    InitProperty();
    InitConnect();
}

CatSlider::~CatSlider()
{

}

void CatSlider::InitUi()
{
    m_pSliderBackGround = new QWidget(this);
    m_pSliderMoveBackGround = new QWidget(this);
    m_pHeadSliding = new QPushButton(this);
    m_pTailSliding = new QPushButton(this);
}

void CatSlider::InitProperty()
{

}

void CatSlider::InitConnect()
{

}

void CatSlider::resizeEvent(QResizeEvent *event)
{

}

void CatSlider::showEvent(QShowEvent *event)
{

}

void CatSlider::mouseMoveEvent(QMouseEvent *event)
{

}

void CatSlider::mousePressEvent(QMouseEvent *event)
{

}

void CatSlider::mouseReleaseEvent(QMouseEvent *event)
{

}
