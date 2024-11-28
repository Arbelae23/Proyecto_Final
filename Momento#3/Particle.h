#ifndef PARTICLE_H
#define PARTICLE_H

#include <QPixmap>
#include <QGraphicsItem>
#include <QRectF> // Rectángulo que limita
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
    void checkCollision(Aves* ave); // Método para verificar colisión

    // Cambiar updatePosition a público
    void updatePosition(); // Método para actualizar la posición

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

    // Nuevos atributos para manejar la explosión
    bool m_showExplosion; // Bandera para mostrar la explosión
    QPixmap m_explosionPixmap; // Imagen de la explosión

    int spaceKeyPressCount = 0; // Contador de veces que se oprime la tecla "Espacio" en la misma posición del ave
    bool isParticleOverAve = false; // Variable para verificar si la partícula y el ave están en la misma posición
};

#endif // PARTICLE_H
