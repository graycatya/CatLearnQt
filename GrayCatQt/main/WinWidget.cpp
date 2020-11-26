#include "WinWidget.h"
#include "ui_WinWidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScreen>
#include <QEvent>
#include <QFile>
#include <QDebug>

WinWidget::WinWidget(QWidget *parent) :
#ifdef Q_OS_LINUX
    QWidget(parent),
#else
    RimlessWindowBase(parent),
#endif
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
    ui->BottomWidget->setVisible(false);
#ifdef Q_OS_LINUX
    ui->TopWidget->setVisible(false);
#else
    ui->TopWidget->installEventFilter(this);
    ui->TopWidget->setMouseTracking(true);
    ui->ToolListWidget->installEventFilter(this);
    ui->ToolListWidget->setMouseTracking(true);
    ui->ExhibitionWidget->installEventFilter(this);
    ui->ExhibitionWidget->setMouseTracking(true);
    ui->BottomWidget->installEventFilter(this);
    ui->BottomWidget->setMouseTracking(true);
    this->installEventFilter(this);
#endif
    QFile file(":/qss/WinWidget.css");
    file.open(QIODevice::ReadOnly);
    QString stylehoot = QLatin1String(file.readAll());
    this->setStyleSheet(stylehoot);
    file.close();
}

bool WinWidget::eventFilter(QObject *watched, QEvent *event)
{
#ifdef Q_OS_LINUX
#else
    if(event->type() == QEvent::MouseMove)
    {
        SetMoveRect(ui->TopWidget->rect());
        this->mouseMoveEvent((QMouseEvent*)event);
    } else if(event->type() == QEvent::MouseButtonRelease)
    {
        this->mouseReleaseEvent((QMouseEvent*)event);
    }
#endif
    //qDebug() << event;
    return QWidget::eventFilter(watched, event);
}


