#ifndef CATQUICKWIDGET_H
#define CATQUICKWIDGET_H

#include <QWidget>

namespace Ui {
class CatQuickWidget;
}

class CatQuickWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CatQuickWidget(QWidget *parent = nullptr);
    ~CatQuickWidget();

private:
    Ui::CatQuickWidget *ui;
};

#endif // CATQUICKWIDGET_H
