#include "CatConfig.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QTimer>

CatConfig* CatConfig::_instance = nullptr;
QMutex* CatConfig::m_pMutex = new QMutex;
QString CatConfig::m_sConfigPath = "";


void CatConfig::SetValue(QString key, QVariant var, QString node)
{
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        QString cmd;
        if(node.isEmpty())
        {
            cmd = QString("%1").arg(key);
        } else {
            cmd = QString("%1/%2").arg(node).arg(key);
        }
        setting.setValue(cmd, var);
    }
}

void CatConfig::RemoveNodeValue(QString node, QString key)
{
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        QString cmd = QString("%1/%2").arg(node).arg(key);
        setting.remove(cmd);
    }
}

void CatConfig::RemoveNode(QString node)
{
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        setting.remove(node);
    }
}

void CatConfig::SetGroup(QString node, QStringList keys, QVariantList vars)
{
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        int size = qMin(keys.size(), vars.size());
        setting.beginGroup(node);
        for(int i = 0; i < size; i++)
        {
            setting.setValue(keys[i], vars[i]);
        }
        setting.endGroup();
    }
}

void CatConfig::SetArray(QString node, QStringList keys, QVariantList vars)
{
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        int size = qMin(keys.size(), vars.size());
        setting.beginWriteArray(node);
        for(int i = 0; i < size; i++)
        {

            setting.setArrayIndex(i);
            setting.setValue(keys[i], vars[i]);
        }
        setting.endArray();
    }
}

QVariant CatConfig::GetValue(QString key, QString node)
{
    QVariant var;
    var.clear();
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        if(node.isEmpty())
        {
            if(setting.contains(key))
            {
                var = setting.value(key);
            }
        } else {
            QString cmd = QString("%1/%2").arg(node).arg(key);
            var = setting.value(cmd);
        }
    }
    return var;
}

QMultiMap<QString, QVariant> CatConfig::GetArray(QString node, QStringList keys)
{
    QMultiMap<QString, QVariant> map;
    map.clear();
    if(ConfigExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        int size = setting.beginReadArray(node);
        for(int i = 0; i < size; i++)
        {
            setting.setArrayIndex(i);
            map.insert(keys[i], setting.value(keys[i]));
        }
        setting.endArray();
    }
    return map;
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
        QFileInfo info(m_sConfigPath);
        info.exists();
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        setting.setValue("AppName", APP_NAME);
        setting.setValue("AppVersion", APP_VERSION);
        QTimer::singleShot(50, this, [=](){
            QStringList style = {"style", "style"};
            QVariantList styleNames = { "CatGray", "CatWhite" };
            SetArray("StyleSheets", style, styleNames);

            QStringList defaultKeys = { "style" };
            QVariantList defaultVars = { "CatGray" };
            SetGroup("Defaule", defaultKeys, defaultVars);
        });
    }
}

bool CatConfig::ConfigExist()
{
    QFileInfo fileInfo(m_sConfigPath);
    return fileInfo.isFile();
}
