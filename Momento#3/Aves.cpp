#include "Aves.h"
#include <QPainter>
#include <QGraphicsScene>

Aves::Aves(qreal initialX, qreal initialY, const QString &imagePath, int movementType)
    : m_movementType(movementType)
{
    m_pixmap.load(imagePath); // Cargar la imagen del ave
    m_pixmap = m_pixmap.scaled(60, 60, Qt::KeepAspectRatio); // Escalar la imagen

    setPos(initialX, initialY); // Posición inicial

    // Establecer velocidades aleatorias
    m_velocityX = (QRandomGenerator::global()->bounded(5) + 3) * (QRandomGenerator::global()->bounded(2) == 0 ? 1 : -1); // Velocidades aleatorias
    m_velocityY = (QRandomGenerator::global()->bounded(5) + 3) * (QRandomGenerator::global()->bounded(2) == 0 ? 1 : -1); // Velocidades aleatorias

    minX = 0; // Limites de la pantalla
    maxX = 1250; // Asumir un ancho de 800
    minY = 0; // Limites de la pantalla
    maxY = 700; // Asumir un alto de 600
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
    if (m_movementType == 0) // Movimiento diagonal
    {
        setPos(x() + m_velocityX, y() + m_velocityY);
    }
    else if (m_movementType == 1) // Movimiento parabólico
    {
        qreal newY = y() + m_velocityY; // Movimiento vertical
        // Implementar fisica para movimiento parabolico
        setPos(x() + m_velocityX, newY);
    }

    //límites de la escena
    if (x() < minX || x() > maxX - m_pixmap.width())
    {
        m_velocityX *= -1; // Rebotar en el eje X
    }
    if (y() < minY || y() > maxY - m_pixmap.height())
    {
        m_velocityY *= -1; // Rebotar en el eje Y
    }
}
