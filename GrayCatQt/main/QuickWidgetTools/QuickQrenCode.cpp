#include "QuickQrenCode.h"
#include "ui_QuickQrenCode.h"

QuickQrenCode::QuickQrenCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickQrenCode)
{
    ui->setupUi(this);
}

QuickQrenCode::~QuickQrenCode()
{
    delete ui;
}
