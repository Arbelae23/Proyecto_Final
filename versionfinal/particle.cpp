#include "Particle.h"
#include "Aves.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>
#include <QRandomGenerator>

Particle::Particle(qreal initialX, qreal initialY) :
    velocity(15.0), minX(0), maxX(1250), minY(0), maxY(700), m_color(Qt::blue),
    keyWPressed(false), keyAPressed(false), keySPressed(false), keyDPressed(false),
    m_showExplosion(false) // Inicializar la bandera de explosion
{
    setPos(initialX, initialY);
    setFlag(ItemIsFocusable); // permitir el enfoque para recibir eventos de teclado

    // Cargar la imagen de la partícula
    m_pixmap.load(":images/mira.png"); // ruta de la imagen de la partícula
    m_pixmap = m_pixmap.scaled(80, 80, Qt::KeepAspectRatio); // Escala la imagen manteniendo la relacion de aspecto
}

QRectF Particle::boundingRect() const
{
    return QRectF(0, 0, m_pixmap.width(), m_pixmap.height()); // Ajusta los limites visuales al tamaño de la imagen
}

void Particle::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->drawPixmap(0, 0, m_pixmap); // Dibuja la imagen de la partícula
    // Si se está mostrando la explosion, dibujarla en el centro de la partícula
    if (m_showExplosion) {
        qreal explosionX = -10;
        qreal explosionY = -10;
        painter->drawPixmap(explosionX, explosionY, m_explosionPixmap);
    }
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
    case Qt::Key_Space: // Espacio liberado
        m_showExplosion = false; // Ocultar explosión al soltar la tecla
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
    case Qt::Key_Space: // Tecla espacio presionada
        m_explosionPixmap.load(":images/explosion.png"); // Cargar imagen de explosion
        m_explosionPixmap = m_explosionPixmap.scaled(100, 100, Qt::KeepAspectRatio); // Escalar imagen de explosion
        m_showExplosion = true;

        // Verificar si hay colision con el ave cuando se presiona la tecla espacio
        if (auto scene = this->scene()) {
            for (auto item : scene->items()) {
                if (auto ave = dynamic_cast<Aves*>(item)) {
                    // Comprobar si la particula está lo suficientemente cerca del ave
                    if (boundingRect().intersects(ave->boundingRect())) {
                        // Tolerancia para la comparación de posiciones
                        if (qAbs(this->pos().x() - ave->pos().x()) < 30 && qAbs(this->pos().y() - ave->pos().y()) < 30) {
                            isParticleOverAve = true;
                            spaceKeyPressCount++;
                            for (auto sceneItem : scene->items()) {
                                if (auto textItem = dynamic_cast<QGraphicsTextItem*>(sceneItem)) {
                                    textItem->setPlainText( QString::number(spaceKeyPressCount)+ " /14" );
                                }
                            }
                            ave->setVisible(false); // Ocultar el ave

                            // Reposicionar el ave despues de un segundo
                            QTimer::singleShot(1000, [this, ave, scene]() {
                                ave->setVisible(true); // Rehabilitar el ave

                                // Reubicar el ave a una nueva posición aleatoria
                                ave->setPos(QRandomGenerator::global()->bounded(scene->width() - ave->boundingRect().width()),
                                            QRandomGenerator::global()->bounded(scene->height() - ave->boundingRect().height()));
                                scene->update(); // Actualizar escena
                            });
                        }
                    }
                }
            }
        }

        // Temporizador para ocultar la explosion después de 1 segundo.
        QTimer::singleShot(1000, [this]() {
            m_showExplosion = false;
            scene()->update(); // Actualizar escena
        });
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

void Particle::updatePosition() {
    if (keyWPressed) {
        moveUp();
    }
    if (keySPressed) {
        moveDown();
    }
    if (keyAPressed) {
        moveLeft();
    }
    if (keyDPressed) {
        moveRight();
    }

    // Asegurarse de que no se salga de los limites de la escena
    if (x() < minX) setPos(minX, y());
    if (x() > maxX - m_pixmap.width()) setPos(maxX - m_pixmap.width(), y());
    if (y() < minY) setPos(x(), minY);
    if (y() > maxY - m_pixmap.height()) setPos(x(), maxY - m_pixmap.height());

    scene()->update(); // Actualiza la escena
}
void Particle::triggerExplosion()
{
    m_explosionPixmap.load(":images/explosion.png");
    m_explosionPixmap = m_explosionPixmap.scaled(100, 100, Qt::KeepAspectRatio);
    m_showExplosion = true;

    // Temporizador para ocultar la explosión después de 1 segundo.
    QTimer::singleShot(250, [this]() {
        m_showExplosion = false;
        scene()->update();
    });

    scene()->update();
}
