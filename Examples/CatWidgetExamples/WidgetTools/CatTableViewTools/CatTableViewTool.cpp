#include "CatTableViewTool.h"
#include <QHeaderView>
#include <QScrollBar>
#include <QStandardItem>
#include <QEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMouseEvent>

#include "CatConfig/CatConfig.h"

CatTableViewTool::CatTableViewTool(QWidget *parent)
    : CatTableViewBasics(parent)
{
    this->setObjectName("CatTableViewTool");
    InitUi();
    InitProperty();
    InitConnect();
}

CatTableViewTool::~CatTableViewTool()
{

}

void CatTableViewTool::AddData(bool state, QString times)
{
    QFont font("Ubuntu");
    font.setPixelSize(16);
    font.setWeight(QFont::Normal);
    m_TotalDataNums++;
    QList<QStandardItem*> headitems;
    QStandardItem *item0 = new QStandardItem();
    item0->setData(QVariant(0), Qt::UserRole);
    QStandardItem *item1 = new QStandardItem();
    item1->setForeground(QColor("#FFFFFF"));
    item1->setFont(font);
    item1->setData(m_TotalDataNums, Qt::UserRole);
    QStandardItem *item2 = new QStandardItem();
    item2->setForeground(QColor("#FFFFFF"));
    item2->setFont(font);
    item2->setData(state, Qt::UserRole);
    QStandardItem *item3 = new QStandardItem();
    item3->setForeground(QColor("#FFFFFF"));
    item3->setFont(font);
    item3->setData(times, Qt::UserRole);
    headitems.append(item0);
    headitems.append(item1);
    headitems.append(item2);
    headitems.append(item3);

    dataModel->appendRow(headitems);

    setRowHeight(m_TotalDataNums, 50);
}

void CatTableViewTool::ClearTable()
{

    this->model()->removeRows(1, m_TotalDataNums);
    m_TotalDataNums = 0;
    this->model()->setData(this->model()->index(0,0), 0, Qt::UserRole);

}

void CatTableViewTool::InitUi()
{
    //setUpdatesEnabled(true);
    horizontalHeader()->setVisible(true);
    verticalHeader()->setVisible(true);// 垂直不可见


    dataModel = new CatTableModel(this);
    dataModel->SetCatTableViewTool(this);

    //dataModel->item(0,0)->setCheckState(Qt::CheckState::PartiallyChecked);

    /*for (int i=0;i<20;i++)
    {
        QList<QStandardItem*> items;
        QStandardItem *item1 = new QStandardItem();
        item1->setData(QVariant(1), Qt::UserRole);
        items.append(item1);
        for (int j=1;j<10;j++)
        {
            items.append(new QStandardItem(QString("item(%1,%2)").arg(i).arg(j)));
        }
        dataModel->appendRow(items);
    }*/

    setModel(dataModel);

    InitTableHead();

    delegate = new CatTableItemDelegate(this);
    setItemDelegate(delegate);

    FrostTableHead(1);
    FrostTableLeft(2);

    GetTopTableView()->setItemDelegate(delegate);
    GetLeftTableView()->setItemDelegate(delegate);
    GetIntersectionView()->setItemDelegate(delegate);

    SetHorizontalHeaderSectionResizeMode(QHeaderView::Fixed);
    SetVerticalHeaderSectionResizeMode(QHeaderView::Fixed);

    HideVerticalHeader();
    HideHorizontalHeader();

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    GetTopTableView()->setEditTriggers(QAbstractItemView::NoEditTriggers);
    GetLeftTableView()->setEditTriggers(QAbstractItemView::NoEditTriggers);
    GetIntersectionView()->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ConnectSelectColumn();
    ConnectSelectRow();

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //所有列都扩展自适应宽度，填充充满整个屏幕宽度
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed); //对第0列单独设置固定宽度
    horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    setColumnWidth(0, 50);
    setColumnWidth(1, 50);
    setColumnWidth(3, 500);

    setRowHeight(0, 50);
    setShowGrid(false);
    GetTopTableView()->setShowGrid(false);
    GetLeftTableView()->setShowGrid(false);
    GetIntersectionView()->setShowGrid(false);

    setFocusPolicy(Qt::NoFocus);
    GetTopTableView()->setFocusPolicy(Qt::NoFocus);
    GetLeftTableView()->setFocusPolicy(Qt::NoFocus);
    GetIntersectionView()->setFocusPolicy(Qt::NoFocus);

    setSelectionBehavior(QTableView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    GetLeftTableView()->setSelectionBehavior(QTableView::SelectRows);
    GetLeftTableView()->setSelectionMode(QAbstractItemView::SingleSelection);

    GetTopTableView()->setSelectionMode(QAbstractItemView::SingleSelection);
    GetIntersectionView()->setSelectionMode(QAbstractItemView::SingleSelection);
}

