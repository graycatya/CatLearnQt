#include "ButtonTool.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QShowEvent>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>

ButtonTool::ButtonTool(QWidget *parent)
    : QWidget(parent)
{
    InitUi();

    InitProperty();
}

ButtonTool::~ButtonTool()
{

}

void ButtonTool::InitUi()
{
    m_pRootLayout = new QVBoxLayout(this);
    m_pRootLayout->setContentsMargins(0,0,0,0);
    m_pRootLayout->setSpacing(0);
    m_pRootWidget = new QWidget(this);
    m_pRootWidget->setObjectName("RootWidget");
    m_pRootWidgetLayout = new QHBoxLayout(m_pRootWidget);
    m_pRootWidgetLayout->setContentsMargins(2,2,2,2);
    m_pRootWidgetLayout->setSpacing(0);
    m_pRootLayout->addWidget(m_pRootWidget);
}

void ButtonTool::InitProperty()
{
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    //获取程序当前运行目录
    //QString path = QCoreApplication::applicationDirPath();

    QFile resourceqss(":/ImageTools/qss/ButtonTool.qss");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    m_qButtons.clear();
}

void ButtonTool::SetCutToolTip()
{
    for(auto temp : m_qButtons)
    {
        if(temp->objectName() == "CutButton")
        {
            temp->setToolTip(tr("cut"));
        }
    }
}

void ButtonTool::SetSaveToolTip()
{
    for(auto temp : m_qButtons)
    {
        if(temp->objectName() == "SaveButton")
        {
            temp->setToolTip(tr("save"));
        }
    }
}

void ButtonTool::SetCloseToolTip()
{
    for(auto temp : m_qButtons)
    {
        if(temp->objectName() == "CloseButton")
        {
            temp->setToolTip(tr("close"));
        }
    }
}

void ButtonTool::InitButtons(QStringList buttons)
{
    m_qButtonList = buttons;
    for(auto button : m_qButtonList)
    {
        QPushButton *m_pButton = new QPushButton(m_pRootWidget);
        m_pButton->setObjectName(button);
        /*button.replace("Button", "");
        m_pButton->setToolTip(tr(button.toUtf8().data()));*/
        connect(m_pButton, &QPushButton::clicked, this, [=](){
            QPushButton* button = qobject_cast<QPushButton*>(sender());
            if(button->objectName() == "CutButton")
            {
                emit clicked(STATE::CUT);
            } else if(button->objectName() == "LampButton")
            {
                emit clicked(STATE::LAMP);
            } else if(button->objectName() == "SaveButton")
            {
                emit clicked(STATE::SAVE);
            } else if(button->objectName() == "CloseButton")
            {
                emit clicked(STATE::CLOSE);
            }
        });
        m_qButtons.push_back(m_pButton);
        m_pRootWidgetLayout->addWidget(m_pButton);
    }

    SetCutToolTip();
    SetSaveToolTip();
    SetCloseToolTip();

}

void ButtonTool::SetLampToolTip(bool lamp)
{
    for(auto temp : m_qButtons)
    {
        if(temp->objectName() == "LampButton")
        {
            if(lamp)
            {
                temp->setToolTip(tr("CloseLamp"));
            } else {
                temp->setToolTip(tr("OpenLamp"));
            }

        }
    }
}

