#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("Juego Qt - Niveles 1 y 2");
    window.show();
    return app.exec();
}
