#ifndef CATFILE_H
#define CATFILE_H

#include <QObject>

class CatFile
{

public:
    CatFile();
    ~CatFile();

    static bool ReadFile(const QString &filePath, QByteArray &content);

    static bool WriteFile(const QString &filePath, QByteArray &content);

    static bool Existe(const QString &filePath, bool newfile = false);


};


#endif // CATFILE_H
