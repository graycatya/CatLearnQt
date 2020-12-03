#ifndef CATCONFIG_H
#define CATCONFIG_H

#include <QSettings>
#include <QMutex>

class CatConfig : public QObject
{
    Q_OBJECT
public:
    static CatConfig* Instance() noexcept
    {

    }

    static void Delete() noexcept
    {

    }

private:
    CatConfig();

private:
    static CatConfig* _instance;
    static QSettings *m_ySetting;
    static QMutex* m_pMutex;
};

#endif // CATCONFIG_H
