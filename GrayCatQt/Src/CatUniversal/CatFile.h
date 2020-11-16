#ifndef CATFILE_H
#define CATFILE_H

#include <QFile>
#include <QString>
#include <QVariant>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QFileInfo>

namespace CatFile {

    static bool ReadFile(const QString &filePath, QByteArray &content)
    {
        QFile file(filePath);
        if(!file.open(QFile::ReadOnly))
        {
            return false;
        }
        content = file.readAll();
        file.close();
        return true;
    }

    static bool WriteFile(const QString &filePath, QByteArray &content)
    {
        QFile file(filePath);
        if(!file.open(QFile::WriteOnly))
        {
            return false;
        }
        file.write(content);
        file.close();
        return true;
    }

    static bool Existe(const QString &filePath, bool newfile = false)
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

}


#endif // CATFILE_H
