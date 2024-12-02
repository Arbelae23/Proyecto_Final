#ifndef LEVEL1_H
#define LEVEL1_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QDebug>

#include "Particle.h"
#include "Aves.h"

class Level1 : public QGraphicsView
{
    Q_OBJECT

public:
    Level1(QWidget *parent = nullptr);

signals:
    void levelCompleted(); // Nivel completado
    void levelFailed();    // Nivel fallido

private slots:
    void updateScene();    // Actualiza la escena
    void updateTime();     // Actualiza el tiempo restante

private:
    QGraphicsScene *scene;
    Particle *particle;
    QGraphicsTextItem *textItemTiempo;
    QGraphicsTextItem *textItemAciertos;
    QTimer *movementTimer;
    QTimer *contadorTimer;
    QTimer *timer;

    int aciertos;
    int contador;

    void checkCompletion();    // Verifica si se ha completado el nivel
    void showGameOver();       // Muestra la pantalla de Game Over
    void incrementarAciertos(); // Incrementa los aciertos
};

#endif // LEVEL1_H
