#include "CatConfig.h"
#include <QSettings>
#include <QTimer>
#include <QTranslator>
#include <CatLog>


CatConfig* CatConfig::_instance = nullptr;
QMutex* CatConfig::m_pMutex = new QMutex;
QString CatConfig::m_sConfigPath = "";
QGuiApplication* CatConfig::m_pApp = nullptr;
QTranslator* CatConfig::m_pTranslator = nullptr;



QList<QString> CatConfig::systemFontFamily(QFontDatabase::WritingSystem writingSystem)
{
    QList<QString> familys;
    QFontDatabase fonts;
    foreach (const QString &family, fonts.families(writingSystem))
    {
         familys.append(family);
    }
    return familys;
}

CatConfig::CatConfig()
{
    m_sConfigPath = QCoreApplication::applicationDirPath() + "/quickexampleconfig.ini";
}

CatConfig::~CatConfig()
{

}
