#include "Particle.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>

Particle::Particle(qreal initialX, qreal initialY) :
    velocity(15.0), minX(0), maxX(1250), minY(0), maxY(700), m_color(Qt::blue),
    keyWPressed(false), keyAPressed(false), keySPressed(false), keyDPressed(false)
{
    setPos(initialX, initialY);
    setFlag(ItemIsFocusable); // permitir el enfoque para recibir eventos de teclado

    // Cargar la imagen de la partícula
    m_pixmap.load("C:/Users/Miller Perez/Documents/Intento_Juego/Sprites/Mira.png"); // ruta de la imagen de la partícula

    // Redimensionar la imagen a 80x80 píxeles (o el tamaño deseado)
    m_pixmap = m_pixmap.scaled(80, 80, Qt::KeepAspectRatio); // Escala la imagen manteniendo la relación de aspecto
}

QRectF Particle::boundingRect() const
{
    return QRectF(0, 0, m_pixmap.width(), m_pixmap.height()); // Ajusta los límites visuales al tamaño de la imagen
}

void Particle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(0, 0, m_pixmap);
}

void Particle::moveLeft()
{
    setPos(x() - velocity, y());
}

void Particle::moveRight()
{
    setPos(x() + velocity, y());
}

void Particle::moveUp()
{
    setPos(x(), y() - velocity);
}

void Particle::moveDown()
{
    setPos(x(), y() + velocity);
}

void Particle::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        keyAPressed = false;
        break;
    case Qt::Key_D:
        keyDPressed = false;
        break;
    case Qt::Key_W:
        keyWPressed = false;
        break;
    case Qt::Key_S:
        keySPressed = false;
        break;
    default:
        break;
    }
}

void Particle::keyPressEvent(QKeyEvent* event)
{
    setFocus();

    switch (event->key())
    {
    case Qt::Key_A:
        keyAPressed = true;
        break;
    case Qt::Key_D:
        keyDPressed = true;
        break;
    case Qt::Key_W:
        keyWPressed = true;
        break;
    case Qt::Key_S:
        keySPressed = true;
        break;
    default:
        break;
    }

    // Movimiento diagonal
    if (keyWPressed && keyDPressed) { // Diagonal hacia arriba a la derecha
        moveRight();
        moveUp();
    }
    else if (keyWPressed && keyAPressed) { // Diagonal hacia arriba a la izquierda
        moveLeft();
        moveUp();
    }
    else if (keySPressed && keyDPressed) { // Diagonal hacia abajo a la derecha
        moveRight();
        moveDown();
    }
    else if (keySPressed && keyAPressed) { // Diagonal hacia abajo a la izquierda
        moveLeft();
        moveDown();
    }
    // Movimiento individual
    if (keyWPressed && !keyDPressed && !keyAPressed) {
        moveUp();
    }
    else if (keyDPressed && !keyWPressed && !keySPressed) {
        moveRight();
    }
    else if (keySPressed && !keyWPressed && !keyDPressed) {
        moveDown();
    }
    else if (keyAPressed && !keyWPressed && !keySPressed) {
        moveLeft();
    }

    // Asegurarse de que no se salga de los límites de la escena
    if (x() < minX) setPos(minX, y());
    if (x() > maxX - m_pixmap.width()) setPos(maxX - m_pixmap.width(), y());
    if (y() < minY) setPos(x(), minY);
    if (y() > maxY - m_pixmap.height()) setPos(x(), maxY - m_pixmap.height());

    scene()->update(); // Actualiza la escena
}
