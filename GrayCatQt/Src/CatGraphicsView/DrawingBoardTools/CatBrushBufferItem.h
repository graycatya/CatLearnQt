#ifndef CATBRUSHBUFFERITEM_H
#define CATBRUSHBUFFERITEM_H

#include <QGraphicsObject>
#include <QPainter>

#include "CatLineObject.h"

class CatBrushBufferItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CatBrushBufferItem(QGraphicsObject *parent = nullptr);
    ~CatBrushBufferItem();

    void Clear();
    void DrawToBuffer(CatLineObject *object);

    void SetSizeRect(QRectF size);
    void SetLastSizeRect(QRectF size);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void InitProperty();
    void InitBrush();

private:
    QRectF m_ySizeRect;
    QRectF m_yLastSizeRect;

    QImage *m_pBufferBrush;
    QPainter *m_pBufferPainter;

};

#endif // CATBRUSHBUFFERITEM_H
