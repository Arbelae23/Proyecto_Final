#include "Explosion.h"

Explosion::Explosion(qreal x, qreal y)
{
    setPixmap(QPixmap(":/images/explosion.png").scaled(80, 80, Qt::KeepAspectRatio));
    setPos(x, y);

    QTimer::singleShot(500, [this]() {
        if (scene()) {
            scene()->removeItem(this);
        }
        delete this;
    });
}
