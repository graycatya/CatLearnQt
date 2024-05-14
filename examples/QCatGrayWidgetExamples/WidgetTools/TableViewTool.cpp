#include "TableViewTool.h"
#include "ui_TableViewTool.h"
#include "../CatConfig/CatConfig.h"


#include <CatLog>
#include <QFile>
#include <QDateTime>

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
    QDateTime time = QDateTime::currentDateTime();
    for(int i = 0; i < 1000; i++)
    {
        TableData data;
        data.state = ((i % 2) == 0);
        data.time = time.toString("yyyy-MM-dd HH:mm:ss");
        time = time.addSecs(1);
        TableDatas.append(data);
    }


    ui->Paging->ClearStyle();
    ui->Paging->InitPaginNavigation(TableDatas.size(), 20);
    ui->Paging->Layout()->setSpacing(5);
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

    connect(ui->Paging, &CatPagingNavigation::CurrentPageed, this, [=](qulonglong currentpage){
        onCurrentPage(currentpage);
    });

    ui->Paging->SetCurrentPage(1);
    onCurrentPage(1);
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

void TableViewTool::onCurrentPage(int page)
{
    ui->TableView->ClearTable();
    int start = (page - 1) * ui->Paging->GetItemsPerPages();

    for(int i = start;
        i < static_cast<int>(start + ui->Paging->GetItemsPerPages());
        i++)
    {
        ui->TableView->AddData(TableDatas.at(i).state, TableDatas.at(i).time);
    }
}
