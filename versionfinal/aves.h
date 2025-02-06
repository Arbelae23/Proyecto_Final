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
    void updatePosition();//controla como se mueve el ave
    void advance(int phase) override;//actualizar la posicion automaticamente
    QVector<QPixmap> m_imagesRight;  // imagenes para el ave moviendose a la derecha
    QVector<QPixmap> m_imagesLeft;   //imagenes para el ave moviendose a la izquierda
    bool m_isMovingRight; //bandera para saber si el ave se mueve a la derecha
    int m_animationFrame; //controla la animacion
    qreal m_initialVelocityY;
    qreal m_velocityX;
    qreal m_velocityY;
    int m_movementType;//tipo de movimiento 1 para parabolico 2 para lateral
    qreal m_time;//tiempo acumulado para el movimiento parabolico

private:

    //rango de coordenadas por donde se puede mover el ave
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
};

#endif // AVES_H


