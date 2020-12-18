#ifndef CATQCUSTOMPLOTTOOLS_H
#define CATQCUSTOMPLOTTOOLS_H

#include <QWidget>

namespace Ui {
class CatQcustomplotTools;
}

class CatQcustomplotTools : public QWidget
{
    Q_OBJECT

public:
    explicit CatQcustomplotTools(QWidget *parent = nullptr);
    ~CatQcustomplotTools();

private:
    Ui::CatQcustomplotTools *ui;
};

#endif // CATQCUSTOMPLOTTOOLS_H
