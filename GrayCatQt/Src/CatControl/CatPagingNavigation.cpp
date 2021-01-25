#include "CatPagingNavigation.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QEvent>
#include <QApplication>
#include <QFile>
#include <QTimer>

CatPagingNavigation::CatPagingNavigation(QWidget *parent)
    : QWidget(parent) ,
      m_nDataSum(0) ,
      m_nItemsPerPages(0) ,
      m_nTotalPages(0) ,
      m_nCurrentPage(0)
{
    InitUi();
    InitProperty();
    InitConnect();
}

CatPagingNavigation::~CatPagingNavigation()
{

}

void CatPagingNavigation::InitPaginNavigation(qulonglong datasum, qulonglong itemsperpages)
{
    if(datasum > 0 && itemsperpages > 0)
    {
        m_nDataSum = datasum;
        m_nItemsPerPages = itemsperpages;
        m_nTotalPages = datasum/itemsperpages + (datasum%itemsperpages > 0 ? 1 : 0);
        m_nCurrentPage = 1;
    } else {
        m_nDataSum = 0;
        m_nItemsPerPages = 0;
        m_nTotalPages = 0;
        m_nCurrentPage = 0;
    }
    UpdatePagingNavigation();
    m_pPageButtons.at(0)->setChecked(true);
    emit TotalPageeed(m_nTotalPages);
}

void CatPagingNavigation::SetDataSum(qulonglong datasum)
{
    if(datasum > 0)
    {
        m_nDataSum = datasum;
        m_nTotalPages = datasum/m_nItemsPerPages + (datasum%m_nItemsPerPages > 0 ? 1 : 0);
        UpdatePagingNavigation();
        emit TotalPageeed(m_nTotalPages);
    }
}

void CatPagingNavigation::SetItemsPerPages(qulonglong itemsperpages)
{
    if(itemsperpages > 0)
    {
        m_nItemsPerPages = itemsperpages;
        m_nTotalPages = m_nDataSum/itemsperpages + (m_nDataSum%itemsperpages > 0 ? 1 : 0);
        UpdatePagingNavigation();
        emit TotalPageeed(m_nTotalPages);
    }
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
        Button->setObjectName(QString("PageButton"));
        Button->setCheckable(true);
        m_pButtonGroup->addButton(Button, i);
        m_pPageButtons.push_back(Button);
    }

    m_pButtonGroup->setExclusive(true);

    m_pPreviousPage = new QPushButton(this);
    m_pPreviousPage->setObjectName("PreviousPage");
    //m_pPreviousPage->setA
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
    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground);

    m_pPreviousPage->setText("<<");
    m_pNextPage->setText(">>");
    m_pPreviousSeveralPage->setText("...");
    m_pNextPageSeveralPage->setText("...");

    m_pPreviousSeveralPage->installEventFilter(this);
    m_pPreviousSeveralPage->setMouseTracking(true);
    m_pNextPageSeveralPage->installEventFilter(this);
    m_pNextPageSeveralPage->setMouseTracking(true);

    UpdatePagingNavigation();

    UpdateStyle();

}

void CatPagingNavigation::InitConnect()
{
    connect(m_pPreviousPage, &QPushButton::clicked, this, [=](){
        SetCurrentPage(m_nCurrentPage - 1);
    });
    connect(m_pPreviousSeveralPage, &QPushButton::clicked, this, [=](){
        SetCurrentPage(m_nCurrentPage - 3);
    });
    connect(m_pNextPageSeveralPage, &QPushButton::clicked, this, [=](){
        SetCurrentPage(m_nCurrentPage + 3);
    });
    connect(m_pNextPage, &QPushButton::clicked, this, [=](){
        SetCurrentPage(m_nCurrentPage + 1);
    });
    connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)),
            this, SLOT(ButtonGrouped(QAbstractButton *)));
}

void CatPagingNavigation::UpdateStyle()
{
    QFile file_1(":/CatControl/PagingNavigation.css");
    file_1.open(QIODevice::ReadOnly);
    QString stylehoot_1 = QLatin1String(file_1.readAll());
    this->setStyleSheet(stylehoot_1);
    file_1.close();
}

