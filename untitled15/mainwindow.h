#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openLevel1();  // Slot para abrir Nivel 1
    void openLevel2();  // Slot para abrir Nivel 2
};

#endif // MAINWINDOW_H
