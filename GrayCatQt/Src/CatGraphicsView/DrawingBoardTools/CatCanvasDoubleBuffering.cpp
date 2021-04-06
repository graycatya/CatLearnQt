#include "CatCanvasDoubleBuffering.h"

CatCanvasDoubleBuffering::CatCanvasDoubleBuffering(const QSizeF &size, QGraphicsObject *parent)
    : QGraphicsObject(parent)
    , m_ySize(size)
{
    InitProperty();
    InitCanvas();
}

CatCanvasDoubleBuffering::~CatCanvasDoubleBuffering()
{
    if(m_pBufferingPainter != nullptr)
    {
        delete m_pBufferingPainter;
        m_pBufferingPainter = nullptr;
    }

    if(m_pBufferingCanvas != nullptr)
    {
        delete m_pBufferingCanvas;
        m_pBufferingCanvas = nullptr;
    }
}

void CatCanvasDoubleBuffering::Clear()
{
    m_pBufferingCanvas->fill(Qt::transparent);
    this->update();
}

void CatCanvasDoubleBuffering::DrawToBuffering(CatLineObject *object)
{
    // 如果enabled为true，则渲染提示提示为启用;否则将被禁用。
    m_pBufferingPainter->setRenderHint(QPainter::Antialiasing, true);
    m_pBufferingPainter->setCompositionMode(QPainter::CompositionMode_Source);
    m_pBufferingPainter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_pBufferingPainter->fillPath(object->StrokePath(5), Qt::red);
    this->update(object->upateRect());
}

QRectF CatCanvasDoubleBuffering::boundingRect() const
{
    return  QRectF(0,0,m_ySize.width(),m_ySize.height());
}

void CatCanvasDoubleBuffering::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(0,0,*m_pBufferingCanvas);
}

void CatCanvasDoubleBuffering::InitProperty()
{
    /*
     * 缓存是在绘制设备级别的设备坐标中启用的。
     * 此模式适用于可以移动但不旋转、缩放或剪切的项目。
     * 如果条目被直接或间接转换，缓存将自动重新生成。
     * 与ItemCoordinateCacheMode不同，
     * DeviceCoordinateCache总是以最高质量呈现。
    */
    setCacheMode(DeviceCoordinateCache);
}

void CatCanvasDoubleBuffering::InitCanvas()
{
    /*
     * 图像存储使用预乘32位ARGB格式(0xAARRGGBB)，
     * 即红色、绿色和蓝色通道乘以alpha分量除以255。
     * (如果RR、GG或BB的值高于alpha通道，则结果是未定义的。)
     * 某些操作(例如使用alpha混合的图像合成)使用预乘ARGB32比使用普通ARGB32更快。
    */
    m_pBufferingCanvas = new QImage(m_ySize.toSize(), QImage::Format_ARGB32_Premultiplied);
    m_pBufferingCanvas->fill(Qt::transparent);
    m_pBufferingPainter = new QPainter(m_pBufferingCanvas);
}
