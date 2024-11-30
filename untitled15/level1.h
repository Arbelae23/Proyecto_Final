#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Level1 : public QWidget {
    Q_OBJECT

public:
    explicit Level1(QWidget *parent = nullptr);

private slots:
    void backToMenu();  // Para volver al menú principal

private:
    QPushButton *buttonBack;  // Botón para regresar al menú
};

#endif // LEVEL1_H
