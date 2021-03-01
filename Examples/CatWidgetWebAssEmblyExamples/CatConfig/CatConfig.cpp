#include "CatConfig.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include <QTimer>
#include <QApplication>
#include <QTranslator>

CatConfig* CatConfig::_instance = nullptr;
QMutex* CatConfig::m_pMutex = new QMutex;
QString CatConfig::m_yStyle = "CatGray";


CatConfig::CatConfig()
{

    //InitConfig();
}

CatConfig::~CatConfig()
{

}



QStringList CatConfig::GetStyles()
{
    return { "CatGray", "CatWhite" };
}

void CatConfig::SetStyle(QString style)
{
    m_yStyle = style;
    emit UpdateStyleSheets();
}

QString CatConfig::GetStyle()
{
    return m_yStyle;
}

void CatConfig::InitConfig()
{
    // [0] 判断配置文件是否存在
}

