#include "Level1.h"
#include "Explosion.h"

Level1::Level1(QWidget *parent) : QGraphicsView(parent), aciertos(0)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    QPixmap backgroundPixmap(":/images/fondonivel1.jpg");
    scene->addPixmap(backgroundPixmap);

    particle = new Particle(100, 100);
    scene->addItem(particle);

    for (int i = 0; i < 3; i++) {
        AvesSencillas *ave = new AvesSencillas(400 + i * 100, 300);
        aves.append(ave);
        scene->addItem(ave);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level1::updateScene);
    timer->start(50);
}

void Level1::updateScene()
{
    particle->updatePosition();
    for (AvesSencillas *ave : aves) {
        ave->updatePosition();
        if (particle->collidesWithItem(ave)) {
            scene->addItem(new Explosion(ave->x(), ave->y()));
            scene->removeItem(ave);
            aves.removeOne(ave);
            delete ave;
            aciertos++;
            checkCompletion();
            break;
        }
    }
    scene->update();
}

void Level1::checkCompletion()
{
    if (aciertos >= 3) {
        emit levelCompleted();
    }
}
