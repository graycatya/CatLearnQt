#include "SideBoxButton.h"

#include "CatConfig.h"
#include <QPaintEvent>
#include <QDebug>
#include <QFile>
#include <QApplication>

SideBoxButton::SideBoxButton(QWidget *parent)
    : QPushButton(parent)
{
    InitUi();
    InitProperty();
    InitConnect();
    UpdateStyle();
}

SideBoxButton::~SideBoxButton()
{

}

void SideBoxButton::setButtonText(QString text)
{
    m_pTextLabel->setText(text);
}

void SideBoxButton::UpdateButtonState()
{
    if(!isChecked())
    {
        SetButtonBackState("NotHover");
        SetButtonRightWidgetState("NotCheck");
    } else {
        SetButtonBackState("Hover");
        SetButtonRightWidgetState("Check");
    }
}

void SideBoxButton::UpdateButtonSideState(bool state)
{
    if(state)
    {
        m_pTextLabel->setVisible(true);
    } else {
        m_pTextLabel->setVisible(false);
    }
}

void SideBoxButton::InitUi()
{
    this->setMinimumHeight(50);
    this->setMaximumHeight(50);
    QHBoxLayout *layout = new QHBoxLayout(this);
    m_pBackWeidget = new QWidget(this);
    m_pBackWeidget->setObjectName("BackWeidget");
    layout->addWidget(m_pBackWeidget);
    //layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);

    m_pBackLayout = new QHBoxLayout(m_pBackWeidget);

    m_pImageLabel = new QLabel(m_pBackWeidget);
    m_pImageLabel->setObjectName("ImageLabel");
    m_pImageLabel->setMinimumSize(24, 24);
    m_pImageLabel->setMaximumSize(24, 24);

    m_pTextLabel = new QLabel(m_pBackWeidget);
    m_pTextLabel->setObjectName("TextLabel");


    m_pRigthWidget = new QWidget(m_pBackWeidget);
    m_pRigthWidget->setObjectName("RigthWidget");

    QSpacerItem *item = new QSpacerItem(10, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_pBackLayout->setContentsMargins(18, 0, 0, 0);
    m_pBackLayout->setSpacing(0);
    m_pBackLayout->addWidget(m_pImageLabel);
    m_pBackLayout->addSpacing(18);
    m_pBackLayout->addWidget(m_pTextLabel);
    m_pBackLayout->addItem(item);
    m_pBackLayout->addWidget(m_pRigthWidget);
}

void SideBoxButton::InitProperty()
{
    m_pBackWeidget->installEventFilter(this);
    m_pImageLabel->installEventFilter(this);
    m_pTextLabel->installEventFilter(this);
    m_pRigthWidget->installEventFilter(this);

    SetButtonBackState("NotHover");
    SetButtonRightWidgetState("NotCheck");
}

void SideBoxButton::InitConnect()
{
    connect(this, &QPushButton::clicked, this, [=](bool checked){
        Q_UNUSED(checked)
    });
}

void SideBoxButton::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "SideBoxButton.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}

void SideBoxButton::SetButtonBackState(QString state)
{
    m_pBackWeidget->setProperty("State", state);
    m_pBackWeidget->setStyle(QApplication::style());
}

void SideBoxButton::SetButtonRightWidgetState(QString state)
{
    m_pRigthWidget->setProperty("State", state);
    m_pRigthWidget->setStyle(QApplication::style());
}

void SideBoxButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //this->paintEvent(event);
}

bool SideBoxButton::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        SetButtonBackState("Hover");
        //qDebug() << "button " << event->type();
    } else if(event->type() == QEvent::Leave)
    {
        UpdateButtonState();
        //qDebug() << "button " << event->type();
    }

    return QWidget::eventFilter(watched, event);
}
