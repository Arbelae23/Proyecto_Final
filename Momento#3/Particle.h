#ifndef PARTICLE_H
#define PARTICLE_H

#include <QPixmap>
#include <QGraphicsItem>
#include <QRectF> // Rectángulo que limita
#include <QPainter> // Pintar o renderizar formas
#include <QKeyEvent>

class Particle : public QGraphicsItem
{
public:
    // Constructor
    Particle(qreal initialX, qreal initialY);
    QRectF boundingRect() const override; // Rectángulo delimitador
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    // Funciones para el movimiento.
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

protected:
    void keyPressEvent(QKeyEvent* event) override; // Evento de tecla presionada
    void keyReleaseEvent(QKeyEvent* event) override; // Evento de tecla liberada

private:
    // Atributos privados sobre velocidad, límites y color.
    qreal velocity;
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
    QColor m_color;

    // Estados de las teclas
    bool keyWPressed;
    bool keyAPressed;
    bool keySPressed;
    bool keyDPressed;

    QPixmap m_pixmap; // Atributo para almacenar la imagen de la partícula
};

#endif // PARTICLE_H
