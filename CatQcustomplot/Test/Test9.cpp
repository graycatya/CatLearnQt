#include "Test9.h"
#include "ui_Test9.h"

Test9::Test9(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test9)
{
    ui->setupUi(this);
}

Test9::~Test9()
{
    delete ui;
}
