#include "ServerConfig.h"
#include <QSettings>
#include <QClipboard>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QVariant>

ServerConfig* ServerConfig::_instance = nullptr;
QMutex* ServerConfig::m_pMutex = new QMutex;
QString ServerConfig::m_sConfigPath = "";

void ServerConfig::setValue(QString key, QVariant var, QString node)
{
    CatSettingBase::SetValue(m_sConfigPath, key, var, node);
}

void ServerConfig::removeNodeValue(QString node, QString key)
{
    CatSettingBase::RemoveNodeValue(m_sConfigPath, node, key);
}

void ServerConfig::removeNode(QString node)
{
    CatSettingBase::RemoveNode(m_sConfigPath, node);
}

void ServerConfig::setGroup(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetGroup(m_sConfigPath, node, keys, vars);
}

void ServerConfig::setArray(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetArray(m_sConfigPath, node, keys, vars);
}

QStringList ServerConfig::getKeys(QString node)
{
    return CatSettingBase::GetKeys(m_sConfigPath, node);
}

QVariant ServerConfig::getValue(QString key, QString node)
{
    return CatSettingBase::GetValue(m_sConfigPath, key, node);
}

QMultiMap<QString, QVariant> ServerConfig::getArray(QString node, QStringList keys)
{
    return CatSettingBase::GetArray(m_sConfigPath, node, keys);
}

QMultiMap<QString, QVariant> ServerConfig::GetArray(QString node)
{
    return CatSettingBase::GetArray(m_sConfigPath, node);
}

QVector<QVariant> ServerConfig::GetArrays(QString node)
{
    return CatSettingBase::GetArrays(m_sConfigPath, node);
}

bool ServerConfig::configExist()
{
    return CatSettingBase::ConfigExist(m_sConfigPath);
}

ServerConfig::ServerConfig()
{
    m_sConfigPath = QCoreApplication::applicationDirPath() + "/SerialServerConfig.ini";
}

ServerConfig::~ServerConfig()
{

}
