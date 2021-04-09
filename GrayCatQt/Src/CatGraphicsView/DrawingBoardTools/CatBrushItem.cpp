#include "CatBrushItem.h"

CatBrushItem::CatBrushItem(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{
    InitProperty();
    InitBrush();
}

CatBrushItem::~CatBrushItem()
{
    if(m_pRealPainter != nullptr)
    {
        delete m_pRealPainter;
        m_pRealPainter = nullptr;
    }

    if(m_pRealBrush != nullptr)
    {
        delete m_pRealBrush;
        m_pRealBrush = nullptr;
    }
}

void CatBrushItem::DrawPress(int id, const QPointF &point)
{
    CatBrushObject *BrushObject = new CatBrushObject(point);
    //BrushObject->
}

void CatBrushItem::DrawMove(int id, const QPointF &lastPoint, const QPointF &curPoint)
{

}

void CatBrushItem::DrawRelease(int id, const QPointF &point)
{

}

void CatBrushItem::SetBackgroundColor(const QColor &color)
{

}

void CatBrushItem::SetMode(CatBrushObject::BrushMode mode)
{

}

void CatBrushItem::Clear()
{

}

QRectF CatBrushItem::boundingRect() const
{

}

void CatBrushItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void CatBrushItem::InitProperty()
{

}

void CatBrushItem::DrawToReal(CatBrushObject *object)
{

}

void CatBrushItem::InitBrush()
{

}

void CatBrushItem::DoErase(QPointF pos1, QPointF pos2, int width)
{

}

QPainterPath CatBrushItem::CreateStrokePath(const QPointF &pos1, const QPointF &pos2, int width)
{

}
