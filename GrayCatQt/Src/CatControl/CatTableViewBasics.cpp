#include "CatTableViewBasics.h"
#include <QHeaderView>
#include <QAbstractSlider>
#include <QScrollBar>
#include <QDebug>

CatTableViewBasics::CatTableViewBasics(QWidget *parent)
    : QTableView(parent)
{

    hideHeader();

    initTable();

    // 将两个表视图的标题和滚动条连接在一起
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionHeight);

}

CatTableViewBasics::~CatTableViewBasics()
{
    DisconnectSelectColumn();
    DisconnectSelectRow();
}

void CatTableViewBasics::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

void CatTableViewBasics::FrostTableHead(int row)
{
    if(m_pTopTableWidget == nullptr)
    {
        m_iFrostRow = row;
        InitTopTable();
        if(m_pLeftTableWidget)
        {
            InitIntersectionTable();
            m_pIntersectionWidget->show();
        }
        updateFrozenTableGeometry(); //更新位置
        m_pTopTableWidget->show();
    }
}

void CatTableViewBasics::CancelTableHead()
{
    if(m_pTopTableWidget != nullptr)
    {
        delete m_pTopTableWidget;
        m_pTopTableWidget = nullptr;
    }
    CancelTableIntersection();
    updateFrozenTableGeometry();
}

void CatTableViewBasics::FrostTableLeft(int column)
{
    if(m_pLeftTableWidget == nullptr)
    {
        m_iFrostColumn = column;
        InitLeftTable();
        if(m_pTopTableWidget)
        {
            InitIntersectionTable();
            m_pIntersectionWidget->show();
        }
        updateFrozenTableGeometry(); //更新位置
        m_pLeftTableWidget->show();
    }
}

void CatTableViewBasics::CancelTableLeft()
{
    if(m_pLeftTableWidget != nullptr)
    {
        delete m_pLeftTableWidget;
        m_pLeftTableWidget = nullptr;
    }
    CancelTableIntersection();
    updateFrozenTableGeometry();
}

QTableView *CatTableViewBasics::GetTopTableView()
{
    return m_pTopTableWidget;
}

QTableView *CatTableViewBasics::GetIntersectionView()
{
    return m_pIntersectionWidget;
}

QTableView *CatTableViewBasics::GetLeftTableView()
{
    return m_pLeftTableWidget;
}

void CatTableViewBasics::SetHorizontalHeaderSectionResizeMode(QHeaderView::ResizeMode mode)
{
    horizontalHeader()->setSectionResizeMode(mode);
    if(m_pTopTableWidget) m_pTopTableWidget->horizontalHeader()->setSectionResizeMode(mode);
    if(m_pLeftTableWidget) m_pLeftTableWidget->horizontalHeader()->setSectionResizeMode(mode);
    if(m_pIntersectionWidget) m_pIntersectionWidget->horizontalHeader()->setSectionResizeMode(mode);
    updateEditorGeometries();
}

void CatTableViewBasics::SetVerticalHeaderSectionResizeMode(QHeaderView::ResizeMode mode)
{
    verticalHeader()->setSectionResizeMode(mode);
    if(m_pTopTableWidget) m_pTopTableWidget->verticalHeader()->setSectionResizeMode(mode);
    if(m_pLeftTableWidget) m_pLeftTableWidget->verticalHeader()->setSectionResizeMode(mode);
    if(m_pIntersectionWidget) m_pIntersectionWidget->verticalHeader()->setSectionResizeMode(mode);
    updateEditorGeometries();
}

void CatTableViewBasics::ShowHorizontalHeader()
{
    horizontalHeader()->show();
    if(m_pTopTableWidget) m_pTopTableWidget->horizontalHeader()->show();
    if(m_pLeftTableWidget) m_pLeftTableWidget->horizontalHeader()->show();
    if(m_pIntersectionWidget) m_pIntersectionWidget->horizontalHeader()->show();
    updateEditorGeometries();
}

void CatTableViewBasics::HideHorizontalHeader()
{
    horizontalHeader()->hide();
    if(m_pTopTableWidget) m_pTopTableWidget->horizontalHeader()->hide();
    if(m_pLeftTableWidget) m_pLeftTableWidget->horizontalHeader()->hide();
    if(m_pIntersectionWidget) m_pIntersectionWidget->horizontalHeader()->hide();
    updateEditorGeometries();
}

void CatTableViewBasics::ShowVerticalHeader()
{
    verticalHeader()->show();
    if(m_pTopTableWidget) m_pTopTableWidget->verticalHeader()->show();
    if(m_pLeftTableWidget) m_pLeftTableWidget->verticalHeader()->show();
    if(m_pIntersectionWidget) m_pIntersectionWidget->verticalHeader()->show();
    updateEditorGeometries();
}

