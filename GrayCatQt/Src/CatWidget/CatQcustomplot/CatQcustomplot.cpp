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

void CatQcustomplot::SetLegendSelectBackground(QBrush brush)
{
    legend->setSelectedBrush(brush);
}

void CatQcustomplot::SetLegendFont(QFont font)
{
    legend->setFont(font);
}

void CatQcustomplot::SetLegendSelectFont(QFont font)
{
    legend->setSelectedFont(font);
}

void CatQcustomplot::SetLegendBorder(QPen border)
{
    legend->setBorderPen(border);
}

void CatQcustomplot::SetLegendSelectBorder(QPen border)
{
    legend->setSelectedBorderPen(border);
}

void CatQcustomplot::SetLegendBorderColor(QColor color)
{
    QPen pen = legend->borderPen();
    pen.setColor(color);
    legend->setBorderPen(pen);
}

void CatQcustomplot::SetLegendSelectBorderColor(QColor color)
{
    QPen pen = legend->selectedBorderPen();
    pen.setColor(color);
    legend->setSelectedBorderPen(pen);
}

void CatQcustomplot::SetLegendBorderWide(qint32 width)
{
    QPen pen = legend->borderPen();
    pen.setWidth(width);
    legend->setBorderPen(pen);
}

void CatQcustomplot::SetLegendSelectBorderWide(qint32 width)
{
    QPen pen = legend->selectedBorderPen();
    pen.setWidth(width);
    legend->setSelectedBorderPen(pen);
}

void CatQcustomplot::SetLegendTextColor(QColor color)
{
    legend->setTextColor(color);
}

void CatQcustomplot::SetLegendSelectTextColor(QColor color)
{
    legend->setSelectedTextColor(color);
}


void CatQcustomplot::SetAxisBasePen_x(QPen pen)
{
    xAxis->setBasePen(pen);
}

