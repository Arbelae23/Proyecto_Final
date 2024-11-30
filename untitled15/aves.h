#ifndef AVES_H
#define AVES_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>

class Aves : public QGraphicsItem
{
public:
    Aves(qreal initialX, qreal initialY, const QString &imagePath, int movementType);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition(); // Método para actualizar la posición

private:
    QPixmap m_pixmap; // Para almacenar la imagen del ave
    QPixmap m_imageRight; // Imagen para el ave moviéndose a la derecha
    QPixmap m_imageLeft; // Imagen para el ave moviéndose a la izquierda
    bool m_isMovingRight; // Flag para saber si el ave se está moviendo a la derecha

    qreal m_velocityX;
    qreal m_velocityY;
    int m_movementType; // Tipo de movimiento: 0 para diagonal, 1 para parabólico
    qreal m_initialVelocityY; // Velocidad vertical inicial
    qreal m_time; // Tiempo transcurrido en el movimiento
    qreal m_bounceHeight; // Altura máxima a la que rebotará el ave
    qreal m_velocityXParabólico; // Velocidad en el eje X para el movimiento parabólico
    qreal m_velocityXLateral; // Velocidad en el eje X para el movimiento lateral

    // Limites de la pantalla
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
};

#endif // AVES_H
