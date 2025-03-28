#include "Aves.h"
#include <QPainter>
#include <QGraphicsScene>

Aves::Aves(qreal initialX, qreal initialY, int movementType)
    : m_movementType(movementType),
    m_time(0.0),
    m_animationFrame(0),
    m_isMovingRight(true)
{
    // Cargar las imágenes en los vectores
    for (int i = 1; i <= 3; ++i) {
        m_imagesRight.append(QPixmap(QString(":images/Ave_derecha_%1.png").arg(i)));
        m_imagesLeft.append(QPixmap(QString(":images/Ave_izquierda_%1.png").arg(i)));
    }

    setPos(initialX, initialY);  // Posición inicial

    // Establecer velocidades aleatorias
    m_velocityX = (QRandomGenerator::global()->bounded(4) + 2) * (QRandomGenerator::global()->bounded(2) == 0 ? 1 : -1);
    m_velocityY = (QRandomGenerator::global()->bounded(4) + 2) * (QRandomGenerator::global()->bounded(2) == 0 ? 1 : -1);

    // Límites de la pantalla
    minX = 0;
    maxX = 1350;
    minY = 0;
    maxY = 710;
}

QRectF Aves::boundingRect() const
{
    return QRectF(0, 0, 80, 80);  // Ajustar el límite visual al tamaño de la imagen
}

void Aves::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_isMovingRight) {
        painter->drawPixmap(0, 0, m_imagesRight[m_animationFrame].scaled(80, 80));
    } else {
        painter->drawPixmap(0, 0, m_imagesLeft[m_animationFrame].scaled(80, 80));
    }
}

void Aves::advance(int phase)
{
    if (!phase) return;//en la fase 0 no hacemos nada

    //cambiar el fotograma de animacion
    m_animationFrame = (m_animationFrame + 1) % 3;

    if (m_velocityX > 0) {
        m_isMovingRight = true;
    } else {
        m_isMovingRight = false;
    }

    if (m_movementType == 1)  //movimiento parabolico
    {
        qreal newX = x() + m_velocityX;
        qreal newY = y() + m_velocityY * m_time - (0.5 * 9.81 * m_time * m_time);

        // Ajustar límites
        if (newX < minX || newX > maxX - 80) {
            m_velocityX = -m_velocityX;
        }

        if (newY > maxY) {
            newY = maxY;
            m_time = 0;  // Reiniciar el tiempo para el próximo rebote
        }

        setPos(newX, newY);
        m_time += 0.05;
    }
    else if (m_movementType == 2)  // Movimiento lateral y vertical
    {
        setPos(x() + m_velocityX, y() + m_velocityY);

        if (x() < minX || x() > maxX - 80) {
            m_velocityX = -m_velocityX;
        }

        if (y() < minY || y() > maxY - 80) {
            m_velocityY = -m_velocityY;
        }
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
