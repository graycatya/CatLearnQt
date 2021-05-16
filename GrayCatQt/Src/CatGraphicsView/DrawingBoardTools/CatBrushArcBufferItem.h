#ifndef CATBRUSHARCBUFFERITEM_H
#define CATBRUSHARCBUFFERITEM_H

#include <QGraphicsEllipseItem>

class CatBrushArcBufferItem : public QGraphicsItem
{
public:
    explicit CatBrushArcBufferItem(QGraphicsItem *parent = nullptr);
    ~CatBrushArcBufferItem();
    void SetProperty(QColor background, qreal broad);
    void ArcStart(QRectF, qreal startAngle);
    void ArcUpdate(qreal updateAngle);
    void ArcEnd();

    QRectF GetRectF() const { return m_yRect; }
    qreal GetStartAngle() const { return m_yStartAngle; }
    qreal GetUpdateAngle() const { return m_yUpdateAngle; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    QPainterPath shape() const;

private:
    QRectF m_yRect;
    qreal m_yStartAngle;
    qreal m_yUpdateAngle;
    QColor m_yBackGround;
    qreal m_yBroad;
};

#endif // CATBRUSHARCBUFFERITEM_H
