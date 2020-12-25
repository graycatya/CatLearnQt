#include "CatAbout.h"
#include "ui_CatAbout.h"
#include "CatConfig/CatConfig.h"

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
    ui->ThankTextBrowser->setReadOnly(true);
    ui->AboutTabWidget->setAttribute(Qt::WA_StyledBackground);
    ui->AboutTabWidget->setAttribute(Qt::WA_TranslucentBackground);

}

void CatAbout::InitProperty()
{

    UpdateStyle();
#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
    QFile file_licence(":/about/Licence/Licence.html");
    file_licence.open(QIODevice::ReadOnly);
    QString licencemd = QLatin1String(file_licence.readAll());
    ui->LicenceTextEdit->setHtml(licencemd);
    file_licence.close();
#else
    QFile file_licence(":/about/Licence/Licence.md");
    file_licence.open(QIODevice::ReadOnly);
    QString licencemd = QLatin1String(file_licence.readAll());
    ui->LicenceTextEdit->setMarkdown(licencemd);
    file_licence.close();
#endif
    retranslateUi();

    ui->AboutTabWidget->installEventFilter(this);
    ui->AboutTabWidget->setMouseTracking(true);

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

    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    connect(ui->ThankTextBrowser, &QTextBrowser::anchorClicked, this, [=](QUrl url){
        retranslateUi();
        QDesktopServices::openUrl(url);
    });
    //connect(ui->ThankTextEdit, &QTextEdit::scrollToAnchor);
}

void CatAbout::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "CatAbout.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();


}

void CatAbout::retranslateUi()
{
    QString lang = CatConfig::GetValue("Language", "Defaule").toString();
    QString explain = ":/about/explain/explain";
    QString thank = ":/about/thank/Thank";
    if(lang == "chinese(china)") {
        explain += "_cn";
        thank += "_cn";
    } else {
        explain += "_en";
        thank += "_en";
    }
    thank += ".html";
#if (QT_VERSION < QT_VERSION_CHECK(5, 14, 0))
    explain += ".html";
#else
    explain += ".md";
#endif
    QFile file_explain(explain);
    file_explain.open(QIODevice::ReadOnly);
    QString str_explain = file_explain.readAll();
    ui->Explain->setText(str_explain);
    file_explain.close();

    QFile file_thank(thank);
    file_thank.open(QIODevice::ReadOnly);
    QString str_thank = file_thank.readAll();
    ui->ThankTextBrowser->setHtml(str_thank);

    file_thank.close();




    ui->AppName->setText(APP_NAME);
    ui->AppVersion->setText(APP_VERSION);
}

void CatAbout::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        this->ui->retranslateUi(this);
        this->retranslateUi();
    } else {
        QWidget::changeEvent(event);
    }
}
