#ifndef SLIDERTOOLS_H
#define SLIDERTOOLS_H

#include <QWidget>

namespace Ui {
class SliderTools;
}

class SliderTools : public QWidget
{
    Q_OBJECT

public:
    explicit SliderTools(QWidget *parent = nullptr);
    ~SliderTools();

private:
    Ui::SliderTools *ui;
};

#endif // SLIDERTOOLS_H
