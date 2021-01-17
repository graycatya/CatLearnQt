#include "ImageTools.h"
#include "ui_ImageTools.h"
#include "../CatConfig/CatConfig.h"

#include <QPushButton>
#include <CatLog>
#include <QFile>
#include <QDesktopWidget>

#include "CatWidget/ImageTools/ImageToolFactory.h"
#include "CatWidget/ImageTools/ImageToolBase.h"

ImageTools::ImageTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageTools)
{
    ui->setupUi(this);
    InitUi();
    InitProperty();
    InitConnect();
}

ImageTools::~ImageTools()
{
    delete ui;
}

void ImageTools::InitUi()
{
    m_pToolButtons.clear();
    QStringList ButtonsList = { "ScreenShotButton", "SpotLightButton",
                                "MagnifyingClassButton" };

    for(int i = 0; i < ButtonsList.size(); i++)
    {
        QPushButton *button = new QPushButton(this);
        button->setObjectName(ButtonsList[i]);
        ui->ToolsLayout->addWidget(button, i/4, i - 4*(i/4));
        m_pToolButtons[ButtonsList[i]] = button;
    }

}

void ImageTools::InitProperty()
{
    UpdateStyle();
}

void ImageTools::InitConnect()
{
    connect(CatConfig::Instance(), &CatConfig::UpdateStyleSheets, this, [=](){
        UpdateStyle();
    });

    connect(m_pToolButtons["ScreenShotButton"], &QPushButton::clicked, this, [=](){
        ImageToolFactory factory;
        ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::SCREENSHOT);
        connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
            if(state == ImageToolBase::STATE::CLOSE){
                base->deleteLater();
            }
        });
        base->setGeometry(0,0,
                          QApplication::desktop()->size().width(),
                          QApplication::desktop()->size().height());
        //base->setWindowState(base->windowState() ^ Qt::WindowFullScreen);

        base->show();
        //base->show();
    });

    connect(m_pToolButtons["SpotLightButton"], &QPushButton::clicked, this, [=](){
        ImageToolFactory factory;
        ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::SPOTLIGHT);
        connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
            if(state == ImageToolBase::STATE::CLOSE){
                base->deleteLater();
            }
        });
        base->setGeometry(0,0,
                          QApplication::desktop()->size().width(),
                          QApplication::desktop()->size().height());
        base->show();
    });

    connect(m_pToolButtons["MagnifyingClassButton"], &QPushButton::clicked, this, [=](){
        ImageToolFactory factory;
        ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::MAGNIFYINGGLASS);
        connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
            if(state == ImageToolBase::STATE::CLOSE){
                base->deleteLater();
            }
        });
        base->setGeometry(0,0,
                          QApplication::desktop()->size().width(),
                          QApplication::desktop()->size().height());
        base->show();
    });
}

void ImageTools::UpdateStyle()
{
    QString stylePath;
    if(CatConfig::ConfigExist())
    {
        stylePath = ":/qss/" + CatConfig::GetValue("style", "Defaule").toString() + "/";
    } else {
        stylePath = ":/qss/CatGray/";
    }

    QFile file_0(stylePath + "ImageTools.css");
    file_0.open(QIODevice::ReadOnly);
    QString stylehoot_0 = QLatin1String(file_0.readAll());
    this->setStyleSheet(stylehoot_0);
    file_0.close();
}
