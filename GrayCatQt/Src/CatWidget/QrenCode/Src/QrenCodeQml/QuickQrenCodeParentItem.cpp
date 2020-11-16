#include "QuickQrenCodeParentItem.h"
#include <QPainter>
#include <QQmlApplicationEngine>
#include <QGuiApplication>

QuickQrenCodeParentItem::QuickQrenCodeParentItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    InitProperty();
}

QuickQrenCodeParentItem::~QuickQrenCodeParentItem()
{

}

void QuickQrenCodeParentItem::paint(QPainter *painter)
{
    if(m_sText.isEmpty())
    {
        return;
    }

    //二维码数据
    QRcode *qrCode = nullptr;

    qrCode = QRcode_encodeString(m_sText.toStdString().c_str(), 2,
                                 static_cast<QRecLevel>(m_eQrlevel),
                                 static_cast<QRencodeMode>(m_eQrmode),
                                 m_bCasesen ? 1 : 0);

    if(nullptr == qrCode)
    {
        return;
    }
    int w = qMin(width(),height());

    QColor background(Qt::white);
    painter->setBrush(background);
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, w, w);
    double scale = w / qrCode->width;
    QColor foreground(Qt::black);
    painter->setBrush(foreground);
    for(int y = 0; y < qrCode->width; y++)
    {
        for(int x = 0; x < qrCode->width; x++)
        {
            unsigned char character = qrCode->data[y * qrCode->width + x];
            if(character & 1)
            {
               QRect rect(x * scale, y * scale, scale, scale);
               painter->drawRects(&rect, 1);
            }
        }
    }

    QRcode_free(qrCode);
    qrCode = nullptr;

    painter->setBrush(QColor("#00ffffff"));
    double icon_width = (w - 2.0) * m_qQrPercent;
    double icon_height = icon_width;
    double wrap_x = (w - icon_width) / 2.0;
    double wrap_y = (w - icon_height) / 2.0;
    QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
    painter->drawRoundedRect(wrap, 50, 50);
    if(!m_sQrLogo.isEmpty()){
        QPixmap image(m_sQrLogo);
        QRectF target(wrap_x, wrap_y, icon_width, icon_height);
        QRectF sources(0, 0, image.width (), image.height ());
        painter->drawPixmap (target, image, sources);
    }
}

void QuickQrenCodeParentItem::InitProperty()
{
    m_eQrmode = MODE_8;
    m_eQrlevel = LEVEL_Q;
    m_bCasesen = true;
    m_qQrPercent = 0.23;
    m_sQrLogo.clear();
    connect(this, &QQuickPaintedItem::widthChanged, this, [=](){
        update();
    });
    connect(this, &QQuickPaintedItem::heightChanged, this, [=](){
        update();
    });
    update();
}
