#include "CatDrawingBoard.h"
#include "ui_CatDrawingBoard.h"
#include "CatGraphicsView/CatGraphicsView.h"
#include "CatGraphicsView/CatGraphicsScene.h"
#include "CatGraphicsView/TeachingTools/TeachingToolRuler.h"
#include "CatControl/ListingOptions.h"
#include "CatWidget/ImageTools/RimlessWindowBase.h"
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

CatGraphicsView *CatDrawingBoard::CreateBoard()
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    CatGraphicsScene *scene = new CatGraphicsScene(this);
    scene->installEventFilter(this);

    //scene->setBackgroundBrush(QBrush(QColor("#244242")));
    scene->setSceneRect(-5000, -5000, 10000, 10000);

    CatGraphicsView *view = new CatGraphicsView(this);
    view->installEventFilter(this);
    view->setMouseTracking(true);
    view->setScene(scene);
    view->setRenderHints (QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    /*view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);*/
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->SetView(view);
    layout->addWidget(view);

    ui->GraphicsStacked->addWidget(widget);
    m_pBoardScenes.push_back(scene);
    return view;
}

void CatDrawingBoard::InitUi()
{
    QVBoxLayout *layout_0 = new QVBoxLayout(ui->GraphicsToolWidget);
    layout_0->setContentsMargins(0,0,0,0);
    layout_0->setSpacing(0);
    m_pTeachingOptions = new ListiongOptions(ListiongOptions::VBox, ui->GraphicsToolWidget);
    layout_0->addWidget(m_pTeachingOptions);

    InitTeachingTool();


}

void CatDrawingBoard::InitProperty()
{
    CreateBoard();

    QFile file_1(":/qss/CatGray/ListingOptionTeaching.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    m_pTeachingOptions->setStyleSheet(stylehoot_1);
    file_1.close();

    QFile file_0(":/qss/CatGray/CatDrawingBoard.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();

    qDebug() << m_pTeachingButtons["TeachingToolRuler"]->height();
    QSpacerItem* item = new QSpacerItem(60, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pTeachingOptions->AddItem(item);
}

void CatDrawingBoard::InitConnect()
{
    connect(m_pTeachingButtons["TeachingToolRuler"], &QPushButton::clicked, this, [=](){
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
}

void CatDrawingBoard::InitTeachingTool()
{
    QStringList list = {"TeachingToolRuler", "TeachingToolTrangle", "TeachingToolProtractor", "TeachingToolCompass"};
    for(int i = 0; i < list.size(); i++)
    {
        QPushButton *button = new QPushButton(m_pTeachingOptions->GetRootWidget());
        button->setObjectName(list[i]);
        m_pTeachingOptions->AddButtonNoGroup(button);
        m_pTeachingButtons[list[i]] = button;
    }
    QSpacerItem* item = new QSpacerItem(60, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pTeachingOptions->AddItem(item);

    static_cast<QVBoxLayout*>(m_pTeachingOptions->GetButtonlayout())->setSpacing(1);
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

void CatDrawingBoard::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
}

void CatDrawingBoard::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
}
