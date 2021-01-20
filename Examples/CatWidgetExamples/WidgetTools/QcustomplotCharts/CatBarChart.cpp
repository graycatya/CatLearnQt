#include "CatBarChart.h"
#include "ui_CatBarChart.h"

CatBarChart::CatBarChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatBarChart)
{
    ui->setupUi(this);
}

CatBarChart::~CatBarChart()
{
    delete ui;
}
