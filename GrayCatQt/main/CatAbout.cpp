#include "CatAbout.h"
#include "ui_CatAbout.h"

CatAbout::CatAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatAbout)
{
    ui->setupUi(this);
}

CatAbout::~CatAbout()
{
    delete ui;
}
