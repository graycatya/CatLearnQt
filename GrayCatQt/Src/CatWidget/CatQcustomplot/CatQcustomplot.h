#ifndef CATQCUSTOMPLOT_H
#define CATQCUSTOMPLOT_H

#include "qcustomplot.h"

class CatQcustomplot : public QCustomPlot
{
    Q_OBJECT
    // 图表 - 样式接口
    Q_PROPERTY(QBrush Background READ GetBackground WRITE SetBackground)

     // 图例 - 样式接口
    Q_PROPERTY(QBrush LegendBackground READ GetLegendBackground WRITE SetLegendBackground)
    Q_PROPERTY(QBrush LegendSelectBackground READ GetLegendSelectBackground WRITE SetLegendSelectBackground)

    Q_PROPERTY(QFont LegendFont READ GetLegendFont WRITE SetLegendFont)
    Q_PROPERTY(QFont LegendSelectFont READ GetLegendSelectFont WRITE SetLegendSelectFont)

    Q_PROPERTY(QPen LegendBorder READ GetLegendBorder WRITE SetLegendBorder)
    Q_PROPERTY(QPen LegendSelectBorder READ GetLegendSelectBorder WRITE SetLegendSelectBorder)

    Q_PROPERTY(QColor LegendBorderColor READ GetLegendBorderColor WRITE SetLegendBorderColor)
    Q_PROPERTY(QColor LegendSelectBorderColor READ GetLegendSelectBorderColor WRITE SetLegendSelectBorderColor)

    Q_PROPERTY(qint32 LegendBorderWide READ GetLegendBorderWide WRITE SetLegendBorderWide)
    Q_PROPERTY(qint32 LegendSelectBorderWide READ GetLegendSelectBorderWide WRITE SetLegendSelectBorderWide)

    Q_PROPERTY(QColor LegendTextColor READ GetLegendTextColor WRITE SetLegendTextColor)
    Q_PROPERTY(QColor LegendSelectTextColor READ GetLegendSelectTextColor WRITE SetLegendSelectTextColor)

    Q_PROPERTY(int LegendSelectIconBorderWidth READ GetLegendSelectIconBorderWidth WRITE SetLegendSelectIconBorderWidth)
    Q_PROPERTY(QColor LegendSelectIconBordeColor READ GetLegendSelectIconBordeColor WRITE SetLegendSelectIconBordeColor)

    // 刻度与边的颜色 - 样式接口
    Q_PROPERTY(QPen AxisBasePen_x READ GetAxisBasePen_x WRITE SetAxisBasePen_x)
    Q_PROPERTY(int AxisBasePenWidth_x READ GetAxisBasePenWidth_x WRITE SetAxisBasePenWidth_x)
    Q_PROPERTY(QColor AxisBasePenColor_x READ GetAxisBasePenColor_x WRITE SetAxisBasePenColor_x)

    Q_PROPERTY(QPen Axis2BasePen_x READ GetAxis2BasePen_x WRITE SetAxis2BasePen_x)
    Q_PROPERTY(int Axis2BasePenWidth_x READ GetAxis2BasePenWidth_x WRITE SetAxis2BasePenWidth_x)
    Q_PROPERTY(QColor Axis2BasePenColor_x READ GetAxis2BasePenColor_x WRITE SetAxis2BasePenColor_x)

    Q_PROPERTY(QPen AxisBasePen_y READ GetAxisBasePen_y WRITE SetAxisBasePen_y)
    Q_PROPERTY(int AxisBasePenWidth_y READ GetAxisBasePenWidth_y WRITE SetAxisBasePenWidth_y)
    Q_PROPERTY(QColor AxisBasePenColor_y READ GetAxisBasePenColor_y WRITE SetAxisBasePenColor_y)

    Q_PROPERTY(QPen Axis2BasePen_y READ GetAxis2BasePen_y WRITE SetAxis2BasePen_y)
    Q_PROPERTY(int Axis2BasePenWidth_y READ GetAxis2BasePenWidth_y WRITE SetAxis2BasePenWidth_y)
    Q_PROPERTY(QColor Axis2BasePenColor_y READ GetAxis2BasePenColor_y WRITE SetAxis2BasePenColor_y)

    Q_PROPERTY(QPen AxisTickPen_x READ GetAxisTickPen_x WRITE SetAxisTickPen_x)
    Q_PROPERTY(int AxisTickPenWidth_x READ GetAxisTickPenWidth_x WRITE SetAxisTickPenWidth_x)
    Q_PROPERTY(QColor AxisTickPenColor_x READ GetAxisTickPenColor_x WRITE SetAxisTickPenColor_x)

    Q_PROPERTY(QPen Axis2TickPen_x READ GetAxis2TickPen_x WRITE SetAxis2TickPen_x)
    Q_PROPERTY(int Axis2TickPenWidth_x READ GetAxis2TickPenWidth_x WRITE SetAxis2TickPenWidth_x)
    Q_PROPERTY(QColor Axis2TickPenColor_x READ GetAxis2TickPenColor_x WRITE SetAxis2TickPenColor_x)

    Q_PROPERTY(QPen AxisTickPen_y READ GetAxisTickPen_y WRITE SetAxisTickPen_y)
    Q_PROPERTY(int AxisTickPenWidth_y READ GetAxisTickPenWidth_y WRITE SetAxisTickPenWidth_y)
    Q_PROPERTY(QColor AxisTickPenColor_y READ GetAxisTickPenColor_y WRITE SetAxisTickPenColor_y)

