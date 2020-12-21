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
    Q_PROPERTY(QColor AxisBasePenColor_x READ GetAxisBasePenColor_x WRITE SetAxisBasePenColor_x)

    Q_PROPERTY(QPen Axis2BasePen_x READ GetAxis2BasePen_x WRITE SetAxis2BasePen_x)
    Q_PROPERTY(QColor Axis2BasePenColor_x READ GetAxis2BasePenColor_x WRITE SetAxis2BasePenColor_x)

    Q_PROPERTY(QPen AxisBasePen_y READ GetAxisBasePen_y WRITE SetAxisBasePen_y)
    Q_PROPERTY(QColor AxisBasePenColor_y READ GetAxisBasePenColor_y WRITE SetAxisBasePenColor_y)

    Q_PROPERTY(QPen Axis2BasePen_y READ GetAxis2BasePen_y WRITE SetAxis2BasePen_y)
    Q_PROPERTY(QColor Axis2BasePenColor_y READ GetAxis2BasePenColor_y WRITE SetAxis2BasePenColor_y)

    Q_PROPERTY(QPen AxisTickPen_x READ GetAxisTickPen_x WRITE SetAxisTickPen_x)
    Q_PROPERTY(QColor AxisTickPenColor_x READ GetAxisTickPenColor_x WRITE SetAxisTickPenColor_x)

    Q_PROPERTY(QPen Axis2TickPen_x READ GetAxis2TickPen_x WRITE SetAxis2TickPen_x)
    Q_PROPERTY(QColor Axis2TickPenColor_x READ GetAxis2TickPenColor_x WRITE SetAxis2TickPenColor_x)

    Q_PROPERTY(QPen AxisTickPen_y READ GetAxisTickPen_y WRITE SetAxisTickPen_y)
    Q_PROPERTY(QColor AxisTickPenColor_y READ GetAxisTickPenColor_y WRITE SetAxisTickPenColor_y)

    Q_PROPERTY(QPen Axis2TickPen_y READ GetAxis2TickPen_y WRITE SetAxis2TickPen_y)
    Q_PROPERTY(QColor Axis2TickPenColor_y READ GetAxis2TickPenColor_y WRITE SetAxis2TickPenColor_y)

    Q_PROPERTY(QPen AxisSubTickPen_x READ GetAxisSubTickPen_x WRITE SetAxisSubTickPen_x)
    Q_PROPERTY(QColor AxisSubTickPenColor_x READ GetAxisSubTickPenColor_x WRITE SetAxisSubTickPenColor_x)

    Q_PROPERTY(QPen Axis2SubTickPen_x READ GetAxis2SubTickPen_x WRITE SetAxis2SubTickPen_x)
    Q_PROPERTY(QColor Axis2SubTickPenColor_x READ GetAxis2SubTickPenColor_x WRITE SetAxis2SubTickPenColor_x)

    Q_PROPERTY(QPen AxisSubTickPen_y READ GetAxisSubTickPen_y WRITE SetAxisSubTickPen_y)
    Q_PROPERTY(QColor AxisSubTickPenColor_y READ GetAxisSubTickPenColor_y WRITE SetAxisSubTickPenColor_y)

    Q_PROPERTY(QPen Axis2SubTickPen_y READ GetAxis2SubTickPen_y WRITE SetAxis2SubTickPen_y)
    Q_PROPERTY(QColor Axis2SubTickPenColor_y READ GetAxis2SubTickPenColor_y WRITE SetAxis2SubTickPenColor_y)

    Q_PROPERTY(QPen AxisGridPen_x READ GetAxisGridPen_x WRITE SetAxisGridPen_x)
    Q_PROPERTY(QColor AxisGridPenColor_x READ GetAxisGridPenColor_x WRITE SetAxisGridPenColor_x)

    Q_PROPERTY(QPen Axis2GridPen_x READ GetAxis2GridPen_x WRITE SetAxis2GridPen_x)
    Q_PROPERTY(QColor Axis2GridPenColor_x READ GetAxis2GridPenColor_x WRITE SetAxis2GridPenColor_x)

    Q_PROPERTY(QPen AxisGridPen_y READ GetAxisGridPen_y WRITE SetAxisGridPen_y)
    Q_PROPERTY(QColor AxisGridPenColor_y READ GetAxisGridPenColor_y WRITE SetAxisGridPenColor_y)

    Q_PROPERTY(QPen Axis2GridPen_y READ GetAxis2GridPen_y WRITE SetAxis2GridPen_y)
    Q_PROPERTY(QColor Axis2GridPenColor_y READ GetAxis2GridPenColor_y WRITE SetAxis2GridPenColor_y)

    Q_PROPERTY(QPen AxisSubGridPen_x READ GetAxisSubGridPen_x WRITE SetAxisSubGridPen_x)
    Q_PROPERTY(QColor AxisSubGridPenColor_x READ GetAxisSubGridPenColor_x WRITE SetAxisSubGridPenColor_x)

    Q_PROPERTY(QPen Axis2SubGridPen_x READ GetAxis2SubGridPen_x WRITE SetAxis2SubGridPen_x)
    Q_PROPERTY(QColor Axis2SubGridPenColor_x READ GetAxis2SubGridPenColor_x WRITE SetAxis2SubGridPenColor_x)

    Q_PROPERTY(QPen AxisSubGridPen_y READ GetAxisSubGridPen_y WRITE SetAxisSubGridPen_y)
    Q_PROPERTY(QColor AxisSubGridPenColor_y READ GetAxisSubGridPenColor_y WRITE SetAxisSubGridPenColor_y)

    Q_PROPERTY(QPen Axis2SubGridPen_y READ GetAxis2SubGridPen_y WRITE SetAxis2SubGridPen_y)
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

