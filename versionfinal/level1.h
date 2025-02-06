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
    void levelCompleted();//nivel completado
    void levelFailed();//nivel fallido

private slots:
    void updateScene();//actualizar la escena
    void updateTime();//actualizar el tiempo restante

private:
    QGraphicsScene *scene;
    Particle *particle;
    QGraphicsTextItem *textItemTiempo;
    QGraphicsTextItem *textItemAciertos;
    QGraphicsPixmapItem* gameOverItem;
    QTimer *movementTimer;
    QTimer *contadorTimer;
    QTimer *timer;

    int aciertos;
    int contador;

    void checkCompletion();//verifica si se ha completado el nivel
    void showGameOverScreen();
    void incrementarAciertos();//incrementa los aciertos
    void closeGame();
    void mouseMoveEvent(QMouseEvent *event) override;
protected:
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // LEVEL1_H
