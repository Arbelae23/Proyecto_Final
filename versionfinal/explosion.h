#ifndef EXPLOSION_H
#define EXPLOSION_H
#include<QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Explosion : public QGraphicsPixmapItem
{
public:
    Explosion(qreal x, qreal y);
};

#endif // EXPLOSION_H
