/*#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QKeyEvent>  // Agregar esta línea al inicio de tu archivo mainwindow.cpp

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), encestes(0)
{
    ui->setupUi(this);

    // Crear escena
    scene = new QGraphicsScene(this);
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(QPixmap("C:/Users/Miller Perez/Documents/Proyecto_Final/Sprites/fondo1.jpg"));
    scene->addItem(background);

    // Crear pelota y establecer posición del aro
    ball = new Ball();
    //ball->setBallSize(0.5);
    ball->setAroPosition(700, 200);  // Posición del aro en la pantalla
    scene->addItem(ball);

    // Conectar la señal de la pelota cuando encesta
    connect(ball, &Ball::scored, this, &MainWindow::onBallScored);

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene->setSceneRect(0, 0, 800, 600);

    ui->graphicsView->setScene(scene);

    // Iniciar con posición inicial de la pelota
    ball->resetPosition();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBallScored()
{
    encestes++;
    if (encestes >= 3) {
        QMessageBox::information(this, "¡Victoria!", "¡Has encestado 3 veces!");
        encestes = 0;  // Reiniciar encestes
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (!ball->isInAir()) {
            ball->launch(); // Iniciar el lanzamiento de la pelota si no está en el aire
        }
    }
}
