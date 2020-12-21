#include "CatLineChart.h"
#include "ui_CatLineChart.h"

CatLineChart::CatLineChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatLineChart)
{
    ui->setupUi(this);
}

CatLineChart::~CatLineChart()
{
    delete ui;
}
