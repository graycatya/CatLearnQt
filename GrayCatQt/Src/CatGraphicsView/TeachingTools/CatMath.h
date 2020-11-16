#ifndef CATMATH_H
#define CATMATH_H

#include <QtGlobal>
#include <QVector2D>

namespace CatMath {
    qreal CmtoPx(qreal cm);
    qreal PxtoCm(qreal px);
    qreal DegreeAngle(QVector2D vector2d);

    // 已知圆心，半径，角度，求圆上的点坐标
    QPointF PointCoordinatesOnACircle(QPointF centerpoint, qreal r, qreal angle);

    // 旋转角度转换，将大于360，与小于0的角度进行极值判断
    qreal AngleJudge(qreal angle);

    // 勾股定理
    qreal PythagoreanTheorem(qreal a, qreal b);

    // 计算 靠近A点 角度方法
    /*
                B____C
                |  /
                |_/
                |/
                A
    */
    // 根据tan算出角度
    qreal TanToAngle(qreal bc, qreal ab);
    // 根据cos算出角度
    qreal CosToAngle(qreal ab, qreal ac);
    // 根据sin算出角度
    qreal SinToAngle(qreal bc, qreal ac);

    QPointF PosMove(QPointF last, QPointF pos);
}



#endif // CATMATH_H
