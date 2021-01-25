#include "PagingNavigationTools.h"
#include "ui_PagingNavigationTools.h"

#include "../CatConfig/CatConfig.h"

#include "CatControl/CatPagingNavigation.h"

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
    ui->PagingNavigationWidget->InitPaginNavigation(1000, 50);
    /*CatPagingNavigation *m_pCatPagingNavigation_1 = new CatPagingNavigation(this);
    m_pCatPagingNavigation_1->InitPaginNavigation(1000, 10);
    connect(m_pCatPagingNavigation_1, &CatPagingNavigation::CurrentPageed, this, [=](qulonglong page){
        qDebug() << "Current Page: " << page;
    });
    ui->PagingNavigationLayout_1->addWidget(m_pCatPagingNavigation_1);*/
}

void PagingNavigationTools::InitProperty()
{
    UpdateStyle();
}

void PagingNavigationTools::InitConnect()
{

}

void PagingNavigationTools::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "PagingNavigationTools.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}
