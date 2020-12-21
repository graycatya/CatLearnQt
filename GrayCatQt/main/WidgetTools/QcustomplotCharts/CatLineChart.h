#ifndef CATLINECHART_H
#define CATLINECHART_H

#include <QWidget>

namespace Ui {
class CatLineChart;
}

class CatLineChart : public QWidget
{
    Q_OBJECT

public:
    explicit CatLineChart(QWidget *parent = nullptr);
    ~CatLineChart();

private:
    Ui::CatLineChart *ui;
};

#endif // CATLINECHART_H
