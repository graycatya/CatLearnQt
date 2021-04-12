#ifndef CATBRUSHOBJECT_H
#define CATBRUSHOBJECT_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QObject>

#include <QDebug>

class CatBrushObject
{
public:
    enum BrushMode {
        PenBrushMode,
        EraserMode
    };
    CatBrushObject(const QPointF &point, QGraphicsItem *parent = nullptr)
    {
        m_yPath.moveTo(point);
        if(parent != nullptr)
        {
            qDebug() << "point - parent->pos(): " << point - parent->boundingRect().topLeft() << "point: " << point << " item pos: " << parent->boundingRect().topLeft();
            m_yPixmapPath.moveTo(point - parent->boundingRect().topLeft());
        }
    }

    int ElementCount()
    {
        return m_yPath.elementCount();
    }

    int ElementPixmapCount()
    {
        return m_yPixmapPath.elementCount();
    }

    void CreateNewpath()
    {
        QPointF endPoint;
        endPoint = m_yPath.currentPosition();
        m_yPath &= QPainterPath();
        m_yPath.moveTo(endPoint);
    }

    void CreateNewPixmapPath()
    {
        QPointF endPoint;
        endPoint = m_yPixmapPath.currentPosition();
        m_yPixmapPath &= QPainterPath();
        m_yPixmapPath.moveTo(endPoint);
    }

    QPainterPath &GetPath()
    {
        return m_yPath;
    }

    QPainterPath &GetPixmapPath()
    {
        return m_yPixmapPath;
    }

    void AddToPath(const QPointF &point1, const QPointF &point2, QGraphicsItem *item = nullptr)
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
        if(item != nullptr)
        {
            tempPt1 = point1 - item->boundingRect().topLeft();
            tempPt2 = point2 - item->boundingRect().topLeft();

            qDebug() << "temp pixmap: " << tempPt1 << " : " << tempPt2;
            d = tempPt2 - tempPt1;
            //   判断绝对值
            if(qAbs(d.x()) > 0 || qAbs(d.y()) > 0)
            {
                // 在当前点和带有(cx, cy)指定的控制点的端点(endPointX, endPointY)之间添加一条二次Bezier曲线。
                m_yPixmapPath.quadTo(tempPt1, (tempPt1 + tempPt2) / 2);
            }

            r = QRectF(tempPt1, tempPt2);
            fixRect = r.normalized();
            m_yUpdatePixmapRect = fixRect.adjusted(-200,-200,400,400);
            m_yRealPixmapPath.addPath(m_yPixmapPath);
        }
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

    QPainterPath StrokePixmapPath(int width)
    {
        // QPainterPathStroker类用于生成可填写的画家为给定路径的轮廓
        QPainterPathStroker stroker;
        stroker.setWidth(width);
        stroker.setCapStyle(Qt::RoundCap);
        stroker.setJoinStyle(Qt::RoundJoin);
        return stroker.createStroke(m_yPixmapPath);
    }

    QRectF UpateRect()
    {
        return m_yUpdateRect;
    }

    QRectF UpatePixmapRect()
    {
        return m_yUpdatePixmapRect;
    }

private:
    QPainterPath m_yPath;
    QPainterPath m_yRealPath;
    QPainterPath m_yPixmapPath;
    QPainterPath m_yRealPixmapPath;

    QRectF m_yUpdateRect;
    QRectF m_yUpdatePixmapRect;

};

#endif // CATBRUSHOBJECT_H
