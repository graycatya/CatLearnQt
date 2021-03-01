#include "PagingNavigationTools.h"
#include "ui_PagingNavigationTools.h"

#include "../CatConfig/CatConfig.h"

#include "CatControl/CatPagingNavigation.h"
#include "CatControl/CatIntValidator.h"

#include <QDebug>
#include <QFile>

PagingNavigationTools::PagingNavigationTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagingNavigationTools)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

PagingNavigationTools::~PagingNavigationTools()
{
    delete ui;
}

void PagingNavigationTools::InitUi()
{
    CatIntValidator *intval = new CatIntValidator(this);
    currentpageval = new CatIntValidator(this);
    intval->setRange(1,99999999);
    ui->DataSumEdit->setValidator(intval);
    ui->ItemsPerPagesEdit->setValidator(intval);
    ui->DataSumEdit->setText(QString::number(10000));
    ui->ItemsPerPagesEdit->setText(QString::number(50));
    ui->CurrentPageEdit->setText(QString::number(1));
    ui->PagingNavigationWidget->ClearStyle();
    ui->PagingNavigationWidget->InitPaginNavigation(10000, 50);
    currentpageval->setRange(1, ui->PagingNavigationWidget->GetTotalPages());
    ui->TotalPagesEdit->setText(QString::number(ui->PagingNavigationWidget->GetTotalPages()));
    ui->PagingNavigationWidget->Layout()->setSpacing(5);
    ui->CurrentPageEdit->setValidator(currentpageval);
}

void PagingNavigationTools::InitProperty()
{
    UpdateStyle();
}

void PagingNavigationTools::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    connect(ui->PagingNavigationWidget, &CatPagingNavigation::CurrentPageed, this, [=](qulonglong currentpage){
        ui->CurrentPageEdit->setText(QString::number(currentpage));
    });

    connect(ui->PagingNavigationWidget, &CatPagingNavigation::TotalPageeed, this, [=](qulonglong totalpage){
        ui->TotalPagesEdit->setText(QString::number(totalpage));
        currentpageval->setRange(1, ui->PagingNavigationWidget->GetTotalPages());
    });
}

void PagingNavigationTools::UpdateStyle()
{
    QString stylePath;
stylePath = ":/qss/" + CatConfig::GetStyle() + "/";

    QFile file_0(stylePath + "PagingNavigationTools.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void PagingNavigationTools::on_InitPagingNavigationButton_clicked()
{
    qulonglong datasum = ui->DataSumEdit->text().toULongLong() == 0 ? 1 : ui->DataSumEdit->text().toULongLong();
    qulonglong itemsperpages = ui->ItemsPerPagesEdit->text().toULongLong() == 0 ? 1 : ui->ItemsPerPagesEdit->text().toULongLong();
    ui->PagingNavigationWidget->InitPaginNavigation(datasum, itemsperpages);
}

void PagingNavigationTools::on_UpdatePagingNavigationButton_clicked()
{
    qulonglong datasum = ui->DataSumEdit->text().toULongLong() == 0 ? 1 : ui->DataSumEdit->text().toULongLong();
    qulonglong itemsperpages = ui->ItemsPerPagesEdit->text().toULongLong() == 0 ? 1 : ui->ItemsPerPagesEdit->text().toULongLong();
    ui->PagingNavigationWidget->SetDataSum(datasum);
    ui->PagingNavigationWidget->SetItemsPerPages(itemsperpages);
}

void PagingNavigationTools::on_SetCurrentPageButton_clicked()
{
    ui->PagingNavigationWidget->SetCurrentPage(ui->CurrentPageEdit->text().toULongLong());
}