void CatPagingNavigation::UpdatePagingNavigation()
{
    if(m_nTotalPages == 0)
    {
        m_pPreviousPage->setVisible(false);
        m_pPreviousSeveralPage->setVisible(false);
        m_pNextPageSeveralPage->setVisible(false);
        m_pNextPage->setVisible(false);
        for(auto button : m_pPageButtons)
        {
            button->setVisible(false);
        }
    } else if(m_nTotalPages <= static_cast<qulonglong>(m_pPageButtons.size()))
    {
        m_pPreviousPage->setVisible(true);
        m_pPreviousSeveralPage->setVisible(false);
        m_pNextPageSeveralPage->setVisible(false);
        m_pNextPage->setVisible(true);
        for(int i = 0; i < m_pPageButtons.size(); i++)
        {
            if(i < static_cast<int>(m_nTotalPages))
            {
                m_pPageButtons.at(i)->setVisible(true);
            } else {
                m_pPageButtons.at(i)->setVisible(false);
            }
        }
        for(int i = 0; i < m_pPageButtons.size(); i++)
        {
            m_pPageButtons.at(i)->setText(QString::number(i+1));
        }
    } else if(m_nTotalPages > static_cast<qulonglong>(m_pPageButtons.size()))
    {
        m_pPreviousPage->setVisible(true);
        m_pPreviousSeveralPage->setVisible(false);
        m_pNextPageSeveralPage->setVisible(false);
        m_pNextPage->setVisible(true);
        for(int i = 0; i < m_pPageButtons.size(); i++)
        {
            m_pPageButtons.at(i)->setVisible(true);
        }
        for(int i = 0; i < 3; i++)
        {
            m_pPageButtons.at(i)->setText(QString::number(i+1));
            m_pPageButtons.at(m_pPageButtons.size()-1-i)->setText(QString::number(m_nTotalPages - i));
        }
        UpdatePageButtonState();
    }
}

void CatPagingNavigation::UpdatePageButtonState()
{
    if(m_nCurrentPage - m_pPageButtons.at(0)->text().toULongLong() <= 3)
    {
        for(int i = 3; i < 6; i++)
        {
            m_pPageButtons.at(i)->setText(QString::number(m_pPageButtons.at(i-1)->text().toULongLong() + 1));
        }
        m_pNextPageSeveralPage->setVisible(true);
    } else if(m_pPageButtons.at(m_pPageButtons.size()-1)->text().toULongLong() - m_nCurrentPage <= 3)
    {
        for(int i = 6; i > 3; i--)
        {
            m_pPageButtons.at(i)->setText(QString::number(m_pPageButtons.at(i+1)->text().toULongLong() - 1));
        }
        m_pPreviousSeveralPage->setVisible(true);
    } else {
        qulonglong pages = m_nCurrentPage - 1;
        for(int i = 3; i < 6; i++)
        {
            m_pPageButtons.at(i)->setText(QString::number(pages));
            pages++;
        }
        m_pPreviousSeveralPage->setVisible(true);
        m_pNextPageSeveralPage->setVisible(true);
    }
    for(auto button : m_pPageButtons)
    {
        if(button->text().toULongLong() == m_nCurrentPage)
        {
            button->setChecked(true);
        }
    }
}

void CatPagingNavigation::SetPageButtonState(QString state, int id)
{
    m_pPageButtons.at(id)->setProperty("State", state);
    m_pPageButtons.at(id)->setStyle(QApplication::style());
}

bool CatPagingNavigation::eventFilter(QObject *watched, QEvent *event)
{
    if(watched->objectName() == "PreviousSeveralPage" ||
            watched->objectName() == "NextPageSeveralPage")
    {
        if(event->type() == QEvent::Type::HoverLeave) {
            if(watched->objectName() == "PreviousSeveralPage") m_pPreviousSeveralPage->setText("...");
            if(watched->objectName() == "NextPageSeveralPage") m_pNextPageSeveralPage->setText("...");
        } else if(event->type() == QEvent::Type::HoverEnter
              || event->type() == QEvent::Type::MouseMove
              || event->type() == QEvent::Type::MouseButtonPress)
        {
            if(watched->objectName() == "PreviousSeveralPage")
            {
                m_pPreviousSeveralPage->setText("<<");
            }
            if(watched->objectName() == "NextPageSeveralPage")
            {
                m_pNextPageSeveralPage->setText(">>");
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void CatPagingNavigation::ButtonGrouped(QAbstractButton *button)
{
    SetCurrentPage(button->text().toULongLong());
}

void CatPagingNavigation::SetCurrentPage(qulonglong currentpage)
{
    if(currentpage > 0 && currentpage <= m_nTotalPages)
    {
        m_nCurrentPage = currentpage;
        UpdatePagingNavigation();
        emit CurrentPageed(m_nCurrentPage);
    }
}

