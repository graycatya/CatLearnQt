#ifndef CATPAGINGNAVIGATION_H
#define CATPAGINGNAVIGATION_H

#include <QWidget>

class QPushButton;
class QButtonGroup;
class QHBoxLayout;

class CatPagingNavigation : public QWidget
{
    Q_OBJECT
public:
    explicit CatPagingNavigation(QWidget *parent = nullptr);
    ~CatPagingNavigation();

private:
    void InitUi();
    void InitProperty();
    void InitConnect();

    void UpdateCurrentPage();

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

    qulonglong m_nDataSum;      // 数据总数
    qulonglong m_nTotalPages;   // 总页数
    qulonglong m_nCurrentPage;  // 当前页



};

#endif // CATPAGINGNAVIGATION_H
