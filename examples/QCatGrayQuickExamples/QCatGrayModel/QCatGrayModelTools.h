#ifndef QCATGRAYMODELTOOLS_H
#define QCATGRAYMODELTOOLS_H


#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include <QDir>
#include <QFileInfo>
#include <QObject>
//#include <QQmlEngine>
#include <QUrl>

#include <type_traits>

namespace QCatGrayModel {

/*************************************************
// 函数名称
Function: readFile
// 函数功能、性能等的描述
Description: 打开文件读取文件所有内容
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 文件
// 对输出参数的说明。
Output:
    content - 输出内容
// 函数返回值的说明
Return:
    读取成功返回真，失败返回假
// 其它说明
Others:
*************************************************/
static bool readFile(const QString &filePath, QByteArray &content)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly))
    {
        qWarning() << "Open file " << filePath << "failed: " << file.errorString();
        return false;
    }
    content = file.readAll();
    file.close();
    return true;
}

/*************************************************
// 函数名称
Function: readJson
// 函数功能、性能等的描述
Description: 解析json数据
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    data - 传入需要解析的数据
// 对输出参数的说明。
Output:
    doc - 传出解析后的json数据
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool readJson(const QByteArray &data, QJsonDocument &doc)
{
    QJsonParseError err;
    doc = QJsonDocument::fromJson(data, &err);
    if(doc.isNull())
    {
        qWarning() << "Parse json failed: " << err.errorString();
        return false;
    }
    return true;
}

/*************************************************
// 函数名称
Function: readJson
// 函数功能、性能等的描述
Description: 解析json数组数据
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    data - 传入需要解析的数据
// 对输出参数的说明。
Output:
    array - 传出解析后的json数组数据
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool readJson(const QByteArray &data, QJsonArray &array)
{
    QJsonDocument doc;
    bool ok = readJson(data, doc);
    if (ok)
    {
        array = doc.array();
    }
    return ok;
}

/*************************************************
// 函数名称
Function: readJson
// 函数功能、性能等的描述
Description: 解析json对象数据
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    data - 传入需要解析的数据
// 对输出参数的说明。
Output:
    object - 传出解析后的json对象数据
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool readJson(const QByteArray &data, QJsonObject &object)
{
    QJsonDocument doc;
    bool ok = readJson(data, doc);
    if (ok)
    {
        object = doc.object();
    }
    return ok;
}

/*************************************************
// 函数名称
Function: readJsonFile
// 函数功能、性能等的描述
Description: 解析json对象数据
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    jsonDoc - 传出解析后的json文档数据
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool readJsonFile(const QString &filePath, QJsonDocument &jsonDoc)
{
    QByteArray data;
    if (!readFile(filePath, data))
    {
        return false;
    }
    return readJson(data, jsonDoc);
}

/*************************************************
// 函数名称
Function: readJsonFile
// 函数功能、性能等的描述
Description: 解析json对象数据
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    jsonObj - 传出解析后的json对象数据
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool readJsonFile(const QString &filePath, QJsonObject &jsonObj)
{
    QByteArray data;
    if (!readFile(filePath, data))
    {
        return false;
    }
    return readJson(data, jsonObj);
}

/*************************************************
// 函数名称
Function: readJsonFile
// 函数功能、性能等的描述
Description: 解析json对象数据
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    jsonArray - 传出解析后的json数组数据
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool readJsonFile(const QString &filePath, QJsonArray &jsonArray)
{
    QByteArray data;
    if (!readFile(filePath, data))
    {
        return false;
    }
    return readJson(data, jsonArray);
}

/*************************************************
// 函数名称
Function: writeFile
// 函数功能、性能等的描述
Description: 读取文件
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    content - 传出文件内容
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool writeFile(const QString &filePath, const QByteArray &content)
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly))
    {
        qWarning() << "Open file " << filePath << "failed:" << file.errorString();
        return false;
    }
    file.write(content);
    file.close();
    return true;
}

/*************************************************
// 函数名称
Function: writeJsonFile
// 函数功能、性能等的描述
Description: 读取文件
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    doc - 传出文件内容
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool writeJsonFile(const QString &filePath, const QJsonDocument &doc, bool compact = true)
{
    return writeFile(filePath, doc.toJson(compact ? QJsonDocument::Compact : QJsonDocument::Indented));
}

/*************************************************
// 函数名称
Function: writeJsonFile
// 函数功能、性能等的描述
Description: 读取文件
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    jsonArray - 传出文件解析后的json数组
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool writeJsonFile(const QString &filePath, const QJsonArray &jsonArray, bool compact = true)
{
    return writeJsonFile(filePath, QJsonDocument(jsonArray), compact);
}

/*************************************************
// 函数名称
Function: writeJsonFile
// 函数功能、性能等的描述
Description: 读取文件
// 被本函数调用的函数清单
Calls: ---
// 被访问的表
Table Accessed: ---
// 被修改的表
Table Updated: ---
// 输入参数说明，包括每个参数的作
Input:
    filePath - 传入文件路径
// 对输出参数的说明。
Output:
    QJsonObject - 传出文件解析后的json数组
// 函数返回值的说明
Return:
    解析成功返回true,失败返回false
// 其它说明
Others:
*************************************************/
static bool writeJsonFile(const QString &filePath, const QJsonObject &jsonObj, bool compact = true)
{
    return writeJsonFile(filePath, QJsonDocument(jsonObj), compact);
}


