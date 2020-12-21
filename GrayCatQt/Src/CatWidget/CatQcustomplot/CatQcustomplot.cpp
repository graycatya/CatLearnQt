#include "CatQcustomplot.h"

CatQcustomplot::CatQcustomplot(QWidget *parent)
    : QCustomPlot(parent)
{
    InitProperty();
}

CatQcustomplot::~CatQcustomplot()
{

}

QCPGraph *CatQcustomplot::AddGraph(QPen pen, QString name, QCPScatterStyle style, QCPGraph::LineStyle linestyle)
{
    QCPGraph *graph = this->addGraph();
    graph->setPen(pen);
    graph->setName(name);
    graph->setScatterStyle(style);
    graph->setLineStyle(linestyle);
    return graph;
}

QCPBars *CatQcustomplot::AddBars(int width, QPen pen, QBrush brush, QString name, QCPBars::WidthType type)
{
    QCPBars *bars = new QCPBars(xAxis, yAxis);
    bars->setWidth(width);
    bars->setPen(pen);
    bars->setBrush(brush);
    bars->setWidthType(type);
    bars->setName(name);
    return bars;
}

QStringList CatQcustomplot::ScatterShapeList()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPScatterStyle::ScatterShape>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

QStringList CatQcustomplot::GraphLineStyleList()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPGraph::LineStyle>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

QStringList CatQcustomplot::BarsWidthType()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPBars::WidthType>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

void CatQcustomplot::SetLegenAlignment(int index, Qt::Alignment alignment)
{
    axisRect()->insetLayout()->setInsetAlignment(index, alignment);
}

void CatQcustomplot::InitProperty()
{
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
    setOpenGl(false);
}

void CatQcustomplot::SetBackground(QBrush brush)
{
    setBackground(brush);
}

void CatQcustomplot::SetLegendBackground(QBrush brush)
{
    legend->setBrush(brush);
}

void CatQcustomplot::SetLegendFont(QFont font)
{
    legend->setFont(font);
}

void CatQcustomplot::SetLegendBorder(QPen border)
{
    legend->setBorderPen(border);
}

void CatQcustomplot::SetAxisBasePen_x(QPen pen)
{
    xAxis->setBasePen(pen);
}

void CatQcustomplot::SetAxisBasePenColor_x(QColor color)
{
    QPen pen = xAxis->basePen();
    pen.setColor(color);
    xAxis->setBasePen(pen);
}

void CatQcustomplot::SetAxisBasePen_y(QPen pen)
{
    yAxis->setBasePen(pen);
}

void CatQcustomplot::SetAxisBasePenColor_y(QColor color)
{
    QPen pen = yAxis->basePen();
    pen.setColor(color);
    yAxis->setBasePen(pen);
}

void CatQcustomplot::SetAxisTickPen_x(QPen pen)
{
    xAxis->setTickPen(pen);
}

void CatQcustomplot::SetAxisTickPenColor_x(QColor color)
{
    QPen pen = xAxis->tickPen();
    pen.setColor(color);
    xAxis->setTickPen(pen);
}

void CatQcustomplot::SetAxisTickPen_y(QPen pen)
{
    yAxis->setTickPen(pen);
}

void CatQcustomplot::SetAxisTickPenColor_y(QColor color)
{
    QPen pen = yAxis->tickPen();
    pen.setColor(color);
    yAxis->setTickPen(pen);
}

void CatQcustomplot::SetAxisSubTickPen_x(QPen pen)
{
    xAxis->setSubTickPen(pen);
}

void CatQcustomplot::SetAxisSubTickPenColor_x(QColor color)
{
    QPen pen = xAxis->subTickPen();
    pen.setColor(color);
    xAxis->setSubTickPen(pen);
}

void CatQcustomplot::SetAxisSubTickPen_y(QPen pen)
{
    yAxis->setSubTickPen(pen);
}

void CatQcustomplot::SetAxisSubTickPenColor_y(QColor color)
{
    QPen pen = yAxis->subTickPen();
    pen.setColor(color);
    yAxis->setSubTickPen(pen);
}

void CatQcustomplot::SetAxisGridPen_x(QPen pen)
{
    xAxis->grid()->setPen(pen);
}

void CatQcustomplot::SetAxisGridPenColor_x(QColor color)
{
    QPen pen = xAxis->grid()->pen();
    pen.setColor(color);
    xAxis->grid()->setPen(pen);
}

void CatQcustomplot::SetAxisGridPen_y(QPen pen)
{
    yAxis->grid()->setPen(pen);
}

void CatQcustomplot::SetAxisGridPenColor_y(QColor color)
{
    QPen pen = yAxis->grid()->pen();
    pen.setColor(color);
    yAxis->grid()->setPen(pen);
}

void CatQcustomplot::SetAxisSubGridPen_x(QPen pen)
{
    xAxis->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxisSubGridPenColor_x(QColor color)
{
    QPen pen = xAxis->grid()->subGridPen();
    pen.setColor(color);
    xAxis->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxisSubGridPen_y(QPen pen)
{
    yAxis->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxisSubGridPenColor_y(QColor color)
{
    QPen pen = yAxis->grid()->subGridPen();
    pen.setColor(color);
    yAxis->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxisLabelColor_x(QColor color)
{
    xAxis->setLabelColor(color);
}

void CatQcustomplot::SetAxisLabelColor_y(QColor color)
{
    yAxis->setLabelColor(color);
}

void CatQcustomplot::SetAxisLabelFont_x(QFont font)
{
    xAxis->setLabelFont(font);
}

void CatQcustomplot::SetAxisLabelFont_y(QFont font)
{
    yAxis->setLabelFont(font);
}

void CatQcustomplot::SetAxisTickLabelColor_x(QColor color)
{
    xAxis->setTickLabelColor(color);
}

void CatQcustomplot::SetAxisTickLabelColor_y(QColor color)
{
    yAxis->setTickLabelColor(color);
}

void CatQcustomplot::SetAxisTickLabelFont_x(QFont font)
{
    xAxis->setTickLabelFont(font);
}

void CatQcustomplot::SetAxisTickLabelFont_y(QFont font)
{
    yAxis->setTickLabelFont(font);
}
