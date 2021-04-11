#ifndef CATBRUSHPIXBUFFERITEM_H
#define CATBRUSHPIXBUFFERITEM_H

#include <QGraphicsPixmapItem>

#include <QPainter>

#include "CatBrushObject.h"

class CatBrushPixBufferItem : public QGraphicsPixmapItem
{
public:
    explicit CatBrushPixBufferItem(QGraphicsItem *parent = nullptr);
    ~CatBrushPixBufferItem();

    void Clear();
    void DrawToBuffer(CatBrushObject *object);

    void InitSizeRect(QRectF size);
    void UpdateSizeRect(QRectF size);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void InitProperty();
    void InitBrush();

private:
    QRectF m_ySizeRect;
    QRectF m_yLastSizeRect;

    QPixmap *m_pBufferBrush;
    QPainter *m_pBufferPainter;
};

#endif // CATBRUSHPIXBUFFERITEM_H
