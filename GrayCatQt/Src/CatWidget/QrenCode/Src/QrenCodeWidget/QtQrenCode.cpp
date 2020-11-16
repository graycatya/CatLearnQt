#include "QtQrenCode.h"
#include "../../qrencode.h"

#include <QPainter>

void GernerateQRCode(const QString &text, QPixmap &qrPixmap, QSize size, QString logo, int margin)
{
    if(text.isEmpty())
    {
        return;
    }

    //二维码数据
    QRcode *qrCode = nullptr;

    //这里二维码版本传入参数是2,实际上二维码生成后，它的版本是根据二维码内容来决定的
    qrCode = QRcode_encodeString(text.toStdString().c_str(), 2,
                                 QR_ECLEVEL_Q, QR_MODE_8, 1);

    if(nullptr == qrCode)
    {
        return;
    }

    int width = qMin(size.width(), size.height());

    QImage image(width, width, QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&image);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width, width);
    double scale = (width - margin) / qrCode->width;
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for(int y = 0; y < qrCode->width; y++)
    {
        for(int x = 0; x < qrCode->width; x++)
        {
            unsigned char character = qrCode->data[y * qrCode->width + x];
            if(character & 1)
            {
               QRect rect(margin*2 + x * scale, margin + y * scale, scale, scale);
               painter.drawRects(&rect, 1);
            }
        }
    }

    QRcode_free(qrCode);
    qrCode = nullptr;

    painter.setBrush(QColor("#00ffffff"));
    double icon_width = (width - 2.0) * 0.23;
    double icon_height = icon_width;
    double wrap_x = (width - icon_width) / 2.0;
    double wrap_y = (width - icon_height) / 2.0;
    QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
    painter.drawRoundedRect(wrap, 50, 50);
    if(!logo.isEmpty()){
        QPixmap image(logo);
        QRectF target(wrap_x, wrap_y, icon_width, icon_height);
        QRectF sources(0, 0, image.width (), image.height ());
        painter.drawPixmap (target, image, sources);
    }

    qrPixmap = QPixmap::fromImage(image);
}
