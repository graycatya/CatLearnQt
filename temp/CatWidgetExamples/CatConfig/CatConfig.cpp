#include "CatConfig.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include <QTimer>
#include <QApplication>
#include <QTranslator>
#include <CatLog>
#include <QColor>


CatConfig* CatConfig::_instance = nullptr;
QMutex* CatConfig::m_pMutex = new QMutex;
QString CatConfig::m_sConfigPath = "";
QApplication* CatConfig::m_pApp = nullptr;
QTranslator* CatConfig::m_pTranslator = nullptr;

void CatConfig::SetTranslator(QApplication* app)
{
    if(m_pTranslator == nullptr && m_pApp == nullptr)
    {
        m_pApp = app;
        m_pTranslator = new QTranslator;
    }
}

void CatConfig::InitLang(QLocale::Language lang)
{
    bool arg = true;
    switch (lang) {
        case QLocale::Chinese: {
            arg = m_pTranslator->load(QString(":/lang/language_zh_CN.qm"));
            CatSettingBase::SetValue(m_sConfigPath, "Language", "chinese(china)", "Defaule");
            break;
        }
        default: {
            arg = m_pTranslator->load(QString(":/lang/language_en.qm"));
            CatSettingBase::SetValue(m_sConfigPath, "Language", "english", "Defaule");
            break;
        }
    }

    m_pApp->installTranslator(m_pTranslator);

    if(!arg)
    {
        QString log = QString("language init error!");
        CATLOG::CatLog::__Write_Log(ERROR_LOG_T(log.toStdString()));
    }
}

void CatConfig::SetValue(QString key, QVariant var, QString node)
{
    CatSettingBase::SetValue(m_sConfigPath, key, var, node);
}

void CatConfig::RemoveNodeValue(QString node, QString key)
{
    CatSettingBase::RemoveNodeValue(m_sConfigPath, node, key);
}

void CatConfig::RemoveNode(QString node)
{
    CatSettingBase::RemoveNode(m_sConfigPath, node);
}

void CatConfig::SetGroup(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetGroup(m_sConfigPath, node, keys, vars);
}

void CatConfig::SetArray(QString node, QStringList keys, QVariantList vars)
{
    CatSettingBase::SetArray(m_sConfigPath, node, keys, vars);
}

QStringList CatConfig::GetKeys(QString node)
{
    return CatSettingBase::GetKeys(m_sConfigPath, node);
}

QVariant CatConfig::GetValue(QString key, QString node)
{
    return CatSettingBase::GetValue(m_sConfigPath, key, node);
}

QMultiMap<QString, QVariant> CatConfig::GetArray(QString node, QStringList keys)
{
    return CatSettingBase::GetArray(m_sConfigPath, node, keys);
}

void CatConfig::SetWindowStyle(QVariant var)
{
    CatSettingBase::SetValue(m_sConfigPath, "style", var, "Defaule");
    emit UpdateStyleSheets();
}

void CatConfig::SetTranslator(QVariant var)
{
    CatSettingBase::SetValue(m_sConfigPath, "Language", var, "Defaule");
    m_pApp->removeTranslator(m_pTranslator);
    UpdateTranslator(var.toString());
}

bool CatConfig::ConfigExist()
{
    return CatSettingBase::ConfigExist(m_sConfigPath);
}

CatConfig::CatConfig()
{
    m_sConfigPath = QCoreApplication::applicationDirPath() + "/config.ini";
    //InitConfig();
}

CatConfig::~CatConfig()
{

}

void CatConfig::UpdateTranslator(QString translator)
{
    bool arg = true;
    if(translator == "chinese(china)") {
        arg = m_pTranslator->load(QString(":/lang/language_zh_CN.qm"));
    } else {
        arg = m_pTranslator->load(QString(":/lang/language_en.qm"));
    }

    m_pApp->installTranslator(m_pTranslator);

    if(!arg)
    {
        QString log = QString("language init error!");
        CATLOG::CatLog::__Write_Log(ERROR_LOG_T(log.toStdString()));
    }
}

void CatConfig::InitConfig()
{
    // [0] 判断配置文件是否存在

    if(!ConfigExist())
    {
        /*QFileInfo info(m_sConfigPath);
        info.exists();*/
        QSettings setting(m_sConfigPath, QSettings::IniFormat);
        setting.setValue("AppName", APP_NAME);
        setting.setValue("AppVersion", APP_VERSION);
        setting.setValue("HomePage", "www.graycatya.com");

        QString savefilepath = QCoreApplication::applicationDirPath() + "/" + "SaveFile";
        setting.setValue("SaveFilePath", savefilepath);

        QStringList style = {"style", "style"};
        QVariantList styleNames = { "CatGray", "CatWhite" };
        CatSettingBase::SetArray(m_sConfigPath, "StyleSheets", style, styleNames);

        QStringList defaultKeys = { "style" };
        QVariantList defaultVars = { "CatGray" };
        CatSettingBase::SetGroup(m_sConfigPath, "Defaule", defaultKeys, defaultVars);
        if(m_pApp != nullptr)
        {
            QStringList langtKeys = { "lang", "lang" };
            QVariantList langVars = { "english", "chinese(china)" };
            CatSettingBase::SetArray(m_sConfigPath, "Langs", langtKeys, langVars);

            QLocale locale;
            InitLang(locale.language());
        }

    } else {
        QString lang = CatConfig::GetValue("Language", "Defaule").toString();
        UpdateTranslator(lang);
    }
}

QStringList CatConfig::GetTableHeader()
{
    QStringList list;
    list << "";
    list << tr("ID");
    list << tr("State");
    list << tr("Time");
    return list;
}

QColor CatConfig::GetTableViewHeadText_Color()
{
    QString style = GetValue("style", "Defaule").toString();
    QColor color;
    if(style == "CatGray")
    {
        color = "#FFFFFF";
    } else {
        color = "#424242";
    }
    return color;
}

QColor CatConfig::GetTableViewItemStateDataError_Color()
{
    QString style = GetValue("style", "Defaule").toString();
    QColor color;
    if(style == "CatGray")
    {
        color = "#FF0000";
    } else {
        color = "#FF0000";
    }
    return color;
}

QColor CatConfig::GetTableViewItemStateDataOk_Color()
{
    QString style = GetValue("style", "Defaule").toString();
    QColor color;
    if(style == "CatGray")
    {
        color = "#00FF0A";
    } else {
        color = "#00FF0A";
    }
    return color;
}

QColor CatConfig::GetTableViewItemText_Color()
{
    QString style = GetValue("style", "Defaule").toString();
    QColor color;
    if(style == "CatGray")
    {
        color = "#FFFFFF";
    } else {
        color = "#424242";
    }
    return color;
}

