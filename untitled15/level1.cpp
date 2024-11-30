#include "level1.h"
#include "mainwindow.h"

Level1::Level1(QWidget *parent) : QWidget(parent) {
    // Configuración básica del nivel 1
    setWindowTitle("Nivel 1");
    resize(640, 360);

    // Botón para regresar al menú principal
    buttonBack = new QPushButton("Regresar al Menú");
    buttonBack->setFixedSize(150, 50);
    buttonBack->setStyleSheet("font-size: 16px; color: white; background-color: red;");

    // Conectar botón con la función de regresar al menú
    connect(buttonBack, &QPushButton::clicked, this, &Level1::backToMenu);

    // Layout para centrar el botón
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(buttonBack, 0, Qt::AlignCenter);
    layout->addStretch();
    setLayout(layout);
}

void Level1::backToMenu() {
    // Mostrar el menú principal y cerrar el nivel
    MainWindow *menu = qobject_cast<MainWindow *>(parent());
    if (menu) {
        menu->show();
    }
    close();  // Cerrar esta ventana
}
