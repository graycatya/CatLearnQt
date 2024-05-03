#ifndef CATCONFIG_H
#define CATCONFIG_H

#include "CatUniversal/CatSettingBase.h"
#include <QMutex>
#include <QLocale>

class QApplication;
class QTranslator;

class CatConfig : public QObject
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

    static QStringList GetStyles( void );
    void SetStyle(QString style);
    static QString GetStyle( void );

    void InitConfig();

signals:
    void UpdateStyleSheets();


private:
    CatConfig();
    ~CatConfig();


    void UpdateTranslator(QString translator);


private:
    static CatConfig* _instance;
    static QMutex* m_pMutex;
    static QString m_yStyle;
};

#endif // CATCONFIG_H
