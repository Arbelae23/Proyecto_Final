#include "Aves.h"
#include <QPainter>
#include <QGraphicsScene>

Aves::Aves(qreal initialX, qreal initialY, const QString &imagePath, int movementType)
    : m_movementType(movementType),
    m_time(0.0),
    m_initialVelocityY(110.0), // Define la velocidad inicial hacia arriba
    m_bounceHeight(680) // Define la altura máxima
{
    m_imageRight.load("C:/Users/Maria.Lucia/Pictures/Sprites/Sprites/Ave_derecha.png");
    m_imageLeft.load("C:/Users/Maria.Lucia/Pictures/Sprites/Sprites/Ave_izquierda.png");
    //m_pixmap.load(imagePath); // Cargar la imagen del ave
    //m_pixmap = m_pixmap.scaled(60, 60, Qt::KeepAspectRatio); // Escalar la imagen
    m_imageRight = m_imageRight.scaled(60, 60, Qt::KeepAspectRatio);
    m_imageLeft = m_imageLeft.scaled(60, 60, Qt::KeepAspectRatio);
    setPos(initialX, initialY); // Posición inicial

    // Establecer velocidades aleatorias
    m_velocityX = (QRandomGenerator::global()->bounded(10) + 2) * (QRandomGenerator::global()->bounded(4) == 0 ? 1 : -1); // Velocidades aleatorias
    m_velocityY = (QRandomGenerator::global()->bounded(10) + 2) * (QRandomGenerator::global()->bounded(4) == 0 ? 1 : -1); // Velocidades aleatorias

    minX = 0; // Límites de la pantalla
    maxX = 1270; // Ancho de la pantalla
    minY = 0; // Límites de la pantalla
    maxY = 700; // Alto de la pantalla
}

QRectF Aves::boundingRect() const
{
    return QRectF(0, 0, m_pixmap.width(), m_pixmap.height()); // Ajustar el límite visual al tamaño de la imagen
}

void Aves::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, m_pixmap); // Dibuja la imagen del ave
}

void Aves::updatePosition()
{
    if (m_velocityX > 0) { // Se mueve a la derecha
        // Cambiar la imagen al ave moviéndose a la derecha
        m_pixmap = m_imageRight;
    } else { // Se mueve a la izquierda
        // Cambiar la imagen al ave moviéndose a la izquierda
        m_pixmap = m_imageLeft;
    }
    // Movimiento parabólico
    if (m_movementType == 1) // Movimiento parabólico
    {
        // Calculamos la nueva posición en Y usando la física del movimiento
        qreal newY = (m_initialVelocityY * m_time) - (0.5 * 9.81 * m_time * m_time);

        // Ajustar posición
        setPos(x() + m_velocityX, maxY - m_bounceHeight + newY); // Se asegura que el ave esté entre el piso y la altura de rebote

        // Verificamos si hemos alcanzado el suelo
        if (pos().y() >= maxY - m_pixmap.height()) { // Alcanza el piso
            setPos(x(), maxY - m_pixmap.height()); // Ajustar posición al suelo
            m_time = 0; // Reiniciar el tiempo para el siguiente rebote
        }
        else if (pos().y() <= maxY - m_bounceHeight) { // Al alcanzar la altura máxima
            setPos(x(), maxY - m_bounceHeight); // Ajustar la altura máxima
            m_time = 0; // Reiniciar el tiempo para el siguiente rebote
        }

        m_time += 0.1; // Aumentar el tiempo

        // Verificar los límites en el eje X
        if (x() < minX || x() > maxX - m_pixmap.width()) {
            m_velocityX *= -1; // Rebotar en el eje X
            // Ajusta la posición para que esté dentro de los límites
            setPos(qMax(minX, qMin(x(), maxX - m_pixmap.width())), pos().y());
        }
    }

    // Movimiento lateral
    if (m_movementType == 2) // Movimiento lateral
    {
        setPos(x() + m_velocityX, y() + m_velocityY); // Se mueve lateralmente y verticalmente

        // Límites de la escena para el movimiento lateral
        if (x() < minX || x() > maxX - m_pixmap.width())
        {
            m_velocityX *= -1; // Rebotar en el eje X
            setPos(qMax(minX, qMin(x(), maxX - m_pixmap.width())), y()); // Ajusta la posición para que esté dentro de los límites
        }

        if (y() < minY || y() > maxY - m_pixmap.height())
        {
            m_velocityY *= -1; // Rebotar en el eje Y
            setPos(x(), qMax(minY, qMin(y(), maxY - m_pixmap.height()))); // Ajusta la posición para que esté dentro de los límites
        }
    }

}
