#ifndef INPUTTOOLS_H
#define INPUTTOOLS_H

#include <QWidget>

namespace Ui {
class InputTools;
}

class InputTools : public QWidget
{
    Q_OBJECT

public:
    explicit InputTools(QWidget *parent = nullptr);
    ~InputTools();

private:
    Ui::InputTools *ui;
};

#endif // INPUTTOOLS_H
