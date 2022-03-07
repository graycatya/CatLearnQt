#include "CatTableItemDelegate.h"
#include <QCheckBox>
#include <QApplication>
#include <QPainter>
#include <qdrawutil.h>
#include <QWidget>
#include <QMouseEvent>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPen>
#include <QJsonObject>
#include <QJsonDocument>
#include "CatConfig/CatConfig.h"

CatTableItemDelegate::CatTableItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    this->installEventFilter(parent);
    m_checkSize = QSize(20, 20);
    m_sortSize = QSize(16, 16);
}

CatTableItemDelegate::~CatTableItemDelegate()
{

}

void CatTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem optiontemp(option);
    optiontemp = paintHover(painter, option, index);
    QStyledItemDelegate::paint(painter, optiontemp, index);
    // 先绘制表头
    paintHead(painter, option, index);
}

void CatTableItemDelegate::paintHead(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.row() == 0)
    {
        //painter->fillRect(option.rect, CatConfig::GetTableViewHeadBackGround_Normal());
        paintHeadCheck(painter, option, index);
        paintHeadData(painter, option, index);
    } else {
        paintDataCheck(painter, option, index);
        paintTableData(painter, option, index);
        paintTableState(painter, option, index);
    }
}

void CatTableItemDelegate::paintHeadData(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == HEAD_ID_COLUMN
            | index.column() == HEAD_STATE_COLUMN
            | index.column() == HEAD_TIME_COLUMN)
    {
        QString text = CatConfig::GetTableHeader().at(index.data(Qt::TextColorRole).toInt());
        if(index.column() >= HEAD_TIME_COLUMN && index.column() <= HEAD_TIME_COLUMN)
        {
            text = CatConfig::GetTableHeader().at(getHeadSortData(index).toInt());
        }
        paintText(painter, option, index, text, CatConfig::GetTableViewHeadText_Color(), Qt::AlignVCenter | Qt::AlignHCenter);
    }

    // 绘制排序按钮
    if(index.column() == HEAD_TIME_COLUMN)
    {
        paintSortButton(painter, option, index, Qt::AlignVCenter | Qt::AlignHCenter);
    }
}

void CatTableItemDelegate::paintHeadCheck(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == HEAD_CHECK_COLUMN)
    {
        QRect checkR = QRect((option.rect.width() - m_checkSize.width()) / 2,
                             (option.rect.height() - m_checkSize.height()) / 2,
                             m_checkSize.width(), m_checkSize.height());
        //qDebug() << QDateTime::currentDateTime() << "option: " << option.rect << " checkR: " << checkR << " m_currentMouse: " << m_currentMouse;
        QString img = "";
        switch (index.data(Qt::UserRole).toInt()) {
            case 0: {
                if(checkR.contains(m_currentMouse))
                {
                    img = ":/Images/CheckOff_Hover.png";
                } else {
                    img = ":/Images/CheckOff_Normal.png";
                }
                break;
            }
            case 1: {
                img = ":/Images/CheckOn_Partially.png";
                break;
            }
            default: {
                img = ":/Images/CheckOn_All.png";
                break;
            }
        }
        QPixmap map(img);
        option.widget->style()->drawItemPixmap(painter
                                               , checkR
                                               , Qt::AlignHCenter | Qt::AlignVCenter
                                               , map);
    }
}

void CatTableItemDelegate::paintText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, QString text, QColor color,  int flags) const
{
    QStandardItem *item = qobject_cast<const QStandardItemModel*>(index.model())->itemFromIndex(index);
    painter->setBrush(color);
    QPen pen(color);
    painter->setPen(pen);
    painter->setFont(item->font());
    painter->drawText(option.rect, flags, text);
}

