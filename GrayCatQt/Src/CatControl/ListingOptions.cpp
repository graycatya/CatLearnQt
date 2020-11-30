#include "ListingOptions.h"
#include <QFile>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QSharedPointer>

ListiongOptions::ListiongOptions(ListiongOptions::LAYOUT layout, QWidget *parent)
 : QWidget(parent)
 , m_yLayout(layout)
{
    InitUi();

    InitProperty();
}

ListiongOptions::~ListiongOptions()
{

}

void ListiongOptions::AddButton(QPushButton *button, int id)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
    }
    button->setCheckable(true);
    m_pButtonGroup->addButton(button, id);
    //button->setChecked(true);
}

void ListiongOptions::AddButtonNoGroup(QPushButton *button)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
    }
}

void ListiongOptions::AddWidget(QWidget *widget)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addWidget(widget);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addWidget(widget);
            break;
        }
    }
}

void ListiongOptions::AddItem(QSpacerItem *item)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addItem(item);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addItem(item);
            break;
        }
    }
}

QWidget *ListiongOptions::GetRootWidget() const
{
    return m_pButtonLists;
}

QButtonGroup *ListiongOptions::GetButtonGroup() const
{
    return m_pButtonGroup;
}

void ListiongOptions::Clear()
{
    for(auto button : m_lButtonList)
    {
        switch (m_yLayout) {
            case VBox: {
                static_cast<QVBoxLayout*>(m_pButtonListsLayout)->removeWidget(button);
                break;
            }
            case HBox: {
                static_cast<QHBoxLayout*>(m_pButtonListsLayout)->removeWidget(button);
                break;
            }
        }
        m_pButtonGroup->removeButton(button);
    }
    for(auto item : m_lItemList)
    {
        switch (m_yLayout) {
            case VBox: {
                static_cast<QVBoxLayout*>(m_pButtonListsLayout)->removeItem(item);
                break;
            }
            case HBox: {
                static_cast<QHBoxLayout*>(m_pButtonListsLayout)->removeItem(item);
                break;
            }
        }
    }
}

void *ListiongOptions::GetButtonlayout()
{
    return m_pButtonListsLayout;
}

void ListiongOptions::InitUi()
{
    m_pRootLayout = new QVBoxLayout(this);
    m_pRootLayout->setContentsMargins(0,0,0,0);
    m_pRootLayout->setSpacing(0);

    m_pRootWidget = new QWidget(this);
    m_pRootWidget->setObjectName("ListiongOptionsRootWidget");
    m_pRootLayout->addWidget(m_pRootWidget);

    m_pRootWidgetLayout = new QVBoxLayout(m_pRootWidget);
    m_pRootWidgetLayout->setContentsMargins(0,0,0,0);
    m_pRootWidgetLayout->setSpacing(0);
    m_pScrollArea = new QScrollArea(m_pRootWidget);
    m_pScrollArea->setObjectName("ListingOptionsScroll");
    m_pScrollArea->setWidgetResizable(true);
    //m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pRootWidgetLayout->addWidget(m_pScrollArea);

    m_pButtonLists = new QWidget();
    m_pButtonLists->setObjectName(QString::fromUtf8("ButtonLists"));
    m_pScrollArea->setWidget(m_pButtonLists);
    switch (m_yLayout) {
        case VBox: {
            m_pButtonListsLayout = new QVBoxLayout(m_pButtonLists);
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->setContentsMargins(0,0,0,0);
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->setSpacing(0);
            break;
        }
        case HBox: {
            m_pButtonListsLayout = new QHBoxLayout(m_pButtonLists);
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->setContentsMargins(0,0,0,0);
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->setSpacing(0);
            break;
        }
    }



    m_pButtonGroup = new QButtonGroup(m_pButtonLists);
    m_pButtonGroup->setExclusive(true);
}

void ListiongOptions::InitProperty()
{
    m_lButtonList.clear();
    /*QFile resourceqss(":/qss/CatGray/ListingOptions.css");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();*/
}

void ListiongOptions::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
}
