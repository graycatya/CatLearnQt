#include "CatSettingBase.h"
#include <QSettings>
#include <QFileInfo>

CatSettingBase::CatSettingBase(QObject *parent)
 : QObject(parent)
{

}

CatSettingBase::~CatSettingBase()
{

}

void CatSettingBase::SetValue(QString file, QString key, QVariant var, QString node)
{

    QSettings setting(file, QSettings::IniFormat);
    QString cmd;
    if(node.isEmpty())
    {
        cmd = QString("%1").arg(key);
    } else {
        cmd = QString("%1/%2").arg(node).arg(key);
    }
    setting.setValue(cmd, var);

}

void CatSettingBase::RemoveNodeValue(QString file, QString node, QString key)
{

    QSettings setting(file, QSettings::IniFormat);
    QString cmd = QString("%1/%2").arg(node).arg(key);
    setting.remove(cmd);

}

void CatSettingBase::RemoveNode(QString file, QString node)
{

    QSettings setting(file, QSettings::IniFormat);
    setting.remove(node);

}

void CatSettingBase::SetGroup(QString file, QString node, QStringList keys, QVariantList vars)
{

    QSettings setting(file, QSettings::IniFormat);
    int size = qMin(keys.size(), vars.size());
    setting.beginGroup(node);
    for(int i = 0; i < size; i++)
    {
        setting.setValue(keys[i], vars[i]);
    }
    setting.endGroup();

}

void CatSettingBase::SetArray(QString file, QString node, QStringList keys, QVariantList vars)
{

    QSettings setting(file, QSettings::IniFormat);
    int size = qMin(keys.size(), vars.size());
    setting.beginWriteArray(node);
    for(int i = 0; i < size; i++)
    {

        setting.setArrayIndex(i);
        setting.setValue(keys[i], vars[i]);
    }
    setting.endArray();

}

QStringList CatSettingBase::GetKeys(QString file, QString node)
{
    QStringList list;

    QSettings setting(file, QSettings::IniFormat);
    if(node.isEmpty())
    {

        list = setting.childKeys();
    } else {
        setting.beginGroup(node);
        list = setting.childKeys();
        setting.endGroup();
    }

    return list;
}


QVariant CatSettingBase::GetValue(QString file, QString key, QString node)
{
    QVariant var;
    var.clear();

    QSettings setting(file, QSettings::IniFormat);
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

    return var;
}

QMultiMap<QString, QVariant> CatSettingBase::GetArray(QString file, QString node, QStringList keys)
{
    QMultiMap<QString, QVariant> map;
    map.clear();

    QSettings setting(file, QSettings::IniFormat);
    int size = setting.beginReadArray(node);
    Q_UNUSED(size)
    QStringList settingkeys = setting.allKeys();
    for(int i = 0; i < settingkeys.size(); i++)
    {
        if(settingkeys[i].split('/').size() == 2)
        {
            if(keys.contains(settingkeys[i].split('/').at(1)))
            {
                map.insert(settingkeys[i].split('/').at(1), setting.value(settingkeys[i]));
            }
        }
    }
    setting.endArray();
    return map;
}

QMultiMap<QString, QVariant> CatSettingBase::GetArray(QString file, QString node)
{
    QMultiMap<QString, QVariant> map;
    map.clear();

    QSettings setting(file, QSettings::IniFormat);
    int size = setting.beginReadArray(node);
    QStringList keys = setting.allKeys();
    for(int i = size - 1; i >= 0; i--)
    {
        setting.setArrayIndex(i);
        map.insert(keys[i], setting.value(keys[i]));
    }
    setting.endArray();

    return map;
}

QVector<QVariant> CatSettingBase::GetArrays(QString file, QString node)
{
    QVector<QVariant> map;
    map.clear();

    QSettings setting(file, QSettings::IniFormat);
    int size = setting.beginReadArray(node);
    QStringList keys = setting.allKeys();
    for(int i = size - 1; i >= 0; i--)
    {
        setting.setArrayIndex(i);
        QString temp = setting.value(QString::number(i)).toString();
        map.push_back(setting.value(QString::number(i)));
    }
    setting.endArray();

    return map;
}

bool CatSettingBase::ConfigExist(QString file)
{
    QFileInfo fileInfo(file);
    return fileInfo.isFile();
}
