#include "CatGraphicsView.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScale>

CatGraphicsView::CatGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    InitProperty();
}

CatGraphicsView::~CatGraphicsView()
{

}

void CatGraphicsView::ScaleZoomIn()
{

    scale(1.2, 1.2);
}

void CatGraphicsView::ScaleZoomOut()
{

    scale(1 / 1.2, 1 / 1.2);
}

void CatGraphicsView::Reset()
{
    //this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    QMatrix q;
    q.setMatrix(1, matrix().m12(), matrix().m21(),1, matrix().dx(), matrix().dy());
    setMatrix(q,false);
}

void CatGraphicsView::InitProperty()
{
    //this->setDragMode(QGraphicsView::RubberBandDrag);
    m_bPress = false;
    scale(1.0 , 1.0);
}

void CatGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void CatGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void CatGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
