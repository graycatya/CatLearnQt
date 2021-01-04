#ifndef CATFONT_H
#define CATFONT_H

#include <QObject>

class CatFont : public QObject
{
    Q_OBJECT
public:
    explicit CatFont(QObject *parent = nullptr);
    ~CatFont();

    static QStringList SystemFontFamilys( void );

private:

};

#endif // CATFONT_H
