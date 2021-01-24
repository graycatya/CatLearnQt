#include "CatPagingNavigation.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>

CatPagingNavigation::CatPagingNavigation(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
    InitProperty();
    InitConnect();
}

CatPagingNavigation::~CatPagingNavigation()
{

}

void CatPagingNavigation::InitUi()
{
    m_pRootLayout = new QHBoxLayout(this);
    m_pRootLayout->setContentsMargins(0,0,0,0);
    m_pRootLayout->setSpacing(0);

    m_pButtonGroup = new QButtonGroup(this);

    for(int i = 1; i < 10; i++)
    {
        QPushButton *Button = new QPushButton(this);
        Button->setObjectName(QString("PageButton_%1").arg(QString::number(i)));
        Button->setCheckable(true);
        m_pButtonGroup->addButton(Button, i);
        m_pPageButtons.push_back(Button);
    }

    m_pButtonGroup->setExclusive(true);

    m_pPreviousPage = new QPushButton(this);
    m_pPreviousPage->setObjectName("PreviousPage");
    m_pPreviousSeveralPage = new QPushButton(this);
    m_pPreviousSeveralPage->setObjectName("PreviousSeveralPage");
    m_pNextPage = new QPushButton(this);
    m_pNextPage->setObjectName("NextPage");
    m_pNextPageSeveralPage = new QPushButton(this);
    m_pNextPageSeveralPage->setObjectName("NextPageSeveralPage");

    m_pRootLayout->addWidget(m_pPreviousPage);
    for(int i = 0; i < 3; i++)
    {
        m_pRootLayout->addWidget(m_pPageButtons.at(i));
    }
    m_pRootLayout->addWidget(m_pPreviousSeveralPage);
    for(int i = 3; i < 6; i++)
    {
        m_pRootLayout->addWidget(m_pPageButtons.at(i));
    }
    m_pRootLayout->addWidget(m_pNextPageSeveralPage);
    for(int i = 6; i < 9; i++)
    {
        m_pRootLayout->addWidget(m_pPageButtons.at(i));
    }
    m_pRootLayout->addWidget(m_pNextPage);
}

void CatPagingNavigation::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
}

void CatPagingNavigation::InitConnect()
{

}

void CatPagingNavigation::UpdateCurrentPage()
{

}
