#include "RimlessWindowTool.h"
#include "ui_RimlessWindowTool.h"
#include "../CatConfig/CatConfig.h"
#include <QVBoxLayout>
#include <QDebug>

#include <QFile>

#include "RimlessWindow.h"


RimlessWindowTool::RimlessWindowTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RimlessWindowTool)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

RimlessWindowTool::~RimlessWindowTool()
{
    delete ui;
}

void RimlessWindowTool::InitUi()
{
    QVBoxLayout *m_pRootLayout = new QVBoxLayout(this);
    m_pRootLayout->setContentsMargins(5,5,5,5);
    m_pRootLayout->setSpacing(0);
    m_pRimlessWindow = new RimlessWindow(this);
    m_pRimlessWindow->setObjectName("CatRimlessWindow");
    m_pRootLayout->addWidget(m_pRimlessWindow);
}

void RimlessWindowTool::InitProperty()
{
    setMouseTracking(true);
    m_pRimlessWindow->installEventFilter(this);
    m_pRimlessWindow->setMouseTracking(true);
    UpdateStyle();
}

void RimlessWindowTool::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void RimlessWindowTool::UpdateStyle()
{
    QString stylePath;
stylePath = ":/qss/" + CatConfig::GetStyle() + "/";

    QFile file_0(stylePath + "RimlessWindowTool.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

bool RimlessWindowTool::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}
