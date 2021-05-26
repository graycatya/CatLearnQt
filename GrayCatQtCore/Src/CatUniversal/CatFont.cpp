#include "CatFont.h"
#include <QFontDatabase>

CatFont::CatFont(QObject *parent)
    : QObject(parent)
{

}

CatFont::~CatFont()
{

}

QStringList CatFont::SystemFontFamilys()
{
    QFontDatabase database;
    QStringList list;
    foreach (const QString &family, database.families())
    {
         list << family;
    }
    return list;
}
