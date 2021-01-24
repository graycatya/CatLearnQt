#ifndef CATPAGINGNAVIGATION_H
#define CATPAGINGNAVIGATION_H

#include <QWidget>

class QPushButton;

class CatPagingNavigation : public QWidget
{
    Q_OBJECT
public:
    explicit CatPagingNavigation(QWidget *parent = nullptr);
    ~CatPagingNavigation();

private:
    QPushButton *m_pPreviousPage;
    QPushButton *m_pNextPage;

};

#endif // CATPAGINGNAVIGATION_H
