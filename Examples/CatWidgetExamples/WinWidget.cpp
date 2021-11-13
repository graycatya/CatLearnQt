#include "WinWidget.h"
#include "ui_WinWidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScreen>
#include <QEvent>
#include <QFile>
#include <QPushButton>
#include <QButtonGroup>
#include <CatLog>
#include <QDesktopWidget>
#include <QTimer>
#include <QQmlDebuggingEnabler>
#include <QDateTime>
//#include <QGraphicsDropShadowEffect>


#include "CatDrawingBoard.h"
#include "CatAbout.h"
#include "CatSettings.h"
#include "CatWidget.h"
#include "CatConfig/CatConfig.h"
#include "CatControl/ListingOptions.h"
#include "CatQuickWidget.h"

WinWidget::WinWidget(QWidget *parent) :
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    QWidget(parent),
#else
    RimlessWindowBase(parent, true),
#endif
    ui(new Ui::WinWidget) ,
    m_bFullScreen(false) ,
    m_bTopWidget(false)
{

    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    retranslateUi();
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
    m_pListiongOptions->setObjectName("ListiongOptions");
    ToolListWidgetLayout->addWidget(m_pListiongOptions);

    InitButtonList();

    QSpacerItem* item_1 = new QSpacerItem(40, 300, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pListiongOptions->AddItem(item_1);

    //Widget 布局
    QVBoxLayout *layout_Widget = new QVBoxLayout(ui->WidgetFunc);
    layout_Widget->setContentsMargins(0,0,0,0);
    layout_Widget->setSpacing(0);

    m_pCatWidget = new CatWidget(ui->WidgetFunc);
    m_pCatWidget->setObjectName("WinCatWidget");
    layout_Widget->addWidget(m_pCatWidget);

    //Graphics 布局
    QVBoxLayout *layout_Graphics = new QVBoxLayout(ui->GraphicsViewFunc);
    layout_Graphics->setContentsMargins(0,0,0,0);
    layout_Graphics->setSpacing(0);

    m_pCatDrawingBoard = new CatDrawingBoard(ui->GraphicsViewFunc);
    m_pCatDrawingBoard->setObjectName("WinCatDrawingBoard");
    layout_Graphics->addWidget(m_pCatDrawingBoard);

    // About 布局
    QVBoxLayout *layout_About = new QVBoxLayout(ui->AboutFunc);
    layout_About->setContentsMargins(0,0,0,0);
    layout_About->setSpacing(0);

    m_pCatAbout = new CatAbout(ui->AboutFunc);
    m_pCatAbout->setObjectName("WinCatAbout");
    layout_About->addWidget(m_pCatAbout);

    // Settings 布局
    QVBoxLayout *layout_Settings = new QVBoxLayout(ui->SettingFunc);
    layout_Settings->setContentsMargins(0,0,0,0);
    layout_Settings->setSpacing(0);

    m_pCatSettings = new CatSettings(ui->SettingFunc);
    m_pCatSettings->setObjectName("WinCatSettings");
    layout_Settings->addWidget(m_pCatSettings);

    // QuickWidget 布局
    QVBoxLayout *layout_QuickWidget = new QVBoxLayout(ui->QuickWidgetFunc);
    layout_QuickWidget->setContentsMargins(0,0,0,0);
    layout_QuickWidget->setSpacing(0);

    m_pCatQuickWidget = new CatQuickWidget(ui->QuickWidgetFunc);
    m_pCatQuickWidget->setObjectName("WinCatQuickWidget");
    layout_QuickWidget->addWidget(m_pCatQuickWidget);

    // 微调布局
    //ui->TopLayout->setAlignment(ui->Title, Qt::AlignVCenter | Qt::AlignHCenter);
    //ui->Title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void WinWidget::InitProperty()
{
    //setAttribute(Qt::WA_DeleteOnClose, true);
    //setAttribute(Qt::WA_QuitOnClose, false);
    ui->BottomWidget->setVisible(false);
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    ui->WinRootWidgetLayout->setContentsMargins(0,0,0,0);
    ui->TopWidget->setVisible(false);
#else
    SetShadowWeight(8);
    SetShadowColor(QColor(0, 0, 0, 50));
#endif
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
    m_pCatDrawingBoard->installEventFilter(this);
    m_pCatDrawingBoard->setMouseTracking(true);
    m_pCatAbout->installEventFilter(this);
    m_pCatAbout->setMouseTracking(true);
    m_pCatSettings->installEventFilter(this);
    m_pCatSettings->setMouseTracking(true);
    m_pCatWidget->installEventFilter(this);
    m_pCatWidget->setMouseTracking(true);
    m_pListiongOptions->installEventFilter(this);
    m_pListiongOptions->setMouseTracking(true);
    m_pCatQuickWidget->installEventFilter(this);
    m_pCatQuickWidget->setMouseTracking(true);
    ui->Title->installEventFilter(this);
    ui->Title->setMouseTracking(true);

    UpdateStyle();


    /*QString title = m_pListiongOptions->GetButtonGroup()->checkedButton()->text();
    SetTitle(title);*/
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
        QApplication::exit(0);
    });
    /*
#if defined (Q_OS_WIN)
    connect(this, &RimlessWindowBase::mouseMoveed, this, [=](QPoint pos){
        if(m_bMousePress && m_bFullScreen && m_bTopWidget)
        {
            //qDebug() << m_bMousePress;
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
#endif*/
    // [初始化工具栏信号与槽]
    connect(m_pListiongOptions->GetButtonGroup(), SIGNAL(buttonClicked(int)), this, SLOT(On_ButtonFunc(int)));



    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    m_pButtons["WidgetFunc"]->setChecked(true);
}

