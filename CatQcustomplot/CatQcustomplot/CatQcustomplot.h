#ifndef CATQCUSTOMPLOT_H
#define CATQCUSTOMPLOT_H

#include "qcustomplot.h"

class CatQcustomplot : public QCustomPlot
{
    Q_OBJECT
public:
    enum CHART {
        LineChart,
        BarGraph
    };
    explicit CatQcustomplot(QWidget *parent = nullptr);
    ~CatQcustomplot();

private:
    CHART m_yChart;
};

#endif // CATQCUSTOMPLOT_H
