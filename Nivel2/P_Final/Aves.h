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
    Aves(qreal initialX, qreal initialY, int movementType);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition(); // Metodo para actualizar la posicion

private:
    QVector<QPixmap> m_imagesRight; // Imágenes para el ave moviendose a la derecha
    QVector<QPixmap> m_imagesLeft;  // Imágenes para el ave moviéndose a la izquierda
    bool m_isMovingRight; // Flag para saber si el ave se está moviendo a la derecha
    int m_animationFrame; // Controla el fotograma de la animacion

    qreal m_velocityX;
    qreal m_velocityY;
    int m_movementType; // Tipo de movimiento: 0 para diagonal, 1 para parabólico
    qreal m_initialVelocityY; // Velocidad vertical inicial
    qreal m_time; // Tiempo transcurrido en el movimiento
    qreal m_bounceHeight; // Altura máxima a la que rebotará el ave
    //Rango de cordenadas por sonde se puede mover el ave
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
};

#endif // AVES_H
