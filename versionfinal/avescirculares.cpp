#include "AvesCirculares.h"

AvesCirculares::AvesCirculares(qreal centerX, qreal centerY)
    : centerX(centerX), centerY(centerY), angle(0), radius(100)
{
    setPixmap(QPixmap(":/images/ave_derecha.png").scaled(80, 80, Qt::KeepAspectRatio));
}

void AvesCirculares::updatePosition()
{
    angle += 0.05;
    qreal x = centerX + radius * std::cos(angle);
    qreal y = centerY + radius * std::sin(angle);
    setPos(x, y);
}