void CatQcustomplot::SetAxisBasePenWidth_x(int width)
{
    QPen pen = xAxis->basePen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2BasePenWidth_x(int width)
{
    QPen pen = xAxis2->basePen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisBasePenWidth_y(int width)
{
    QPen pen = yAxis->basePen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2BasePenWidth_y(int width)
{
    QPen pen = yAxis2->basePen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisTickPenWidth_x(int width)
{
    QPen pen = xAxis->tickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2TickPenWidth_x(int width)
{
    QPen pen = xAxis2->tickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisTickPenWidth_y(int width)
{
    QPen pen = yAxis->tickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2TickPenWidth_y(int width)
{
    QPen pen = yAxis2->tickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisSubTickPenWidth_x(int width)
{
    QPen pen = xAxis->subTickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2SubTickPenWidth_x(int width)
{
    QPen pen = xAxis2->subTickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisSubTickPenWidth_y(int width)
{
    QPen pen = yAxis->subTickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2SubTickPenWidth_y(int width)
{
    QPen pen = yAxis2->subTickPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisGridPenWidth_x(int width)
{
    QPen pen = xAxis->grid()->pen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2GridPenWidth_x(int width)
{
    QPen pen = xAxis2->grid()->pen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisGridPenWidth_y(int width)
{
    QPen pen = yAxis->grid()->pen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2GridPenWidth_y(int width)
{
    QPen pen = yAxis2->grid()->pen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisSubGridPenWidth_x(int width)
{
    QPen pen = xAxis->grid()->subGridPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2SubGridPenWidth_x(int width)
{
    QPen pen = xAxis2->grid()->subGridPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxisSubGridPenWidth_y(int width)
{
    QPen pen = yAxis->grid()->subGridPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetAxis2SubGridPenWidth_y(int width)
{
    QPen pen = yAxis2->grid()->subGridPen();
    pen.setWidth(width);
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

void CatQcustomplot::SetGraphSelectionDecoratorWidth(int width)
{
    m_qSelectionDecorator.setWidth(width);
}

void CatQcustomplot::SetGraphSelectionDecoratorColor(QColor color)
{
    m_qSelectionDecorator.setColor(color);
}

void CatQcustomplot::SetLegendSelectIconBorderWidth(int width)
{
    QPen pen = legend->selectedIconBorderPen();
    pen.setWidth(width);
    legend->setSelectedIconBorderPen(pen);
}

void CatQcustomplot::SetLegendSelectIconBordeColor(QColor color)
{
    QPen pen = legend->selectedIconBorderPen();
    pen.setColor(color);
    legend->setSelectedIconBorderPen(pen);
}

void CatQcustomplot::SetAxisSelectedBasePenWidth_x(int width)
{
    QPen pen = xAxis->selectedBasePen();
    pen.setWidth(width);
    xAxis->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxisSelectedBasePenColor_x(QColor color)
{
    QPen pen = xAxis->selectedBasePen();
    pen.setColor(color);
    xAxis->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxis2SelectedBasePenWidth_x(int width)
{
    QPen pen = xAxis2->selectedBasePen();
    pen.setWidth(width);
    xAxis2->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxis2SelectedBasePenColor_x(QColor color)
{
    QPen pen = xAxis2->selectedBasePen();
    pen.setColor(color);
    xAxis2->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxisSelectedBasePenWidth_y(int width)
{
    QPen pen = yAxis->selectedBasePen();
    pen.setWidth(width);
    yAxis->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxisSelectedBasePenColor_y(QColor color)
{
    QPen pen = yAxis->selectedBasePen();
    pen.setColor(color);
    yAxis->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxis2SelectedBasePenWidth_y(int width)
{
    QPen pen = yAxis2->selectedBasePen();
    pen.setWidth(width);
    yAxis2->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxis2SelectedBasePenColor_y(QColor color)
{
    QPen pen = yAxis2->selectedBasePen();
    pen.setColor(color);
    yAxis2->setSelectedBasePen(pen);
}

void CatQcustomplot::SetAxisSelectedTickPenWidth_x(int width)
{
    QPen pen = xAxis->selectedTickPen();
    pen.setWidth(width);
    xAxis->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedTickPenColor_x(QColor color)
{
    QPen pen = xAxis->selectedTickPen();
    pen.setColor(color);
    xAxis->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedTickPenWidth_x(int width)
{
    QPen pen = xAxis2->selectedTickPen();
    pen.setWidth(width);
    xAxis2->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedTickPenColor_x(QColor color)
{
    QPen pen = xAxis2->selectedTickPen();
    pen.setColor(color);
    xAxis2->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedTickPenWidth_y(int width)
{
    QPen pen = yAxis->selectedTickPen();
    pen.setWidth(width);
    yAxis->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedTickPenColor_y(QColor color)
{
    QPen pen = yAxis->selectedTickPen();
    pen.setColor(color);
    yAxis->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedTickPenWidth_y(int width)
{
    QPen pen = yAxis2->selectedTickPen();
    pen.setWidth(width);
    yAxis2->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedTickPenColor_y(QColor color)
{
    QPen pen = yAxis2->selectedTickPen();
    pen.setColor(color);
    yAxis2->setSelectedTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedSubTickPenWidth_x(int width)
{
    QPen pen = xAxis->selectedSubTickPen();
    pen.setWidth(width);
    xAxis->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedSubTickPenColor_x(QColor color)
{
    QPen pen = xAxis->selectedSubTickPen();
    pen.setColor(color);
    xAxis->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedSubTickPenWidth_x(int width)
{
    QPen pen = xAxis2->selectedSubTickPen();
    pen.setWidth(width);
    xAxis2->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedSubTickPenColor_x(QColor color)
{
    QPen pen = xAxis2->selectedSubTickPen();
    pen.setColor(color);
    xAxis2->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedSubTickPenWidth_y(int width)
{
    QPen pen = yAxis->selectedSubTickPen();
    pen.setWidth(width);
    yAxis->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedSubTickPenColor_y(QColor color)
{
    QPen pen = yAxis->selectedSubTickPen();
    pen.setColor(color);
    yAxis->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedSubTickPenWidth_y(int width)
{
    QPen pen = yAxis2->selectedSubTickPen();
    pen.setWidth(width);
    yAxis2->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxis2SelectedSubTickPenColor_y(QColor color)
{
    QPen pen = yAxis2->selectedSubTickPen();
    pen.setColor(color);
    yAxis2->setSelectedSubTickPen(pen);
}

void CatQcustomplot::SetAxisSelectedLabelColor_x(QColor color)
{
    xAxis->setSelectedLabelColor(color);
}

void CatQcustomplot::SetAxis2SelectedLabelColor_x(QColor color)
{
    xAxis2->setSelectedLabelColor(color);
}

void CatQcustomplot::SetAxisSelectedLabelColor_y(QColor color)
{
    yAxis->setSelectedLabelColor(color);
}

void CatQcustomplot::SetAxis2SelectedLabelColor_y(QColor color)
{
    yAxis2->setSelectedLabelColor(color);
}

void CatQcustomplot::SetAxisSelectedLabelFont_x(QFont font)
{
    xAxis->setSelectedLabelFont(font);
}

void CatQcustomplot::SetAxis2SelectedLabelFont_x(QFont font)
{
    xAxis2->setSelectedLabelFont(font);
}

void CatQcustomplot::SetAxisSelectedLabelFont_y(QFont font)
{
    yAxis->setSelectedLabelFont(font);
}

void CatQcustomplot::SetAxis2SelectedLabelFont_y(QFont font)
{
    yAxis2->setSelectedLabelFont(font);
}

void CatQcustomplot::SetAxisSelectedTickLabelColor_x(QColor color)
{
    xAxis->setSelectedTickLabelColor(color);
}

void CatQcustomplot::SetAxis2SelectedTickLabelColor_x(QColor color)
{
    xAxis2->setSelectedTickLabelColor(color);
}

void CatQcustomplot::SetAxisSelectedTickLabelColor_y(QColor color)
{
    yAxis->setSelectedTickLabelColor(color);
}

void CatQcustomplot::SetAxis2SelectedTickLabelColor_y(QColor color)
{
    yAxis2->setSelectedTickLabelColor(color);
}

void CatQcustomplot::SetAxisSelectedTickLabelFont_x(QFont font)
{
    xAxis->setSelectedTickLabelFont(font);
}

void CatQcustomplot::SetAxis2SelectedTickLabelFont_x(QFont font)
{
    xAxis2->setSelectedTickLabelFont(font);
}

void CatQcustomplot::SetAxisSelectedTickLabelFont_y(QFont font)
{
    yAxis->setSelectedTickLabelFont(font);
}

void CatQcustomplot::SetAxis2SelectedTickLabelFont_y(QFont font)
{
    yAxis2->setSelectedTickLabelFont(font);
}
