#include "CatGraphicPen.h"

CatGraphicPen::CatGraphicPen(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

CatGraphicPen::~CatGraphicPen()
{

}

QRectF CatGraphicPen::boundingRect() const
{
    return GetBaseItemSize();
}

void CatGraphicPen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QPainterPath CatGraphicPen::shape() const
{
    QPainterPath path;
    return path;
}

void CatGraphicPen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void CatGraphicPen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void CatGraphicPen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