    Q_PROPERTY(QPen Axis2TickPen_y READ GetAxis2TickPen_y WRITE SetAxis2TickPen_y)
    Q_PROPERTY(int Axis2TickPenWidth_y READ GetAxis2TickPenWidth_y WRITE SetAxis2TickPenWidth_y)
    Q_PROPERTY(QColor Axis2TickPenColor_y READ GetAxis2TickPenColor_y WRITE SetAxis2TickPenColor_y)

    Q_PROPERTY(QPen AxisSubTickPen_x READ GetAxisSubTickPen_x WRITE SetAxisSubTickPen_x)
    Q_PROPERTY(int AxisSubTickPenWidth_x READ GetAxisSubTickPenWidth_x WRITE SetAxisSubTickPenWidth_x)
    Q_PROPERTY(QColor AxisSubTickPenColor_x READ GetAxisSubTickPenColor_x WRITE SetAxisSubTickPenColor_x)

    Q_PROPERTY(QPen Axis2SubTickPen_x READ GetAxis2SubTickPen_x WRITE SetAxis2SubTickPen_x)
    Q_PROPERTY(int Axis2SubTickPenWidth_x READ GetAxis2SubTickPenWidth_x WRITE SetAxis2SubTickPenWidth_x)
    Q_PROPERTY(QColor Axis2SubTickPenColor_x READ GetAxis2SubTickPenColor_x WRITE SetAxis2SubTickPenColor_x)

    Q_PROPERTY(QPen AxisSubTickPen_y READ GetAxisSubTickPen_y WRITE SetAxisSubTickPen_y)
    Q_PROPERTY(int AxisSubTickPenWidth_y READ GetAxisSubTickPenWidth_y WRITE SetAxisSubTickPenWidth_y)
    Q_PROPERTY(QColor AxisSubTickPenColor_y READ GetAxisSubTickPenColor_y WRITE SetAxisSubTickPenColor_y)

    Q_PROPERTY(QPen Axis2SubTickPen_y READ GetAxis2SubTickPen_y WRITE SetAxis2SubTickPen_y)
    Q_PROPERTY(int Axis2SubTickPenWidth_y READ GetAxis2SubTickPenWidth_y WRITE SetAxis2SubTickPenWidth_y)
    Q_PROPERTY(QColor Axis2SubTickPenColor_y READ GetAxis2SubTickPenColor_y WRITE SetAxis2SubTickPenColor_y)

    Q_PROPERTY(QPen AxisGridPen_x READ GetAxisGridPen_x WRITE SetAxisGridPen_x)
    Q_PROPERTY(int AxisGridPenWidth_x READ GetAxisGridPenWidth_x WRITE SetAxisGridPenWidth_x)
    Q_PROPERTY(QColor AxisGridPenColor_x READ GetAxisGridPenColor_x WRITE SetAxisGridPenColor_x)

    Q_PROPERTY(QPen Axis2GridPen_x READ GetAxis2GridPen_x WRITE SetAxis2GridPen_x)
    Q_PROPERTY(int Axis2GridPenWidth_x READ GetAxis2GridPenWidth_x WRITE SetAxis2GridPenWidth_x)
    Q_PROPERTY(QColor Axis2GridPenColor_x READ GetAxis2GridPenColor_x WRITE SetAxis2GridPenColor_x)

    Q_PROPERTY(QPen AxisGridPen_y READ GetAxisGridPen_y WRITE SetAxisGridPen_y)
    Q_PROPERTY(int AxisGridPenWidth_y READ GetAxisGridPenWidth_y WRITE SetAxisGridPenWidth_y)
    Q_PROPERTY(QColor AxisGridPenColor_y READ GetAxisGridPenColor_y WRITE SetAxisGridPenColor_y)

    Q_PROPERTY(QPen Axis2GridPen_y READ GetAxis2GridPen_y WRITE SetAxis2GridPen_y)
    Q_PROPERTY(int Axis2GridPenWidth_y READ GetAxis2GridPenWidth_y WRITE SetAxis2GridPenWidth_y)
    Q_PROPERTY(QColor Axis2GridPenColor_y READ GetAxis2GridPenColor_y WRITE SetAxis2GridPenColor_y)

    Q_PROPERTY(QPen AxisSubGridPen_x READ GetAxisSubGridPen_x WRITE SetAxisSubGridPen_x)
    Q_PROPERTY(int AxisSubGridPenWidth_x READ GetAxisSubGridPenWidth_x WRITE SetAxisSubGridPenWidth_x)
    Q_PROPERTY(QColor AxisSubGridPenColor_x READ GetAxisSubGridPenColor_x WRITE SetAxisSubGridPenColor_x)

    Q_PROPERTY(QPen Axis2SubGridPen_x READ GetAxis2SubGridPen_x WRITE SetAxis2SubGridPen_x)
    Q_PROPERTY(int Axis2SubGridPenWidth_x READ GetAxis2SubGridPenWidth_x WRITE SetAxis2SubGridPenWidth_x)
    Q_PROPERTY(QColor Axis2SubGridPenColor_x READ GetAxis2SubGridPenColor_x WRITE SetAxis2SubGridPenColor_x)

    Q_PROPERTY(QPen AxisSubGridPen_y READ GetAxisSubGridPen_y WRITE SetAxisSubGridPen_y)
    Q_PROPERTY(int AxisSubGridPenWidth_y READ GetAxisSubGridPenWidth_y WRITE SetAxisSubGridPenWidth_y)
    Q_PROPERTY(QColor AxisSubGridPenColor_y READ GetAxisSubGridPenColor_y WRITE SetAxisSubGridPenColor_y)

