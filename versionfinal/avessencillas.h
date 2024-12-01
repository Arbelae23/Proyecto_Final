#ifndef AVESSENCILLES_H
#define AVESSENCILLES_H

#include <QGraphicsPixmapItem>

class AvesSencillas : public QGraphicsPixmapItem
{
public:
    AvesSencillas(qreal startX, qreal startY);
    void updatePosition();

private:
    qreal dx;
};

#endif // AVESSENCILLES_H
