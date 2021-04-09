#ifndef CATVECTORDRAWING_H
#define CATVECTORDRAWING_H

#include <QGraphicsObject>
#include "CatLineObject.h"

struct PathState {
    QPainterPath DrawPath;
    CatLineObject::CanvasMode Mode;
};

class CatVectorDrawing : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CatVectorDrawing(QGraphicsObject *parent = 0);
    ~CatVectorDrawing();

    void SetPath(const QPainterPath &path);
    QPainterPath VectorPath() { return m_yPath; };
    void DoEraseLine(const QPointF &point1, const QPointF &point2, int width);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE;
    QRectF boundingRect() const;

private:
    QPainterPath CreateStrokePath(const QPointF &p1, const QPointF &p2, int width);

private:
    QPainterPath m_yPath;
    QVector<PathState> m_yDrawPaths;
};

#endif // CATVECTORDRAWING_H
