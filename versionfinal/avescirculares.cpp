#include "AvesCirculares.h"
#include <QPainter>
#include <cmath>

AvesCirculares::AvesCirculares(qreal x, qreal y, int tipo)
    : Aves(x, y, tipo), centerX(x), centerY(y), radius(50), angle(0), angularVelocity(0.3) {

    for (int i = 1; i <= 3; ++i) {
        m_imagesRight.append(QPixmap(QString(":images/Ave_derecha_%1.png").arg(i)));
        m_imagesLeft.append(QPixmap(QString(":images/Ave_izquierda_%1.png").arg(i)));
    }
}

void AvesCirculares::advance(int phase) {
    if (!phase) return;


    m_animationFrame = (m_animationFrame + 1) % 3;


    angle += angularVelocity;
    if (angle >= 2 * M_PI) angle -= 2 * M_PI;

    // Calcular la nueva posición en el círculo
    qreal newX = centerX + radius * std::cos(angle);
    qreal newY = centerY + radius * std::sin(angle);

    // Determinar la dirección de la imagen
    m_isMovingRight = (std::cos(angle) >= 0);

    setPos(newX, newY);
}

void AvesCirculares::updatePosition() {
    advance(1);  // Llamar a advance para actualizar la posición y animación
}

QRectF AvesCirculares::boundingRect() const {
    return QRectF(0, 0, 80, 80);
}

void AvesCirculares::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_isMovingRight) {
        painter->drawPixmap(0, 0, m_imagesRight[m_animationFrame].scaled(80, 80));
    } else {
        painter->drawPixmap(0, 0, m_imagesLeft[m_animationFrame].scaled(80, 80));
    }
}
void AvesCirculares::setCenter(qreal x, qreal y) {
    centerX = x;
    centerY = y;
    angle = 0;
}

