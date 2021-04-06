#ifndef CATCANVASDOUBLEBUFFERING_H
#define CATCANVASDOUBLEBUFFERING_H

#include <QGraphicsObject>
#include <QPainter>

#include "CatLineObject.h"

/*
 * 双缓冲实现类
*/
class CatCanvasDoubleBuffering : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CatCanvasDoubleBuffering(const QSizeF & size, QGraphicsObject *parent = nullptr);
    ~CatCanvasDoubleBuffering();

    void Clear();                           // 清空画布
    void DrawToBuffering(CatLineObject *object); // 在临时层绘图

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void InitProperty();
    void InitCanvas();  // 初始化图层

private:
    QSizeF m_ySize;
    QImage *m_pBufferingCanvas;     // 临时画布
    QPainter *m_pBufferingPainter;  // 临时画布的painter
};

#endif // CATCANVASDOUBLEBUFFERING_H
