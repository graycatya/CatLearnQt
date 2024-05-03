#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <QObject>
#include "CatSettingBase.h"

#include <QMutex>
#include <QMultiMap>
#include <QVariant>

class ServerConfig : public CatSettingBase
{
    Q_OBJECT
public:
    static ServerConfig* Instance() noexcept
    {
        if(_instance == nullptr)
        {
            m_pMutex->lock();
            if(_instance == nullptr)
            {
                _instance = new ServerConfig;
            }
            m_pMutex->unlock();
        }
        return _instance;
    }

    static void Delete( void ) noexcept
    {
        if(_instance != nullptr)
        {
            if(m_pMutex != nullptr)
            {
                delete m_pMutex;
                m_pMutex = nullptr;
            }

            delete _instance;
            _instance = nullptr;
        }
    }

    Q_INVOKABLE static void setValue(QString key, QVariant var, QString node = "");
    Q_INVOKABLE static void removeNodeValue(QString node, QString key);
    Q_INVOKABLE static void removeNode(QString node);

    Q_INVOKABLE static void setGroup(QString node, QStringList keys, QVariantList vars);
    Q_INVOKABLE static void setArray(QString node, QStringList keys, QVariantList vars);

    Q_INVOKABLE static QStringList getKeys(QString node = "");
    Q_INVOKABLE static QVariant getValue(QString key, QString node = "");
    Q_INVOKABLE static QMultiMap<QString, QVariant> getArray(QString node, QStringList keys);
    Q_INVOKABLE static QMultiMap<QString, QVariant> GetArray(QString node);
    Q_INVOKABLE static QVector<QVariant> GetArrays(QString node);

    Q_INVOKABLE static bool configExist();


private:
    ServerConfig();
    ~ServerConfig();

signals:

private:
    static ServerConfig* _instance;
    static QMutex* m_pMutex;
    static QString m_sConfigPath;

};

#endif // SERVERCONFIG_H
