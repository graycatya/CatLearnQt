#ifndef CATWIDGET_H
#define CATWIDGET_H

#include <QWidget>

namespace Ui {
class CatWidget;
}

class CatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CatWidget(QWidget *parent = nullptr);
    ~CatWidget();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

private:
    Ui::CatWidget *ui;
};

#endif // CATWIDGET_H
