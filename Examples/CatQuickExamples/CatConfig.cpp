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



void CatConfig::InitConfig()
{
    if(!configExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);

        setting.setValue("Style", 0);

    } else {

        // nullptr
    }
}

bool CatConfig::configExist()
{
    return CatSettingBase::ConfigExist(m_sConfigPath);
}

void CatConfig::setValue(QString key, QVariant var, QString node)
{
    CatSettingBase::SetValue(m_sConfigPath, key, var, node);
}

void CatConfig::removeNodeValue(QString node, QString key)
{
    CatSettingBase::RemoveNodeValue(m_sConfigPath, node, key);
}

void CatConfig::removeNode(QString node)
{
    CatSettingBase::RemoveNode(m_sConfigPath, node);
}

void CatConfig::setGroup(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetGroup(m_sConfigPath, node, keys, vars);
}

void CatConfig::setArray(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetArray(m_sConfigPath, node, keys, vars);
}

QStringList CatConfig::getKeys(QString node)
{
    return CatSettingBase::GetKeys(m_sConfigPath, node);
}

QVariant CatConfig::getValue(QString key, QString node)
{
    return CatSettingBase::GetValue(m_sConfigPath, key, node);
}

QMultiMap<QString, QVariant> CatConfig::getArray(QString node, QStringList keys)
{
    return CatSettingBase::GetArray(m_sConfigPath, node, keys);
}

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
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(QCoreApplication::applicationDirPath().toStdString()));
    m_sConfigPath = QCoreApplication::applicationDirPath() + "/quickexampleconfig.ini";
}

CatConfig::~CatConfig()
{

}
