#include "Test10.h"
#include "ui_Test10.h"

Test10::Test10(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test10)
{
    ui->setupUi(this);
}

Test10::~Test10()
{
    delete ui;
}
