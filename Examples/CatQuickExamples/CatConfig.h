#ifndef CATCONFIG_H
#define CATCONFIG_H

#include "CatSettingBase.h"
#include <QMutex>
#include <QLocale>
#include <QDebug>
#include <QGuiApplication>
#include <QFontDatabase>

class QTranslator;

class CatConfig : public CatSettingBase
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

    void InitConfig();

    Q_INVOKABLE static bool configExist();

    Q_INVOKABLE static void setValue(QString key, QVariant var, QString node = "");
    Q_INVOKABLE static void removeNodeValue(QString node, QString key);
    Q_INVOKABLE static void removeNode(QString node);

    Q_INVOKABLE static void setGroup(QString node, QStringList keys, QVariantList vars);
    Q_INVOKABLE static void setArray(QString node, QStringList keys, QVariantList vars);

    Q_INVOKABLE static QStringList getKeys(QString node = "");
    Q_INVOKABLE static QVariant getValue(QString key, QString node = "");
    Q_INVOKABLE static QMultiMap<QString, QVariant> getArray(QString node, QStringList keys);


    Q_INVOKABLE static QList<QString> getAppDefineLanguages();
    Q_INVOKABLE static QString getCurrentLanguage();
    Q_INVOKABLE static void setCurrentLanguage(QString lan);


    Q_INVOKABLE QList<QString> systemFontFamily(QFontDatabase::WritingSystem writingSystem = QFontDatabase::Any);

    Q_INVOKABLE bool qtQuick3D()
    {
        #ifdef QT_QUICK3D_LIB
                return true;
        #else
                return false;
        #endif
    }

    Q_INVOKABLE bool qtWebEngine()
    {
        #ifdef QT_WEBENGINE_LIB
            return true;
        #else
            return false;
        #endif
    }

    Q_INVOKABLE QString getWebResourcePath()
    {
    #ifdef QT_NO_DEBUG
        return QCoreApplication::applicationDirPath() + "/WebResource";
    #else
        qDebug() << WEBRESOURCEPATH;
        return WEBRESOURCEPATH;
    #endif
    }

    void InitQmlRegisterType();

private:
    CatConfig();
    ~CatConfig();

    static void InitLanguage(int l);
    static bool FileExiste(const QString &filePath, bool newfile = false);

signals:
    //void updateStyleSheets();
    void updateLanguage();

private:
    static CatConfig* _instance;
    static QMutex* m_pMutex;
    static QString m_sConfigPath;
    static QGuiApplication *m_pApp;
    static QTranslator *m_pTranslator;
    static QTranslator *m_pTranslatorDi;
};

#endif // CATCONFIG_H
