#include "CatQuickWidget.h"
#include "ui_CatQuickWidget.h"

CatQuickWidget::CatQuickWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatQuickWidget)
{
    ui->setupUi(this);
}

CatQuickWidget::~CatQuickWidget()
{
    delete ui;
}
