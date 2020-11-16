#include "ImageToolBase.h"
#include "ProcessObject.h"
#include <QApplication>
#include <QDebug>

ImageToolBase::ImageToolBase(QWidget *parent)
    : QWidget(parent)
    , m_qMovePos(QPoint(-1, -1))
    , m_pScreen(nullptr)
    , m_pFullScreen(nullptr)
    , m_pBackgroundScreen(nullptr)
    , m_pButtonTool(nullptr)
    , m_bLight(true)
    , m_bCut(false)
    , m_bInit(false)
    , m_pParent(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
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
