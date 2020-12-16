#include "Test11.h"
#include "ui_Test11.h"

Test11::Test11(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test11)
{
    ui->setupUi(this);
}

Test11::~Test11()
{
    delete ui;
}
