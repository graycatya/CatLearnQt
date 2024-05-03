#include "CatSettings.h"
#include "ui_CatSettings.h"

#include <QFile>
#include <QListView>
#include "CatConfig/CatConfig.h"
#include <QDebug>
#include <QTimer>
#include <QFileDialog>

CatSettings::CatSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatSettings),
    m_bShowWidget(false)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

CatSettings::~CatSettings()
{
    delete ui;
}

void CatSettings::InitUi()
{
    ui->RootLayout->setStretchFactor(ui->LogVboxLayout, 2);
    ui->RootLayout->setStretchFactor(ui->ScrollRootArea, 8);
    QListView *view = new QListView();
    view->setObjectName("StyleComboBoxView");
    ui->StyleComboBox->setView(view);
}

void CatSettings::InitProperty()
{
    InitSettings();
    UpdateStyle();
}

void CatSettings::InitConnect()
{
    /*connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        qDebug() << "update style: " << CatConfig::GetValue("style", "Defaule");
    });*/
    connect(ui->StyleComboBox, &QComboBox::currentTextChanged, this, [=](QString style){
        if(!style.isEmpty() && !m_bShowWidget)
        {
            CatConfig::Instance()->SetStyle(style);
        }
        m_bShowWidget = false;
    });


    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatSettings::InitSettings()
{
    ui->StyleComboBox->clear();


    ui->StyleComboBox->addItems(CatConfig::GetStyles());
    ui->StyleComboBox->setCurrentText(CatConfig::GetStyle());
}

void CatSettings::UpdateStyle()
{
    QString stylePath;
    stylePath = ":/qss/" + CatConfig::GetStyle() + "/";

    QFile file_0(stylePath + "CatSettings.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatSettings::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    //m_bShowWidget = true;
}

void CatSettings::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        this->ui->retranslateUi(this);
    } else {
        QWidget::changeEvent(event);
    }
}

void CatSettings::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
}

