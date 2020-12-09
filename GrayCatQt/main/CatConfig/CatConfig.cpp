#include "CatConfig.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include <QTimer>

CatConfig* CatConfig::_instance = nullptr;
QMutex* CatConfig::m_pMutex = new QMutex;
QString CatConfig::m_sConfigPath = "";



void CatConfig::SetValue(QString key, QVariant var, QString node)
{
    CatSettingBase::SetValue(m_sConfigPath, key, var, node);
}

void CatConfig::RemoveNodeValue(QString node, QString key)
{
    CatSettingBase::RemoveNodeValue(m_sConfigPath, node, key);
}

void CatConfig::RemoveNode(QString node)
{
    CatSettingBase::RemoveNode(m_sConfigPath, node);
}

void CatConfig::SetGroup(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetGroup(m_sConfigPath, node, keys, vars);
}

void CatConfig::SetArray(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetArray(m_sConfigPath, node, keys, vars);
}

QStringList CatConfig::GetKeys(QString node)
{
    return CatSettingBase::GetKeys(m_sConfigPath, node);
}

QVariant CatConfig::GetValue(QString key, QString node)
{
    return CatSettingBase::GetValue(m_sConfigPath, key, node);
}

QMultiMap<QString, QVariant> CatConfig::GetArray(QString node, QStringList keys)
{
    return CatSettingBase::GetArray(m_sConfigPath, node, keys);
}

void CatConfig::SetWindowStyle(QVariant var)
{
    CatSettingBase::SetValue(m_sConfigPath, "style", var, "Defaule");
    emit UpdateStyleSheets();
}

bool CatConfig::ConfigExist()
{
    return CatSettingBase::ConfigExist(m_sConfigPath);
}

CatConfig::CatConfig()
{
    m_sConfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    InitConfig();
}

CatConfig::~CatConfig()
{

}

void CatConfig::InitConfig()
{
    // [0] 判断配置文件是否存在

    if(!ConfigExist())
    {
        /*QFileInfo info(m_sConfigPath);
        info.exists();*/
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        setting.setValue("AppName", APP_NAME);
        setting.setValue("AppVersion", APP_VERSION);
        setting.setValue("HomePage", "www.graycatya.com");

        QStringList style = {"style", "style"};
        QVariantList styleNames = { "CatGray", "CatWhite" };
        CatSettingBase::SetArray(m_sConfigPath, "StyleSheets", style, styleNames);

        QStringList defaultKeys = { "style" };
        QVariantList defaultVars = { "CatGray" };
        CatSettingBase::SetGroup(m_sConfigPath, "Defaule", defaultKeys, defaultVars);

    }
}