class ModelTool : public QObject {
    Q_OBJECT
public:
    // 返回格式化为本地文件路径的URL的路径
    Q_INVOKABLE static inline QString toLocalFile(const QString& urlStr)
    {
        return QUrl(urlStr).toLocalFile();
    }
    Q_INVOKABLE static inline QString toLocalFile(const QUrl& url)
    {
        return url.toLocalFile();
    }

    // 返回localFile的QUrl表示，解释为本地文件
    Q_INVOKABLE static inline QUrl fromLocalFile(const QString& file)
    {
        return QUrl::fromLocalFile(file);
    }
    // 如果文件存在则返回true; 否则返回false
    Q_INVOKABLE static inline bool isExist(const QString& file)
    {
        return QFileInfo::exists(file);
    }
    // 返回文件名，包括路径(可以是绝对路径也可以是相对路径)
    Q_INVOKABLE static inline QString filePath(const QString& file)
    {
        return QFileInfo(file).filePath();
    }
    // 返回包含文件名的绝对路径
    Q_INVOKABLE static inline QString absoluteFilePath(const QString& file)
    {
        return QFileInfo(file).absoluteFilePath();
    }
    // 返回包含文件名的规范路径，即没有符号链接或冗余的"."或".."元素的绝对路径
    Q_INVOKABLE static inline QString canonicalFilePath(const QString& file)
    {
        return QFileInfo(file).canonicalFilePath();
    }

    // 返回文件的名称，不包括路径
    Q_INVOKABLE static inline QString fileName(const QString& file)
    {
        return QFileInfo(file).fileName();
    }

    // 返回不含路径的文件的基本名称
    Q_INVOKABLE static inline QString baseName(const QString& file)
    {
        return QFileInfo(file).baseName();
    }

    // 返回不含路径的文件的完整基名
    Q_INVOKABLE static inline QString completeBaseName(const QString& file)
    {
        return QFileInfo(file).completeBaseName();
    }

    // 返回文件的后缀(扩展名)
    Q_INVOKABLE static inline QString suffix(const QString& file)
    {
        return QFileInfo(file).suffix();
    }

    // 返回包的名称
    Q_INVOKABLE static inline QString bundleName(const QString& file)
    {
        return QFileInfo(file).bundleName();
    }

    // 返回文件的完整后缀(扩展名)
    Q_INVOKABLE static inline QString completeSuffix(const QString& file)
    {
        return QFileInfo(file).completeSuffix();
    }

    // 返回文件的路径。 这并不包括文件名
    Q_INVOKABLE static inline QString path(const QString& file)
    {
        return QFileInfo(file).path();
    }

    // 返回文件的绝对路径。 这并不包括文件名
    Q_INVOKABLE static inline QString absolutePath(const QString& file)
    {
        return QFileInfo(file).absolutePath();
    }

    // 创建的子目录
    Q_INVOKABLE static inline bool mkdir(const QString& file)
    {
        return QDir().mkdir(file);
    }

    // 创建目录路径
    Q_INVOKABLE static inline bool mkpath(const QString& file)
    {
        return QDir().mkpath(file);
    }

    // 返回格式化为本地文件路径的URL的路径
    Q_INVOKABLE static QList<QString> toLocalFileList(const QList<QUrl>& urls)
    {
        QList<QString> list;
        for(const auto& url : urls)
        {
            list.append(url.toLocalFile());
        }
        return list;
    }

    // 判断路径是否存在，不存在则创建
    Q_INVOKABLE static bool checkOrCreatePath(const QString& path)
    {
        QDir dir(path);
        if(!dir.exists())
        {
            return dir.mkpath(path);
        } else {
            return true;
        }
    }

    // 读取文件内容
    Q_INVOKABLE static QString readFile(const QString& path)
    {
        QByteArray data;
        if(QCatGrayModel::readFile(path,data)) {
            return { data };
        }
        return {};
    }

    // 写文件内容
    Q_INVOKABLE static void writeFile(const QString& path, const QString& content)
    {
        writeFile(path, content.toUtf8());
    }

};

}

#endif


