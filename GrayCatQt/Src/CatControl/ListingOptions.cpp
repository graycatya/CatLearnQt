#include "ListingOptions.h"
#include <QFile>


ListiongOptions::ListiongOptions(QWidget *parent) : QWidget(parent)
{
    InitUi();

    InitProperty();

}

ListiongOptions::~ListiongOptions()
{

}

void ListiongOptions::AddButton(QPushButton *button)
{
    m_pRootWidgetLayout->addWidget(button);
    button->setCheckable(true);
    m_pButtonGroup->addButton(button);
    button->setChecked(true);

}

void ListiongOptions::AddItem(QSpacerItem *item)
{
    m_pRootWidgetLayout->addItem(item);
}

QWidget *ListiongOptions::GetRootWidget() const
{
    return m_pRootWidget;
}

QButtonGroup *ListiongOptions::GetButtonGroup() const
{
    return m_pButtonGroup;
}

void ListiongOptions::Clear()
{
    for(auto button : m_lButtonList)
    {
        m_pRootWidgetLayout->removeWidget(button);
        m_pButtonGroup->removeButton(button);
    }
    for(auto item : m_lItemList)
    {
        m_pRootWidgetLayout->removeItem(item);
    }
}

void ListiongOptions::InitUi()
{
    m_pRootLayout = new QVBoxLayout(this);
    m_pRootLayout->setContentsMargins(0,0,0,0);
    m_pRootLayout->setSpacing(0);

    m_pRootWidget = new QWidget(this);
    m_pRootWidget->setObjectName("ListiongOptionsRootWidget");
    m_pRootWidgetLayout = new QVBoxLayout(m_pRootWidget);
    m_pRootWidgetLayout->setContentsMargins(0,0,0,0);
    m_pRootWidgetLayout->setSpacing(0);

    m_pButtonGroup = new QButtonGroup(m_pRootWidget);
    m_pButtonGroup->setExclusive(true);

    m_pRootLayout->addWidget(m_pRootWidget);

}

void ListiongOptions::InitProperty()
{
    m_lButtonList.clear();
    QFile resourceqss(":/qss/defaultstyle/ListingOptions.qss");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();
}

void ListiongOptions::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
}
