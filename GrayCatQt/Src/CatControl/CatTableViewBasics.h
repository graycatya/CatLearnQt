#ifndef CATTABLEVIEWBASICS_H
#define CATTABLEVIEWBASICS_H

#include <QTableView>

class CatTableViewBasics : public QTableView
{
    Q_OBJECT
public:
    explicit CatTableViewBasics(QWidget *parent = nullptr);
    ~CatTableViewBasics();

private:
    QTableView *m_pHeadTableView;
    QTableView *m_pLeftTableView;
    QTableView *m_pRightTableView;
    QTableView *m_pBottomTableView;

};

#endif // CATTABLEVIEWBASICS_H