    Q_PROPERTY(QPen Axis2SubGridPen_y READ GetAxis2SubGridPen_y WRITE SetAxis2SubGridPen_y)
    Q_PROPERTY(int Axis2SubGridPenWidth_y READ GetAxis2SubGridPenWidth_y WRITE SetAxis2SubGridPenWidth_y)
    Q_PROPERTY(QColor Axis2SubGridPenColor_y READ GetAxis2SubGridPenColor_y WRITE SetAxis2SubGridPenColor_y)

    Q_PROPERTY(QColor AxisLabelColor_x READ GetAxisLabelColor_x WRITE SetAxisLabelColor_x)
    Q_PROPERTY(QColor Axis2LabelColor_x READ GetAxis2LabelColor_x WRITE SetAxis2LabelColor_x)

    Q_PROPERTY(QColor AxisLabelColor_y READ GetAxisLabelColor_y WRITE SetAxisLabelColor_y)
    Q_PROPERTY(QColor Axis2LabelColor_y READ GetAxis2LabelColor_y WRITE SetAxis2LabelColor_y)

    Q_PROPERTY(QFont AxisLabelFont_x READ GetAxisLabelFont_x WRITE SetAxisLabelFont_x)
    Q_PROPERTY(QFont Axis2LabelFont_x READ GetAxis2LabelFont_x WRITE SetAxis2LabelFont_x)

    Q_PROPERTY(QFont AxisLabelFont_y READ GetAxisLabelFont_y WRITE SetAxisLabelFont_y)
    Q_PROPERTY(QFont Axis2LabelFont_y READ GetAxis2LabelFont_y WRITE SetAxis2LabelFont_y)

    Q_PROPERTY(QColor AxisTickLabelColor_x READ GetAxisTickLabelColor_x WRITE SetAxisTickLabelColor_x)
    Q_PROPERTY(QColor Axis2TickLabelColor_x READ GetAxis2TickLabelColor_x WRITE SetAxis2TickLabelColor_x)

    Q_PROPERTY(QColor AxisTickLabelColor_y READ GetAxisTickLabelColor_y WRITE SetAxisTickLabelColor_y)
    Q_PROPERTY(QColor Axis2TickLabelColor_y READ GetAxis2TickLabelColor_y WRITE SetAxis2TickLabelColor_y)

    Q_PROPERTY(QFont AxisTickLabelFont_x READ GetAxisTickLabelFont_x WRITE SetAxisTickLabelFont_x)
    Q_PROPERTY(QFont Axis2TickLabelFont_x READ GetAxis2TickLabelFont_x WRITE SetAxis2TickLabelFont_x)

    Q_PROPERTY(QFont AxisTickLabelFont_y READ GetAxisTickLabelFont_y WRITE SetAxisTickLabelFont_y)
    Q_PROPERTY(QFont Axis2TickLabelFont_y READ GetAxis2TickLabelFont_y WRITE SetAxis2TickLabelFont_y)

    Q_PROPERTY(int GraphSelectionDecoratorWidth READ GetGraphSelectionDecoratorWidth WRITE SetGraphSelectionDecoratorWidth)
    Q_PROPERTY(QColor GraphSelectionDecoratorColor READ GetGraphSelectionDecoratorColor WRITE SetGraphSelectionDecoratorColor)

    // 选择后 刻度与边的颜色 - 样式接口
    Q_PROPERTY(int AxisSelectedBasePenWidth_x READ GetAxisSelectedBasePenWidth_x WRITE SetAxisSelectedBasePenWidth_x)
    Q_PROPERTY(QColor AxisSelectedBasePenColor_x READ GetAxisSelectedBasePenColor_x WRITE SetAxisSelectedBasePenColor_x)

    Q_PROPERTY(int Axis2SelectedBasePenWidth_x READ GetAxis2SelectedBasePenWidth_x WRITE SetAxis2SelectedBasePenWidth_x)
    Q_PROPERTY(QColor Axis2SelectedBasePenColor_x READ GetAxis2SelectedBasePenColor_x WRITE SetAxis2SelectedBasePenColor_x)

    Q_PROPERTY(int AxisSelectedBasePenWidth_y READ GetAxisSelectedBasePenWidth_y WRITE SetAxisSelectedBasePenWidth_y)
    Q_PROPERTY(QColor AxisSelectedBasePenColor_y READ GetAxisSelectedBasePenColor_y WRITE SetAxisSelectedBasePenColor_y)

    Q_PROPERTY(int Axis2SelectedBasePenWidth_y READ GetAxis2SelectedBasePenWidth_y WRITE SetAxis2SelectedBasePenWidth_y)
    Q_PROPERTY(QColor Axis2SelectedBasePenColor_y READ GetAxis2SelectedBasePenColor_y WRITE SetAxis2SelectedBasePenColor_y)

    Q_PROPERTY(int AxisSelectedTickPenWidth_x READ GetAxisSelectedTickPenWidth_x WRITE SetAxisSelectedTickPenWidth_x)
    Q_PROPERTY(QColor AxisSelectedTickPenColor_x READ GetAxisSelectedTickPenColor_x WRITE SetAxisSelectedTickPenColor_x)

    Q_PROPERTY(int Axis2SelectedTickPenWidth_x READ GetAxis2SelectedTickPenWidth_x WRITE SetAxis2SelectedTickPenWidth_x)
    Q_PROPERTY(QColor Axis2SelectedTickPenColor_x READ GetAxis2SelectedTickPenColor_x WRITE SetAxis2SelectedTickPenColor_x)

