#include "CatGrayQuickWidget.h"
#include "ui_CatGrayQuickWidget.h"
#include "CatConfig/CatConfig.h"
#include "QCatGrayListingOptions.h"

#include <QPushButton>
#include <QButtonGroup>
#include <QFile>
#include <QQmlDebuggingEnabler>
#include "CatGrayQuickWidgetTest.h"

CatGrayQuickWidget::CatGrayQuickWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatGrayQuickWidget)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

CatGrayQuickWidget::~CatGrayQuickWidget()
{
    delete ui;
}

void CatGrayQuickWidget::InitUi()
{
    InitToolWidgets();
    InitToolButtons();
}

void CatGrayQuickWidget::InitProperty()
{
    m_pToolButtons["CatGrayQuickWidgetTest"]->setChecked(true);

    UpdateStyle();
}

void CatGrayQuickWidget::InitConnect()
{
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    connect(m_pToolListiongOptions->GetButtonGroup(), SIGNAL(buttonClicked(int)), this, SLOT(On_ToolButtons(int)));
#else
    connect(m_pToolListiongOptions->GetButtonGroup(), SIGNAL(idClicked(int)), this, SLOT(On_ToolButtons(int)));
#endif

    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatGrayQuickWidget::InitToolButtons()
{
    QVBoxLayout *layout_ToolOptions = new QVBoxLayout(ui->ToolWidget);
    layout_ToolOptions->setContentsMargins(0,5,0,5);
    layout_ToolOptions->setSpacing(0);
    m_pToolListiongOptions = new QCatGrayListingOptions(QCatGrayListingOptions::VBox, ui->ToolWidget);
    layout_ToolOptions->addWidget(m_pToolListiongOptions);

    static_cast<QVBoxLayout*>(m_pToolListiongOptions->GetButtonlayout())->setSpacing(2);

    QStringList ToolButtonList = {"CatGrayQuickWidgetTest"};
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

void CatGrayQuickWidget::InitToolWidgets()
{
    m_pCatGrayQuickWidgetTest = new CatGrayQuickWidgetTest;
    m_pCatGrayQuickWidgetTest->setObjectName("CatGrayQuickWidgetTest");
    ui->ToolStackedWidget->addWidget(m_pCatGrayQuickWidgetTest);
}

void CatGrayQuickWidget::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_1(stylePath + "ListingOptionCatGrayQuickWidgetTool.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pToolListiongOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(stylePath + "CatGrayQuickWidget.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatGrayQuickWidget::On_ToolButtons(int id)
{
    ui->ToolStackedWidget->setCurrentIndex(id);
}
