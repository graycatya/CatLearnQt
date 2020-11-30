#include "CatAbout.h"
#include "ui_CatAbout.h"

#include <QFile>

CatAbout::CatAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatAbout)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

CatAbout::~CatAbout()
{
    delete ui;
}

void CatAbout::InitUi()
{
    ui->RootLayout->setStretchFactor(ui->LogVboxLayout, 2);
    ui->RootLayout->setStretchFactor(ui->AboutTabWidget, 8);
    ui->LicenceTextEdit->setReadOnly(true);
    ui->AboutTabWidget->setAttribute(Qt::WA_StyledBackground);
    ui->AboutTabWidget->setAttribute(Qt::WA_TranslucentBackground);
}

void CatAbout::InitProperty()
{
    QFile file_0(":/qss/CatGray/CatAbout.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();

    QFile file_licence(":/about/Licence/Licence.md");
    file_licence.open(QIODevice::ReadOnly);
    QString licencemd = QLatin1String(file_licence.readAll());
    ui->LicenceTextEdit->setMarkdown(licencemd);
    file_licence.close();
}