void WinWidget::InitButtonList()
{
    QStringList buttonList = { "WidgetFunc", "GraphicsViewFunc",
                               "QuickWidgetFunc", "Setting",
                               "About" };
    for(int i = 0; i < buttonList.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pListiongOptions->GetRootWidget());
        button->setObjectName(buttonList[i]);
        m_pListiongOptions->AddButton(button, i);
        m_pButtons[buttonList[i]] = button;
    }

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
        this->setGeometry(rect.x()-5, rect.y()-5, rect.width()+10, rect.height()+10);
        SetZoomButtonState("Max");
    } else {
        this->setGeometry(m_pLastRect);
        SetZoomButtonState("Min");
    }
}

void WinWidget::SetTitle(QString state)
{
    QString title = APP_NAME;
    if(!state.isEmpty())
    {
        title += QString(" - " + state);
    }
    this->setWindowTitle(title);
    ui->Title->setText(title);
    ui->Title->adjustSize();
}

void WinWidget::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
        QString icon = ":/Images/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
        this->setWindowIcon(QIcon(icon + "CATicon.png"));
    } else {
        stylePath = ":/qss/CatGray/";
        this->setWindowIcon(QIcon(":/Images/CatGray/CATicon.png"));
    }

    QFile file_1(stylePath + "ListingOptionsWin.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pListiongOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(stylePath + "WinWidget.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();

    if(m_bFullScreen)
    {
        SetZoomButtonState("Max");
    } else {
        SetZoomButtonState("Min");
    }
}

void WinWidget::retranslateUi()
{
    if(!m_pButtons.isEmpty())
    {
        QStringList buttonList = { "WidgetFunc", "GraphicsViewFunc",
                                   "QuickWidgetFunc", "Setting",
                                   "About" };
        m_pButtons[buttonList[0]]->setText(tr("QWidget"));
        m_pButtons[buttonList[1]]->setText(tr("QGraphicsView"));
        m_pButtons[buttonList[2]]->setText(tr("QQuickWidget"));
        m_pButtons[buttonList[3]]->setText(tr("Setting"));
        m_pButtons[buttonList[4]]->setText(tr("About"));

    }

    QString title = m_pListiongOptions->GetButtonGroup()->checkedButton()->text();
    SetTitle(title);
}

bool WinWidget::eventFilter(QObject *watched, QEvent *event)
{
    //qDebug() << watched->objectName() << event->type();
/*#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
#else*/
    if(event->type() == QEvent::MouseMove)
    {
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
#else
        SetMoveRect(ui->TopWidget->rect());
#endif
        this->mouseMoveEvent((QMouseEvent*)event);
    } else if(event->type() == QEvent::MouseButtonRelease)
    {
        this->mouseReleaseEvent((QMouseEvent*)event);
    }

    QStringList list = { "WidgetFunc", "GraphicsViewFunc",
                         "AboutFunc", "Setting",
                         "About", "WinCatDrawingBoard",
                            "WinCatAbout", "WinCatSettings",
                         "WinCatWidget", "ToolListWidget",
                            "ListiongOptions", "QuickWidgetFunc",
                         "WinCatQuickWidget"};
    if(watched->objectName() == "WinCatWidget")
    {
        watched->eventFilter(watched, event);
    } else if(watched->objectName() == "WinCatDrawingBoard") {
        watched->eventFilter(watched, event);

        if(event->type() == QEvent::Paint)
        {
            return watched->eventFilter(watched, event);
        }
    }

    m_bTopWidget = watched->objectName() == "TopWidget" ? true : false;

    for(auto temp : list)
    {
        if(watched->objectName() == temp && event->type() == QEvent::MouseMove)
        {

            this->setCursor(Qt::ArrowCursor);
            return QWidget::eventFilter(watched, event);
        }
    }

/*#endif*/
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

void WinWidget::mouseMoveEvent(QMouseEvent *event)
{

#ifdef Q_OS_WIN
    RimlessWindowBase::mouseMoveEvent(event);
    QPoint pos = event->pos();
    if(m_bMousePress && m_bFullScreen && m_bTopWidget)
    {
        //qDebug() << m_bMousePress;
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
#else
    Q_UNUSED(event)
#endif
}

void WinWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        this->ui->retranslateUi(this);
        this->retranslateUi();
    } else {
        QWidget::changeEvent(event);
    }
}

void WinWidget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    //this->deleteLater();
}

void WinWidget::On_ButtonFunc(int id)
{

    ui->FuncStackWidget->setCurrentIndex(id);
    QString title = m_pListiongOptions->GetButtonGroup()->checkedButton()->text();
    SetTitle(title);
}
