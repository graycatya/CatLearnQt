#include "CatGraphicsView.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScale>
#include <QGLWidget>
#include "CatGraphicsScene.h"

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
    this->setCacheMode(QGraphicsView::CacheBackground);
}

void CatGraphicsView::mousePressEvent(QMouseEvent *event)
{
    m_bPress = true;
    QPointF point = this->mapToScene(event->pos());
    lastPoint = point;
    dynamic_cast<CatGraphicsScene*>(this->scene())->mousePressEventPenState(point);
    QGraphicsView::mousePressEvent(event);
}

void CatGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bPress)
    {
        qDebug() << "CatGraphicsView::mouseMoveEvent";
        QPointF point = this->mapToScene(event->pos());
        dynamic_cast<CatGraphicsScene*>(this->scene())->mouseMoveEventPenState(lastPoint, point);
        lastPoint = point;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void CatGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPress = false;
    QPointF point = this->mapToScene(event->pos());
    dynamic_cast<CatGraphicsScene*>(this->scene())->mouseReleaseEventPenState(point);
    QGraphicsView::mouseReleaseEvent(event);
}