    Q_PROPERTY(int AxisSelectedTickPenWidth_y READ GetAxisSelectedTickPenWidth_y WRITE SetAxisSelectedTickPenWidth_y)
    Q_PROPERTY(QColor AxisSelectedTickPenColor_y READ GetAxisSelectedTickPenColor_y WRITE SetAxisSelectedTickPenColor_y)

    Q_PROPERTY(int Axis2SelectedTickPenWidth_y READ GetAxis2SelectedTickPenWidth_y WRITE SetAxis2SelectedTickPenWidth_y)
    Q_PROPERTY(QColor Axis2SelectedTickPenColor_y READ GetAxis2SelectedTickPenColor_y WRITE SetAxis2SelectedTickPenColor_y)

    Q_PROPERTY(int AxisSelectedSubTickPenWidth_x READ GetAxisSelectedSubTickPenWidth_x WRITE SetAxisSelectedSubTickPenWidth_x)
    Q_PROPERTY(QColor AxisSelectedSubTickPenColor_x READ GetAxisSelectedSubTickPenColor_x WRITE SetAxisSelectedSubTickPenColor_x)

    Q_PROPERTY(int Axis2SelectedSubTickPenWidth_x READ GetAxis2SelectedSubTickPenWidth_x WRITE SetAxis2SelectedSubTickPenWidth_x)
    Q_PROPERTY(QColor Axis2SelectedSubTickPenColor_x READ GetAxis2SelectedSubTickPenColor_x WRITE SetAxis2SelectedSubTickPenColor_x)

    Q_PROPERTY(int AxisSelectedSubTickPenWidth_y READ GetAxisSelectedSubTickPenWidth_y WRITE SetAxisSelectedSubTickPenWidth_y)
    Q_PROPERTY(QColor AxisSelectedSubTickPenColor_y READ GetAxisSelectedSubTickPenColor_y WRITE SetAxisSelectedSubTickPenColor_y)

    Q_PROPERTY(int Axis2SelectedSubTickPenWidth_y READ GetAxis2SelectedSubTickPenWidth_y WRITE SetAxis2SelectedSubTickPenWidth_y)
    Q_PROPERTY(QColor Axis2SelectedSubTickPenColor_y READ GetAxis2SelectedSubTickPenColor_y WRITE SetAxis2SelectedSubTickPenColor_y)

    Q_PROPERTY(QColor AxisSelectedLabelColor_x READ GetAxisSelectedLabelColor_x WRITE SetAxisSelectedLabelColor_x)
    Q_PROPERTY(QColor Axis2SelectedLabelColor_x READ GetAxis2SelectedLabelColor_x WRITE SetAxis2SelectedLabelColor_x)

    Q_PROPERTY(QColor AxisSelectedLabelColor_y READ GetAxisSelectedLabelColor_y WRITE SetAxisSelectedLabelColor_y)
    Q_PROPERTY(QColor Axis2SelectedLabelColor_y READ GetAxis2SelectedLabelColor_y WRITE SetAxis2SelectedLabelColor_y)

    Q_PROPERTY(QFont AxisSelectedLabelFont_x READ GetAxisSelectedLabelFont_x WRITE SetAxisSelectedLabelFont_x)
    Q_PROPERTY(QFont Axis2SelectedLabelFont_x READ GetAxis2SelectedLabelFont_x WRITE SetAxis2SelectedLabelFont_x)

    Q_PROPERTY(QFont AxisSelectedLabelFont_y READ GetAxisSelectedLabelFont_y WRITE SetAxisSelectedLabelFont_y)
    Q_PROPERTY(QFont Axis2SelectedLabelFont_y READ GetAxis2SelectedLabelFont_y WRITE SetAxis2SelectedLabelFont_y)

    Q_PROPERTY(QColor AxisSelectedTickLabelColor_x READ GetAxisSelectedTickLabelColor_x WRITE SetAxisSelectedTickLabelColor_x)
    Q_PROPERTY(QColor Axis2SelectedTickLabelColor_x READ GetAxis2SelectedTickLabelColor_x WRITE SetAxis2SelectedTickLabelColor_x)

    Q_PROPERTY(QColor AxisSelectedTickLabelColor_y READ GetAxisSelectedTickLabelColor_y WRITE SetAxisSelectedTickLabelColor_y)
    Q_PROPERTY(QColor Axis2SelectedTickLabelColor_y READ GetAxis2SelectedTickLabelColor_y WRITE SetAxis2SelectedTickLabelColor_y)

    Q_PROPERTY(QFont AxisSelectedTickLabelFont_x READ GetAxisSelectedTickLabelFont_x WRITE SetAxisSelectedTickLabelFont_x)
    Q_PROPERTY(QFont Axis2SelectedTickLabelFont_x READ GetAxis2SelectedTickLabelFont_x WRITE SetAxis2SelectedTickLabelFont_x)

    Q_PROPERTY(QFont AxisSelectedTickLabelFont_y READ GetAxisSelectedTickLabelFont_y WRITE SetAxisSelectedTickLabelFont_y)
    Q_PROPERTY(QFont Axis2SelectedTickLabelFont_y READ GetAxis2SelectedTickLabelFont_y WRITE SetAxis2SelectedTickLabelFont_y)
public:
    explicit CatQcustomplot(QWidget *parent = nullptr);
    ~CatQcustomplot();

