#ifndef PAGINGNAVIGATIONTOOLS_H
#define PAGINGNAVIGATIONTOOLS_H

#include <QWidget>

namespace Ui {
class PagingNavigationTools;
}

class PagingNavigationTools : public QWidget
{
    Q_OBJECT

public:
    explicit PagingNavigationTools(QWidget *parent = nullptr);
    ~PagingNavigationTools();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

private:
    Ui::PagingNavigationTools *ui;
};

#endif // PAGINGNAVIGATIONTOOLS_H
