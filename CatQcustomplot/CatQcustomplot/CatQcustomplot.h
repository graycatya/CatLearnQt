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

public:
    explicit CatQcustomplot(QWidget *parent = nullptr);
    ~CatQcustomplot();

    QBrush GetBackground() const { return background(); }

    QBrush GetLegendBackground() const { return legend->brush(); }
    QFont GetLegendFont() const { return legend->font(); }
    QPen GetLegendBorder() const { return legend->borderPen(); }
    QPen GetAxisBasePen_x() const { return xAxis->basePen(); }
    QPen GetAxisBasePen_y() const { return yAxis->basePen(); }

    QStringList ScatterShapeList( void );
    QStringList GraphLineStyleList( void );
    QStringList BarsWidthType( void );

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



};

#endif // CATQCUSTOMPLOT_H
