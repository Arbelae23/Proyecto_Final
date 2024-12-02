#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Ball : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Ball(QGraphicsItem *parent = nullptr);  // Constructor
    void launch();                          // Inicia el movimiento parabólico
    void resetPosition();                   // Restablece la posición inicial
    bool isInAir() const;                   // Verifica si la pelota está en el aire
    void setAroPosition(int aroX, int aroY); // Establece la posición del

    void setBallSize(qreal scale);  // Declaración del método para cambiar el tamaño de la imagen de la pelota

signals:
    void scored();  // Señal para notificar cuando se encesta

private slots:
    void updatePosition();  // Actualiza la posición en el aire

private:
    int initialX;
    int initialY;
    int currentX;
    int currentY;
    bool inAir;
    QTimer *timer;
    int aroX, aroY;  // Posición del aro
};

#endif // BALL_H
