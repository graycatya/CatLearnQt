#ifndef CATLINECHARTS_H
#define CATLINECHARTS_H

#include "CatQcustomplot/CatQcustomplot.h"

class CatLineCharts : public CatQcustomplot
{
    Q_OBJECT
public:
    explicit CatLineCharts(QWidget *parent = nullptr);
    ~CatLineCharts();
};

#endif // CATLINECHARTS_H