    // 获取图表样式
    QBrush GetBackground() const { return background();  }

    // 获取图列样式
    QBrush GetLegendBackground() const { return legend->brush(); }
    QBrush GetLegendSelectBackground() const { return legend->selectedBrush(); }

    QFont GetLegendFont() const { return legend->font(); }
    QFont GetLegendSelectFont() const { return legend->selectedFont(); }

    QPen GetLegendBorder() const { return legend->borderPen(); }
    QPen GetLegendSelectBorder() const { return legend->selectedBorderPen(); }

    QColor GetLegendBorderColor() const { return legend->borderPen().color(); }
    QColor GetLegendSelectBorderColor() const { return legend->selectedBorderPen().color(); }

    qint32 GetLegendBorderWide() const { return legend->borderPen().width(); }
    qint32 GetLegendSelectBorderWide() const { return legend->selectedBorderPen().width(); }

    QColor GetLegendTextColor() const { return legend->textColor(); }
    QColor GetLegendSelectTextColor() const { return legend->selectedTextColor(); }

    int GetLegendSelectIconBorderWidth() const { return legend->selectedIconBorderPen().width(); }
    QColor GetLegendSelectIconBordeColor() const { return legend->selectedIconBorderPen().color(); }

    // 获取坐标轴样式
    QPen GetAxisBasePen_x() const { return xAxis->basePen(); }
    int GetAxisBasePenWidth_x() const { return xAxis->basePen().width(); }
    QColor GetAxisBasePenColor_x() const { return xAxis->basePen().color(); }

    QPen GetAxis2BasePen_x() const { return  xAxis2->basePen(); }
    int GetAxis2BasePenWidth_x() const { return xAxis2->basePen().width(); }
    QColor GetAxis2BasePenColor_x() const { return xAxis2->basePen().color(); }

    QPen GetAxisBasePen_y() const { return yAxis->basePen(); }
    int GetAxisBasePenWidth_y() const { return yAxis->basePen().width(); }
    QColor GetAxisBasePenColor_y() const { return yAxis->basePen().color(); }

    QPen GetAxis2BasePen_y() const { return yAxis2->basePen(); }
    int GetAxis2BasePenWidth_y() const { return yAxis2->basePen().width(); }
    QColor GetAxis2BasePenColor_y() const { return yAxis2->basePen().color(); }

    QPen GetAxisTickPen_x() const { return xAxis->tickPen(); }
    int GetAxisTickPenWidth_x() const { return xAxis->tickPen().width(); }
    QColor GetAxisTickPenColor_x() const { return xAxis->tickPen().color(); }

    QPen GetAxis2TickPen_x() const { return xAxis2->tickPen(); }
    int GetAxis2TickPenWidth_x() const { return xAxis2->tickPen().width(); }
    QColor GetAxis2TickPenColor_x() const { return xAxis2->tickPen().color(); }

    QPen GetAxisTickPen_y() const { return yAxis->tickPen(); }
    int GetAxisTickPenWidth_y() const { return yAxis->tickPen().width(); }
    QColor GetAxisTickPenColor_y() const { return yAxis->tickPen().color(); }

    QPen GetAxis2TickPen_y() const { return yAxis2->tickPen(); }
    int GetAxis2TickPenWidth_y() const { return yAxis2->tickPen().width(); }
    QColor GetAxis2TickPenColor_y() const { return yAxis2->tickPen().color(); }

    QPen GetAxisSubTickPen_x() const { return xAxis->subTickPen(); }
    int GetAxisSubTickPenWidth_x() const { return xAxis->subTickPen().width(); }
    QColor GetAxisSubTickPenColor_x() const { return xAxis->subTickPen().color(); }

    QPen GetAxis2SubTickPen_x() const { return xAxis2->subTickPen(); }
    int GetAxis2SubTickPenWidth_x() const { return xAxis2->subTickPen().width(); }
    QColor GetAxis2SubTickPenColor_x() const { return xAxis2->subTickPen().color(); }

    QPen GetAxisSubTickPen_y() const { return yAxis->subTickPen(); }
    int GetAxisSubTickPenWidth_y() const { return yAxis->subTickPen().width(); }
    QColor GetAxisSubTickPenColor_y() const { return yAxis->subTickPen().color(); }

    QPen GetAxis2SubTickPen_y() const { return yAxis2->subTickPen(); }
    int GetAxis2SubTickPenWidth_y() const { return yAxis2->subTickPen().width(); }
    QColor GetAxis2SubTickPenColor_y() const { return yAxis2->subTickPen().color(); }

    QPen GetAxisGridPen_x() const { return xAxis->grid()->pen(); }
    int GetAxisGridPenWidth_x() const { return xAxis->grid()->pen().width(); }
    QColor GetAxisGridPenColor_x() const { return xAxis->grid()->pen().color(); }

    QPen GetAxis2GridPen_x() const { return xAxis2->grid()->pen(); }
    int GetAxis2GridPenWidth_x() const { return xAxis2->grid()->pen().width(); }
    QColor GetAxis2GridPenColor_x() const { return xAxis2->grid()->pen().color(); }

    QPen GetAxisGridPen_y() const { return yAxis->grid()->pen(); }
    int GetAxisGridPenWidth_y() const { return yAxis->grid()->pen().width(); }
    QColor GetAxisGridPenColor_y() const { return yAxis->grid()->pen().color(); }

