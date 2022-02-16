#ifndef CATTABLEWIDGETBASICS_H
#define CATTABLEWIDGETBASICS_H

#include <QTableWidget>

class CatTableWidgetBasics : public QTableWidget
{
    Q_OBJECT
public:
    explicit CatTableWidgetBasics(QWidget *parent = nullptr);
    ~CatTableWidgetBasics();

    // 冻结头
    void FrostTableHead(int row);
    void CancelTableHead();
    // 冻结左侧
    void FrostTableLeft(int column);
    void CancelTableLeft();

protected:
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
     * @brief scrollTo          TableWidget移动事件
     * @param index
     * @param hint
     */
    void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

private:
    /**
     * @brief updateFrozenTableGeometry 更新被冻结的tableWidget位置
     */
    void updateFrozenTableGeometry();

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

private:
    QTableWidget *m_pHeadTableWidget = nullptr;
    QTableWidget *m_pLeftTableWidget = nullptr;
    int m_iFrostRow = 0;
    int m_iFrostColumn = 0;

};

#endif // CATTABLEWIDGETBASICS_H
