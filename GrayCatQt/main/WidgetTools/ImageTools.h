#ifndef IMAGETOOLS_H
#define IMAGETOOLS_H

#include <QWidget>

class QPushButton;

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
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

private:
    Ui::ImageTools *ui;
    QHash<QString, QPushButton*> m_pToolButtons;
};

#endif // IMAGETOOLS_H