    QPen GetAxis2GridPen_y() const { return yAxis2->grid()->pen(); }
    int GetAxis2GridPenWidth_y() const { return yAxis2->grid()->pen().width(); }
    QColor GetAxis2GridPenColor_y() const { return yAxis2->grid()->pen().color(); }

    QPen GetAxisSubGridPen_x() const { return xAxis->grid()->subGridPen(); }
    int GetAxisSubGridPenWidth_x() const { return xAxis->grid()->subGridPen().width(); }
    QColor GetAxisSubGridPenColor_x() const { return xAxis->grid()->subGridPen().color(); }

    QPen GetAxis2SubGridPen_x() const { return xAxis2->grid()->subGridPen(); }
    int GetAxis2SubGridPenWidth_x() const { return xAxis2->grid()->subGridPen().width(); }
    QColor GetAxis2SubGridPenColor_x() const { return xAxis2->grid()->subGridPen().color(); }

    QPen GetAxisSubGridPen_y() const { return yAxis->grid()->subGridPen(); }
    int GetAxisSubGridPenWidth_y() const { return yAxis->grid()->subGridPen().width(); }
    QColor GetAxisSubGridPenColor_y() const { return yAxis->grid()->subGridPen().color(); }

    QPen GetAxis2SubGridPen_y() const { return yAxis2->grid()->subGridPen(); }
    int GetAxis2SubGridPenWidth_y() const { return yAxis2->grid()->subGridPen().width(); }
    QColor GetAxis2SubGridPenColor_y() const { return yAxis2->grid()->subGridPen().color(); }

    QColor GetAxisLabelColor_x() const { return xAxis->labelColor(); }
    QColor GetAxis2LabelColor_x() const { return xAxis2->labelColor(); }

    QColor GetAxisLabelColor_y() const { return yAxis->labelColor(); }
    QColor GetAxis2LabelColor_y() const { return yAxis2->labelColor(); }

    QFont GetAxisLabelFont_x() const { return xAxis->labelFont(); }
    QFont GetAxis2LabelFont_x() const { return xAxis2->labelFont(); }

    QFont GetAxisLabelFont_y() const { return yAxis->labelFont(); }
    QFont GetAxis2LabelFont_y() const { return yAxis2->labelFont(); }

    QColor GetAxisTickLabelColor_x() const { return xAxis->tickLabelColor(); }
    QColor GetAxis2TickLabelColor_x() const { return xAxis2->tickLabelColor(); }

    QColor GetAxisTickLabelColor_y() const { return yAxis->tickLabelColor(); }
    QColor GetAxis2TickLabelColor_y() const { return yAxis2->tickLabelColor(); }

    QFont GetAxisTickLabelFont_x() const { return xAxis->tickLabelFont(); }
    QFont GetAxis2TickLabelFont_x() const { return xAxis2->tickLabelFont(); }

    QFont GetAxisTickLabelFont_y() const { return yAxis->tickLabelFont(); }
    QFont GetAxis2TickLabelFont_y() const { return yAxis2->tickLabelFont(); }

    int GetGraphSelectionDecoratorWidth() const { return m_qSelectionDecorator.width(); }
    QColor GetGraphSelectionDecoratorColor() const { return m_qSelectionDecorator.color(); }
    QPen GetGraphSelectionDecoratorPen() const { return m_qSelectionDecorator; }

    // 取坐标轴选择后样式
    int GetAxisSelectedBasePenWidth_x() const { return xAxis->selectedBasePen().width(); }
    QColor GetAxisSelectedBasePenColor_x() const { return xAxis->selectedBasePen().color(); }

    int GetAxis2SelectedBasePenWidth_x() const { return xAxis2->selectedBasePen().width(); }
    QColor GetAxis2SelectedBasePenColor_x() const { return xAxis2->selectedBasePen().color(); }

    int GetAxisSelectedBasePenWidth_y() const { return yAxis->selectedBasePen().width(); }
    QColor GetAxisSelectedBasePenColor_y() const { return yAxis->selectedBasePen().color(); }

    int GetAxis2SelectedBasePenWidth_y() const { return yAxis2->selectedBasePen().width(); }
    QColor GetAxis2SelectedBasePenColor_y() const { return yAxis2->selectedBasePen().color(); }

    int GetAxisSelectedTickPenWidth_x() const { return xAxis->selectedTickPen().width(); }
    QColor GetAxisSelectedTickPenColor_x() const { return xAxis->selectedTickPen().color(); }

    int GetAxis2SelectedTickPenWidth_x() const { return xAxis2->selectedTickPen().width(); }
    QColor GetAxis2SelectedTickPenColor_x() const { return xAxis2->selectedTickPen().color(); }

    int GetAxisSelectedTickPenWidth_y() const { return yAxis->selectedTickPen().width(); }
    QColor GetAxisSelectedTickPenColor_y() const { return yAxis->selectedTickPen().color(); }

    int GetAxis2SelectedTickPenWidth_y() const { return yAxis2->selectedTickPen().width(); }
    QColor GetAxis2SelectedTickPenColor_y() const { return yAxis2->selectedTickPen().color(); }

    int GetAxisSelectedSubTickPenWidth_x() const { return xAxis->selectedSubTickPen().width(); }
    QColor GetAxisSelectedSubTickPenColor_x() const { return xAxis->selectedSubTickPen().color(); }

    int GetAxis2SelectedSubTickPenWidth_x() const { return xAxis2->selectedSubTickPen().width(); }
    QColor GetAxis2SelectedSubTickPenColor_x() const { return xAxis2->selectedSubTickPen().color(); }

