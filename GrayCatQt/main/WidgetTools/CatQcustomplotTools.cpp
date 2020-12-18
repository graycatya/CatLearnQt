#include "CatQcustomplotTools.h"
#include "ui_CatQcustomplotTools.h"

CatQcustomplotTools::CatQcustomplotTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatQcustomplotTools)
{
    ui->setupUi(this);
}

CatQcustomplotTools::~CatQcustomplotTools()
{
    delete ui;
}