public:
    explicit CatQcustomplot(QWidget *parent = nullptr);
    ~CatQcustomplot();

    // 获取图表样式
    QBrush GetBackground() const { return background(); }

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
    QColor GetAxisBasePenColor_x() const { return xAxis->basePen().color(); }

    QPen GetAxis2BasePen_x() const { return  xAxis2->basePen(); }
    QColor GetAxis2BasePenColor_x() const { return xAxis2->basePen().width(); }

    QPen GetAxisBasePen_y() const { return yAxis->basePen(); }
    QColor GetAxisBasePenColor_y() const { return yAxis->basePen().color(); }

    QPen GetAxis2BasePen_y() const { return yAxis2->basePen(); }
    QColor GetAxis2BasePenColor_y() const { return yAxis2->basePen().color(); }

    QPen GetAxisTickPen_x() const { return xAxis->tickPen(); }
    QColor GetAxisTickPenColor_x() const { return xAxis->tickPen().color(); }

    QPen GetAxis2TickPen_x() const { return xAxis2->tickPen(); }
    QColor GetAxis2TickPenColor_x() const { return xAxis2->tickPen().color(); }

    QPen GetAxisTickPen_y() const { return yAxis->tickPen(); }
    QColor GetAxisTickPenColor_y() const { return yAxis->tickPen().color(); }

    QPen GetAxis2TickPen_y() const { return yAxis2->tickPen(); }
    QColor GetAxis2TickPenColor_y() const { return yAxis2->tickPen().color(); }

    QPen GetAxisSubTickPen_x() const { return xAxis->subTickPen(); }
    QColor GetAxisSubTickPenColor_x() const { return xAxis->subTickPen().color(); }

    QPen GetAxis2SubTickPen_x() const { return xAxis2->subTickPen(); }
    QColor GetAxis2SubTickPenColor_x() const { return xAxis2->subTickPen().color(); }

    QPen GetAxisSubTickPen_y() const { return yAxis->subTickPen(); }
    QColor GetAxisSubTickPenColor_y() const { return yAxis->subTickPen().color(); }

    QPen GetAxis2SubTickPen_y() const { return yAxis2->subTickPen(); }
    QColor GetAxis2SubTickPenColor_y() const { return yAxis2->subTickPen().color(); }

    QPen GetAxisGridPen_x() const { return xAxis->grid()->pen(); }
    QColor GetAxisGridPenColor_x() const { return xAxis->grid()->pen().color(); }

    QPen GetAxis2GridPen_x() const { return xAxis2->grid()->pen(); }
    QColor GetAxis2GridPenColor_x() const { return xAxis2->grid()->pen().color(); }

    QPen GetAxisGridPen_y() const { return yAxis->grid()->pen(); }
    QColor GetAxisGridPenColor_y() const { return yAxis->grid()->pen().color(); }

    QPen GetAxis2GridPen_y() const { return yAxis->grid()->pen(); }
    QColor GetAxis2GridPenColor_y() const { return yAxis->grid()->pen().color(); }

    QPen GetAxisSubGridPen_x() const { return xAxis->grid()->subGridPen(); }
    QColor GetAxisSubGridPenColor_x() const { return xAxis->grid()->subGridPen().color(); }

    QPen GetAxis2SubGridPen_x() const { return xAxis2->grid()->subGridPen(); }
    QColor GetAxis2SubGridPenColor_x() const { return xAxis2->grid()->subGridPen().color(); }

    QPen GetAxisSubGridPen_y() const { return yAxis->grid()->subGridPen(); }
    QColor GetAxisSubGridPenColor_y() const { return yAxis->grid()->subGridPen().color(); }

    QPen GetAxis2SubGridPen_y() const { return yAxis2->grid()->subGridPen(); }
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

    QStringList ScatterShapeList( void );
    QStringList GraphLineStyleList( void );
    QStringList BarsWidthType( void );

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
    void SetAxisBasePenColor_x(QColor color);

    void SetAxis2BasePen_x(QPen pen);
    void SetAxis2BasePenColor_x(QColor color);

    void SetAxisBasePen_y(QPen pen);
    void SetAxisBasePenColor_y(QColor color);

    void SetAxis2BasePen_y(QPen pen);
    void SetAxis2BasePenColor_y(QColor color);

    void SetAxisTickPen_x(QPen pen);
    void SetAxisTickPenColor_x(QColor color);

    void SetAxis2TickPen_x(QPen pen);
    void SetAxis2TickPenColor_x(QColor color);

    void SetAxisTickPen_y(QPen pen);
    void SetAxisTickPenColor_y(QColor color);

    void SetAxis2TickPen_y(QPen pen);
    void SetAxis2TickPenColor_y(QColor color);

    void SetAxisSubTickPen_x(QPen pen);
    void SetAxisSubTickPenColor_x(QColor color);

    void SetAxis2SubTickPen_x(QPen pen);
    void SetAxis2SubTickPenColor_x(QColor color);

    void SetAxisSubTickPen_y(QPen pen);
    void SetAxisSubTickPenColor_y(QColor color);

    void SetAxis2SubTickPen_y(QPen pen);
    void SetAxis2SubTickPenColor_y(QColor color);

    void SetAxisGridPen_x(QPen pen);
    void SetAxisGridPenColor_x(QColor color);

    void SetAxis2GridPen_x(QPen pen);
    void SetAxis2GridPenColor_x(QColor color);

    void SetAxisGridPen_y(QPen pen);
    void SetAxisGridPenColor_y(QColor color);

    void SetAxis2GridPen_y(QPen pen);
    void SetAxis2GridPenColor_y(QColor color);

    void SetAxisSubGridPen_x(QPen pen);
    void SetAxisSubGridPenColor_x(QColor color);

    void SetAxis2SubGridPen_x(QPen pen);
    void SetAxis2SubGridPenColor_x(QColor color);

    void SetAxisSubGridPen_y(QPen pen);
    void SetAxisSubGridPenColor_y(QColor color);

    void SetAxis2SubGridPen_y(QPen pen);
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

protected:
    QPen m_qSelectionDecorator;

};

#endif // CATQCUSTOMPLOT_H
