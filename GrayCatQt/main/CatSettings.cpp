#include "CatSettings.h"
#include "ui_CatSettings.h"

#include <QFile>
#include <QListView>
#include "CatConfig/CatConfig.h"
#include <QDebug>
#include <QTimer>

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
    QFile file_0(":/qss/CatGray/CatSettings.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatSettings::InitConnect()
{
    /*connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        qDebug() << "update style: " << CatConfig::GetValue("style", "Defaule");
    });*/

    connect(ui->StyleComboBox, &QComboBox::currentTextChanged, this, [=](QString style){
        if(!style.isEmpty() && !m_bShowWidget)
        {
            CatConfig::Instance()->SetWindowStyle(style);
        }
        m_bShowWidget = false;
    });
}

void CatSettings::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->StyleComboBox->clear();

    m_bShowWidget = true;

    QMultiMap<QString, QVariant> styles = CatConfig::GetArray("StyleSheets", {"style", "style"});
    for (QMultiMap<QString, QVariant>::iterator i = styles.begin(); i != styles.end(); i++)
    {
        ui->StyleComboBox->addItem(i.value().toString());
    }
    ui->StyleComboBox->setCurrentText(CatConfig::GetValue("style", "Defaule").toString());

}
