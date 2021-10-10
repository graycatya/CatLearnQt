#ifndef MODELTOOLS_H
#define MODELTOOLS_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

namespace CatModel {

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
static bool writeJsonFile(const QString &filePath, const QJsonArray &jsonArray, bool compact = true)
{
    return writeJsonFile(filePath, QJsonDocument(jsonArray), compact);
}
static bool writeJsonFile(const QString &filePath, const QJsonObject &jsonObj, bool compact = true)
{
    return writeJsonFile(filePath, QJsonDocument(jsonObj), compact);
}

}

#endif // MODELTOOLS_H
