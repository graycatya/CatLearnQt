#include "CatConfig.h"
#include <QSettings>
#include <QTimer>
#include <QTranslator>
#include <CatLog>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>

#include "CatEncp.h"
#include "QrenCode/QuickQrenCodeParentItem.h"
#ifdef _MSC_VER
#include "Src/WebChannelFunction/CatEchatswebChannel.h"
#endif


CatConfig* CatConfig::_instance = nullptr;
QMutex* CatConfig::m_pMutex = new QMutex;
QString CatConfig::m_sConfigPath = "";
QGuiApplication* CatConfig::m_pApp = nullptr;
QTranslator* CatConfig::m_pTranslator = nullptr;
QTranslator* CatConfig::m_pTranslatorDi = nullptr;



void CatConfig::InitConfig()
{
    InitQmlRegisterType();
    if(!configExist())
    {
        QSettings setting(m_sConfigPath, QSettings::IniFormat);

        setting.setValue("Style", 0);
        QLocale locale;
        switch (locale.system().language()) {
            case QLocale::Chinese: {
                setting.setValue("Language", 1);
                break;
            }
            default: {
                setting.setValue("Language", 0);
                break;
            }
        }
        InitLanguage(getValue("Language").toInt());
    } else {
        InitLanguage(getValue("Language").toInt());
    }
}

bool CatConfig::configExist()
{
    return CatSettingBase::ConfigExist(m_sConfigPath);
}

void CatConfig::setValue(QString key, QVariant var, QString node)
{
    CatSettingBase::SetValue(m_sConfigPath, key, var, node);
}

void CatConfig::removeNodeValue(QString node, QString key)
{
    CatSettingBase::RemoveNodeValue(m_sConfigPath, node, key);
}

void CatConfig::removeNode(QString node)
{
    CatSettingBase::RemoveNode(m_sConfigPath, node);
}

void CatConfig::setGroup(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetGroup(m_sConfigPath, node, keys, vars);
}

void CatConfig::setArray(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetArray(m_sConfigPath, node, keys, vars);
}

QStringList CatConfig::getKeys(QString node)
{
    return CatSettingBase::GetKeys(m_sConfigPath, node);
}

QVariant CatConfig::getValue(QString key, QString node)
{
    return CatSettingBase::GetValue(m_sConfigPath, key, node);
}

QMultiMap<QString, QVariant> CatConfig::getArray(QString node, QStringList keys)
{
    return CatSettingBase::GetArray(m_sConfigPath, node, keys);
}

QList<QString> CatConfig::getAppDefineLanguages()
{
    QList<QString> list;
    QLocale locale;
    switch (locale.system().language()) {
        case QLocale::Chinese: {
            list.push_back("English");
            list.push_back(QStringLiteral("Chinese"));
            break;
        }
        default: {
            list.push_back("English");
            list.push_back("Chinese");
            break;
        }
    }
    return list;
}

QString CatConfig::getCurrentLanguage()
{
    QString lang;
    QLocale locale;
    switch (locale.system().language()) {
        case QLocale::Chinese: {
            if(getValue("Language").toInt() == 1)
            {
                lang = QStringLiteral("Chinese");
            } else {
                lang = "English";
            }
            break;
        }
        default: {
            if(getValue("Language").toInt() == 1)
            {
                lang = "Chinese";
            } else {
                lang = "English";
            }
            break;
        }
    }

    return lang;
}

void CatConfig::setCurrentLanguage(QString lan)
{
    QLocale locale;
     switch (locale.system().language()) {
         case QLocale::Chinese: {
             if(lan == QStringLiteral("Chinese"))
             {
                 setValue("Language", 1);
             } else {
                 setValue("Language", 0);
             }
             break;
         }
         default: {
             if(lan == "Chinese")
             {
                 setValue("Language", 1);
             } else {
                 setValue("Language", 0);
             }
             break;
         }
     }
     InitLanguage(getValue("Language").toInt());
}

QByteArray CatConfig::getLicenceHtml()
{
    QFile file_licence(":/Licence/Licence.html");
    file_licence.open(QIODevice::ReadOnly);
    QByteArray licencemd = file_licence.readAll();
    file_licence.close();
    return licencemd;
}

void CatConfig::openWebUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

QString CatConfig::getQtVersion()
{
    return QT_VERSION_STR;
}

QList<QString> CatConfig::systemFontFamily(QFontDatabase::WritingSystem writingSystem)
{
    QList<QString> familys;
    QFontDatabase fonts;
    foreach (const QString &family, fonts.families(writingSystem))
    {
         familys.append(family);
    }
    return familys;
}

void CatConfig::InitQmlRegisterType()
{
    qmlRegisterType<QuickQrenCodeParentItem>("QParentQrenCode", 1, 0, "ParentQrenCode");
    qmlRegisterType<CatEncp>("CatEncp", 1, 0, "CatEncp");
#ifdef QT_WEBENGINE_LIB
    qmlRegisterType<CatEchatswebChannel>("io.decovar.CatEchatswebChannel", 1, 0, "CatEchatswebChannel");
#endif
}

CatConfig::CatConfig()
{
    CATLOG::CatLog::__Write_Log(DEBUG_LOG_T(QCoreApplication::applicationDirPath().toStdString()));
    m_sConfigPath = QCoreApplication::applicationDirPath() + "/quickexampleconfig.ini";
    m_pTranslator = new QTranslator;
    m_pTranslatorDi = new QTranslator;
}

CatConfig::~CatConfig()
{

}

void CatConfig::InitLanguage(int l)
{
    bool arg = true;
    QString qexeFullPath = QCoreApplication::applicationDirPath() + "/translations";
    switch (l) {
        case 1: {
            arg = m_pTranslator->load(QString(":/Lang/language_zh_CN.qm"));
            qexeFullPath = qexeFullPath + "/qt_zh_CN.qm";
            if(FileExiste(qexeFullPath))
            {
                m_pTranslatorDi->load(qexeFullPath);
                QCoreApplication::installTranslator(m_pTranslatorDi);
            }
            QCoreApplication::installTranslator(m_pTranslator);
            break;
        }
        default: {
            arg = m_pTranslator->load(QString(":/Lang/language_en.qm"));
            qexeFullPath = qexeFullPath + "/qt_en.qm";
            if(FileExiste(qexeFullPath))
            {
                m_pTranslatorDi->load(qexeFullPath);
                QCoreApplication::installTranslator(m_pTranslatorDi);
            }
            QCoreApplication::installTranslator(m_pTranslator);
            break;
        }
    }
    emit _instance->updateLanguage();
}

bool CatConfig::FileExiste(const QString &filePath, bool newfile)
{
    QFileInfo fileinfo(filePath);
    if(!fileinfo.exists())
    {
        bool ret = false;
        if(newfile)
        {
            QDir dir;
            ret = dir.mkpath(fileinfo.filePath());
        }
        return ret;
    }
    return true;
}
