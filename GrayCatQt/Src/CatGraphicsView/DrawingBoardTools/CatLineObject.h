#ifndef CATLINEOBJECT_H
#define CATLINEOBJECT_H

#include <QPainterPath>
#include <QObject>

class CatLineObject
{
public:
    CatLineObject(const QPointF &point)
    {
        m_yPath.moveTo(point);
    }

    int elementCount()
    {
        // 返回 绘制器路径中路径元素的数量
        return m_yPath.elementCount();
    }

    void createNewPath()
    {
        QPointF endPoint;
        // currentPosition 返回路径的当前位置
        endPoint = m_yPath.currentPosition();
        m_yPath &= QPainterPath();
        m_yPath.moveTo(endPoint);
    }

    void createNewRealPath()
    {
        m_yRealPath &= QPainterPath();
    }

    QPainterPath& Path()
    {
        return m_yPath;
    }

    void addToPath(const QPointF &p1, const QPointF &p2)
    {
        QPointF pt1 = p1;
        QPointF pt2 = p2;
        QPointF d = pt2 - pt1;
        //   判断绝对值
        if(qAbs(d.x()) > 0 || qAbs(d.y()) > 0)
        {
            // 在当前点和带有(cx, cy)指定的控制点的端点(endPointX, endPointY)之间添加一条二次Bezier曲线。
            m_yPath.quadTo(pt1,(pt1+pt2)/2);
        }

        QRectF r(p1, p2);
        // 返回一个规格化矩形;即，具有非负宽和高的矩形。
        QRectF fixRect = r.normalized();
        /*
         *  QRect QRect::adjusted(int dx1, int dy1, int dx2, int dy2) const
         *  返回一个新的矩形，分别在该矩形的现有坐标上添加dx1、dy1、dx2和dy2。
         */
        m_yUpdateRect = fixRect.adjusted(-200,-200,400,400);
        m_yRealPath.addPath(m_yPath);
    }

    QPainterPath StrokePath(int width)
    {
        // QPainterPathStroker类用于生成可填写的画家为给定路径的轮廓
        QPainterPathStroker stroker;
        stroker.setWidth(width);
        stroker.setCapStyle(Qt::RoundCap);
        stroker.setJoinStyle(Qt::RoundJoin);
        return stroker.createStroke(m_yPath);
    }

    QPainterPath StrokeRealPath(int width)
    {
        // QPainterPathStroker类用于生成可填写的画家为给定路径的轮廓
        QPainterPathStroker stroker;
        stroker.setWidth(width);
        stroker.setCapStyle(Qt::RoundCap);
        stroker.setJoinStyle(Qt::RoundJoin);
        return stroker.createStroke(m_yRealPath);
    }

    QRectF upateRect()
    {
        return m_yUpdateRect;
    }

private:
    QPainterPath m_yPath;       // 路径
    QPainterPath m_yRealPath;   // 实际路径
    QRectF m_yUpdateRect;
};

#endif // CATLINEOBJECT_H
