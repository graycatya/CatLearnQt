#include "WinWidget.h"
#include "ui_WinWidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScreen>
#include <QEvent>
#include <QFile>
#include <QDebug>
#include "CatControl/ListingOptions.h"
#include <QPushButton>
#include <QButtonGroup>
#include <CatLog>
#include "CatDrawingBoard.h"

WinWidget::WinWidget(QWidget *parent) :
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
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
    QVBoxLayout *ToolListWidgetLayout = new QVBoxLayout(ui->ToolListWidget);
    ToolListWidgetLayout->setContentsMargins(0,0,0,0);
    ToolListWidgetLayout->setSpacing(0);
    m_pListiongOptions = new ListiongOptions(ui->ToolListWidget);
    ToolListWidgetLayout->addWidget(m_pListiongOptions);

    InitButtonList();

    QSpacerItem* item_1 = new QSpacerItem(40, 300, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pListiongOptions->AddItem(item_1);

    //Graphics 布局
    QVBoxLayout *layout_0 = new QVBoxLayout(ui->GraphicsViewFunc);
    layout_0->setContentsMargins(0,0,0,0);
    layout_0->setSpacing(0);

    m_pCatDrawingBoard = new CatDrawingBoard(ui->GraphicsViewFunc);
    layout_0->addWidget(m_pCatDrawingBoard);

}

void WinWidget::InitProperty()
{
    ui->BottomWidget->setVisible(false);
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    ui->WinRootWidgetLayout->setContentsMargins(0,0,0,0);
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
    ui->WinRootWidget->installEventFilter(this);
    ui->WinRootWidget->setMouseTracking(true);
    this->installEventFilter(this);
#endif
    QFile file(":/qss/CatGray/WinWidget.css");
    file.open(QIODevice::ReadOnly);
    QString stylehoot = QLatin1String(file.readAll());
    this->setStyleSheet(stylehoot);
    file.close();

    // [初始化工具栏信号与槽]
    connect(m_pListiongOptions->GetButtonGroup(), SIGNAL(buttonClicked(int)), this, SLOT(On_ButtonFunc(int)));

    m_pButtons["WidgetFunc"]->setChecked(true);
}

void WinWidget::InitButtonList()
{
    QStringList buttonList = { "WidgetFunc", "GraphicsViewFunc", "Setting", "About" };
    for(int i = 0; i < buttonList.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pListiongOptions->GetRootWidget());
        button->setObjectName(buttonList[i]);
        m_pListiongOptions->AddButton(button, i);
        m_pButtons[buttonList[i]] = button;
    }

    m_pButtons[buttonList[0]]->setText(tr("QWidget"));
    m_pButtons[buttonList[1]]->setText(tr("QGraphicsView"));
    m_pButtons[buttonList[2]]->setText(tr("Setting"));
    m_pButtons[buttonList[3]]->setText(tr("About"));
}

bool WinWidget::eventFilter(QObject *watched, QEvent *event)
{
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
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

void WinWidget::On_ButtonFunc(int id)
{
    QString log = QString("On_ButtonFunc id: %1").arg(QString::number(id));
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
    ui->FuncStackWidget->setCurrentIndex(id);
}


