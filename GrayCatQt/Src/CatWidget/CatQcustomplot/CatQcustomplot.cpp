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

void CatQcustomplot::SetLegendBorderColor(QColor color)
{
    QPen pen = legend->borderPen();
    pen.setColor(color);
    legend->setBorderPen(pen);
}

void CatQcustomplot::SetLegendTextColor(QColor color)
{
    legend->setTextColor(color);
}

void CatQcustomplot::SetLegendBorderWide(int width)
{
    QPen pen = legend->borderPen();
    pen.setWidth(width);
    legend->setBorderPen(pen);
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

void CatQcustomplot::SetAxis2BasePen_x(QPen pen)
{
    xAxis2->setBasePen(pen);
}

void CatQcustomplot::SetAxis2BasePenColor_x(QColor color)
{
    QPen pen = xAxis2->basePen();
    pen.setColor(color);
    xAxis2->setBasePen(pen);
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

void CatQcustomplot::SetAxis2BasePen_y(QPen pen)
{
    yAxis2->setBasePen(pen);
}

void CatQcustomplot::SetAxis2BasePenColor_y(QColor color)
{
    QPen pen = yAxis2->basePen();
    pen.setColor(color);
    yAxis2->setBasePen(pen);
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

void CatQcustomplot::SetAxis2TickPen_x(QPen pen)
{
    xAxis2->setTickPen(pen);
}

void CatQcustomplot::SetAxis2TickPenColor_x(QColor color)
{
    QPen pen = xAxis2->tickPen();
    pen.setColor(color);
    xAxis2->setTickPen(pen);
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

void CatQcustomplot::SetAxis2TickPen_y(QPen pen)
{
    yAxis2->setTickPen(pen);
}

void CatQcustomplot::SetAxis2TickPenColor_y(QColor color)
{
    QPen pen = yAxis2->tickPen();
    pen.setColor(color);
    yAxis2->setTickPen(pen);
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

void CatQcustomplot::SetAxis2SubTickPen_x(QPen pen)
{
    xAxis2->setSubTickPen(pen);
}

void CatQcustomplot::SetAxis2SubTickPenColor_x(QColor color)
{
    QPen pen = xAxis2->subTickPen();
    pen.setColor(color);
    xAxis2->setSubTickPen(pen);
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

void CatQcustomplot::SetAxis2SubTickPen_y(QPen pen)
{
    yAxis2->setSubTickPen(pen);
}

void CatQcustomplot::SetAxis2SubTickPenColor_y(QColor color)
{
    QPen pen = yAxis2->subTickPen();
    pen.setColor(color);
    yAxis2->setSubTickPen(pen);
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

void CatQcustomplot::SetAxis2GridPen_x(QPen pen)
{
    xAxis2->grid()->setPen(pen);
}

void CatQcustomplot::SetAxis2GridPenColor_x(QColor color)
{
    QPen pen = xAxis2->grid()->pen();
    pen.setColor(color);
    xAxis2->grid()->setPen(pen);
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

void CatQcustomplot::SetAxis2GridPen_y(QPen pen)
{
    yAxis2->grid()->setPen(pen);
}

void CatQcustomplot::SetAxis2GridPenColor_y(QColor color)
{
    QPen pen = yAxis2->grid()->pen();
    pen.setColor(color);
    yAxis2->grid()->setPen(pen);
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

void CatQcustomplot::SetAxis2SubGridPen_x(QPen pen)
{
    xAxis2->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxis2SubGridPenColor_x(QColor color)
{
    QPen pen = xAxis2->grid()->subGridPen();
    pen.setColor(color);
    xAxis2->grid()->setSubGridPen(pen);
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

void CatQcustomplot::SetAxis2SubGridPen_y(QPen pen)
{
    yAxis2->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxis2SubGridPenColor_y(QColor color)
{
    QPen pen = yAxis2->grid()->subGridPen();
    pen.setColor(color);
    yAxis2->grid()->setSubGridPen(pen);
}

void CatQcustomplot::SetAxisLabelColor_x(QColor color)
{
    xAxis->setLabelColor(color);
}

void CatQcustomplot::SetAxis2LabelColor_x(QColor color)
{
    xAxis2->setLabelColor(color);
}

void CatQcustomplot::SetAxisLabelColor_y(QColor color)
{
    yAxis->setLabelColor(color);
}

void CatQcustomplot::SetAxis2LabelColor_y(QColor color)
{
    yAxis2->setLabelColor(color);
}

void CatQcustomplot::SetAxisLabelFont_x(QFont font)
{
    xAxis->setLabelFont(font);
}

void CatQcustomplot::SetAxis2LabelFont_x(QFont font)
{
    xAxis2->setLabelFont(font);
}

void CatQcustomplot::SetAxisLabelFont_y(QFont font)
{
    yAxis->setLabelFont(font);
}

void CatQcustomplot::SetAxis2LabelFont_y(QFont font)
{
    yAxis2->setLabelFont(font);
}

void CatQcustomplot::SetAxisTickLabelColor_x(QColor color)
{
    xAxis->setTickLabelColor(color);
}

void CatQcustomplot::SetAxis2TickLabelColor_x(QColor color)
{
    xAxis2->setTickLabelColor(color);
}

void CatQcustomplot::SetAxisTickLabelColor_y(QColor color)
{
    yAxis->setTickLabelColor(color);
}

void CatQcustomplot::SetAxis2TickLabelColor_y(QColor color)
{
    yAxis2->setTickLabelColor(color);
}

void CatQcustomplot::SetAxisTickLabelFont_x(QFont font)
{
    xAxis->setTickLabelFont(font);
}

void CatQcustomplot::SetAxis2TickLabelFont_x(QFont font)
{
    xAxis2->setTickLabelFont(font);
}

void CatQcustomplot::SetAxisTickLabelFont_y(QFont font)
{
    yAxis->setTickLabelFont(font);
}

void CatQcustomplot::SetAxis2TickLabelFont_y(QFont font)
{
    yAxis2->setTickLabelFont(font);
}
