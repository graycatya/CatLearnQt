#include "CatDrawingBoard.h"
#include "ui_CatDrawingBoard.h"
#include "QCatGrayGraphicsDrawingBoardView.h"
#include "QCatGrayGraphicsDrawingBoardScene.h"
#include "QCatGrayTeachingToolRuler.h"
#include "QCatGrayListingOptions.h"
#include "CatConfig/CatConfig.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QDebug>

CatDrawingBoard::CatDrawingBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatDrawingBoard)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

CatDrawingBoard::~CatDrawingBoard()
{
    delete ui;
}

QCatGrayGraphicsDrawingBoardView *CatDrawingBoard::CreateBoard()
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    QCatGrayGraphicsDrawingBoardScene *scene = new QCatGrayGraphicsDrawingBoardScene(this);
    scene->installEventFilter(this);

    //scene->setBackgroundBrush(QBrush(QColor("#244242")));
    scene->setSceneRect(-2000, -2000, 4000, 4000);

    QCatGrayGraphicsDrawingBoardView *view = new QCatGrayGraphicsDrawingBoardView(this);
    view->installEventFilter(this);
    view->setMouseTracking(true);
    view->setScene(scene);
    view->setRenderHints (QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->SetView(view);
    view->resize(scene->sceneRect().size().toSize());
    layout->addWidget(view);

    scene->InitProperty();

    ui->GraphicsStacked->addWidget(widget);
    m_pBoardScenes.push_back(scene);
    return view;
}

void CatDrawingBoard::InitUi()
{
    QVBoxLayout *layout_0 = new QVBoxLayout(ui->GraphicsToolWidget);
    layout_0->setContentsMargins(0,0,0,0);
    layout_0->setSpacing(0);
    m_pTeachingOptions = new QCatGrayListingOptions(QCatGrayListingOptions::VBox, ui->GraphicsToolWidget);
    layout_0->addWidget(m_pTeachingOptions);

    QVBoxLayout *layout_1 = new QVBoxLayout(ui->GraphicsTopToolWidget);
    ui->GraphicsTopToolWidget->setMinimumHeight(30);
    ui->GraphicsTopToolWidget->setMaximumHeight(30);
    layout_1->setContentsMargins(0,0,0,0);
    layout_1->setSpacing(0);
    m_pBoardOptions = new QCatGrayListingOptions(QCatGrayListingOptions::HBox, ui->GraphicsTopToolWidget);
    layout_1->addWidget(m_pBoardOptions);


    InitTeachingTool();

    InitBoardTool();


}

void CatDrawingBoard::InitProperty()
{
    CreateBoard();

    UpdateStyle();

    //qDebug() << m_pTeachingButtons["QCatGrayTeachingToolRuler"]->height();
    QSpacerItem* item = new QSpacerItem(60, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pTeachingOptions->AddItem(item);
}

void CatDrawingBoard::InitConnect()
{
    // 教具工具栏
    connect(m_pTeachingButtons["QCatGrayTeachingToolRuler"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->AddTeachingToolRuler();
    });
    connect(m_pTeachingButtons["TeachingToolTrangle"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->AddTeachingToolTrangle();
    });
    connect(m_pTeachingButtons["TeachingToolProtractor"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->AddTeachingToolProtractor();
    });
    connect(m_pTeachingButtons["TeachingToolCompass"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->AddTeachingToolCompass();
    });
    // 画板工具栏
    connect(m_pBoardButtons["BoardSelect"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->On_DrawingBoard_SelectState();
    });

    connect(m_pBoardButtons["BoardBrushes"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->On_DrawingBoard_PenState();
    });

    connect(m_pBoardButtons["BoardErasure"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->On_DrawingBoard_EraserState();
    });

    connect(m_pBoardButtons["BoardClear"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->Clear();
    });
    connect(m_pBoardButtons["BoardZoomIn"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->View()->ScaleZoomIn();
    });
    connect(m_pBoardButtons["BoardZoomOut"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->View()->ScaleZoomOut();
    });
    connect(m_pBoardButtons["BoardReset"], &QPushButton::clicked, this, [=](){
        m_pBoardScenes[ui->GraphicsStacked->currentIndex()]->View()->Reset();
    });

    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
}

void CatDrawingBoard::InitTeachingTool()
{
    QStringList list = {"QCatGrayTeachingToolRuler", "TeachingToolTrangle",
                        "TeachingToolProtractor", "TeachingToolCompass"};
    for(int i = 0; i < list.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pTeachingOptions->GetRootWidget());
        button->setObjectName(list[i]);
        m_pTeachingOptions->AddButtonNoGroup(button);
        m_pTeachingButtons[list[i]] = button;
    }
    QSpacerItem* item = new QSpacerItem(60, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pTeachingOptions->AddItem(item);

    static_cast<QVBoxLayout*>(m_pTeachingOptions->GetButtonlayout())->setSpacing(2);
}

void CatDrawingBoard::InitBoardTool()
{
    //"BoardSelect", "BoardBrushes",
    QStringList list = {"BoardSelect", "BoardBrushes", "BoardErasure", "BoardClear", "BoardZoomIn", "BoardZoomOut", "BoardReset"};
    // 占位

    QLabel *label = new QLabel(m_pTeachingOptions->GetRootWidget());
    label->setObjectName("BoardLabel");
    m_pBoardOptions->AddWidget(label);
    for(int i = 0; i < list.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pTeachingOptions->GetRootWidget());
        button->setObjectName(list[i]);
        if(i == 0 || i == 1 || i == 2)
        {
            m_pBoardOptions->AddButton(button, i);
        } else {
            m_pBoardOptions->AddButtonNoGroup(button);
        }
        m_pBoardButtons[list[i]] = button;
    }
    QSpacerItem* item = new QSpacerItem(60, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_pBoardOptions->AddItem(item);

    static_cast<QHBoxLayout*>(m_pBoardOptions->GetButtonlayout())->setSpacing(2);

    m_pBoardButtons["BoardSelect"]->setChecked(true);
}

void CatDrawingBoard::UpdateStyle()
{

    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_2(stylePath + "ListingOptionBoard.css");
    file_2.open(QIODevice::ReadOnly);
    QString stylehoot_2 = QLatin1String(file_2.readAll());
    m_pBoardOptions->setStyleSheet(stylehoot_2);
    file_2.close();

    QFile file_1(stylePath + "ListingOptionTeaching.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pTeachingOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(stylePath + "CatDrawingBoard.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void CatDrawingBoard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void CatDrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void CatDrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
}

void CatDrawingBoard::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
}

void CatDrawingBoard::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
}

void CatDrawingBoard::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event)
}
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
void CatDrawingBoard::enterEvent(QEnterEvent *event)
#else
void CatDrawingBoard::enterEvent(QEvent *event)
#endif

{
    Q_UNUSED(event)
}

void CatDrawingBoard::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
}
