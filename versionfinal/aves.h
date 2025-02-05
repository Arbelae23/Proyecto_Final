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
    Aves(qreal initialX, qreal initialY, int movementType);// constructor
    QRectF boundingRect() const override;//area ocupada por el ave
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;//dibuja el sprite en la escena
    void updatePosition();  // controla como se mueve el ave
    void advance(int phase) override;  // Este metodo actualizara la posición automaticamente

private:
    QVector<QPixmap> m_imagesRight;  // Imágenes para el ave moviéndose a la derecha
    QVector<QPixmap> m_imagesLeft;   // Imágenes para el ave moviéndose a la izquierda
    bool m_isMovingRight;            // Bandera para saber si el ave se mueve a la derecha
    int m_animationFrame;            // Controla el fotograma de la animación
    qreal m_initialVelocityY;
    qreal m_velocityX;
    qreal m_velocityY;
    int m_movementType;              // Tipo de movimiento: 1 para parabólico, 2 para lateral
    qreal m_time;                    // Tiempo acumulado para el movimiento parabólico

    // Rango de coordenadas por donde se puede mover el ave
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
};

#endif // AVES_H


