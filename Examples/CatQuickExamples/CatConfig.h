#ifndef CATCONFIG_H
#define CATCONFIG_H

#include "CatSettingBase.h"
#include <QMutex>
#include <QLocale>
#include <QGuiApplication>

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
        return WEBRESOURCEPATH;
    #endif
    }

private:
    CatConfig();
    ~CatConfig();

signals:
    void UpdateStyleSheets();

private:
    static CatConfig* _instance;
    static QMutex* m_pMutex;
    static QString m_sConfigPath;
    static QGuiApplication *m_pApp;
    static QTranslator *m_pTranslator;
};

#endif // CATCONFIG_H