    int GetAxisSelectedSubTickPenWidth_y() const { return yAxis->selectedSubTickPen().width(); }
    QColor GetAxisSelectedSubTickPenColor_y() const { return yAxis->selectedSubTickPen().color(); }

    int GetAxis2SelectedSubTickPenWidth_y() const { return yAxis2->selectedSubTickPen().width(); }
    QColor GetAxis2SelectedSubTickPenColor_y() const { return yAxis2->selectedSubTickPen().color(); }

    QColor GetAxisSelectedLabelColor_x() const { return xAxis->selectedLabelColor(); }
    QColor GetAxis2SelectedLabelColor_x() const { return xAxis2->selectedLabelColor(); }

    QColor GetAxisSelectedLabelColor_y() const { return yAxis->selectedLabelColor(); }
    QColor GetAxis2SelectedLabelColor_y() const { return yAxis2->selectedLabelColor(); }

    QFont GetAxisSelectedLabelFont_x() const { return xAxis->selectedLabelFont(); }
    QFont GetAxis2SelectedLabelFont_x() const { return xAxis2->selectedLabelFont(); }

    QFont GetAxisSelectedLabelFont_y() const { return yAxis->selectedLabelFont(); }
    QFont GetAxis2SelectedLabelFont_y() const { return yAxis2->selectedLabelFont(); }

    QColor GetAxisSelectedTickLabelColor_x() const { return xAxis->selectedTickLabelColor(); }
    QColor GetAxis2SelectedTickLabelColor_x() const { return xAxis2->selectedTickLabelColor(); }

    QColor GetAxisSelectedTickLabelColor_y() const { return yAxis->selectedTickLabelColor(); }
    QColor GetAxis2SelectedTickLabelColor_y() const { return yAxis2->selectedTickLabelColor(); }

    QFont GetAxisSelectedTickLabelFont_x() const { return xAxis->selectedTickLabelFont(); }
    QFont GetAxis2SelectedTickLabelFont_x() const { return xAxis2->selectedTickLabelFont(); }

    QFont GetAxisSelectedTickLabelFont_y() const { return yAxis->selectedTickLabelFont(); }
    QFont GetAxis2SelectedTickLabelFont_y() const { return yAxis2->selectedTickLabelFont(); }

    QStringList ScatterShapeList( void );
    QStringList GraphLineStyleList( void );
    QStringList BarsWidthType( void );
    QStringList TracerStyleList( void );
    QStringList PositionTypeList( void );

    // 布局接口
    void SetLegenAlignment(int index, Qt::Alignment alignment);

public:
    // 添加 线性图元项
    QCPGraph *AddGraph(QPen pen, QString name = "",
                       QCPScatterStyle style = QCPScatterStyle::ssNone,
                       QCPGraph::LineStyle linestyle = QCPGraph::LineStyle::lsLine);

    // 添加 矩形图元项
    QCPBars *AddBars(int width, QPen pen, QBrush brush, QString name = "",
                     QCPBars::WidthType type = QCPBars::WidthType::wtAbsolute);

private:
    void InitProperty();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void SetBackground(QBrush brush);

    void SetLegendBackground(QBrush brush);
    void SetLegendSelectBackground(QBrush brush);

    void SetLegendFont(QFont font);
    void SetLegendSelectFont(QFont font);

    void SetLegendBorder(QPen border);
    void SetLegendSelectBorder(QPen border);

    void SetLegendBorderColor(QColor color);
    void SetLegendSelectBorderColor(QColor color);

    void SetLegendBorderWide(qint32 width);
    void SetLegendSelectBorderWide(qint32 width);

    void SetLegendTextColor(QColor color);
    void SetLegendSelectTextColor(QColor color);

    void SetAxisBasePen_x(QPen pen);
    void SetAxisBasePenWidth_x(int width);
    void SetAxisBasePenColor_x(QColor color);

    void SetAxis2BasePen_x(QPen pen);
    void SetAxis2BasePenWidth_x(int width);
    void SetAxis2BasePenColor_x(QColor color);

    void SetAxisBasePen_y(QPen pen);
    void SetAxisBasePenWidth_y(int width);
    void SetAxisBasePenColor_y(QColor color);

    void SetAxis2BasePen_y(QPen pen);
    void SetAxis2BasePenWidth_y(int width);
    void SetAxis2BasePenColor_y(QColor color);

    void SetAxisTickPen_x(QPen pen);
    void SetAxisTickPenWidth_x(int width);
    void SetAxisTickPenColor_x(QColor color);

    void SetAxis2TickPen_x(QPen pen);
    void SetAxis2TickPenWidth_x(int width);
    void SetAxis2TickPenColor_x(QColor color);

    void SetAxisTickPen_y(QPen pen);
    void SetAxisTickPenWidth_y(int width);
    void SetAxisTickPenColor_y(QColor color);

    void SetAxis2TickPen_y(QPen pen);
    void SetAxis2TickPenWidth_y(int width);
    void SetAxis2TickPenColor_y(QColor color);

    void SetAxisSubTickPen_x(QPen pen);
    void SetAxisSubTickPenWidth_x(int width);
    void SetAxisSubTickPenColor_x(QColor color);

    void SetAxis2SubTickPen_x(QPen pen);
    void SetAxis2SubTickPenWidth_x(int width);
    void SetAxis2SubTickPenColor_x(QColor color);

    void SetAxisSubTickPen_y(QPen pen);
    void SetAxisSubTickPenWidth_y(int width);
    void SetAxisSubTickPenColor_y(QColor color);

