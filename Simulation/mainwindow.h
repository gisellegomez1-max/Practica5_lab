#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updatePhysics(); // Función que calculará el rebote

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsEllipseItem *ball;
    QTimer *timer;

    qreal dx; // Velocidad en el eje X
    qreal dy; // Velocidad en el eje Y
};

#endif // MAINWINDOW_H