#ifndef CATGRAPHICPEN_H
#define CATGRAPHICPEN_H

#include <QGraphicsItem>
#include "AbsDrawingBoardBase.h"


class CatGraphicPen : public AbsDrawingBoardBase, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit CatGraphicPen(QGraphicsItem *parent = nullptr);
    ~CatGraphicPen();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

};

#endif // CATGRAPHICPEN_H
