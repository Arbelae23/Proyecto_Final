#include "MainMenu.h"
#include <QLabel>
MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    // Establecer tamaño fijo del menú principal
    setFixedSize(1336, 725);

    // Crear un layout vertical para los botones
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Crear botones
    QPushButton *startButton = new QPushButton("Iniciar Nivel 1");
    QPushButton *exitButton = new QPushButton("Salir");

    // Ajustar tamaño de los botones
    startButton->setFixedSize(200, 80);
    exitButton->setFixedSize(200, 80);

    // Estilo de los botones
    QString buttonStyle = "QPushButton {"
                          "background-image: url(:/images/boton.jpg);"
                          "background-repeat: no-repeat;"
                          "background-position: center;"
                          "font-family: 'Comic Sans MS';"
                          "border: none;"      // Sin bordes
                          "color: yellow;"     // Texto amarillo
                          "font-size: 20px;"   // Tamaño de fuente
                          "padding: 10px;"     // Relleno interno
                          "}";

    startButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    // Layout horizontal para alinear los botones uno al lado del otro
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(startButton);
    hLayout->addWidget(exitButton);
    hLayout->setSpacing(1);  // Espaciado horizontal entre los botones

    // Layout principal vertical para centrar los botones
    layout->addStretch();
    layout->addLayout(hLayout);
    layout->addStretch();

    QLabel *background = new QLabel(this);
    background->setPixmap(QPixmap(":/images/fondo.jpg"));
    background->setScaledContents(true);
    background->setGeometry(0, 0, width(), height());
    background->lower(); // Asegura que el fondo esté detrás de otros widgets

    // Conectar las señales de los botones
    connect(startButton, &QPushButton::clicked, this, &MainMenu::startLevel1);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::exitGame);
}

