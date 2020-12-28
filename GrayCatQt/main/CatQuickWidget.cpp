#include "CatQuickWidget.h"
#include "ui_CatQuickWidget.h"
#include "CatConfig/CatConfig.h"
#include "CatControl/ListingOptions.h"

#include <QPushButton>
#include <QButtonGroup>
#include <CatLog>
#include <QFile>
#include <QQmlDebuggingEnabler>


#include "QuickWidgetTools/QuickSliders.h"
#include "QuickWidgetTools/QuickQrenCode.h"


CatQuickWidget::CatQuickWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatQuickWidget)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

CatQuickWidget::~CatQuickWidget()
{
    QString log = QString("CatQuickWidget Delete...");
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
    delete ui;
}

void CatQuickWidget::InitUi()
{
    InitToolWidgets();
    InitToolButtons();
}

void CatQuickWidget::InitProperty()
{
    m_pToolButtons["CatQmlSliders"]->setChecked(true);

    UpdateStyle();
}

void CatQuickWidget::InitConnect()
{
    connect(m_pToolListiongOptions->GetButtonGroup(), SIGNAL(buttonClicked(int)), this, SLOT(On_ToolButtons(int)));
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatQuickWidget::InitToolButtons()
{
    QVBoxLayout *layout_ToolOptions = new QVBoxLayout(ui->ToolWidget);
    layout_ToolOptions->setContentsMargins(0,5,0,5);
    layout_ToolOptions->setSpacing(0);
    m_pToolListiongOptions = new ListiongOptions(ListiongOptions::VBox, ui->ToolWidget);
    layout_ToolOptions->addWidget(m_pToolListiongOptions);

    static_cast<QVBoxLayout*>(m_pToolListiongOptions->GetButtonlayout())->setSpacing(2);

    QStringList ToolButtonList = {"CatQmlSliders", "CatQmlQrenCode"};
    for(int i = 0; i < ToolButtonList.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pToolListiongOptions->GetRootWidget());
        button->setObjectName(ToolButtonList[i]);
        m_pToolListiongOptions->AddButton(button, i);
        m_pToolButtons[ToolButtonList[i]] = button;
    }

    QSpacerItem* item = new QSpacerItem(50, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_pToolListiongOptions->AddItem(item);
}

void CatQuickWidget::InitToolWidgets()
{
    m_pQuickSliders = new QuickSliders;
    m_pQuickSliders->setObjectName("QuickSlidersWidget");
    ui->ToolStackedWidget->addWidget(m_pQuickSliders);

    m_pQuickQrenCode = new QuickQrenCode;
    m_pQuickQrenCode->setObjectName("QuickQrenCodeWidget");
    ui->ToolStackedWidget->addWidget(m_pQuickQrenCode);


}

void CatQuickWidget::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_1(stylePath + "ListingOptionCatQuickWidgetTool.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pToolListiongOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(stylePath + "CatQuickWidget.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatQuickWidget::On_ToolButtons(int id)
{
    ui->ToolStackedWidget->setCurrentIndex(id);
}
