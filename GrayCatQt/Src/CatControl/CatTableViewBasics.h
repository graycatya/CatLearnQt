#ifndef CATTABLEVIEWBASICS_H
#define CATTABLEVIEWBASICS_H

#include <QTableView>
#include <QHeaderView>

class CatTableViewBasics : public QTableView
{
    Q_OBJECT
public:
    explicit CatTableViewBasics(QWidget *parent = nullptr);
    ~CatTableViewBasics();

    void setModel(QAbstractItemModel *model) override;

    /**
     * @brief FrostTableHead 冻结头
     * @param row
     */
    void FrostTableHead(int row);

    /**
     * @brief CancelTableHead 取消头冻结
     */
    void CancelTableHead();

    /**
     * @brief FrostTableLeft 冻结左侧
     * @param column
     */
    void FrostTableLeft(int column);

    /**
     * @brief CancelTableLeft 取消左冻结
     */
    void CancelTableLeft();

    QTableView* GetTopTableView();
    QTableView* GetIntersectionView();
    QTableView* GetLeftTableView();

    void SetHorizontalHeaderSectionResizeMode(QHeaderView::ResizeMode mode);
    void SetVerticalHeaderSectionResizeMode(QHeaderView::ResizeMode mode);

    void ShowHorizontalHeader();
    void HideHorizontalHeader();
    void ShowVerticalHeader();
    void HideVerticalHeader();

    void ConnectSelectColumn();
    void DisconnectSelectColumn();
    void ConnectSelectRow();
    void DisconnectSelectRow();

private:
    /**
     * @brief updateFrozenTableGeometry 更新被冻结的tableWidget位置
     */
    void updateFrozenTableGeometry();

    void InitTopTable();

    void InitLeftTable();

    void InitIntersectionTable();

    void CancelTableIntersection();

protected:
    /**
     * @brief initTable
     */
    virtual void initTable();

    /**
     * @brief resizeEvent       重载虚函数 resize事件，同时更新冻结行列位置的位置
     * @param event
     */
    virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    /**
     * @brief moveCursor        重载虚函数 鼠标移动事件
     * @param cursorAction
     * @param modifiers
     * @return
     */
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;

    /**
     * @brief scrollTo          QTableView移动事件
     * @param index
     * @param hint
     */
    void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

    virtual void hideHeader();

private slots:
    /**
    * @brief updateSectionWidth 更新部分宽度
    * @param logicalIndex
    * @param oldSize
    * @param newSize
    */
    void updateSectionWidth(int logicalIndex, int oldSize, int newSize);

    /**
    * @brief updateSectionHeight 更新部分高度
    * @param logicalIndex
    * @param oldSize
    * @param newSize
    */
    void updateSectionHeight(int logicalIndex, int oldSize, int newSize);

    void selectTableColumn(int column);
    void selectTableRow(int row);

protected:
    QTableView *m_pTopTableWidget = nullptr;
    QTableView *m_pIntersectionWidget = nullptr;
    QTableView *m_pLeftTableWidget = nullptr;

private:
    int m_iFrostRow = 0;
    int m_iFrostColumn = 0;

    QMetaObject::Connection m_pThisTableSelectColumn;
    QMetaObject::Connection m_pTopTableSelectColumn;
    QMetaObject::Connection m_pLeftTableSelectColumn;
    QMetaObject::Connection m_pIntersectionSelectColumn;

    QMetaObject::Connection m_pThisTableSelectRow;
    QMetaObject::Connection m_pTopTableSelectRow;
    QMetaObject::Connection m_pLeftTableSelectRow;
    QMetaObject::Connection m_pIntersectionSelectRow;

};

#endif // CATTABLEVIEWBASICS_H
