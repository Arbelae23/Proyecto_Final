#include "Aves.h"
#include <QPainter>
#include <QGraphicsScene>

Aves::Aves(qreal initialX, qreal initialY, int movementType)
    : m_movementType(movementType),
    m_time(0.0),
    m_initialVelocityY(110.0),
    m_bounceHeight(680),
    m_animationFrame(0) // Inicializa el fotograma de animacion
{
    // Cargar las imágenes en los vectores
    for (int i = 1; i <= 3; ++i) {
        m_imagesRight.append(QPixmap(QString("C:/Users/Miller Perez/Documents/P_Final/Sprites/Ave_derecha_%1.png").arg(i)));
        m_imagesLeft.append(QPixmap(QString("C:/Users/Miller Perez/Documents/P_Final/Sprites/Ave_izquierda_%1.png").arg(i)));
    }

    setPos(initialX, initialY); // Posición inicial

    // Establecer velocidades aleatorias
    m_velocityX = (QRandomGenerator::global()->bounded(10) + 2) * (QRandomGenerator::global()->bounded(4) == 0 ? 1 : -1);
    m_velocityY = (QRandomGenerator::global()->bounded(10) + 2) * (QRandomGenerator::global()->bounded(4) == 0 ? 1 : -1);

    // Límites de la pantalla
    minX = 0;
    maxX = 1270;
    minY = 0;//
    maxY = 700;
}

QRectF Aves::boundingRect() const
{
    return QRectF(0, 0, 60, 60); // Ajustar el limite visual al tamaño de la imagen
}

void Aves::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_isMovingRight) {
        painter->drawPixmap(0, 0, m_imagesRight[m_animationFrame].scaled(80, 80)); // Dibujar la imagen del ave moviendose a la derecha
    } else {
        painter->drawPixmap(0, 0, m_imagesLeft[m_animationFrame].scaled(80, 80)); // Dibujar la imagen del ave moviendose a la izquierda
    }
}

void Aves::updatePosition()
{
    // Cambiar el fotograma de animación
    m_animationFrame = (m_animationFrame + 1) % 3; // Cambiar entre 0, 1, 2

    if (m_velocityX > 0) { // Se mueve a la derecha
        m_isMovingRight = true; // Actualizar el estado de movimiento
    } else { // Se mueve a la izquierda
        m_isMovingRight = false; // Actualizar el estado de movimiento
    }

    // Movimiento parabolico
    if (m_movementType == 1) // Movimiento parabolico
    {
        qreal newX = x() + m_velocityX; // Calcular la nueva posicion en X
        qreal newY = (m_initialVelocityY * m_time) - (0.5 * 9.81 * m_time * m_time); // Calcular la nueva posicion en Y con una simulacion de gravedad

        // Ajustar la posición en X dentro de los limites
        if (newX < minX || newX > maxX - 80) {
            m_velocityX = -m_velocityX; // Invertir la direccion en el eje X para simular el rebote
        }

        // Verificar y ajustar el rebote en el techo
        if (newY <= 0) {
            newY = 0; // Rebote en el techo
            m_velocityY = -m_velocityY; // Invertir la dirección en el eje Y para simular el rebote
            m_time = 0; // Reiniciar el tiempo para evitar que la ave siga subiendo
        }

        // Actualizar la posición de la ave
        setPos(newX, newY);

        // Verificar el rebote en el suelo
        if (newY >= maxY - m_imagesRight[0].height()) {
            m_time = 0; // Reiniciar el tiempo para el proximo rebote
        }

        m_time += 0.1;
    }

    if (m_movementType == 2) // Movimiento lateral
    {
        setPos(x() + m_velocityX, y() + m_velocityY); // Se mueve lateralmente y verticalmente

        // Límites de la escena para el movimiento lateral
        if (x() < minX || x() > maxX - 60) {
            m_velocityX *= -1; // Rebotar en el eje X
            setX(qMax(minX, qMin(x(), maxX - 60))); // Ajustar la posición para que esté dentro de los limites
        }

        if (y() < minY || y() > maxY - m_imagesRight[0].height()) {
            m_velocityY *= -1; // Rebotar en el eje Y
            setY(qMax(minY, qMin(y(), maxY - m_imagesRight[0].height()))); // Ajustar la posición para que este dentro de los límites
        }
    }
}
