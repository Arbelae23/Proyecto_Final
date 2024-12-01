#include "Level2.h"

Level2::Level2(QWidget *parent)
    : QGraphicsView(parent), contador(60)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    QPixmap backgroundPixmap(":/images/fondonivel2.jpg");
    scene->addPixmap(backgroundPixmap);

    particle = new Particle(100, 100);
    scene->addItem(particle);

    for (int i = 0; i < 3; i++) {
        AvesCirculares *ave = new AvesCirculares(400 + i * 100, 300);
        aves.append(ave);
        scene->addItem(ave);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level2::updateScene);
    timer->start(50);

    QTimer *countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &Level2::updateCountdown);
    countdownTimer->start(1000);
}

void Level2::updateScene()
{
    particle->updatePosition();
    for (AvesCirculares *ave : aves) {
        ave->updatePosition();
    }
    scene->update();
}

void Level2::updateCountdown()
{
    if (contador > 0) {
        contador--;
    } else {
        QGraphicsTextItem *text = new QGraphicsTextItem("Game Over");
        text->setDefaultTextColor(Qt::red);
        text->setFont(QFont("Arial", 48));
        text->setPos(200, 200);
        scene->addItem(text);
        timer->stop();
    }
}
