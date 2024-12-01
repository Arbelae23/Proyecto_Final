#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mainMenu(new MainMenu(this)), level1(nullptr), level2(nullptr)
{
    setCentralWidget(mainMenu);

    connect(mainMenu, &MainMenu::startLevel1, this, &MainWindow::startLevel1);
    connect(mainMenu, &MainMenu::exitGame, this, &MainWindow::close);
}

void MainWindow::startLevel1()
{
    if (level2) {
        delete level2;
        level2 = nullptr;
    }

    level1 = new Level1(this);
    setCentralWidget(level1);

    connect(level1, &Level1::levelCompleted, this, &MainWindow::startLevel2);
}

void MainWindow::startLevel2()
{
    if (level1) {
        delete level1;
        level1 = nullptr;
    }

    level2 = new Level2(this);
    setCentralWidget(level2);
}
