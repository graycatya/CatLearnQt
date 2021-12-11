#include "InputTools.h"
#include "ui_InputTools.h"

InputTools::InputTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputTools)
{
    ui->setupUi(this);
}

InputTools::~InputTools()
{
    delete ui;
}
