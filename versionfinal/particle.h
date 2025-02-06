#ifndef PARTICLE_H
#define PARTICLE_H

#include <QPixmap>
#include <QGraphicsItem>
#include <QRectF> // Rectangulo que limita
#include <QPainter> // Pintar o renderizar formas
#include <QKeyEvent>

class Aves; // Declaración anticipada de la clase Aves

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
    void checkCollision(Aves* ave); // Método para verificar colision

    // Cambiar updatePosition a publico
    void updatePosition(); // Método para actualizar la posición
    void triggerExplosion();

protected:
    void keyPressEvent(QKeyEvent* event) override; // Evento de tecla presionada
    void keyReleaseEvent(QKeyEvent* event) override; // Evento de tecla liberada

private:
    // Atributos privados sobre velocidad, limites y color.
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

    QPixmap m_pixmap;//atributo para almacenar la imagen de la particula

   //nuevos atributos para manejar la explosion
    bool m_showExplosion;//bandera para mostrar la explosion
    QPixmap m_explosionPixmap;//imagen de la explosion

    int spaceKeyPressCount = 0;//contador de veces que se oprime la tecla "Espacio" en la misma posicion
    bool isParticleOverAve = false;//variable para verificar si la particula y el ave estan en la misma posicion
};

#endif // PARTICLE_H
