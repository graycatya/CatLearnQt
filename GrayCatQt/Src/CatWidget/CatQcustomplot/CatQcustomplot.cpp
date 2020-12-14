#include "CatQcustomplot.h"

CatQcustomplot::CatQcustomplot(CHART chart, QWidget *parent)
    : QCustomPlot(parent)
    , m_yChart(chart)
{
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
    xAxis->setRange(-8, 8);
    yAxis->setRange(-5, 5);
    axisRect()->setupFullAxesBox();
}

CatQcustomplot::~CatQcustomplot()
{

}
