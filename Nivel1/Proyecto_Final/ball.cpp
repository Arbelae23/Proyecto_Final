#include "ball.h"
#include <QTimer>

Ball::Ball(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), inAir(false)
{
    setPixmap(QPixmap("C:/Users/Miller Perez/Documents/Proyecto_Final/Sprites/pelota.png"));
    initialX = 50;
    initialY = 300;
    setPos(initialX, initialY);

    // Inicializar temporizador
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ball::updatePosition);
}

void Ball::launch()
{
    if (!inAir) {
        currentX = initialX;
        currentY = initialY;
        timer->start(50);  // Actualización de 50 ms
        inAir = true;
    }
}

void Ball::updatePosition()
{
    currentX += 10;    // Movimiento horizontal constante
    currentY -= 5;     // Movimiento vertical decreciente (parabólico)
    setPos(currentX, currentY);

    // Verificar si alcanzó el aro
    if (currentX > aroX && currentX < aroX + 30 && currentY < aroY + 20) {
        emit scored();   // Emitir señal de enceste
        resetPosition(); // Reiniciar posición
    }

    // Si la pelota sale de la pantalla, resetear
    if (currentX > 800 || currentY > 600) {
        resetPosition();
    }
}

void Ball::resetPosition()
{
    setPos(initialX, initialY);
    timer->stop();
    inAir = false;
}

bool Ball::isInAir() const
{
    return inAir;
}

void Ball::setAroPosition(int x, int y)
{
    aroX = x;
    aroY = y;
}
void Ball::setBallSize(qreal scale)
{
    setScale(scale); // Utiliza setScale para ajustar la escala de la imagen de la pelota
}
