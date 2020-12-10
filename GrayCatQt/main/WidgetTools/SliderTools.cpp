#include "SliderTools.h"
#include "ui_SliderTools.h"

SliderTools::SliderTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderTools)
{
    ui->setupUi(this);
}

SliderTools::~SliderTools()
{
    delete ui;
}
