#ifndef LEVEL1_H
#define LEVEL1_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "Particle.h"
#include "AvesSencillas.h"

class Level1 : public QGraphicsView
{
    Q_OBJECT

public:
    Level1(QWidget *parent = nullptr);

signals:
    void levelCompleted();

private:
    QGraphicsScene *scene;
    Particle *particle;
    QList<AvesSencillas *> aves;
    QTimer *timer;
    int aciertos;

private slots:
    void updateScene();
    void checkCompletion();
};

#endif // LEVEL1_H
