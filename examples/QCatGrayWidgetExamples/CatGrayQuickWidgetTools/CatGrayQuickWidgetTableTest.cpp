#include "CatGrayQuickWidgetTableTest.h"

#include <QVBoxLayout>
#include <QDebug>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlEngine>
#include "CatConfig.h"
#include "QCatGrayQuickPlugins.h"
#include "QCatGrayQuickWidget.h"

CatGrayQuickWidgetTableTest::CatGrayQuickWidgetTableTest(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
    InitProperty();
    InitConnect();
}

CatGrayQuickWidgetTableTest::~CatGrayQuickWidgetTableTest()
{

}

void CatGrayQuickWidgetTableTest::InitUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    m_pCatGrayQuickWidget = new QCatGrayQuickWidget(this);
    layout->addWidget(m_pCatGrayQuickWidget);
}

void CatGrayQuickWidgetTableTest::InitProperty()
{
    QCatGrayQuickPlugins qcatgrayquickplugins;
    qcatgrayquickplugins.InitQCatGrayQuickPlugins(m_pCatGrayQuickWidget->view()->engine());
}

void CatGrayQuickWidgetTableTest::InitConnect()
{
    connect(m_pCatGrayQuickWidget, &QCatGrayQuickWidget::statusChanged, this, [=](){
        qDebug() << "CatGrayQuickWidget status: " << m_pCatGrayQuickWidget->status();
        if(m_pCatGrayQuickWidget->status() == QCatGrayQuickWidget::Ready)
        {
            connect(this, SIGNAL(updateStyleed(int)),
                    m_pCatGrayQuickWidget->view()->rootObject(), SIGNAL(updateStyle(int)));

            UpdateStyle();
        }
    });



    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    m_pCatGrayQuickWidget->setSource(QUrl("qrc:/qml/CatGrayQuickWidgetTableTest.qml"));
}

void CatGrayQuickWidgetTableTest::UpdateStyle()
{
    if(CatConfig::GetValue("style", "Defaule").toString() == "CatWhite")
    {
        emit updateStyleed(0);
    } else if(CatConfig::GetValue("style", "Defaule").toString() == "CatGray")
    {
        emit updateStyleed(1);
    }
}
