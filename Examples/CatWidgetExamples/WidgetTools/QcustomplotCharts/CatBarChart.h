#ifndef CATBARCHART_H
#define CATBARCHART_H

#include <QWidget>

namespace Ui {
class CatBarChart;
}

class CatBarChart : public QWidget
{
    Q_OBJECT

public:
    explicit CatBarChart(QWidget *parent = nullptr);
    ~CatBarChart();

private:
    Ui::CatBarChart *ui;
};

#endif // CATBARCHART_H