void CatTableItemDelegate::paintSortButton(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index, int flags) const
{
    QStandardItem *item = qobject_cast<const QStandardItemModel*>(index.model())->itemFromIndex(index);
    QFontMetrics fm(item->font());
    QString text = item->data(Qt::TextColorRole).toString();
    if(index.column() >= 5 && index.column() <= 8)
    {
        text = CatConfig::GetTableHeader().at(getHeadSortData(index).toInt());
    }
    QRect textRect = fm.boundingRect(text);

    QSize textsize(textRect.width(), textRect.height());
    int textx;
    int texty;
    if(flags & Qt::AlignHCenter)
    {
        textx = (option.rect.width() - textsize.width()) / 2;
    } else if(flags & Qt::AlignLeft)
    {
        textx = 0;
    } else if(flags & Qt::AlignRight)
    {
        textx = option.rect.left() + textsize.width();
    }


    if(flags & Qt::AlignVCenter)
    {
        texty = (option.rect.height() - textsize.height()) / 2;
    } else if(flags & Qt::AlignTop)
    {
        texty = 0;
    } else if(flags & Qt::AlignBottom)
    {
        texty = option.rect.bottom() - textsize.height();
    }



    textRect = QRect(textx,
                     texty,
                     textsize.width(), textsize.height());

    QRect UpButtonRect = QRect(option.rect.x() + textRect.right() + 8, 12,
                               m_sortSize.width(), m_sortSize.height());
    QRect BelowButtonRect = QRect(option.rect.x() + textRect.right() + 8, 28, m_sortSize.width(), m_sortSize.height());

    QString upimg = ":/Images/UpNormal.png";
    QString belowimg = ":/Images/BelowNormal.png";

    if(getHeadSortState(index) == 0)
    {
        if(UpButtonRect.contains(m_currentMouse))
        {
            upimg = ":/Images/UpHover.png";
        }

        if(BelowButtonRect.contains(m_currentMouse))
        {
            belowimg = ":/Images/BelowHover.png";
        }
    } else if(getHeadSortState(index) == 1)
    {
        upimg = ":/Images/UpHover.png";
    } else if(getHeadSortState(index) == 2)
    {
        belowimg = ":/Images/BelowHover.png";
    }

    QPixmap Upmap(upimg);
    option.widget->style()->drawItemPixmap(painter
                                           , UpButtonRect
                                           , Qt::AlignHCenter | Qt::AlignVCenter
                                           , Upmap);

    QPixmap Belowmap(belowimg);
    option.widget->style()->drawItemPixmap(painter
                                           , BelowButtonRect
                                           , Qt::AlignHCenter | Qt::AlignVCenter
                                           , Belowmap);
}

void CatTableItemDelegate::paintDataCheck(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == DATA_CHECK_COLUMN)
    {
        QRect checkR = QRect(option.rect.x() + (option.rect.width() - m_checkSize.width()) / 2,
                             option.rect.y() + (option.rect.height() - m_checkSize.height()) / 2,
                             m_checkSize.width(), m_checkSize.height());
        //qDebug() << QDateTime::currentDateTime() << "option: " << option.rect << " checkR: " << checkR << " m_currentMouse: " << m_currentMouse;
        QString img = ":/Images/CheckOff_Normal.png";
        switch (index.data(Qt::UserRole).toInt()) {
            case 0: {
                if(checkR.contains(m_currentMouse))
                {
                    img = ":/Images/CheckOff_Hover.png";
                }
                break;
            }
            case 1: {
                img = ":/Images/CheckOn_Partially.png";
                break;
            }
            default: {
                img = ":/Images/CheckOn_All.png";
                break;
            }
        }
        QPixmap map(img);
        option.widget->style()->drawItemPixmap(painter
                                               , checkR
                                               , Qt::AlignHCenter | Qt::AlignVCenter
                                               , map);
    }
}

void CatTableItemDelegate::paintTableData(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == DATA_ID_COLUMN || index.column() == DATA_TIME_COLUMN)
    {
        QString text = index.data(Qt::UserRole).toString();
        paintText(painter, option, index, text, CatConfig::GetTableViewItemText_Color(), Qt::AlignVCenter | Qt::AlignHCenter);
    }
}

