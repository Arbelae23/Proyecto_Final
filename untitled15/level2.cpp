#include "level2.h"
#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QVBoxLayout>

Level2::Level2(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Nivel 2");
    resize(1300, 650);

    // Botón para regresar al menú principal
    buttonBack = new QPushButton("Regresar al Menú");
    buttonBack->setFixedSize(150, 50);
    buttonBack->setStyleSheet("font-size: 16px; color: white; background-color: red;");
    int buttonX = 600; // Posición X del botón
    int buttonY = 600; // Posición Y del botón
    buttonBack->setGeometry(buttonX, buttonY, buttonBack->width(), buttonBack->height());

    // Conectar botón con la función de regresar al menú
    connect(buttonBack, &QPushButton::clicked, this, &Level2::backToMenu);

    // Layout para centrar el botón
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(buttonBack, 0, Qt::AlignCenter);
    layout->addStretch();
    setLayout(layout);

    // Crear una escena con fondo blanco
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(1300, 650);
    view->setStyleSheet("background-color: white;"); // Establecer color de fondo blanco

    layout->addWidget(view, 0, Qt::AlignCenter);
    layout->addStretch();

    setLayout(layout);
}

void Level2::backToMenu() {
    // Agregar la lógica para regresar al menú principal
    MainWindow *menu = static_cast<MainWindow *>(parent());
    if (menu) {
        menu->show();
    }
    close();  // Cerrar esta ventana
}
