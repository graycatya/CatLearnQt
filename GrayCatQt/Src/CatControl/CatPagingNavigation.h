#ifndef CATPAGINGNAVIGATION_H
#define CATPAGINGNAVIGATION_H

#include <QWidget>

class QPushButton;
class QButtonGroup;
class QHBoxLayout;
class QAbstractButton;

class CatPagingNavigation : public QWidget
{
    Q_OBJECT
public:
    explicit CatPagingNavigation(QWidget *parent = nullptr);
    ~CatPagingNavigation();

    void InitPaginNavigation(qulonglong datasum, qulonglong itemsperpages = 10);
    void SetDataSum(qulonglong datasum);
    void SetItemsPerPages(qulonglong itemsperpages);

    qulonglong GetDataSum( void ) const { return m_nDataSum; }
    qulonglong GetItemsPerPages( void ) const { return m_nItemsPerPages; }
    qulonglong GetTotalPages( void ) const { return m_nTotalPages; }
    qulonglong GetCurrentPage( void ) const { return m_nCurrentPage; }

    QHBoxLayout *Layout( void ) const { return m_pRootLayout; }

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateStyle();

    void UpdatePagingNavigation();

    void UpdatePageButtonState();

    void SetPageButtonState(QString state, int id);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void ButtonGrouped(QAbstractButton *button);

public slots:
    void SetCurrentPage(qulonglong currentpage);

signals:
    void CurrentPageed(qulonglong currentpage);
    void TotalPageeed(qulonglong totalpage);

private:
    // 切页按钮
    QPushButton *m_pPreviousPage;
    QPushButton *m_pPreviousSeveralPage;
    QPushButton *m_pNextPage;
    QPushButton *m_pNextPageSeveralPage;
    QButtonGroup *m_pButtonGroup;
    // 页数显示按钮
    QList<QPushButton*> m_pPageButtons;

    // 布局器
    QHBoxLayout *m_pRootLayout;

    qulonglong m_nDataSum;          // 数据总数
    qulonglong m_nItemsPerPages;    // 分页的每页数据行数
    qulonglong m_nTotalPages;       // 总页数
    qulonglong m_nCurrentPage;      // 当前页



};

#endif // CATPAGINGNAVIGATION_H