void CatTableItemDelegate::paintTableState(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == DATA_STATE_COLUMN)
    {
        QStandardItem *item = qobject_cast<const QStandardItemModel*>(index.model())->itemFromIndex(index);
        QString text = "";
        QColor textcolor = item->foreground().color();

        if(index.data(Qt::UserRole).toBool())
        {
            text = "ERROR";
            textcolor = CatConfig::GetTableViewItemStateDataError_Color();
        } else {
            text = "OK";
            textcolor = CatConfig::GetTableViewItemStateDataOk_Color();
        }

        QPen pen(textcolor);
        painter->setPen(pen);
        painter->setFont(item->font());
        painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignHCenter, text);
    }
}

QStyleOptionViewItem CatTableItemDelegate::paintHover(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem optiont(option);
    if(m_hoverrow == index.row())
    {
        optiont.state |= QStyle::State_MouseOver;
        //State_Selected
    }
    return optiont;
}

void CatTableItemDelegate::editorHeadCheck(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == 0)
    {
        QRect checkR = QRect((option.rect.width() - m_checkSize.width()) / 2,
                             (option.rect.height() - m_checkSize.height()) / 2,
                             m_checkSize.width(), m_checkSize.height());
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *eventM = dynamic_cast<QMouseEvent*>(event);
            if(checkR.contains(eventM->pos()))
            {
                int data = index.data(Qt::UserRole).toInt();
                data = data == 2 ? 0 : 2;
                model->setData(index, data, Qt::UserRole);

                for(int i = 1; i < model->rowCount(); i++)
                {
                    model->setData(model->index(i, 0),
                                   model->data(index, Qt::UserRole).toInt(),
                                   Qt::UserRole);
                }
            }
        }
    }
}

void CatTableItemDelegate::editorHeadSortButton(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    int flags = Qt::AlignVCenter | Qt::AlignHCenter;
    QStandardItem *item = qobject_cast<const QStandardItemModel*>(index.model())->itemFromIndex(index);
    QFontMetrics fm(item->font());
    QString text = item->data(Qt::TextColorRole).toString();
    if(index.column() >= 5 && index.column() <= 8)
    {
        text = getHeadSortData(index);
    }
    QRect textRect = fm.boundingRect(text);

    QSize textsize(textRect.width(), textRect.height());
    int textx;
    int texty;
    if(flags & Qt::AlignHCenter)
    {
        textx = (option.rect.width() - textsize.width()) / 2;
    } else if(flags & Qt::AlignLeft)
    {
        textx = 0;
    } else if(flags & Qt::AlignRight)
    {
        textx = option.rect.left() + textsize.width();
    }


    if(flags & Qt::AlignVCenter)
    {
        texty = (option.rect.height() - textsize.height()) / 2;
    } else if(flags & Qt::AlignTop)
    {
        texty = 0;
    } else if(flags & Qt::AlignBottom)
    {
        texty = option.rect.bottom() - textsize.height();
    }



    textRect = QRect(textx,
                     texty,
                     textsize.width(), textsize.height());

    QRect UpButtonRect = QRect(option.rect.x() + textRect.right() + 8, 12,
                               m_sortSize.width(), m_sortSize.height());
    QRect BelowButtonRect = QRect(option.rect.x() + textRect.right() + 8, 28, m_sortSize.width(), m_sortSize.height());

    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *eventM = dynamic_cast<QMouseEvent*>(event);
        if(UpButtonRect.contains(eventM->pos()))
        {
            if(getHeadSortState(index) != 1)
            {
                setHeadSortState(model, index, 1);
                emit sortColumned(index.column(), Qt::AscendingOrder);
            } else {
                setHeadSortState(model, index, 0);
                emit sortColumned(1, Qt::AscendingOrder);
            }

        } else if(BelowButtonRect.contains(eventM->pos()))
        {
            if(getHeadSortState(index) != 2)
            {
                emit sortColumned(index.column(), Qt::DescendingOrder);
                setHeadSortState(model, index, 2);
            } else {
                setHeadSortState(model, index, 0);
                emit sortColumned(1, Qt::AscendingOrder);
            }
        }
    }
}

