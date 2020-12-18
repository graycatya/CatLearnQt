#ifndef CATLINECHART_H
#define CATLINECHART_H

#include "CatQcustomplot/CatQcustomplot.h"
#include "CatQcustomplot/CatAxisTag.h"

class CatLineChart : public CatQcustomplot
{
    Q_OBJECT
public:
    explicit CatLineChart(QWidget *parent = nullptr);
    ~CatLineChart();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

private:
    QPen m_pSelectionGraphPen;
    QCPGraph *m_pSelectGraph;
};

#endif // CATLINECHART_H
