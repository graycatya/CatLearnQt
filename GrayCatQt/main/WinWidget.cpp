#include "WinWidget.h"
#include "ui_WinWidget.h"

WinWidget::WinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinWidget)
{
    ui->setupUi(this);
}

WinWidget::~WinWidget()
{
    delete ui;
}