void CatTableViewBasics::HideVerticalHeader()
{
    verticalHeader()->hide();
    if(m_pTopTableWidget) m_pTopTableWidget->verticalHeader()->hide();
    if(m_pLeftTableWidget) m_pLeftTableWidget->verticalHeader()->hide();
    if(m_pIntersectionWidget) m_pIntersectionWidget->verticalHeader()->hide();
    updateEditorGeometries();
}

void CatTableViewBasics::ConnectSelectColumn()
{
    if(!m_pThisTableSelectColumn)
    {
        m_pThisTableSelectColumn = connect(this, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
    if(m_pTopTableWidget && !m_pTopTableSelectColumn)
    {
        m_pTopTableSelectColumn = connect(m_pTopTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
    if(m_pLeftTableWidget && !m_pLeftTableSelectColumn)
    {
        m_pLeftTableSelectColumn = connect(m_pLeftTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
    if(m_pIntersectionWidget && !m_pIntersectionSelectColumn)
    {
        m_pIntersectionSelectColumn = connect(m_pIntersectionWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
}

void CatTableViewBasics::DisconnectSelectColumn()
{
    disconnect(m_pThisTableSelectColumn);
    disconnect(m_pTopTableSelectColumn);
    disconnect(m_pLeftTableSelectColumn);
    disconnect(m_pIntersectionSelectColumn);
}

void CatTableViewBasics::ConnectSelectRow()
{
    if(!m_pThisTableSelectRow)
    {
        m_pThisTableSelectRow = connect(this, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }
    if(m_pTopTableWidget && !m_pTopTableSelectRow)
    {
        m_pTopTableSelectRow = connect(m_pTopTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }
    if(m_pLeftTableWidget && !m_pLeftTableSelectRow)
    {
        m_pLeftTableSelectRow = connect(m_pLeftTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }
    /*if(m_pIntersectionWidget && !m_pIntersectionSelectRow)
    {
        m_pIntersectionSelectRow = connect(m_pIntersectionWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }*/
}

void CatTableViewBasics::DisconnectSelectRow()
{
    disconnect(m_pThisTableSelectRow);
    disconnect(m_pTopTableSelectRow);
    disconnect(m_pLeftTableSelectRow);
    disconnect(m_pIntersectionSelectRow);
}

void CatTableViewBasics::updateFrozenTableGeometry()
{
    if(m_pTopTableWidget && m_pLeftTableWidget)
    {
        m_pTopTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pTopTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        m_pLeftTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pLeftTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        m_pIntersectionWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pIntersectionWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        int height = 0;
        int width = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }

        m_pIntersectionWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width())
                                           + frameWidth(),
                                           (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height())
                                           + frameWidth(),
                                           (verticalHeader()->isVisible() ? verticalHeader()->width() : 0)
                                           + width,
                                           (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0)
                                           + height);

        m_pTopTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                       (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + viewport()->width(),
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + height);

        m_pLeftTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                        (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + width,
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + viewport()->height());

        viewport()->stackUnder(m_pLeftTableWidget);//设置窗口层次
        viewport()->stackUnder(m_pTopTableWidget);//设置窗口层次
    } else if(m_pTopTableWidget)
    {
        m_pTopTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pTopTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        m_pTopTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                       (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + viewport()->width(),
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + height);
    } else if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pLeftTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        m_pLeftTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                        (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + width,
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + viewport()->height());
    }
}

void CatTableViewBasics::InitTopTable()
{
    m_pTopTableWidget = new QTableView(this);
    m_pTopTableWidget->setObjectName("CatTopTableWidget");
    m_pTopTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏滚动条
    m_pTopTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //
    m_pTopTableWidget->setHorizontalScrollMode(ScrollPerPixel);
    m_pTopTableWidget->setVerticalScrollMode(ScrollPerPixel);
    m_pTopTableWidget->setFocusPolicy(Qt::NoFocus);

    m_pTopTableWidget->setModel(model());

    viewport()->stackUnder(m_pTopTableWidget);//设置窗口层次

    m_pTopTableWidget->setSelectionModel(selectionModel());
    for (int row = m_iFrostRow; row < model()->rowCount(); ++row)
          m_pTopTableWidget->setRowHidden(row, true);

    connect(m_pTopTableWidget->horizontalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionWidth);
    connect(m_pTopTableWidget->verticalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionHeight);

    //连接信号槽, 用于滚动条联动
    connect(m_pTopTableWidget->horizontalScrollBar(), &QAbstractSlider::valueChanged,
            horizontalScrollBar(), &QAbstractSlider::setValue);
    connect(horizontalScrollBar(), &QAbstractSlider::valueChanged,
            m_pTopTableWidget->horizontalScrollBar(), &QAbstractSlider::setValue);

    m_pTopTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTopTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTopTableWidget->show();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);


}

void CatTableViewBasics::InitLeftTable()
{
    m_pLeftTableWidget = new QTableView(this);
    m_pLeftTableWidget->setObjectName("CatLeftTableWidget");
    m_pLeftTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    m_pLeftTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
    m_pLeftTableWidget->setHorizontalScrollMode(ScrollPerPixel);
    m_pLeftTableWidget->setFocusPolicy(Qt::NoFocus);

    m_pLeftTableWidget->setModel(model());

    viewport()->stackUnder(m_pLeftTableWidget);//设置窗口层次

    m_pLeftTableWidget->setSelectionModel(selectionModel());
    for (int col = m_iFrostColumn; col < model()->columnCount(); ++col)
          m_pLeftTableWidget->setColumnHidden(col, true);

    connect(m_pLeftTableWidget->horizontalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionWidth);
    connect(m_pLeftTableWidget->verticalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionHeight);

    //连接信号槽, 用于滚动条联动
    connect(m_pLeftTableWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            m_pLeftTableWidget->verticalScrollBar(), &QAbstractSlider::setValue);

    m_pLeftTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pLeftTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pLeftTableWidget->show();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    m_pLeftTableWidget->setVerticalScrollMode(ScrollPerPixel);
}

void CatTableViewBasics::InitIntersectionTable()
{
    m_pIntersectionWidget = new QTableView(this);
    m_pIntersectionWidget->setObjectName("CatIntersectionWidget");
    m_pIntersectionWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    m_pIntersectionWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
    m_pIntersectionWidget->setHorizontalScrollMode(ScrollPerPixel);
    m_pIntersectionWidget->setFocusPolicy(Qt::NoFocus);

    m_pIntersectionWidget->setModel(model());
    viewport()->stackUnder(m_pIntersectionWidget);//设置窗口层次
    m_pIntersectionWidget->setSelectionModel(selectionModel());
    for (int col = m_iFrostColumn; col < model()->columnCount(); ++col)
          m_pIntersectionWidget->setColumnHidden(col, true);
    for (int row = m_iFrostRow; row < model()->rowCount(); ++row)
          m_pIntersectionWidget->setRowHidden(row, true);

    connect(m_pIntersectionWidget->horizontalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionWidth);
    connect(m_pIntersectionWidget->verticalHeader(),&QHeaderView::sectionResized, this,
            &CatTableViewBasics::updateSectionHeight);

    //连接信号槽, 用于滚动条联动
    connect(m_pIntersectionWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            m_pIntersectionWidget->verticalScrollBar(), &QAbstractSlider::setValue);

    m_pIntersectionWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pIntersectionWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pIntersectionWidget->show();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    m_pIntersectionWidget->setVerticalScrollMode(ScrollPerPixel);
}

void CatTableViewBasics::CancelTableIntersection()
{
    if(m_pIntersectionWidget != nullptr)
    {
        delete m_pIntersectionWidget;
        m_pIntersectionWidget = nullptr;
    }
}

void CatTableViewBasics::initTable()
{

}

void CatTableViewBasics::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}

QModelIndex CatTableViewBasics::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
    if(m_pTopTableWidget && m_pLeftTableWidget)
    {
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        if (cursorAction == MoveLeft && current.column() > 0
                && visualRect(current).topLeft().x() < width ){
              const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - width;
              horizontalScrollBar()->setValue(newValue);
        }
        if (cursorAction == MoveUp && current.row() > 0
                && visualRect(current).topLeft().y() < height ){
              const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - height;
              verticalScrollBar()->setValue(newValue);
        }
    }
    else if(m_pLeftTableWidget)
    {
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        if (cursorAction == MoveLeft && current.column() > 0
                && visualRect(current).topLeft().x() < width ){
              const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - width;
              horizontalScrollBar()->setValue(newValue);
        }
    }
    else if(m_pTopTableWidget)
    {
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        if (cursorAction == MoveUp && current.row() > 0
                && visualRect(current).topLeft().x() < width ){
              const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - width;
              verticalScrollBar()->setValue(newValue);
        }
    }

    return current;
}

void CatTableViewBasics::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    QTableView::scrollTo(index, hint);
}

void CatTableViewBasics::hideHeader()
{
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
}

void CatTableViewBasics::updateSectionWidth(int logicalIndex, int oldSize, int newSize)
{
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->setColumnWidth(logicalIndex, newSize);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->setColumnWidth(logicalIndex, newSize);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->setColumnWidth(logicalIndex, newSize);
    }
    this->setColumnWidth(logicalIndex, newSize);
    updateFrozenTableGeometry();
}

void CatTableViewBasics::updateSectionHeight(int logicalIndex, int oldSize, int newSize)
{
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->setRowHeight(logicalIndex, newSize);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->setRowHeight(logicalIndex, newSize);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->setRowHeight(logicalIndex, newSize);
    }
    this->setRowHeight(logicalIndex, newSize);
    updateFrozenTableGeometry();
}

void CatTableViewBasics::selectTableColumn(int column)
{
    this->selectColumn(column);
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->selectColumn(column);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->selectColumn(column);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->selectColumn(column);
    }
}

void CatTableViewBasics::selectTableRow(int row)
{
    this->selectRow(row);
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->selectRow(row);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->selectRow(row);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->selectRow(row);
    }
}
