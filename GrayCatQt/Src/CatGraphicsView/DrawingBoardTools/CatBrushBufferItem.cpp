#include "CatBrushBufferItem.h"

CatBrushBufferItem::CatBrushBufferItem(QGraphicsObject *parent)
    : QGraphicsObject(parent)
{
    InitProperty();
    InitBrush();
}

CatBrushBufferItem::~CatBrushBufferItem()
{
    if(m_pBufferBrush != nullptr)
    {
        delete m_pBufferBrush;
        m_pBufferBrush = nullptr;
    }

    if(m_pBufferPainter != nullptr)
    {
        delete m_pBufferPainter;
        m_pBufferPainter = nullptr;
    }

}

void CatBrushBufferItem::Clear()
{
    m_pBufferBrush->fill(Qt::transparent);
    this->update();
}

void CatBrushBufferItem::DrawToBuffer(CatLineObject *object)
{
    if(m_pBufferPainter != nullptr)
    {
        m_pBufferPainter->setRenderHint(QPainter::Antialiasing, true);
        m_pBufferPainter->setCompositionMode(QPainter::CompositionMode_Source);
        m_pBufferPainter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        m_pBufferPainter->fillPath(object->StrokePath(5), Qt::red);
        this->update(object->upateRect());
    }
}

void CatBrushBufferItem::SetSizeRect(QRectF size)
{
    m_yLastSizeRect = m_ySizeRect;
    m_ySizeRect = size;

    if(m_pBufferBrush != nullptr)
    {
        delete m_pBufferBrush;
        m_pBufferBrush = nullptr;
    }

    if(m_pBufferPainter != nullptr)
    {
        delete m_pBufferPainter;
        m_pBufferPainter = nullptr;
    }

    m_pBufferBrush = new QImage(m_ySizeRect.size().toSize(),
                                QImage::Format_ARGB32_Premultiplied);
    m_pBufferBrush->fill(Qt::transparent);
    m_pBufferPainter = new QPainter(m_pBufferBrush);
}

QRectF CatBrushBufferItem::boundingRect() const
{
    return m_ySizeRect;
}

void CatBrushBufferItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if(m_pBufferBrush != nullptr)
    {
        painter->drawImage(0, 0, *m_pBufferBrush);
    }
}

void CatBrushBufferItem::InitProperty()
{
    /*
     * 缓存是在绘制设备级别的设备坐标中启用的。
     * 此模式适用于可以移动但不旋转、缩放或剪切的项目。
     * 如果条目被直接或间接转换，缓存将自动重新生成。
     * 与ItemCoordinateCacheMode不同，
     * DeviceCoordinateCache总是以最高质量呈现。
    */
    setCacheMode(DeviceCoordinateCache);

    m_ySizeRect = QRectF(0,0,0,0);
    m_yLastSizeRect = QRectF(0,0,0,0);
}

void CatBrushBufferItem::InitBrush()
{
    /*
     * 图像存储使用预乘32位ARGB格式(0xAARRGGBB)，
     * 即红色、绿色和蓝色通道乘以alpha分量除以255。
     * (如果RR、GG或BB的值高于alpha通道，则结果是未定义的。)
     * 某些操作(例如使用alpha混合的图像合成)使用预乘ARGB32比使用普通ARGB32更快。
    */
    m_pBufferBrush = nullptr;
    m_pBufferPainter = nullptr;
}
