#ifndef QTQRENCODE_H
#define QTQRENCODE_H

#include <QString>
#include <QPixmap>

struct QRCODE {
    QString text = "";
    QSize size = QSize(200, 200);
    QColor backgroundColor;
    QColor qrencodeColor;
    QString logo = "";
    qreal qrpercent = 0.23;
};

/**
 * @brief GernerateQRCode
 * 生成二维码函数
 * @param text  二维码内容
 * @param qrPixmap  二维码像素图
 * @param scale 二维码缩放比例
 */
void GernerateQRCode(QRCODE qrcodestyle, QPixmap &qrPixmap);

#endif // QTQRENCODE_H
