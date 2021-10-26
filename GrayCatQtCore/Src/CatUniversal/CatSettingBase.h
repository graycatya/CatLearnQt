#ifndef CATSETTINGBASE_H
#define CATSETTINGBASE_H

#include <QObject>
#include <QVector>

class CatSettingBase : public QObject
{
    Q_OBJECT
public:
    explicit CatSettingBase(QObject *parent = nullptr);
    ~CatSettingBase();

protected:
    static void SetValue(QString file, QString key, QVariant var, QString node = "");
    static void RemoveNodeValue(QString file, QString node, QString key);
    static void RemoveNode(QString file, QString node);

    static void SetGroup(QString file, QString node, QStringList keys, QVariantList vars);
    static void SetArray(QString file, QString node, QStringList keys, QVariantList vars);

    static QStringList GetKeys(QString file, QString node = "");
    static QVariant GetValue(QString file, QString key, QString node = "");
    static QMultiMap<QString, QVariant> GetArray(QString file, QString node, QStringList keys);
    static QMultiMap<QString, QVariant> GetArray(QString file, QString node);
    static QVector<QVariant> GetArrays(QString file, QString node);
    static bool ConfigExist(QString file);

};

#endif // CATSETTINGBASE_H
