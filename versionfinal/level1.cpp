#include "Level1.h"

Level1::Level1(QWidget *parent) : QGraphicsView(parent), aciertos(0), contador(90)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(115, 720); // Ajustar el tamaño de la vista

    // Agregar la imagen de fondo
    QPixmap backgroundPixmap(":images/fondonivel2.jpg");
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    backgroundItem->setPos(0, 0);
    scene->addItem(backgroundItem);

    // Cargar la imagen del cronómetro
    QPixmap cronometroPixmap(":images/cronometro.png");
    QPixmap scaledCronometroPixmap = cronometroPixmap.scaled(80, 80, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *cronometroItem = new QGraphicsPixmapItem(scaledCronometroPixmap);
    cronometroItem->setPos(1091, 10);
    scene->addItem(cronometroItem);

    // Fondo de aciertos
    QPixmap fondoPixmap(":images/fondo_aciertos.png");
    QPixmap scaledFondoPixmap = fondoPixmap.scaled(250, 100, Qt::IgnoreAspectRatio);
    QGraphicsPixmapItem *fondoItem = new QGraphicsPixmapItem(scaledFondoPixmap);
    fondoItem->setPos(1030, 605);
    scene->addItem(fondoItem);

    // Cargar la imagen del ave muerta
    QPixmap aveMuertaPixmap(":images/ave_muerta.png");
    QPixmap scaledAveMuertaPixmap = aveMuertaPixmap.scaled(100, 100, Qt::KeepAspectRatio);
    QGraphicsPixmapItem* aveMuertaItem = new QGraphicsPixmapItem(scaledAveMuertaPixmap);
    aveMuertaItem->setPos(1030,600);
    scene->addItem(aveMuertaItem);

    // Texto de tiempo restante
    textItemTiempo = new QGraphicsTextItem(QString::number(contador));
    textItemTiempo->setDefaultTextColor(Qt::black);
    textItemTiempo->setFont(QFont("Arial", 32));
    textItemTiempo->setPos(1160, 25);
    scene->addItem(textItemTiempo);

    // Texto de aciertos
    textItemAciertos = new QGraphicsTextItem(QString("0 / 15"));
    textItemAciertos->setDefaultTextColor(Qt::green);
    textItemAciertos->setFont(QFont("Arial", 37));
    textItemAciertos->setPos(1124, 620);
    scene->addItem(textItemAciertos);

    // Crear la particula o jugador
    particle = new Particle(100, 100);
    scene->addItem(particle);

    // Crear dos aves y agregarlas a la escena
    Aves *ave1 = new Aves(200, 200, 1);
    Aves *ave2 = new Aves(400, 200, 2);
    scene->addItem(ave1);
    scene->addItem(ave2);

    // Timer para mover las aves
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, [ave1, ave2]() {
        ave1->updatePosition();
        ave2->updatePosition();
    });
    movementTimer->start(50);

    // Timer para la cuenta regresiva del nivel
    contadorTimer = new QTimer(this);
    connect(contadorTimer, &QTimer::timeout, this, &Level1::updateTime);
    contadorTimer->start(1000);

    // Timer general para actualizar la escena
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Level1::updateScene);
    timer->start(50);
    connect(timer, &QTimer::timeout, [this]() {
        scene->advance();  // Avanza todos los objetos
        checkCompletion();
    });
}

void Level1::updateScene()
{
    checkCompletion();
}

void Level1::updateTime()
{
    if (contador > 0)
    {
        contador--;
        textItemTiempo->setPlainText(QString::number(contador));
    }
    else
    {
        contadorTimer->stop();
        movementTimer->stop();
        emit levelFailed(); // Emitir señal de nivel fallido si no se logró en el tiempo
    }
}

void Level1::checkCompletion()
{
    if (aciertos >= 15)
    {
        contadorTimer->stop();
        movementTimer->stop();
        emit levelCompleted(); // Emitir señal de nivel completado
    }
}

void Level1::incrementarAciertos()
{
    aciertos++;
    textItemAciertos->setPlainText(QString("%1 / 15").arg(aciertos));
    if (aciertos >= 15)
    {
        checkCompletion();
    }
}
