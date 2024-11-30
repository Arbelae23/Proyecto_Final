#ifndef LEVEL2_H
#define LEVEL2_H

#include <QWidget>
#include <QPushButton>

class Level2 : public QWidget {
    Q_OBJECT

public:
    explicit Level2(QWidget *parent = nullptr);
private slots:
    void backToMenu();  // Para volver al menú principal

private:
    QPushButton *buttonBack;  // Botón para regresar al menú
};


#endif// LEVEL2_H
