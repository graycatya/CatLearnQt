#include "QuickSliders.h"
#include "ui_QuickSliders.h"
#include <QQuickItem>

#include "../CatConfig/CatConfig.h"


QuickSliders::QuickSliders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickSliders)
{
    ui->setupUi(this);
    InitUi();
    InitConnect();
    InitProperty();

}

QuickSliders::~QuickSliders()
{
    delete ui;
}

void QuickSliders::InitUi()
{
    QUrl source("qrc:/qml/CatSliders.qml");
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    // 如果此属性设置为SizeRootObjectToView，视图将自动将根项调整为视图的大小。
    ui->QuickSlidersWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->QuickSlidersWidget->setSource(source);
    ui->QuickSlidersWidget->setClearColor(QColor(Qt::transparent));

}

void QuickSliders::InitProperty()
{
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    UpdateStyle();
}

void QuickSliders::InitConnect()
{
    QQuickItem *item = ui->QuickSlidersWidget->rootObject();

    connect(this, SIGNAL(setRootBackgroundColor(QColor)), item, SIGNAL(setRootBackgroundColor(QColor)));
    connect(this, SIGNAL(setSliderBackgroundColor(QColor)), item, SIGNAL(setSliderBackgroundColor(QColor)));
    connect(this, SIGNAL(setSliderColor(QColor)), item, SIGNAL(setSliderColor(QColor)));
    connect(this, SIGNAL(setSlidingBlockColor(QColor)), item, SIGNAL(setSlidingBlockColor(QColor)));
    connect(this, SIGNAL(setSlidingBlockPressColor(QColor)), item, SIGNAL(setSlidingBlockPressColor(QColor)));
    connect(this, SIGNAL(setSlidingBorderColor(QColor)), item, SIGNAL(setSlidingBorderColor(QColor)));
    connect(this, SIGNAL(setTextColor(QColor)), item, SIGNAL(setTextColor(QColor)));
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void QuickSliders::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "QuickSliders.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}


void QuickSliders::SetRootBackgroundColor(QColor color)
{
    emit setRootBackgroundColor(color);
}

void QuickSliders::SetSliderBackgroundColor(QColor color)
{
    emit setSliderBackgroundColor(color);
}

void QuickSliders::SetSliderColor(QColor color)
{
    emit setSliderColor(color);
}

void QuickSliders::SetSlidingBlockColor(QColor color)
{
    emit setSlidingBlockColor(color);
}

void QuickSliders::SetSlidingBlockPressColor(QColor color)
{
    emit setSlidingBlockPressColor(color);
}

void QuickSliders::SetSlidingBorderColor(QColor color)
{
    emit setSlidingBorderColor(color);
}

void QuickSliders::SetTextColor(QColor color)
{
    emit setTextColor(color);
}
