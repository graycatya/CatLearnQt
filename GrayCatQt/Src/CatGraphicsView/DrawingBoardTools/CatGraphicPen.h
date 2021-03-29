#ifndef CATGRAPHICPEN_H
#define CATGRAPHICPEN_H

#include <QGraphicsItem>
#include "AbsDrawingBoardBase.h"

struct Bezier {
    QPointF c1;
    QPointF c2;
    QPointF endpoint;
};


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

    void GraphicPenAddPoint(QPointF point);
   // void

private:
    void InitProperty();

    void UpdateRectSize(QPointF point);

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QVector<QLineF> m_pLines;
    QPainterPath m_pBeziner;
    QPointF m_pLastPoint;

};

#endif // CATGRAPHICPEN_H