    void SetAxis2SubTickPen_y(QPen pen);
    void SetAxis2SubTickPenWidth_y(int width);
    void SetAxis2SubTickPenColor_y(QColor color);

    void SetAxisGridPen_x(QPen pen);
    void SetAxisGridPenWidth_x(int width);
    void SetAxisGridPenColor_x(QColor color);

    void SetAxis2GridPen_x(QPen pen);
    void SetAxis2GridPenWidth_x(int width);
    void SetAxis2GridPenColor_x(QColor color);

    void SetAxisGridPen_y(QPen pen);
    void SetAxisGridPenWidth_y(int width);
    void SetAxisGridPenColor_y(QColor color);

    void SetAxis2GridPen_y(QPen pen);
    void SetAxis2GridPenWidth_y(int width);
    void SetAxis2GridPenColor_y(QColor color);

    void SetAxisSubGridPen_x(QPen pen);
    void SetAxisSubGridPenWidth_x(int width);
    void SetAxisSubGridPenColor_x(QColor color);

    void SetAxis2SubGridPen_x(QPen pen);
    void SetAxis2SubGridPenWidth_x(int width);
    void SetAxis2SubGridPenColor_x(QColor color);

    void SetAxisSubGridPen_y(QPen pen);
    void SetAxisSubGridPenWidth_y(int width);
    void SetAxisSubGridPenColor_y(QColor color);

    void SetAxis2SubGridPen_y(QPen pen);
    void SetAxis2SubGridPenWidth_y(int width);
    void SetAxis2SubGridPenColor_y(QColor color);

    void SetAxisLabelColor_x(QColor color);
    void SetAxis2LabelColor_x(QColor color);

    void SetAxisLabelColor_y(QColor color);
    void SetAxis2LabelColor_y(QColor color);

    void SetAxisLabelFont_x(QFont font);
    void SetAxis2LabelFont_x(QFont font);

    void SetAxisLabelFont_y(QFont font);
    void SetAxis2LabelFont_y(QFont font);

    void SetAxisTickLabelColor_x(QColor color);
    void SetAxis2TickLabelColor_x(QColor color);

    void SetAxisTickLabelColor_y(QColor color);
    void SetAxis2TickLabelColor_y(QColor color);

    void SetAxisTickLabelFont_x(QFont font);
    void SetAxis2TickLabelFont_x(QFont font);

    void SetAxisTickLabelFont_y(QFont font);
    void SetAxis2TickLabelFont_y(QFont font);

    void SetGraphSelectionDecoratorWidth(int width);
    void SetGraphSelectionDecoratorColor(QColor color);

    void SetLegendSelectIconBorderWidth(int width);
    void SetLegendSelectIconBordeColor(QColor color);

    void SetAxisSelectedBasePenWidth_x(int width);
    void SetAxisSelectedBasePenColor_x(QColor color);

    void SetAxis2SelectedBasePenWidth_x(int width);
    void SetAxis2SelectedBasePenColor_x(QColor color);

    void SetAxisSelectedBasePenWidth_y(int width);
    void SetAxisSelectedBasePenColor_y(QColor color);

    void SetAxis2SelectedBasePenWidth_y(int width);
    void SetAxis2SelectedBasePenColor_y(QColor color);

    void SetAxisSelectedTickPenWidth_x(int width);
    void SetAxisSelectedTickPenColor_x(QColor color);

    void SetAxis2SelectedTickPenWidth_x(int width);
    void SetAxis2SelectedTickPenColor_x(QColor color);

    void SetAxisSelectedTickPenWidth_y(int width);
    void SetAxisSelectedTickPenColor_y(QColor color);

    void SetAxis2SelectedTickPenWidth_y(int width);
    void SetAxis2SelectedTickPenColor_y(QColor color);

    void SetAxisSelectedSubTickPenWidth_x(int width);
    void SetAxisSelectedSubTickPenColor_x(QColor color);

    void SetAxis2SelectedSubTickPenWidth_x(int width);
    void SetAxis2SelectedSubTickPenColor_x(QColor color);

    void SetAxisSelectedSubTickPenWidth_y(int width);
    void SetAxisSelectedSubTickPenColor_y(QColor color);

    void SetAxis2SelectedSubTickPenWidth_y(int width);
    void SetAxis2SelectedSubTickPenColor_y(QColor color);

    void SetAxisSelectedLabelColor_x(QColor color);
    void SetAxis2SelectedLabelColor_x(QColor color);

    void SetAxisSelectedLabelColor_y(QColor color);
    void SetAxis2SelectedLabelColor_y(QColor color);

    void SetAxisSelectedLabelFont_x(QFont font);
    void SetAxis2SelectedLabelFont_x(QFont font);

    void SetAxisSelectedLabelFont_y(QFont font);
    void SetAxis2SelectedLabelFont_y(QFont font);

    void SetAxisSelectedTickLabelColor_x(QColor color);
    void SetAxis2SelectedTickLabelColor_x(QColor color);

    void SetAxisSelectedTickLabelColor_y(QColor color);
    void SetAxis2SelectedTickLabelColor_y(QColor color);

    void SetAxisSelectedTickLabelFont_x(QFont font);
    void SetAxis2SelectedTickLabelFont_x(QFont font);

    void SetAxisSelectedTickLabelFont_y(QFont font);
    void SetAxis2SelectedTickLabelFont_y(QFont font);

protected:
    QPen m_qSelectionDecorator;


};

#endif // CATQCUSTOMPLOT_H
