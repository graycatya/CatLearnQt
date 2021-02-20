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
    QListView *view_1 = new QListView();
    view_1->setObjectName("StyleComboBoxView");
    ui->LangComboBox->setView(view_1);
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
            CatConfig::Instance()->SetWindowStyle(style);
        }
        m_bShowWidget = false;
    });
    connect(ui->LangComboBox, &QComboBox::currentTextChanged, this, [=](QString lang){
        if(!lang.isEmpty())
        {
            CatConfig::Instance()->SetTranslator(QVariant(lang));
        }
    });


    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatSettings::InitSettings()
{
    ui->StyleComboBox->clear();

    QMultiMap<QString, QVariant> styles = CatConfig::GetArray("StyleSheets", {"style", "style"});
    for (QMultiMap<QString, QVariant>::iterator i = styles.begin(); i != styles.end(); i++)
    {
        ui->StyleComboBox->addItem(i.value().toString());
    }
    ui->StyleComboBox->setCurrentText(CatConfig::GetValue("style", "Defaule").toString());
    QMultiMap<QString, QVariant> langs = CatConfig::GetArray("Langs", {"lang", "lang"});
    for (QMultiMap<QString, QVariant>::iterator i = langs.begin(); i != langs.end(); i++)
    {
        ui->LangComboBox->addItem(i.value().toString());
    }
    ui->LangComboBox->setCurrentText(CatConfig::GetValue("Language", "Defaule").toString());
}

void CatSettings::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "CatSettings.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatSettings::SetSaveFilePathLineEdit(QString str)
{
    QFontMetrics fontMetrics(ui->SavePathEdit->font());
    if(fontMetrics.horizontalAdvance(str) > ui->SavePathEdit->width() - 5)
    {
        str = QFontMetrics(ui->SavePathEdit->font())
                .elidedText(str, Qt::ElideRight,
                            ui->SavePathEdit->width() - 5);
    }
    ui->SavePathEdit->setText(str);
}

void CatSettings::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    SetSaveFilePathLineEdit(CatConfig::GetValue("SaveFilePath").toString());
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
    SetSaveFilePathLineEdit(CatConfig::GetValue("SaveFilePath").toString());
}

void CatSettings::on_ChangeButton_clicked()
{
    QString filepath = QFileDialog::getExistingDirectory(this,
                                      tr("Select the road strength to be saved"),
                                      CatConfig::GetValue("SaveFilePath").toString());
    if(!filepath.isEmpty())
    {
        CatConfig::SetValue("SaveFilePath", filepath);
    }
    SetSaveFilePathLineEdit(CatConfig::GetValue("SaveFilePath").toString());
}
