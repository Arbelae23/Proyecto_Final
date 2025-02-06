#include "Level2.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QApplication>

Level2::Level2(QWidget *parent)
    : QGraphicsView(parent), contador(60), aciertos(0)
{
    scene = new QGraphicsScene(this);
    setScene(scene);

    QPixmap backgroundPixmap(":/images/fondonivel2.jpg");
    scene->addPixmap(backgroundPixmap);

    particle = new Particle(100, 100);
    scene->addItem(particle);
    setMouseTracking(true);
    setCursor(Qt::CrossCursor);

    QPixmap cronometroPixmap(":images/cronometro.png");
    QPixmap scaledCronometroPixmap = cronometroPixmap.scaled(80, 80, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *cronometroItem = new QGraphicsPixmapItem(scaledCronometroPixmap);
    cronometroItem->setPos(1091, 10);
    scene->addItem(cronometroItem);

    QPixmap aveMuertaPixmap(":images/ave_muerta.png");
    QPixmap scaledAveMuertaPixmap = aveMuertaPixmap.scaled(100, 100, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *aveMuertaItem = new QGraphicsPixmapItem(scaledAveMuertaPixmap);
    aveMuertaItem->setPos(1030, 600);
    scene->addItem(aveMuertaItem);

    AvesCirculares *ave1 = new AvesCirculares(200, 200, 1);
    AvesCirculares *ave2 = new AvesCirculares(500, 430, 1);
    scene->addItem(ave1);
    scene->addItem(ave2);

    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, [ave1, ave2]() {
        ave1->updatePosition();
        ave2->updatePosition();
    });
    movementTimer->start(50);

    contadorTimer = new QTimer(this);
    connect(contadorTimer, &QTimer::timeout, this, &Level2::updateCountdown);
    contadorTimer->start(1000);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level2::updateScene);
    timer->start(50);

    textItemTiempo = new QGraphicsTextItem(QString::number(contador));
    textItemTiempo->setDefaultTextColor(Qt::white);
    textItemTiempo->setFont(QFont("Arial", 32));
    textItemTiempo->setPos(1160, 25);
    scene->addItem(textItemTiempo);

    QPixmap fondoPixmap(":images/fondo_aciertos.png");
    QPixmap scaledFondoPixmap = fondoPixmap.scaled(250, 100, Qt::IgnoreAspectRatio);
    QGraphicsPixmapItem *fondoItem = new QGraphicsPixmapItem(scaledFondoPixmap);
    fondoItem->setPos(1030, 605);
    scene->addItem(fondoItem);

    textItemAciertos = new QGraphicsTextItem(QString("0 / 15"));
    textItemAciertos->setDefaultTextColor(Qt::green);
    textItemAciertos->setFont(QFont("Arial", 37));
    textItemAciertos->setPos(1124, 620);
    scene->addItem(textItemAciertos);
}

void Level2::updateScene()
{
   checkCompletion();
}

void Level2::updateCountdown()
{
    if (contador > 0) {
        contador--;
        textItemTiempo->setPlainText(QString::number(contador));
    } else {
        QGraphicsPixmapItem *gameOverItem = new QGraphicsPixmapItem(QPixmap(":/images/game_over.png"));
        gameOverItem->setPos(200, 200);
        scene->addItem(gameOverItem);

        timer->stop();
        contadorTimer->stop();

        QTimer::singleShot(2000, this, []() {
            QApplication::quit();
        });
    }
}
void Level2::checkCompletion()
{
    if (aciertos >= 15) {
        QGraphicsPixmapItem *winItem = new QGraphicsPixmapItem(QPixmap(":/images/you_win.png"));
        winItem->setPos(200, 200);
        scene->addItem(winItem);

        timer->stop();
        contadorTimer->stop();

        QTimer::singleShot(2000, []() {
            QApplication::quit();
        });
    }
}

void Level2::incrementarAciertos()
{
    aciertos++;
    textItemAciertos->setPlainText(QString("%1 / 15").arg(aciertos));
    if (aciertos >= 15) {
        checkCompletion();
    }
}

void Level2::mouseMoveEvent(QMouseEvent *event)
{
    if (particle) {
        QPointF mousePos = mapToScene(event->pos());
        qreal offsetX = particle->boundingRect().width() / 2;
        qreal offsetY = particle->boundingRect().height() / 2;
        particle->setPos(mousePos.x() - offsetX, mousePos.y() - offsetY);
    }
}

void Level2::mousePressEvent(QMouseEvent *event)
{
    QPointF mousePos = mapToScene(event->pos());
    QList<QGraphicsItem *> itemsUnderCursor = scene->items(mousePos);

    if (particle) {
        particle->triggerExplosion();
    }

    for (QGraphicsItem *item : itemsUnderCursor) {
        AvesCirculares *ave = dynamic_cast<AvesCirculares *>(item);
        if (ave) {
            qreal newX = QRandomGenerator::global()->bounded(100, 900);
            qreal newY = QRandomGenerator::global()->bounded(100, 500);

            ave->setPos(newX, newY);
            ave->setCenter(newX, newY);

            incrementarAciertos();
            return;
        }
    }
}
