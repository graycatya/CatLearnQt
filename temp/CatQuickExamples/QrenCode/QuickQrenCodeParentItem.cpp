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

QImage QuickQrenCodeParentItem::getQrenImage()
{
    QRcode *qrCode = nullptr;

    qrCode = QRcode_encodeString(const_cast<const char*>(m_sText.toStdString().c_str()), 2,
                                 static_cast<QRecLevel>(m_eQrlevel),
                                 static_cast<QRencodeMode>(m_eQrmode),
                                 static_cast<int>(m_bCasesen ? 1 : 0));

    if(nullptr == qrCode)
    {
        return QImage();
    }

    int w = qMin(width(),height());
    double scale = w / qrCode->width;
    QPixmap *pixmap = new QPixmap(qrCode->width * scale, qrCode->width * scale);
    QPainter *painter = new QPainter(pixmap);

    painter->save();
    painter->eraseRect(0,0,w,w);

    //painter.begin(&m_qImage);
    QColor background(m_qBackgroundColor);
    painter->setBrush(background);
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, w, w);

    QColor foreground(m_qQrencodeColor);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBackground(foreground);
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
    painter->restore();
    delete painter;
    painter = nullptr;

    QRcode_free(qrCode);
    qrCode = nullptr;

    m_qImage = pixmap->scaled(w, w, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).toImage().copy();
    delete pixmap;
    pixmap = nullptr;

    return m_qImage;
}

void QuickQrenCodeParentItem::paint(QPainter *painter)
{
    if(m_sText.isEmpty())
    {
        return;
    }

    int w = qMin(width(),height());
    painter->eraseRect(0,0,w,w);
    painter->drawImage(0, 0, getQrenImage(), 0, 0, w, w);

    if(!m_sQrLogo.isEmpty()){
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#00ffffff"));
        double icon_width = (w - 2.0) * m_qQrPercent;
        double icon_height = icon_width;
        double wrap_x = (w - icon_width) / 2.0;
        double wrap_y = (w - icon_height) / 2.0;
        QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
        painter->drawRoundedRect(wrap, 50, 50);
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
    m_qBackgroundColor = Qt::white;
    m_qQrencodeColor = Qt::black;
    m_sQrLogo.clear();
    connect(this, &QQuickPaintedItem::widthChanged, this, [=](){
        update();
    });
    connect(this, &QQuickPaintedItem::heightChanged, this, [=](){
        update();
    });
    update();
}
