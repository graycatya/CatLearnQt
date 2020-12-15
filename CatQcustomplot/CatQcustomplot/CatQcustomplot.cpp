#include "CatQcustomplot.h"

CatQcustomplot::CatQcustomplot(QWidget *parent)
    : QCustomPlot(parent)
{
    /*setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);
    xAxis->setRange(-8, 8);
    yAxis->setRange(-5, 5);
    axisRect()->setupFullAxesBox();*/
}

CatQcustomplot::~CatQcustomplot()
{

}
