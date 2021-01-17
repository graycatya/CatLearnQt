#include "SliderTools.h"
#include "ui_SliderTools.h"
#include "../CatConfig/CatConfig.h"


#include <CatLog>
#include <QFile>
#include <QSlider>

SliderTools::SliderTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderTools)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    UpdateStyle();
}

SliderTools::~SliderTools()
{
    delete ui;
}

void SliderTools::InitUi()
{
    InitDefauleSlider();
}

void SliderTools::InitProperty()
{
    UpdateStyle();
}

void SliderTools::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void SliderTools::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "SliderTools.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void SliderTools::InitDefauleSlider()
{
    QSlider *Slider0 = new QSlider(this);
    Slider0->setObjectName("Slider0");
    Slider0->setOrientation(Qt::Horizontal);
    Slider0->setValue(50);
    ui->SilderVbLayout->addWidget(Slider0);

    QSlider *Slider1 = new QSlider(this);
    Slider1->setObjectName("Slider1");
    Slider1->setOrientation(Qt::Horizontal);
    Slider1->setValue(30);
    ui->SilderVbLayout->addWidget(Slider1);

    QSlider *Slider2 = new QSlider(this);
    Slider2->setObjectName("Slider2");
    Slider2->setOrientation(Qt::Vertical);
    Slider2->setValue(50);
    ui->SilderHbLayout->addWidget(Slider2);

    QSlider *Slider3 = new QSlider(this);
    Slider3->setObjectName("Slider3");
    Slider3->setOrientation(Qt::Vertical);
    Slider3->setValue(30);
    ui->SilderHbLayout->addWidget(Slider3);

}


