#ifndef LEVEL2_H
#define LEVEL2_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QDebug>
#include "Particle.h"
#include "AvesCirculares.h"

class Level2 : public QGraphicsView
{
    Q_OBJECT

public:
    Level2(QWidget *parent = nullptr);

private:
    QGraphicsScene *scene;
    Particle *particle;
    QList<AvesCirculares *> aves;
    QTimer *timer;
    QTimer *movementTimer;
    QTimer *contadorTimer;
    QGraphicsTextItem *textItemAciertos;
    QGraphicsTextItem *textItemTiempo;
    QGraphicsPixmapItem* gameOverItem;
    int contador;
    int aciertos;
    void mouseMoveEvent(QMouseEvent *event) override;
    void checkCompletion();//verificar  si se ha completado el nivel
    void incrementarAciertos();//incrementar los aciertos
    void showGameOverScreen();//muestra la pantalla de Game Over
    void closeGame();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void updateScene();
    void updateCountdown();
signals:
    void levelCompleted();
};



#endif // LEVEL2_H
