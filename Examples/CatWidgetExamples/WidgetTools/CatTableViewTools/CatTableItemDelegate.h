#ifndef CATTABLEITEMDELEGATE_H
#define CATTABLEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class CatTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    enum HEADCOLUM {
        HEAD_CHECK_COLUMN = 0,
        HEAD_ID_COLUMN,
        HEAD_STATE_COLUMN,
        HEAD_TIME_COLUMN,
    };
    enum DATAROW {
        DATA_CHECK_COLUMN = 0,
        DATA_ID_COLUMN,
        DATA_STATE_COLUMN,
        DATA_TIME_COLUMN,
    };
    explicit CatTableItemDelegate(QObject *parent = nullptr);
    ~CatTableItemDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    void paintHead(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintHeadData(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintHeadCheck(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, QString text, int flags) const;
    void paintSortButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, int flags) const;
    void paintDataCheck(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintTableData(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintTableState(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QStyleOptionViewItem paintHover(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;


    // editor api
    void editorHeadCheck(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void editorHeadSortButton(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
    void editorTableDataCheck(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

    int getHeadSortState(const QModelIndex &index) const;
    void setHeadSortState(QAbstractItemModel *model, const QModelIndex &index, int state) const;
    QString getHeadSortData(const QModelIndex &index) const;
    void setHeadSortData(QAbstractItemModel *model, const QModelIndex &index, QString data) const;

    int getSelectCheckTableData(QAbstractItemModel *model);

public slots:
    void onHoverIndexChanged(const QModelIndex &index);
    void onShiftOutChanged();
    void onCurrentMouseed(QPoint pot);

protected:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    int m_hoverrow;
    int m_hovercolumn;
    QSize m_checkSize;
    QSize m_sortSize;
    QPoint m_currentMouse;

};

#endif // CATTABLEITEMDELEGATE_H
