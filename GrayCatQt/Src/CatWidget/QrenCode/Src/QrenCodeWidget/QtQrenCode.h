#ifndef QTQRENCODE_H
#define QTQRENCODE_H

#include <QString>
#include <QPixmap>

/**
 * @brief GernerateQRCode
 * 生成二维码函数
 * @param text  二维码内容
 * @param qrPixmap  二维码像素图
 * @param scale 二维码缩放比例
 */
void GernerateQRCode(const QString &text, QPixmap &qrPixmap, QSize size = QSize(200, 200), QString logo = "", int margin = 5);

#endif // QTQRENCODE_H
