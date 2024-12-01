#include "AvesSencillas.h"

AvesSencillas::AvesSencillas(qreal startX, qreal startY)
    : QGraphicsPixmapItem(), dx(2)
{
    setPixmap(QPixmap(":/images/Ave.png").scaled(80, 80, Qt::KeepAspectRatio));
    setPos(startX, startY);
}

void AvesSencillas::updatePosition()
{
    setX(x() + dx);
    if (x() < 0 || x() > 800) {
        dx = -dx;
    }
}
