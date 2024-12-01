#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    MainMenu *mainMenu;
    Level1 *level1;
    Level2 *level2;

private slots:
    void startLevel1();
    void startLevel2();
};

#endif // MAINWINDOW_H
