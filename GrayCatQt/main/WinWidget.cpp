#include "WinWidget.h"
#include "ui_WinWidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScreen>
#include <QEvent>
#include <QFile>
#include <QDebug>

WinWidget::WinWidget(QWidget *parent) :
    RimlessWindowBase(parent),
    ui(new Ui::WinWidget)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
}

WinWidget::~WinWidget()
{
    delete ui;
}

void WinWidget::InitUi()
{
    ui->ToolLayout->setStretchFactor(ui->ToolListWidget, 2);
    ui->ToolLayout->setStretchFactor(ui->ExhibitionWidget, 8);
}

void WinWidget::InitProperty()
{
    ui->TopWidget->installEventFilter(this);
    ui->TopWidget->setMouseTracking(true);
    ui->ToolListWidget->installEventFilter(this);
    ui->ToolListWidget->setMouseTracking(true);
    ui->ExhibitionWidget->installEventFilter(this);
    ui->ExhibitionWidget->setMouseTracking(true);
    ui->BottomWidget->installEventFilter(this);
    ui->BottomWidget->setMouseTracking(true);
    QFile file(":/qss/WinWidget.css");
    file.open(QIODevice::ReadOnly);
    QString stylehoot = QLatin1String(file.readAll());
    this->setStyleSheet(stylehoot);
    file.close();
}

bool WinWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseMove)
    {
        SetMoveRect(ui->TopWidget->rect());
        this->mouseMoveEvent((QMouseEvent*)event);
    }
    return QWidget::eventFilter(watched, event);
}


