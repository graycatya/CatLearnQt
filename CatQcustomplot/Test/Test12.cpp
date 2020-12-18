#include "Test12.h"
#include "ui_Test12.h"

Test12::Test12(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Test12)
{
    ui->setupUi(this);
}

Test12::~Test12()
{
    delete ui;
}
