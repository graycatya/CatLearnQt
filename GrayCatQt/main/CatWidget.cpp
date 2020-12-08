#include "CatWidget.h"
#include "ui_CatWidget.h"

CatWidget::CatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatWidget)
{
    ui->setupUi(this);
}

CatWidget::~CatWidget()
{
    delete ui;
}
