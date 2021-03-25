#include "CatGraphicPen.h"

#include <QDebug>

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
    QGraphicsItem::mousePressEvent(event);
    qDebug() << "CatGraphicPen press";
}

void CatGraphicPen::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);

    qDebug() << "CatGraphicPen move";
}

void CatGraphicPen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    qDebug() << "CatGraphicPen release";
}
