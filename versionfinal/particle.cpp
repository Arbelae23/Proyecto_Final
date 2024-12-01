#include "Particle.h"
#include <QPainter>

Particle::Particle(qreal initialX, qreal initialY)
    : velocity(15.0), minX(0), maxX(1250), minY(0), maxY(700),
    m_showExplosion(false)
{
    setPos(initialX, initialY);
    setFlag(ItemIsFocusable);
    setFocus();

    m_pixmap.load(":/images/mira.png");
    m_pixmap = m_pixmap.scaled(80, 80, Qt::KeepAspectRatio);
}

Particle::~Particle() {}

QRectF Particle::boundingRect() const {
    return QRectF(0, 0, 80, 80);
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (m_showExplosion) {
        painter->drawPixmap(-40, -40, m_explosionPixmap);
    } else {
        painter->drawPixmap(-40, -40, m_pixmap);
    }
}

void Particle::updatePosition() {
    if (x() < minX) setX(minX);
    if (x() > maxX - boundingRect().width()) setX(maxX - boundingRect().width());
    if (y() < minY) setY(minY);
    if (y() > maxY - boundingRect().height()) setY(maxY - boundingRect().height());
}

void Particle::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        m_explosionPixmap.load(":/images/explosion.png");
        m_explosionPixmap = m_explosionPixmap.scaled(100, 100, Qt::KeepAspectRatio);
        m_showExplosion = true;

        QTimer::singleShot(1000, [this]() {
            m_showExplosion = false;
            scene()->update();
        });
    }
    scene()->update();
}
