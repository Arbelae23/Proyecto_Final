#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *startButton = new QPushButton("Iniciar Nivel 1");
    QPushButton *exitButton = new QPushButton("Salir");

    layout->addWidget(startButton);
    layout->addWidget(exitButton);

    connect(startButton, &QPushButton::clicked, this, &MainMenu::startLevel1);
    connect(exitButton, &QPushButton::clicked, this, &MainMenu::exitGame);
}
