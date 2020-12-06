#include "CatSettings.h"
#include "ui_CatSettings.h"

CatSettings::CatSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatSettings)
{
    ui->setupUi(this);
}

CatSettings::~CatSettings()
{
    delete ui;
}
