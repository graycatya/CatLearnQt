#include "PagingNavigationTools.h"
#include "ui_PagingNavigationTools.h"

#include "CatControl/CatPagingNavigation.h"

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
    CatPagingNavigation *m_pCatPagingNavigation_1 = new CatPagingNavigation(this);
    ui->PagingNavigationLayout_1->addWidget(m_pCatPagingNavigation_1);
}

void PagingNavigationTools::InitProperty()
{

}

void PagingNavigationTools::InitConnect()
{

}
