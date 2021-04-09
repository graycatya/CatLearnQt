#ifndef CATCANVASITEM_H
#define CATCANVASITEM_H

#include <QGraphicsObject>

#include "CatLineObject.h"
#include "CatCanvasDoubleBuffering.h"

#define LINEOFVECTOR

class CatCanvasItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CatCanvasItem(const QSizeF &size, QGraphicsObject * parent = nullptr);
    ~CatCanvasItem();

    void DrawPress(int id,const QPointF &point);
    void DrawMove(int id,const QPointF &lastPoint,const QPointF &curPoint);
    void DrawRelease(int id, const QPointF &point);
    void SetBackgroundColor(const QColor & color);
    void SetMode(CatLineObject::CanvasMode mode);

    void Clear();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void InitProperty();
    void ReSize(const QSizeF & size);
    void DrawToReal(CatLineObject * object);  //在真实层绘非矢量图
    void InitCanvas();                     //初始化图层
    void DoErase(QPointF pos1, QPointF pos2, int width);    // 线擦除
    QPainterPath CreateStrokePath(const QPointF &pos1, const QPointF &pos2, int width);


private:
    QSizeF m_ySize;

    CatCanvasDoubleBuffering *m_pCatCanvasDoubleBuffering;

    QImage *m_pRealCancvas;
    QPainter *m_pRealPainter;

    QMap<int, CatLineObject*> m_yLineObjects;

    QColor m_yBgColor;

    CatLineObject::CanvasMode m_yCanvasMode = CatLineObject::DrawMode;
};

#endif // CATCANVASITEM_H
