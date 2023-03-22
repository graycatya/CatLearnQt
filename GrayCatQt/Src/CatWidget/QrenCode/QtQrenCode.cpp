#include "QtQrenCode.h"

extern "C" {
    #include "QrenCodeSrc/qrencode.h"
}

#include <QDebug>
#include <QImage>
#include <QPainter>

void getQrenImage(QRCODE qrcodestyle, QImage &image) {
    QRcode *qrCode = nullptr;
    QImage tmp;

    qrCode = QRcode_encodeString(const_cast<const char*>(qrcodestyle.text.toStdString().c_str()), 2,
                                 QR_ECLEVEL_Q, QR_MODE_8, static_cast<int>(1));
    if(nullptr == qrCode)
    {
        return;
    }
    int w = qMin(qrcodestyle.size.width(),qrcodestyle.size.height());
    double scale = w / qrCode->width;
    QPixmap *pixmap = new QPixmap(qrCode->width * scale, qrCode->width * scale);
    QPainter *painter = new QPainter(pixmap);

    painter->eraseRect(0,0,w,w);

    //painter.begin(&m_qImage);
    QColor background(qrcodestyle.backgroundColor);
    painter->setBrush(background);
    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, w, w);
    QColor foreground(qrcodestyle.qrencodeColor);
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

    delete painter;
    painter = nullptr;

    QRcode_free(qrCode);
    qrCode = nullptr;
    pixmap->save("pix.png");
    image = pixmap->scaled(w, w, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).toImage().copy();
    delete pixmap;
    pixmap = nullptr;
}

//void GernerateQRCode(const QString &text, QPixmap &qrPixmap, QSize size, QString logo, int margin)
//{
//    if(text.isEmpty())
//    {
//        return;
//    }

//    //二维码数据
//    QRcode *qrCode = nullptr;
//    //这里二维码版本传入参数是2,实际上二维码生成后，它的版本是根据二维码内容来决定的
//    qrCode = QRcode_encodeString(text.toStdString().c_str(), 2,
//                                 QR_ECLEVEL_Q, QR_MODE_8, static_cast<int>(1));

//    if(nullptr == qrCode)
//    {
//        return;
//    }

//    int width = qMin(size.width(), size.height());

//    QImage image(width, width, QImage::Format_ARGB32_Premultiplied);

//    QPainter painter(&image);
//    QColor background(Qt::white);
//    painter.setBrush(background);
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(0, 0, width, width);
//    double scale = (width - margin) / qrCode->width;
//    QColor foreground(Qt::black);
//    painter.setBrush(foreground);
//    for(int y = 0; y < qrCode->width; y++)
//    {
//        for(int x = 0; x < qrCode->width; x++)
//        {
//            unsigned char character = qrCode->data[y * qrCode->width + x];
//            if(character & 1)
//            {
//               QRect rect(margin*2 + x * scale, margin*2 + y * scale, scale, scale);
//               painter.drawRects(&rect, 1);
//            }
//        }
//    }

//    QRcode_free(qrCode);
//    qrCode = nullptr;

//    painter.setBrush(QColor("#00ffffff"));
//    double icon_width = (width - 2.0) * 0.23;
//    double icon_height = icon_width;
//    double wrap_x = (width - icon_width) / 2.0;
//    double wrap_y = (width - icon_height) / 2.0;
//    QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
//    painter.drawRoundedRect(wrap, 50, 50);
//    if(!logo.isEmpty()){
//        QPixmap image(logo);
//        QRectF target(wrap_x, wrap_y, icon_width, icon_height);
//        QRectF sources(0, 0, image.width (), image.height ());
//        painter.drawPixmap (target, image, sources);
//    }

//    qrPixmap = QPixmap::fromImage(image);
//}

void GernerateQRCode(QRCODE qrcodestyle, QPixmap &qrPixmap)
{
        if(qrcodestyle.text.isEmpty())
        {
            return;
        }

        //二维码数据
        QRcode *qrCode = nullptr;
        //这里二维码版本传入参数是2,实际上二维码生成后，它的版本是根据二维码内容来决定的
        qrCode = QRcode_encodeString(qrcodestyle.text.toStdString().c_str(), 2,
                                     QR_ECLEVEL_Q, QR_MODE_8, static_cast<int>(1));

        if(nullptr == qrCode)
        {
            return;
        }

        double width = qMin(qrcodestyle.size.width(), qrcodestyle.size.height());

        QImage image(width, width, QImage::Format_ARGB32_Premultiplied);

        QPainter painter;
        painter.begin(&image);
        painter.eraseRect(0,0,width,width);
        QColor background(qrcodestyle.backgroundColor);
        painter.setBrush(background);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, width, width);
        double scale = width / (double)qrCode->width;
        QColor foreground(qrcodestyle.qrencodeColor);
        painter.setBrush(foreground);
        for(int y = 0; y < qrCode->width; y++)
        {
            for(int x = 0; x < qrCode->width; x++)
            {
                unsigned char character = qrCode->data[y * qrCode->width + x];
                if(character & 1)
                {
                   QRectF rect(x * scale, y * scale, scale, scale);
                   painter.drawRects(&rect, 1);
                }
            }
        }
        painter.end();

        QRcode_free(qrCode);
        qrCode = nullptr;

        QPixmap tempPixmap(QSize(width, width));
        painter.begin(&tempPixmap);
        QImage imagepix = image.scaled(width, width, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).copy();
        painter.eraseRect(0,0,width,width);
        painter.drawImage(0, 0, imagepix, 0, 0, width, width);


        if(!qrcodestyle.logo.isEmpty()){
            painter.setBrush(QColor("#00ffffff"));
            double icon_width = (width - 2.0) * 0.23;
            double icon_height = icon_width;
            double wrap_x = (width - icon_width) / 2.0;
            double wrap_y = (width - icon_height) / 2.0;
            QRectF wrap(wrap_x - 5, wrap_y - 5, icon_width + 10, icon_height + 10);
            painter.drawRoundedRect(wrap, 50, 50);
            QPixmap image(qrcodestyle.logo);
            QRectF target(wrap_x, wrap_y, icon_width, icon_height);
            QRectF sources(0, 0, image.width (), image.height ());
            painter.drawPixmap (target, image, sources);
        }
        painter.end();

        qrPixmap = tempPixmap;
}
