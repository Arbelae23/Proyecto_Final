#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include <QKeyEvent>

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
    QPixmap backgroundPixmap("C:/Users/Miller Perez/Documents/Intento_Juego/Sprites/Background.jpg");
    QGraphicsPixmapItem* backgroundItem = new QGraphicsPixmapItem(backgroundPixmap);
    backgroundItem->setPos(0, 0);
    scene.addItem(backgroundItem);

    // Agregar la partícula
    Particle particle(100, 100);
    scene.addItem(&particle);

    // Crear una ave y agregarla a la escena
    Aves* ave = new Aves(100, 100, "C:/Users/Miller Perez/Documents/Intento_Juego/Sprites/Ave.png", 0);
    scene.addItem(ave);

    // Configurar el temporizador para actualizar la posición de la ave
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, [ave]() {
        ave->updatePosition();
    });
    timer->start(50); // Actualiza cada 50 ms

    // Set the main window properties
    view.setWindowTitle("Movimiento por teclado");
    view.setRenderHint(QPainter::Antialiasing);
    view.show();

    return app.exec();
}
