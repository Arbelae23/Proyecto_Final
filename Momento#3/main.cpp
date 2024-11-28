#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>

#include "Particle.h"
#include "Aves.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear la ventana
    QGraphicsView view;
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Crear una escena para manejar elementos gráficos
    QGraphicsScene scene;
    view.setScene(&scene);

    // Agregar la imagen de fondo
    QPixmap backgroundPixmap("C:/Users/Miller Perez/Documents/P_Final/Sprites/Background.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    backgroundItem->setPos(0, 0);
    scene.addItem(backgroundItem);

    // Cargar la imagen del cronómetro
    QPixmap cronometroPixmap("C:/Users/Miller Perez/Documents/P_Final/Sprites/cronometro.png");
    QPixmap scaledCronometroPixmap = cronometroPixmap.scaled(80, 80, Qt::KeepAspectRatio);
    QGraphicsPixmapItem* cronometroItem = new QGraphicsPixmapItem(scaledCronometroPixmap);
    cronometroItem->setPos(1091, 10);
    scene.addItem(cronometroItem);

    // Cargar la imagen del fondo de aciertos
    QPixmap fondoPixmap("C:/Users/Miller Perez/Documents/P_Final/Sprites/fondo_aciertos.png");
    QPixmap scaledFondoPixmap = fondoPixmap.scaled(250, 100, Qt::IgnoreAspectRatio);
    QGraphicsPixmapItem* fondoItem = new QGraphicsPixmapItem(scaledFondoPixmap);
    fondoItem->setPos(1030, 605);
    scene.addItem(fondoItem);

    // Cargar la imagen del ave muerta
    QPixmap aveMuertaPixmap("C:/Users/Miller Perez/Documents/P_Final/Sprites/ave_muerta.png");
    QPixmap scaledAveMuertaPixmap = aveMuertaPixmap.scaled(100, 100, Qt::KeepAspectRatio);
    QGraphicsPixmapItem* aveMuertaItem = new QGraphicsPixmapItem(scaledAveMuertaPixmap);
    aveMuertaItem->setPos(1030,600);
    scene.addItem(aveMuertaItem);



    // Agregar la partícula o jugador
    Particle* particle = new Particle(100, 100);
    scene.addItem(particle);

    // Crear una ave y agregarla a la escena
    Aves* ave = new Aves(200, 200, "C:/Users/Miller Perez/Documents/P_Final/Sprites/Ave.png", 1);
    scene.addItem(ave);

    // Crear la segunda ave y agregarla a la escena
    Aves* ave2 = new Aves(200, 200, "C:/Users/Miller Perez/Documents/P_Final/Sprites/Ave.png", 2);
    scene.addItem(ave2);
    // Configurar el temporizador para actualizar la posición de la partícula
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [particle, ave]() {
        particle->updatePosition(); // Actualizar la posición de la partícula
    });
    timer->start(50); // Actualiza cada 50 ms

    // Configurar un temporizador para actualizar la posición del ave
    QTimer* aveTimer = new QTimer();
    QObject::connect(aveTimer, &QTimer::timeout, [ave, ave2]() {
        ave->updatePosition(); // Actualizar la posición del ave
        ave2->updatePosition(); // Actualizar la posición del ave
    });
    aveTimer->start(50); // Actualizar cada 50 ms

    // Crear un contador para la cuenta atras
    int contador = 60;
    QGraphicsTextItem* textItem = new QGraphicsTextItem( QString::number(contador));
    textItem->setDefaultTextColor(Qt::black);
    textItem->setFont(QFont("Arial", 32));
    textItem->setPos(1160, 25); // Posición del texto de tiempo restante
    scene.addItem(textItem); // Agregar el texto a la escena


    // Texto para los aciertos
    QGraphicsTextItem* textItemAciertos = new QGraphicsTextItem(QString("0 /15"));
    textItemAciertos->setDefaultTextColor(Qt::green);
    textItemAciertos->setFont(QFont("Arial", 37));
    textItemAciertos->setPos(1124, 620); // Posición del segundo texto
    scene.addItem(textItemAciertos); // Agregar el segundo texto a la escena


    // Cargar y agregar una imagen de "Game Over"
    QPixmap gameOverPixmap("C:/Users/Miller Perez/Documents/P_Final/Sprites/game_over.png");
    QGraphicsPixmapItem* gameOverItem = scene.addPixmap(gameOverPixmap);
    gameOverItem->setPos(250, 120); // Posición de la imagen
    gameOverItem->hide(); // Ocultar la imagen al inicio

    // Cargar y agregar la imagen de "you win"
    QPixmap youWinPixmap("C:/Users/Miller Perez/Documents/P_Final/Sprites/you_win.png");
    youWinPixmap = youWinPixmap.scaled(QSize(900, 900), Qt::KeepAspectRatio);
    QGraphicsPixmapItem* youWinItem = scene.addPixmap(youWinPixmap);
    youWinItem->hide(); // Ocultar la imagen al inicio

    // Configurar un temporizador para decrementar el contador
    QTimer* contadorTimer = new QTimer();
    QObject::connect(contadorTimer, &QTimer::timeout, [&contador, textItem,textItemAciertos, gameOverItem, youWinPixmap, gameOverPixmap, &scene]() {
        if (contador > 0) {
            contador--; // Decrementar el contador
            textItem->setPlainText( QString::number(contador)); // Actualizar el texto en la pantalla

            if (contador == 0) {
                textItem->hide(); // Ocultar el texto del contador

                // Verificar si se gana o se pierde
                int aciertos = textItemAciertos->toPlainText().toInt();
                if (aciertos >= 15) {
                    gameOverItem->setPos(160, 200);
                    gameOverItem->setPixmap(youWinPixmap);
                } else {
                    gameOverItem->setPixmap(gameOverPixmap);
                }
                gameOverItem->show(); // Mostrar la imagen de "You Win" o "You Lose"
            }
        }
    });
    contadorTimer->start(1000); // Decrementar el contador cada segundo


    view.setWindowTitle("nivel_2");
    view.setRenderHint(QPainter::Antialiasing);
    view.show();

    return app.exec();
}