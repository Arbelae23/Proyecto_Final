#ifndef AVESCIRCULARES_H
#define AVESCIRCULARES_H

#include "Aves.h"
#include <cmath>


class AvesCirculares : public Aves {
public:
    AvesCirculares(qreal x, qreal y, int tipo);
    void updatePosition();
    void advance(int phase) override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setCenter(qreal x, qreal y);

    qreal centerX;
    qreal centerY;
    qreal angle;
    qreal radius;
    qreal angularVelocity;
private:

};

#endif // AVESCIRCULARES_H
