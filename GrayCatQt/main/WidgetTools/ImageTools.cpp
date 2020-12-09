#include "ImageTools.h"
#include "ui_ImageTools.h"

ImageTools::ImageTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageTools)
{
    ui->setupUi(this);
}

ImageTools::~ImageTools()
{
    delete ui;
}
