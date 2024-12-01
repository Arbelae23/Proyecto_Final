#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>

class Particle : public QGraphicsItem
{
public:
    Particle(qreal initialX, qreal initialY);
    ~Particle() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    qreal velocity;
    qreal minX, maxX;
    qreal minY, maxY;

    QPixmap m_pixmap;
    QPixmap m_explosionPixmap;
    bool m_showExplosion;

    void triggerExplosion();
};

#endif // PARTICLE_H
