#include "CatQcustomplotTools.h"
#include "ui_CatQcustomplotTools.h"

#include <CatLog>
#include <QFile>
#include <QPushButton>

#include "../CatConfig/CatConfig.h"
#include "CatControl/ListingOptions.h"

CatQcustomplotTools::CatQcustomplotTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatQcustomplotTools)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

CatQcustomplotTools::~CatQcustomplotTools()
{
    delete ui;
}

void CatQcustomplotTools::InitUi()
{
    InitChartsTool();
}

void CatQcustomplotTools::InitProperty()
{
    UpdateStyle();
}

void CatQcustomplotTools::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatQcustomplotTools::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_1(stylePath + "ListingOptionQcustompCharts.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pToolListiongOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(stylePath + "CatQcustomplotTools.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatQcustomplotTools::InitChartsTool()
{
    QVBoxLayout *layout_0 = new QVBoxLayout(ui->QCustomplptToolWidget);
    layout_0->setContentsMargins(0,0,0,0);
    layout_0->setSpacing(0);
    m_pToolListiongOptions = new ListiongOptions(ListiongOptions::HBox, ui->QCustomplptToolWidget);
    //m_pToolListiongOptions->GetWidget()->setObjectName("CatQcustomplotListOptions");
    layout_0->addWidget(m_pToolListiongOptions);
    QStringList list = { "CatLineChart" };
    for(int i = 0; i < list.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pToolListiongOptions->GetRootWidget());
        button->setObjectName(list[i]);
        m_pToolListiongOptions->AddButton(button, i);
        m_pToolButtons[list[i]] = button;
    }
    QSpacerItem* item = new QSpacerItem(60, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pToolListiongOptions->AddItem(item);

    static_cast<QHBoxLayout*>(m_pToolListiongOptions->GetButtonlayout())->setSpacing(2);
}
