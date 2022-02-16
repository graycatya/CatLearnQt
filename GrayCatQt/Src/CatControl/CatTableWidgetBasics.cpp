#include "CatTableWidgetBasics.h"
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>

CatTableWidgetBasics::CatTableWidgetBasics(QWidget *parent)
    : QTableWidget(parent)
{
    //connect the headers and scrollbars of both tableviews together
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &CatTableWidgetBasics::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &CatTableWidgetBasics::updateSectionHeight);
}

CatTableWidgetBasics::~CatTableWidgetBasics()
{

}

void CatTableWidgetBasics::FrostTableHead(int row)
{
    if(m_pHeadTableWidget == nullptr)
    {
        m_iFrostRow = row;
        m_pHeadTableWidget = new QTableWidget(this);
        m_pHeadTableWidget->horizontalHeader()->setVisible(false);//表头不可见
        m_pHeadTableWidget->verticalHeader()->setVisible(false);//表头不可见
        m_pHeadTableWidget->setShowGrid(false);//网格线不可见
        m_pHeadTableWidget->setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
        m_pHeadTableWidget->setFrameShape(QFrame::NoFrame);//去除边框
        m_pHeadTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
        m_pHeadTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
        m_pHeadTableWidget->setHorizontalScrollMode(ScrollPerPixel);

        viewport()->stackUnder(m_pHeadTableWidget);//设置窗口层次

        m_pHeadTableWidget->setRowCount(row);

        for(int temprow = row; temprow < m_pHeadTableWidget->rowCount(); temprow++)
        {
            m_pHeadTableWidget->setRowHeight(temprow, true);
        }

        //连接信号槽, 用于滚动条联动
        connect(m_pHeadTableWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
                verticalScrollBar(), &QAbstractSlider::setValue);
        connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
                m_pHeadTableWidget->verticalScrollBar(), &QAbstractSlider::setValue);

        updateFrozenTableGeometry();//更新位置
        m_pHeadTableWidget->show();
    }
}

void CatTableWidgetBasics::CancelTableHead()
{
    if(m_pHeadTableWidget != nullptr)
    {
        delete m_pHeadTableWidget;
        m_pHeadTableWidget = nullptr;
    }
}

void CatTableWidgetBasics::FrostTableLeft(int column)
{
    if(m_pLeftTableWidget == nullptr)
    {
        m_iFrostColumn = column;
        m_pLeftTableWidget = new QTableWidget(this);
        m_pLeftTableWidget->horizontalHeader()->setVisible(false);//表头不可见
        m_pLeftTableWidget->verticalHeader()->setVisible(false);//表头不可见

        m_pLeftTableWidget->setShowGrid(false);//网格线不可见
        m_pLeftTableWidget->setFocusPolicy(Qt::NoFocus);//解决选中虚框问题
        m_pLeftTableWidget->setFrameShape(QFrame::NoFrame);//去除边框
        m_pLeftTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
        m_pLeftTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
        m_pLeftTableWidget->setHorizontalScrollMode(ScrollPerPixel);

        viewport()->stackUnder(m_pLeftTableWidget);//设置窗口层次

        m_pLeftTableWidget->setColumnCount(column);

        for(int tempcolumn = column; tempcolumn < m_pLeftTableWidget->columnCount(); tempcolumn++)
        {
            m_pLeftTableWidget->setColumnHidden(tempcolumn, true);
        }

        //连接信号槽.用于滚动条联动
        connect(m_pLeftTableWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
                verticalScrollBar(), &QAbstractSlider::setValue);
        connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
                m_pLeftTableWidget->verticalScrollBar(), &QAbstractSlider::setValue);

        updateFrozenTableGeometry();//更新位置
        m_pLeftTableWidget->show();
    }
}

void CatTableWidgetBasics::CancelTableLeft()
{
    if(m_pLeftTableWidget != nullptr)
    {
        delete m_pLeftTableWidget;
        m_pLeftTableWidget = nullptr;
    }
}

void CatTableWidgetBasics::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}

QModelIndex CatTableWidgetBasics::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if(m_pLeftTableWidget)
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

    if(m_pHeadTableWidget)
    {
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        if (cursorAction == MoveUp && current.row() > 0
                && visualRect(current).topLeft().y() < height ){
              const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().y()
                                   - height;
              verticalScrollBar()->setValue(newValue);
        }
    }

    return current;
}

void CatTableWidgetBasics::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    QTableView::scrollTo(index, hint);
}

void CatTableWidgetBasics::updateFrozenTableGeometry()
{
    if(m_pHeadTableWidget)
    {
        int height = 0;
        for(int i = 1; i < m_iFrostColumn; i++)
        {
            height += rowHeight(i);
        }
        m_pHeadTableWidget->setGeometry(frameWidth(), frameWidth(),
                                        viewport()->width(),
                                        horizontalHeader()->height() + height);
    }

    if(m_pLeftTableWidget)
    {
        int width = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            width += columnWidth(i);
        }
        int y = 0;
        y = m_pHeadTableWidget ? m_pHeadTableWidget->height() : horizontalHeader()->height();
        qDebug() << "y: " << y << " width: " << width;
        m_pLeftTableWidget->setGeometry(verticalHeader()->width() + frameWidth(),
                                        horizontalHeader()->height(), width,
                                        viewport()->height()+horizontalHeader()->height());
    }
}

void CatTableWidgetBasics::updateSectionWidth(int logicalIndex, int oldSize, int newSize)
{
    Q_UNUSED(logicalIndex)
    Q_UNUSED(oldSize)
    Q_UNUSED(newSize)
    /*if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->setColumnWidth()
    }*/
}

void CatTableWidgetBasics::updateSectionHeight(int logicalIndex, int oldSize, int newSize)
{
    Q_UNUSED(logicalIndex)
    Q_UNUSED(oldSize)
    Q_UNUSED(newSize)
}
