#ifndef CATBRUSHPIXITEM_H
#define CATBRUSHPIXITEM_H

#include <QGraphicsPixmapItem>

#include "CatBrushObject.h"
#include "CatBrushPixBufferItem.h"

class CatBrushPixItem : public QGraphicsPixmapItem
{
public:
    explicit CatBrushPixItem(QGraphicsItem *parent = nullptr);
    ~CatBrushPixItem();

    void DrawPress(int id,const QPointF &point);
    void DrawMove(int id,const QPointF &lastPoint,const QPointF &curPoint);
    void DrawRelease(int id, const QPointF &point);
    void SetBackgroundColor(const QColor & color);
    void SetMode(CatBrushObject::BrushMode mode);
    void SetBrushSize(QRectF size);

    void Clear();

protected:
    QRectF boundingRect() const;

private:
    void InitProperty();
    void DrawToReal(CatBrushObject* object);  //在真实层绘非矢量图
    void InitBrush();                    //初始化图层
    void DoErase(QPointF pos1, QPointF pos2, int width);    // 线擦除
    QPainterPath CreateStrokePath(const QPointF &pos1, const QPointF &pos2, int width);
    void UpdateRectSize(QPointF point);

private:
    QRectF m_ySizeRect;
    QRectF m_yLastSizeRect;

    CatBrushPixBufferItem *m_pCatBrushPixBufferItem;

    QPixmap *m_pRealBrush;
    QPainter *m_pRealPainter;

    QMap<int, CatBrushObject*> m_yBrushObjects;

    QColor m_yBgColor;

    CatBrushObject::BrushMode m_yBrushMode;

    bool m_bFixedSize;

};

#endif // CATBRUSHPIXITEM_H
