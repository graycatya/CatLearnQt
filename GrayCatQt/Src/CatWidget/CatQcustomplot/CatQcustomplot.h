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
    Q_PROPERTY(QFont LegendFont READ GetLegendFont WRITE SetLegendFont)
    Q_PROPERTY(QPen LegendBorder READ GetLegendBorder WRITE SetLegendBorder)
    // 刻度与边的颜色 - 样式接口
    Q_PROPERTY(QPen AxisBasePen_x READ GetAxisBasePen_x WRITE SetAxisBasePen_x)
    Q_PROPERTY(QPen AxisBasePen_y READ GetAxisBasePen_y WRITE SetAxisBasePen_y)
    Q_PROPERTY(QPen AxisTickPen_x READ GetAxisTickPen_x WRITE SetAxisTickPen_x)
    Q_PROPERTY(QPen AxisTickPen_y READ GetAxisTickPen_y WRITE SetAxisTickPen_y)
    Q_PROPERTY(QPen AxisSubTickPen_x READ GetAxisSubTickPen_x WRITE SetAxisSubTickPen_x)
    Q_PROPERTY(QPen AxisSubTickPen_y READ GetAxisSubTickPen_y WRITE SetAxisSubTickPen_y)
    Q_PROPERTY(QPen AxisGridPen_x READ GetAxisGridPen_x WRITE SetAxisGridPen_x)
    Q_PROPERTY(QPen AxisGridPen_y READ GetAxisGridPen_y WRITE SetAxisGridPen_y)
    Q_PROPERTY(QPen AxisSubGridPen_x READ GetAxisSubGridPen_x WRITE SetAxisSubGridPen_x)
    Q_PROPERTY(QPen AxisSubGridPen_y READ GetAxisSubGridPen_y WRITE SetAxisSubGridPen_y)
    Q_PROPERTY(QColor AxisLabelColor_x READ GetAxisLabelColor_x WRITE SetAxisLabelColor_x)
    Q_PROPERTY(QColor AxisLabelColor_y READ GetAxisLabelColor_y WRITE SetAxisLabelColor_y)
    Q_PROPERTY(QFont AxisLabelFont_x READ GetAxisLabelFont_x WRITE SetAxisLabelFont_x)
    Q_PROPERTY(QFont AxisLabelFont_y READ GetAxisLabelFont_y WRITE SetAxisLabelFont_y)
    Q_PROPERTY(QColor AxisTickLabelColor_x READ GetAxisTickLabelColor_x WRITE SetAxisTickLabelColor_x)
    Q_PROPERTY(QColor AxisTickLabelColor_y READ GetAxisTickLabelColor_y WRITE SetAxisTickLabelColor_y)
    Q_PROPERTY(QFont AxisTickLabelFont_x READ GetAxisTickLabelFont_x WRITE SetAxisTickLabelFont_x)
    Q_PROPERTY(QFont AxisTickLabelFont_y READ GetAxisTickLabelFont_y WRITE SetAxisTickLabelFont_y)


public:
    explicit CatQcustomplot(QWidget *parent = nullptr);
    ~CatQcustomplot();

    // 获取图表样式
    QBrush GetBackground() const { return background(); }

    // 获取图列样式
    QBrush GetLegendBackground() const { return legend->brush(); }
    QFont GetLegendFont() const { return legend->font(); }
    QPen GetLegendBorder() const { return legend->borderPen(); }

    // 获取坐标轴样式
    QPen GetAxisBasePen_x() const { return xAxis->basePen(); }
    QPen GetAxisBasePen_y() const { return yAxis->basePen(); }
    QPen GetAxisTickPen_x() const { return xAxis->tickPen(); }
    QPen GetAxisTickPen_y() const { return yAxis->tickPen(); }
    QPen GetAxisSubTickPen_x() const { return xAxis->subTickPen(); }
    QPen GetAxisSubTickPen_y() const { return yAxis->subTickPen(); }
    QPen GetAxisGridPen_x() const { return xAxis->grid()->pen(); }
    QPen GetAxisGridPen_y() const { return yAxis->grid()->pen(); }
    QPen GetAxisSubGridPen_x() const { return xAxis->grid()->subGridPen(); }
    QPen GetAxisSubGridPen_y() const { return yAxis->grid()->subGridPen(); }
    QColor GetAxisLabelColor_x() const { return xAxis->labelColor(); }
    QColor GetAxisLabelColor_y() const { return yAxis->labelColor(); }
    QFont GetAxisLabelFont_x() const { return xAxis->labelFont(); }
    QFont GetAxisLabelFont_y() const { return yAxis->labelFont(); }
    QColor GetAxisTickLabelColor_x() const { return xAxis->tickLabelColor(); }
    QColor GetAxisTickLabelColor_y() const { return yAxis->tickLabelColor(); }
    QFont GetAxisTickLabelFont_x() const { return xAxis->tickLabelFont(); }
    QFont GetAxisTickLabelFont_y() const { return yAxis->tickLabelFont(); }

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
    void SetLegendFont(QFont font);
    void SetLegendBorder(QPen border);
    void SetAxisBasePen_x(QPen pen);
    void SetAxisBasePen_y(QPen pen);
    void SetAxisTickPen_x(QPen pen);
    void SetAxisTickPen_y(QPen pen);
    void SetAxisSubTickPen_x(QPen pen);
    void SetAxisSubTickPen_y(QPen pen);
    void SetAxisGridPen_x(QPen pen);
    void SetAxisGridPen_y(QPen pen);
    void SetAxisSubGridPen_x(QPen pen);
    void SetAxisSubGridPen_y(QPen pen);
    void SetAxisLabelColor_x(QColor color);
    void SetAxisLabelColor_y(QColor color);
    void SetAxisLabelFont_x(QFont font);
    void SetAxisLabelFont_y(QFont font);
    void SetAxisTickLabelColor_x(QColor color);
    void SetAxisTickLabelColor_y(QColor color);
    void SetAxisTickLabelFont_x(QFont font);
    void SetAxisTickLabelFont_y(QFont font);




};

#endif // CATQCUSTOMPLOT_H
