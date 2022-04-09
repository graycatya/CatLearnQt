#include "ImageToolBase.h"
#include "ProcessObject.h"
#include <QApplication>
#include <QDebug>

ImageToolBase::ImageToolBase(QWidget *parent)
    : QWidget(parent)
    , m_pParent(parent)
    , m_pButtonTool(nullptr)
    , m_pScreen(nullptr)
    , m_pFullScreen(nullptr)
    , m_pBackgroundScreen(nullptr)
    , m_qMovePos(QPoint(-1, -1))
    , m_bLight(true)
    , m_bCut(false)
    , m_bInit(false)
{
    /*this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAutoFillBackground(true);*/
    /*QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);*/
    //setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
    //获得DPI缩放值
    m_screenDpi = QApplication::primaryScreen()->devicePixelRatio();
}

ImageToolBase::~ImageToolBase()
{

}

void ImageToolBase::SetLightState(QString state)
{
    this->setProperty("State", state);
    this->setStyle(QApplication::style());
}

void ImageToolBase::SetMaskLayerColor(QColor color)
{
    MaskLayerColor = color;
}

QColor ImageToolBase::GetMaskLayerColor() const
{
    return MaskLayerColor;
}