void CatTableItemDelegate::editorTableDataCheck(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == 0)
    {
        QRect checkR = QRect(option.rect.x() + (option.rect.width() - m_checkSize.width()) / 2,
                             option.rect.y() + (option.rect.height() - m_checkSize.height()) / 2,
                             m_checkSize.width(), m_checkSize.height());
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *eventM = dynamic_cast<QMouseEvent*>(event);
            if(checkR.contains(eventM->pos()))
            {
                int data = index.data(Qt::UserRole).toInt();
                data = data == 2 ? 0 : 2;
                model->setData(index, data, Qt::UserRole);

                if(this->getSelectCheckTableData(model) == (model->rowCount() - 1))
                {
                    model->setData(model->index(0, 0),
                                   2,
                                   Qt::UserRole);
                } else if(this->getSelectCheckTableData(model) == 0)
                {
                    model->setData(model->index(0, 0),
                                   0,
                                   Qt::UserRole);
                } else {
                    model->setData(model->index(0, 0),
                                   1,
                                   Qt::UserRole);
                }
            }
        }
    }
}

int CatTableItemDelegate::getHeadSortState(const QModelIndex &index) const
{
    QJsonObject object = QJsonDocument::fromJson(index.data(Qt::TextColorRole).toString().toUtf8()).object();
    return object["sort"].toInt();
}

void CatTableItemDelegate::setHeadSortState(QAbstractItemModel *model, const QModelIndex &index, int state) const
{
    QJsonObject object = QJsonDocument::fromJson(index.data(Qt::TextColorRole).toString().toUtf8()).object();
    object["sort"] = state;
    model->setData(index, QJsonDocument(object).toJson(QJsonDocument::Compact), Qt::TextColorRole);
}

QString CatTableItemDelegate::getHeadSortData(const QModelIndex &index) const
{
    QJsonObject object = QJsonDocument::fromJson(index.data(Qt::TextColorRole).toString().toUtf8()).object();
    return object["data"].toString();
}

void CatTableItemDelegate::setHeadSortData(QAbstractItemModel *model, const QModelIndex &index, QString data) const
{
    QJsonObject object = QJsonDocument::fromJson(index.data(Qt::TextColorRole).toString().toUtf8()).object();
    object["data"] = data;
    model->setData(index, QJsonDocument(object).toJson(QJsonDocument::Compact), Qt::TextColorRole);
}

int CatTableItemDelegate::getSelectCheckTableData(QAbstractItemModel *model)
{
    int checks = 0;
    for(int i = 1; i < model->rowCount(); i++)
    {
        if(model->index(i, 0).data(Qt::UserRole).toUInt() == 2)
        {
            checks++;
        }
    }
    return checks;
}

void CatTableItemDelegate::onHoverIndexChanged(const QModelIndex &index)
{
    m_hoverrow = index.row();
    m_hovercolumn = index.column();
}

void CatTableItemDelegate::onShiftOutChanged()
{
    m_hoverrow = -1;
    m_hovercolumn = -1;
}

void CatTableItemDelegate::onCurrentMouseed(QPoint pot)
{
    m_currentMouse = pot;
}

bool CatTableItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.row() == 0)
    {
        // isHead 表头
        if(index.column() == HEAD_CHECK_COLUMN)
        {
            editorHeadCheck(event, model, option, index);
        } else if(index.column() == HEAD_TIME_COLUMN)
        {
            editorHeadSortButton(event, model, option, index);
        }
    } else {
        // isData 表数据
        if(index.column() == DATA_CHECK_COLUMN)
        {
            editorTableDataCheck(event, model, option, index);
        }
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mevent = dynamic_cast<QMouseEvent*>(event);
            if(mevent->button() == Qt::RightButton)
            {
                qDebug() << "editorEvent: " << "right";
                //QToolTip
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
