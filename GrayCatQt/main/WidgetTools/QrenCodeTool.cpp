#include "QrenCodeTool.h"
#include "ui_QrenCodeTool.h"

QrenCodeTool::QrenCodeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QrenCodeTool)
{
    ui->setupUi(this);
}

QrenCodeTool::~QrenCodeTool()
{
    delete ui;
}
