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

void CatQcustomplot::SetAxisBasePen_x(QPen pen)
{
    xAxis->setBasePen(pen);
}

void CatQcustomplot::SetAxisBasePen_y(QPen pen)
{
    yAxis->setBasePen(pen);
}
