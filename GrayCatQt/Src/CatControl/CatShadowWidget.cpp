#include "CatShadowWidget.h"
#include <QtMath>
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

CatShadowWidget::CatShadowWidget(QWidget *widget)
    : QWidget(widget)
{

}

CatShadowWidget::~CatShadowWidget()
{

}

void CatShadowWidget::SetShadowColor(QColor color)
{
    ShadowColor = color;
    update();
}

void CatShadowWidget::SetShadowWeight(int weight)
{
    ShadowWeight = weight;
    update();
}

void CatShadowWidget::SetShadowRadius(int radius)
{
    ShadowRadius = radius;
    update();
}

void CatShadowWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(ShadowWeight, ShadowWeight,
                 this->width()-ShadowWeight*2, this->height()-ShadowWeight*2, ShadowRadius, ShadowRadius);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color = ShadowColor;
    for(int i=0; i<ShadowWeight; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(ShadowWeight-i, ShadowWeight-i,
                     this->width()-(ShadowWeight-i)*2,
                     this->height()-(ShadowWeight-i)*2, ShadowRadius, ShadowRadius);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void CatShadowWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
