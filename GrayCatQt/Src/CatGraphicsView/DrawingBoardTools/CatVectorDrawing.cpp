#include "CatVectorDrawing.h"

CatVectorDrawing::CatVectorDrawing(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{

}

CatVectorDrawing::~CatVectorDrawing()
{

}

void CatVectorDrawing::SetPath(const QPainterPath &path)
{

}

void CatVectorDrawing::DoEraseLine(const QPointF &point1, const QPointF &point2, int width)
{

}

void CatVectorDrawing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

QRectF CatVectorDrawing::boundingRect() const
{
    return QRectF();
}

QPainterPath CatVectorDrawing::CreateStrokePath(const QPointF &p1, const QPointF &p2, int width)
{
    return QPainterPath();
}