void CatTableViewTool::InitProperty()
{
    setMouseTracking(true);
    installEventFilter(this);

    viewport()->installEventFilter(this);
    GetIntersectionView()->installEventFilter(this);
    GetIntersectionView()->setMouseTracking(true);
    GetIntersectionView()->viewport()->installEventFilter(this);
    GetTopTableView()->installEventFilter(this);
    GetTopTableView()->setMouseTracking(true);
    GetTopTableView()->viewport()->installEventFilter(this);
    GetLeftTableView()->installEventFilter(this);
    GetLeftTableView()->setMouseTracking(true);
    GetLeftTableView()->viewport()->installEventFilter(this);
    this->setUpdatesEnabled(true);
    GetLeftTableView()->setUpdatesEnabled(true);

    setSortingEnabled(true);
}

void CatTableViewTool::InitConnect()
{
    connect(delegate, &CatTableItemDelegate::sortColumned, this, [=](int column, Qt::SortOrder order){
        //horizontalHeader()->setSortIndicator(column, order);
        model()->sort(column, order);
    });
    connect(this, &CatTableViewTool::hoverIndexChanged, delegate, [=](const QModelIndex &index){
        delegate->onHoverIndexChanged(index);
        viewport()->update();
    });
    connect(this, &QTableView::entered, this, [=](const QModelIndex &index){
        emit hoverIndexChanged(index);
    });
    connect(GetLeftTableView(), &QTableView::entered, this, [=](const QModelIndex &index){
        emit hoverIndexChanged(index);
    });
}

void CatTableViewTool::InitTableHead()
{
    QList<QStandardItem*> headitems;
    QStandardItem *head0 = new QStandardItem();
    head0->setData(QVariant(0), Qt::UserRole);
    headitems.append(head0);
    for(int i = 1; i < CatConfig::GetTableHeader().size(); i++)
    {
        QStandardItem *item = new QStandardItem();
        QFont font("Ubuntu");
        font.setPixelSize(16);
        font.setWeight(QFont::Medium);
        item->setForeground(QColor("#FFFFFF"));
        item->setFont(font);
        if(i == 3)
        {
            QJsonObject object;
            object.insert("sort", 0);
            object.insert("data", QString::number(i));
            item->setData(QJsonDocument(object).toJson(QJsonDocument::Compact), Qt::TextColorRole);
        } else {
            item->setData(QString::number(i), Qt::TextColorRole);
        }

        headitems.append(item);
    }
    dataModel->appendRow(headitems);
}

bool CatTableViewTool::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::MouseMove)
    {
        delegate->onCurrentMouseed(dynamic_cast<QMouseEvent*>(event)->pos());
        viewport()->update();
    } else if(event->type() == QEvent::Leave)
    {
        delegate->onShiftOutChanged();
        viewport()->update();
    }

    return CatTableViewBasics::eventFilter(object, event);
}

void CatTableViewTool::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    CatTableViewBasics::resizeEvent(event);
}
