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
#include <QDesktopWidget>
#include "CatDrawingBoard.h"

WinWidget::WinWidget(QWidget *parent) :
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    QWidget(parent),
#else
    RimlessWindowBase(parent),
#endif
    ui(new Ui::WinWidget) ,
    m_bFullScreen(false)
{

    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
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
    m_pListiongOptions = new ListiongOptions(ListiongOptions::VBox, ui->ToolListWidget);
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

    // 微调布局
    ui->TopLayout->setAlignment(ui->Title, Qt::AlignVCenter | Qt::AlignHCenter);
    //ui->Title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void WinWidget::InitProperty()
{
    ui->BottomWidget->setVisible(false);
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    ui->WinRootWidgetLayout->setContentsMargins(0,0,0,0);
    ui->TopWidget->setVisible(false);
#else
    // 注册事件过滤 - 提供窗体拖拽
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
    for(auto button : m_pButtons)
    {
        button->installEventFilter(this);
        button->setMouseTracking(true);
    }
    ui->MinimizeButton->installEventFilter(this);
    ui->MinimizeButton->setMouseTracking(true);
    ui->ZoomButton->installEventFilter(this);
    ui->ZoomButton->setMouseTracking(true);
    ui->CloseButton->installEventFilter(this);
    ui->CloseButton->setMouseTracking(true);

#endif

    QFile file_1(":/qss/CatGray/ListingOptionsWin.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pListiongOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(":/qss/CatGray/WinWidget.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();

    SetZoomButtonState("Min");
}

void WinWidget::InitConnect()
{
    connect(ui->MinimizeButton, &QPushButton::clicked, this, [=](){
        showMinimized();
    });

    connect(ui->ZoomButton, &QPushButton::clicked, this, [=](){
        SetWindowZoom();
    });

    connect(ui->CloseButton, &QPushButton::clicked, this, [=](){
        QApplication::exit();
    });
#if defined (Q_OS_WIN)
    connect(this, &RimlessWindowBase::mouseMoveed, this, [=](QPoint pos){
        if(m_bMousePress && m_bFullScreen)
        {
            if(ui->TopWidget->rect().contains(pos))
            {
                m_bFullScreen = !m_bFullScreen;
                float ration = static_cast<float>(pos.x()) / static_cast<float>(this->width());
                int x = static_cast<int>(static_cast<float>(m_pLastRect.width()) * ration);
                SetProcessGeometry(pos.x() - x , 0, m_pLastRect.width(), m_pLastRect.height());
                this->resize(QSize(m_pLastRect.size()));
                SetZoomButtonState("Min");
            }
        }
    });
#endif
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

void WinWidget::SetZoomButtonState(QString state)
{
    ui->ZoomButton->setProperty("State", state);
    ui->ZoomButton->setStyle(QApplication::style());
}

void WinWidget::SetWindowZoom()
{
    m_bFullScreen = !m_bFullScreen;
    if(m_bFullScreen)
    {
        m_pLastRect = QRect(this->pos().x(), this->pos().y(), this->width(), this->height());
        QRect rect = QApplication::desktop()->availableGeometry(this);
        this->setGeometry(rect.x()-2, rect.y()-2, rect.width()+4, rect.height()+4);
        SetZoomButtonState("Max");
    } else {
        this->setGeometry(m_pLastRect);
        SetZoomButtonState("Min");
    }
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

void WinWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(ui->TopWidget->rect().contains(event->pos()))
        {
            SetWindowZoom();
        }
    }
}

void WinWidget::On_ButtonFunc(int id)
{
    QString log = QString("On_ButtonFunc id: %1").arg(QString::number(id));
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(log.toStdString()));
    ui->FuncStackWidget->setCurrentIndex(id);
}



