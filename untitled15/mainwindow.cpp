#include "mainwindow.h"
#include "level1.h"  // Incluir los niveles
#include "level2.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Crear botones para los niveles
    QPushButton *buttonLevel1 = new QPushButton("Nivel 1");
    QPushButton *buttonLevel2 = new QPushButton("Nivel 2");
    // Establecer tamaño fijo de los botones
    buttonLevel1->setFixedSize(120, 40);
    buttonLevel2->setFixedSize(120, 40);
    // Establecer estilos de los botones con imagen de fondo
    QString buttonStyle = "QPushButton {"
                          "background-image: url(:/images/boton.jpg);"
                          "background-repeat: no-repeat;"
                          "background-position: center;"
                          "font-family: 'Comic Sans MS';"
                          "border: none;"  // Sin bordes
                          "color: yellow;"  // Texto blanco
                          "font-size: 18px;"
                          "padding: 10px;"
                          "}";
    QString buttonStyle2 = "QPushButton {"
                          "background-image: url(:/images/boton2.jpg);"
                          "background-repeat: no-repeat;"
                          "background-position: center;"
                          "font-family: 'Comic Sans MS';"
                          "border: none;"  // Sin bordes

                          "color: yellow;"  // Texto blanco
                          "font-size: 18px;"
                          "padding: 10px;"
                          "}";
    buttonLevel1->setStyleSheet(buttonStyle);
    buttonLevel2->setStyleSheet(buttonStyle2);
    // Conectar botones con los slots
    connect(buttonLevel1, &QPushButton::clicked, this, &MainWindow::openLevel1);
    connect(buttonLevel2, &QPushButton::clicked, this, &MainWindow::openLevel2);

    // Layout horizontal para alinear los botones uno al lado del otro
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(buttonLevel1);
    hLayout->addWidget(buttonLevel2);
    hLayout->setSpacing(1);  // Espaciado horizontal entre los botones

    // Layout vertical para centrar los botones horizontalmente y verticalmente
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addSpacing(200);      // Empuja los botones hacia el centro verticalmente
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    // Widget central con el layout vertical
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);

    // Establecer la imagen de fondo en el widget central
    centralWidget->setStyleSheet("background-image: url(:/images/fondomenu.jpg);"
                                 "background-position: center;"
                                 "background-size: cover;"
                                 "background-repeat: no-repeat;");
    setCentralWidget(centralWidget);
    setWindowTitle("Menú de Inicio");
    resize(640, 360);

}

void MainWindow::openLevel1() {
    Level1 *level1 = new Level1(this);
    level1->show();
    this->hide();  // Ocultar menú principal
}

void MainWindow::openLevel2() {
    Level2 *level2 = new Level2(this);
    level2->show();
    this->hide();  // Ocultar menú principal
}

