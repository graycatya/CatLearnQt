#ifndef CATQCUSTOMPLOT_H
#define CATQCUSTOMPLOT_H

#include "qcustomplot.h"

class CatQcustomplot : public QCustomPlot
{
    Q_OBJECT
    // 图表背景
    Q_PROPERTY(QBrush Background READ GetBackground WRITE SetBackground)
     // 管理图例
    Q_PROPERTY(QBrush LegendBackground READ GetLegendBackground WRITE SetLegendBackground)

public:
    explicit CatQcustomplot(QWidget *parent = nullptr);
    ~CatQcustomplot();


    QBrush GetBackground();
    QBrush GetLegendBackground();

    QStringList ScatterShapeList( void );

public slots:
    void SetBackground(QBrush brush);
    void SetLegendBackground(QBrush brush);



};

#endif // CATQCUSTOMPLOT_H
