#include "InputTools.h"
#include "ui_InputTools.h"
#include "../CatConfig/CatConfig.h"

#include <CatLog>
#include <QFile>
#include <QSlider>

#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QFontComboBox>
#include <QKeySequenceEdit>

InputTools::InputTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputTools)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    UpdateStyle();
}

InputTools::~InputTools()
{
    delete ui;
}

void InputTools::InitUi()
{
    InitDefauleSlider();
}

void InputTools::InitProperty()
{
    UpdateStyle();
}

void InputTools::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void InputTools::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "InputTools.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void InputTools::InitDefauleSlider()
{
    m_pCatFlowLayout = new CatFlowLayout(20, 10, 10);
    ui->InputLayout->addLayout(m_pCatFlowLayout);
    /*
        #include <QLineEdit>
        #include <QSpinBox>
        #include <QDoubleSpinBox>
        #include <QDateTimeEdit>
        #include <QDateEdit>
        #include <QComboBox>
        #include <QFontComboBox>
        #include <QKeySequenceEdit>
    */
    QLineEdit *lineedit = new QLineEdit(this);
    lineedit->setMinimumWidth(200);

    QSpinBox *spinbox = new QSpinBox(this);
    spinbox->setMinimumWidth(200);

    QDoubleSpinBox *doublespinbox = new QDoubleSpinBox(this);
    doublespinbox->setMinimumWidth(200);

    QDateTimeEdit *datetimedit = new QDateTimeEdit(this);
    datetimedit->setMinimumWidth(200);

    QDateEdit *dateedit = new QDateEdit(this);
    dateedit->setMinimumWidth(200);

    QComboBox *combobox = new QComboBox(this);
    combobox->setMinimumWidth(200);

    QFontComboBox *fontcombobox = new QFontComboBox(this);
    fontcombobox->setMinimumWidth(200);

    QKeySequenceEdit *keysequenceedit = new QKeySequenceEdit(this);
    keysequenceedit->setMinimumWidth(200);

    m_pCatFlowLayout->addWidget(lineedit);
    m_pCatFlowLayout->addWidget(spinbox);
    m_pCatFlowLayout->addWidget(doublespinbox);
    m_pCatFlowLayout->addWidget(datetimedit);
    m_pCatFlowLayout->addWidget(dateedit);
    m_pCatFlowLayout->addWidget(combobox);
    m_pCatFlowLayout->addWidget(fontcombobox);
    m_pCatFlowLayout->addWidget(keysequenceedit);

}
