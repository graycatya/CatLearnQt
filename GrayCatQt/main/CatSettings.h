#ifndef CATSETTINGS_H
#define CATSETTINGS_H

#include <QWidget>

namespace Ui {
class CatSettings;
}

class CatSettings : public QWidget
{
    Q_OBJECT

public:
    explicit CatSettings(QWidget *parent = nullptr);
    ~CatSettings();

private:
    Ui::CatSettings *ui;
};

#endif // CATSETTINGS_H
