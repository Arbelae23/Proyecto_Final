#ifndef AVESCIRCULARES_H
#define AVESCIRCULARES_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cmath>

class AvesCirculares : public QGraphicsPixmapItem
{
public:
    AvesCirculares(qreal centerX, qreal centerY);
    void updatePosition();

private:
    qreal centerX;
    qreal centerY;
    qreal angle;
    qreal radius;
};

#endif // AVESCIRCULARES_H
