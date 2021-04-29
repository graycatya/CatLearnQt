#include "QrenCodeTool.h"
#include "ui_QrenCodeTool.h"
#include "CatWidget/QrenCode/QtQrenCode.h"
#include "../CatConfig/CatConfig.h"

#include <CatLog>

QrenCodeTool::QrenCodeTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QrenCodeTool)
{
    ui->setupUi(this);
    InitProperty();
    InitConnect();
}

QrenCodeTool::~QrenCodeTool()
{
    delete ui;
}

void QrenCodeTool::InitProperty()
{
    ui->QrenCodeEdit->setText(CatConfig::GetValue("HomePage").toString());
}

void QrenCodeTool::InitConnect()
{
    connect(ui->QrenCodeEdit, &QLineEdit::textEdited, this, [=](QString){
        UpdateQrenCode();
    });
}

void QrenCodeTool::UpdateQrenCode()
{
    QPixmap qrPixmap;
    int width = ui->QrenCodeLabel->width();
    int height = ui->QrenCodeLabel->height();
    GernerateQRCode(ui->QrenCodeEdit->text(), qrPixmap, QSize(width, height), "", 5);

    ui->QrenCodeLabel->setPixmap(qrPixmap);
}

void QrenCodeTool::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    UpdateQrenCode();
}

void QrenCodeTool::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    QPixmap qrPixmap;
    UpdateQrenCode();
}
