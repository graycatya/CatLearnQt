#ifndef IMAGETOOLS_H
#define IMAGETOOLS_H

#include <QWidget>

namespace Ui {
class ImageTools;
}

class ImageTools : public QWidget
{
    Q_OBJECT

public:
    explicit ImageTools(QWidget *parent = nullptr);
    ~ImageTools();

private:
    Ui::ImageTools *ui;
};

#endif // IMAGETOOLS_H
