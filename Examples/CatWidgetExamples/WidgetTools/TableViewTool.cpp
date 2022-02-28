#include "TableViewTool.h"
#include "ui_TableViewTool.h"
#include "../CatConfig/CatConfig.h"


#include <CatLog>
#include <QFile>

TableViewTool::TableViewTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewTool)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    UpdateStyle();
}

TableViewTool::~TableViewTool()
{
    delete ui;
}

void TableViewTool::InitUi()
{

}

void TableViewTool::InitProperty()
{
    UpdateStyle();
}

void TableViewTool::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void TableViewTool::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "TableViewTool.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}
