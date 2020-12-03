#include "CatAbout.h"
#include "ui_CatAbout.h"

#include <QFile>
#include <QDesktopServices>

CatAbout::CatAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatAbout)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
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
    ui->AppName->setText(APP_NAME);
    ui->AppVersion->setText(APP_VERSION);

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

    QFile file_explain(":/about/explain/explain_en.md");
    file_explain.open(QIODevice::ReadOnly);
    QString explain = QLatin1String(file_explain.readAll());
    ui->Explain->setText(explain);
    file_explain.close();

    ui->AboutTabWidget->installEventFilter(this);
    ui->AboutTabWidget->setMouseTracking(true);

    /*connect(ui->Test, &QTextBrowser::anchorClicked, this, [=](QUrl url){
        QDesktopServices::openUrl(url);
    });*/
}

void CatAbout::InitConnect()
{
    connect(ui->GrayCatYa, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl("https://www.graycatya.com/"));
    });
    connect(ui->GitHub, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl("https://github.com/graycatya/CatLearnQt"));
    });
    connect(ui->Gitee, &QPushButton::clicked, this, [=](){
        QDesktopServices::openUrl(QUrl("https://gitee.com/graycatya/CatLearnQt"));
    });
}
