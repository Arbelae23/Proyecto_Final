#include "MainMenu.h"


MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    // Crear un layout vertical para los botones
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *startButton = new QPushButton("Iniciar Nivel 1");
    QPushButton *exitButton = new QPushButton("Salir");
    startButton->setFixedSize(120, 40);
    exitButton->setFixedSize(120, 40);

    // Estilo de los botones
    QString buttonStyle = "QPushButton {"
                          "background-image: url(:/images/boton.jpg);"
                          "background-repeat: no-repeat;"
                          "background-position: center;"
                          "font-family: 'Comic Sans MS';"
                          "border: none;"  // Sin bordes
                          "color: yellow;"  // Texto amarillo
                          "font-size: 18px;"
                          "padding: 10px;"
                          "}";

    startButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // Añadir los botones al layout vertical
    layout->addStretch(1);  // Empuja los botones hacia el centro verticalmente
    layout->addWidget(startButton);
    layout->addWidget(exitButton);
    layout->addStretch(1);

    // Establecer la imagen de fondo
    setStyleSheet("background-image: url(:/images/fondomenu.jpg);"
                  "background-position: center;"
                  "background-size: cover;"
                  "background-repeat: no-repeat;");

    // Conectar los botones con sus acciones
    connect(startButton, &QPushButton::clicked, this, &MainMenu::startLevel1);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::exitGame);

    // Establecer el layout en el widget principal
    setLayout(layout);
    // Configura el tamaño del widget si es necesario
    this->resize(1280, 720);  // O el tamaño deseado para la ventana
}

