#include "QuickSliders.h"
#include "ui_QuickSliders.h"

QuickSliders::QuickSliders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickSliders)
{
    ui->setupUi(this);
}

QuickSliders::~QuickSliders()
{
    delete ui;
}
