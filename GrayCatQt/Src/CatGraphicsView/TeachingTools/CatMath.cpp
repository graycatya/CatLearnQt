#include "CatMath.h"
#include <QApplication>
#include <QScreen>
#include <QtMath>
#include <math.h>
#include <QDebug>

// 求弧度 180度/π是1弧度对应多少度！
const qreal AnglePerPI = 180.0 / M_PI;

qreal GetDpi()
{
   //QGuiApplication::highDpiScaleFactorRoundingPolicy();
   return QApplication::primaryScreen()->logicalDotsPerInch();
}

qreal CatMath::CmtoPx(qreal cm)
{
    //获取主屏幕分辨率
    QScreen *screen = QApplication::primaryScreen();
    // 1 英寸的像素
    qreal inchToPx = qreal(1)/GetDpi();
    //qreal inchToPx = qreal(1.0)/130.0;
    // 屏幕宽度
    qreal width = static_cast<qreal>(screen->geometry().width());
    // 1 英寸＝2.54 厘米 WidthToCm为当前屏幕宽度所对应的厘米尺寸
    qreal WidthToCm = width * inchToPx * qreal(2.54);
    // 换算cm 转 px
    qreal px = (cm * width)/WidthToCm;
    return px;
}

qreal CatMath::PxtoCm(qreal px)
{
    //获取主屏幕分辨率
    QScreen *screen = QApplication::primaryScreen();
    // 1 英寸的像素
    qreal inchToPx = qreal(1)/GetDpi();
    // 屏幕宽度
    qreal width = static_cast<qreal>(screen->geometry().width());
    // 1 英寸＝2.54 厘米 WidthToCm为当前屏幕宽度所对应的厘米尺寸
    qreal WidthToCm = width * inchToPx * qreal(2.54);
    // 换算px 转 cm
    qreal cm = (px * WidthToCm)/width;
    return cm;

}

qreal CatMath::DegreeAngle(QVector2D vector2d)
{
    // qAtan2 返回的是弧度 - 官方文档有误
    // qAtan2 * AnglePerPI + 360.0  用度表示反正切值
    // fmod 求余
    return fmod((qAtan2(static_cast<qreal>(vector2d.y()), static_cast<qreal>(vector2d.x())) * AnglePerPI + 360.0), 360.0);
}

QPointF CatMath::PointCoordinatesOnACircle(QPointF centerpoint, qreal r, qreal angle)
{
    QPointF point;
    qreal rotate = angle * M_PI / 180.0;
    point.setX(centerpoint.rx() + r * qCos(rotate));
    point.setY(centerpoint.ry() + r * qSin(rotate));
    return point;
}

qreal CatMath::AngleJudge(qreal angle)
{
    qreal temp = angle;
    if (temp > 360.0)
    {
        while(1)
        {
            temp -= 360.0;
            if (temp < 360.0) break;
        }
    }
    else if (temp < 0.0)
    {
        while(1)
        {
            temp += 360.0;
            if (temp > 0.0) break;
        }
    }
    return temp;
}

qreal CatMath::PythagoreanTheorem(qreal a, qreal b)
{
    qreal c = 0;
    c = qSqrt(qPow(a, 2) + qPow(b, 2));
    return c;
}

qreal CatMath::TanToAngle(qreal bc, qreal ab)
{
    return qAtan(bc/ab) * 180 / M_PI;
}

qreal CatMath::CosToAngle(qreal ab, qreal ac)
{
    return qAcos(ab/ac) * 180 / M_PI;
}

qreal CatMath::SinToAngle(qreal bc, qreal ac)
{
    return qAsin(bc/ac) * 180 / M_PI;
}

QPointF CatMath::PosMove(QPointF last, QPointF pos)
{
   return QPointF(last.rx() + pos.rx(), last.ry() + pos.ry());
}
