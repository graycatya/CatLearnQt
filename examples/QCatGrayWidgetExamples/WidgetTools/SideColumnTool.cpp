#include "SideColumnTool.h"
#include "ui_SideColumnTool.h"
#include "CatConfig.h"


#include <QFile>
#include <QSlider>
#include <QDebug>

SideColumnTool::SideColumnTool(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideColumnTool)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
    UpdateStyle();
}

SideColumnTool::~SideColumnTool()
{
    delete ui;
}

void SideColumnTool::InitUi()
{
    //m_pSideAnimation = new QPropertyAnimation(ui->SideWidget, "maximumWidth");

    m_pSideButtonGroup = new QButtonGroup(ui->SideWidget);
    for(int i = 0; i < 6; i++)
    {
        SideBoxButton *button = new SideBoxButton(ui->SideWidget);
        button->setButtonText(QString("Text-%1").arg(i));
        button->installEventFilter(ui->SideWidget);
        button->UpdateButtonSideState(false);
        ui->SideWidgetLayout->addWidget(button);
        m_pSideButtons.append(button);
        button->setCheckable(true);
        m_pSideButtonGroup->addButton(button, i);
    }
    m_pSideButtons[2]->setVisible(false);
    QSpacerItem *buttonitem = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->SideWidgetLayout->addItem(buttonitem);

    m_pSideButton = new QPushButton(ui->SideWidget);
    m_pSideButton->setMinimumSize(QSize(16, 50));
    m_pSideButton->setMaximumSize(QSize(16, 50));

    m_pSideButton->setObjectName("SideButton");
    m_pSideButton->setVisible(false);
    SetUnfold(false);
    InitDefauleSlider();

}

void SideColumnTool::InitProperty()
{
    m_bUnfold = false;
    ui->SideWidget->setMinimumWidth(60);
    ui->SideWidget->setMaximumWidth(60);
    SetSideButtonState("Open");
    //ui->SideWidget->maximumWidth()
    ui->SideWidget->installEventFilter(this);

    UpdateStyle();
}

void SideColumnTool::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });
#if (QT_VERSION <= QT_VERSION_CHECK(5,12,11))
    connect(m_pSideButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, [=](int id){
        qDebug() << "button group clicked: " << id;
        foreach(auto button , m_pSideButtons)
        {
            button->UpdateButtonState();
        }
    });
#else
    connect(m_pSideButtonGroup, &QButtonGroup::idClicked, this, [=](int id){
        qDebug() << "button group clicked: " << id;
        foreach(auto button , m_pSideButtons)
        {
            button->UpdateButtonState();
        }
    });
#endif


    connect(m_pSideButton, &QPushButton::clicked, this, [=](){
        SetUnfold(!m_bUnfold);
    });
}

void SideColumnTool::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "SideColumnTool.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void SideColumnTool::InitDefauleSlider()
{

}

void SideColumnTool::SetUnfold(bool unfold)
{
    m_bUnfold = unfold;
    if(m_bUnfold)
    {
        QPropertyAnimation *animation_0 = new QPropertyAnimation(ui->SideWidget, "minimumWidth");
        QPropertyAnimation *animation_1 = new QPropertyAnimation(ui->SideWidget, "maximumWidth");
        animation_0->setDuration(200);
        animation_0->setStartValue(60);
        animation_0->setEndValue(200);
        animation_1->setDuration(200);
        animation_1->setStartValue(60);
        animation_1->setEndValue(200);
        animation_0->start(QAbstractAnimation::DeleteWhenStopped);
        animation_1->start(QAbstractAnimation::DeleteWhenStopped);
        SetSideButtonState("Close");
    } else {
        QPropertyAnimation *animation_0 = new QPropertyAnimation(ui->SideWidget, "minimumWidth");
        QPropertyAnimation *animation_1 = new QPropertyAnimation(ui->SideWidget, "maximumWidth");
        animation_0->setDuration(200);
        animation_0->setStartValue(200);
        animation_0->setEndValue(60);
        animation_1->setDuration(200);
        animation_1->setStartValue(200);
        animation_1->setEndValue(60);
        animation_0->start(QAbstractAnimation::DeleteWhenStopped);
        animation_1->start(QAbstractAnimation::DeleteWhenStopped);
        SetSideButtonState("Open");
    }

    foreach(auto button , m_pSideButtons)
    {
        button->UpdateButtonSideState(m_bUnfold);
    }
    m_pSideButton->move(ui->SideWidget->width() - m_pSideButton->width(),
                        (ui->SideWidget->height() - m_pSideButton->height())/2);
}

void SideColumnTool::SetSideButtonState(QString state)
{
    m_pSideButton->setProperty("State", state);
    m_pSideButton->setStyle(QApplication::style());
}

void SideColumnTool::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    m_pSideButton->move(ui->SideWidget->width() - m_pSideButton->width(),
                        (ui->SideWidget->height() - m_pSideButton->height())/2);
}

void SideColumnTool::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    m_pSideButton->move(ui->SideWidget->width() - m_pSideButton->width(),
                        (ui->SideWidget->height() - m_pSideButton->height())/2);
}

bool SideColumnTool::eventFilter(QObject *watched, QEvent *event)
{
    //qDebug() << "watched: " << watched->objectName() << " : " << event->type();
    if(watched->objectName() == "SideWidget")
    {
        //qDebug() << "watched: " << watched->objectName() << " : " << event->type();
        if(event->type() == QEvent::Enter)
        {
            m_pSideButton->setVisible(true);
        } else if(event->type() == QEvent::Leave)
        {
            m_pSideButton->setVisible(false);
        } else if(event->type() == QEvent::Resize)
        {
            m_pSideButton->move(ui->SideWidget->width() - m_pSideButton->width(),
                                (ui->SideWidget->height() - m_pSideButton->height())/2);
        }
    }
    return QWidget::eventFilter(watched, event);
}
