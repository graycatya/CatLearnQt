#include "CatQcustomplotTools.h"
#include "ui_CatQcustomplotTools.h"

#include <QFile>
#include <QPushButton>
#include <QButtonGroup>

#include "../CatConfig/CatConfig.h"
#include "CatControl/ListingOptions.h"

#include "QcustomplotCharts/CatLineChart.h"
#include "QcustomplotCharts/CatBarChart.h"

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
    InitChartWidgets();
}

void CatQcustomplotTools::InitProperty()
{
    UpdateStyle();
    m_pToolButtons["CatLineChart"]->setChecked(true);
}

void CatQcustomplotTools::InitConnect()
{
    connect(m_pToolListiongOptions->GetButtonGroup(), SIGNAL(buttonClicked(int)), this, SLOT(On_ToolButtons(int)));
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatQcustomplotTools::UpdateStyle()
{
    QString stylePath;
stylePath = ":/qss/" + CatConfig::GetStyle() + "/";

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
    QStringList list = { "CatLineChart", "CatBarGraph" };
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

void CatQcustomplotTools::InitChartWidgets()
{
    CatLineChart *m_pCatLineChart = new CatLineChart;
    m_pCatLineChart->setObjectName("CatLineChart");
    ui->QCustomplptToolStacked->addWidget(m_pCatLineChart);

    CatBarChart *m_pCatBarChart = new CatBarChart;
    m_pCatBarChart->setObjectName("CatBarChart");
    ui->QCustomplptToolStacked->addWidget(m_pCatBarChart);
}

void CatQcustomplotTools::On_ToolButtons(int id)
{
    ui->QCustomplptToolStacked->setCurrentIndex(id);
}

