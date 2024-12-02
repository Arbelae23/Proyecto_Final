#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "ball.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
/*
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
*/
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onBallScored();   // Manejar enceste

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Ball *ball;            // Instancia de la pelota
    int encestes;          // Contador de encestes
};

#endif // MAINWINDOW_H
