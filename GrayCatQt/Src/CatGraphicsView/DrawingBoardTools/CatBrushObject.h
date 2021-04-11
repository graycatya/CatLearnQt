#ifndef CATBRUSHOBJECT_H
#define CATBRUSHOBJECT_H

#include <QPainterPath>
#include <QObject>

class CatBrushObject
{
public:
    enum BrushMode {
        PenBrushMode,
        EraserMode
    };
    CatBrushObject(const QPointF &point)
    {
        m_yPath.moveTo(point);
    }

    int ElementCount()
    {
        return m_yPath.elementCount();
    }

    void CreateNewpath()
    {
        QPointF endPoint;
        endPoint = m_yPath.currentPosition();
        m_yPath &= QPainterPath();
        m_yPath.moveTo(endPoint);
    }

    QPainterPath &GetPath()
    {
        return m_yPath;
    }

    void AddToPath(const QPointF &point1, const QPointF &point2)
    {
        QPointF tempPt1 = point1;
        QPointF tempPt2 = point2;
        QPointF d = tempPt2 - tempPt1;
        //   判断绝对值
        if(qAbs(d.x()) > 0 || qAbs(d.y()) > 0)
        {
            // 在当前点和带有(cx, cy)指定的控制点的端点(endPointX, endPointY)之间添加一条二次Bezier曲线。
            m_yPath.quadTo(tempPt1, (tempPt1 + tempPt2) / 2);
        }

        QRectF r(point1, point2);
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

    QRectF upateRect()
    {
        return m_yUpdateRect;
    }

private:
    QPainterPath m_yPath;
    QPainterPath m_yRealPath;

    QRectF m_yUpdateRect;

};

#endif // CATBRUSHOBJECT_H
