#ifndef LEVEL2_H
#define LEVEL2_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
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
    int contador;

private slots:
    void updateScene();
    void updateCountdown();
};

#endif // LEVEL2_H
