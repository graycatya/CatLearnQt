#ifndef CATCONFIG_H
#define CATCONFIG_H

#include <QSettings>
#include <QMutex>

class CatConfig : public QSettings
{
    Q_OBJECT
public:
    static CatConfig* Instance() noexcept
    {
        if(_instance == nullptr)
        {
            m_pMutex->lock();
            if(_instance == nullptr)
            {
                _instance = new CatConfig;
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

    static void SetValue(QString key, QVariant var, QString node = "");
    static void RemoveNodeValue(QString node, QString key);
    static void RemoveNode(QString node);

    static void SetGroup(QString node, QStringList keys, QVariantList vars);
    static void SetArray(QString node, QStringList keys, QVariantList vars);

    static QVariant GetValue(QString key, QString node = "");
    static QMultiMap<QString, QVariant> GetArray(QString node, QStringList keys);

signals:
    void UpdateStyleSheets();


private:
    CatConfig();
    ~CatConfig();

    void InitConfig();

    static bool ConfigExist();

private:
    static CatConfig* _instance;
    static QMutex* m_pMutex;
    static QString m_sConfigPath;

};

#endif // CATCONFIG_H
