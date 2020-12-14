#include "RimlessWindowTool.h"
#include "ui_RimlessWindowTool.h"

RimlessWindowTool::RimlessWindowTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RimlessWindowTool)
{
    ui->setupUi(this);
}

RimlessWindowTool::~RimlessWindowTool()
{
    delete ui;
}
