#include "mainwindow.h"
#include <QBrush>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), dx(5.0), dy(5.0) // Velocidad inicial
{
    // Configurar la escena
    scene = new QGraphicsScene(0, 0, 600, 400, this);

    // Configurar la vista
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing); // Suavizar bordes
    setCentralWidget(view); // Poner la vista en el centro de la ventana

    // Crear la pelota y añadirla a la escena
    ball = scene->addEllipse(0, 0, 40, 40, QPen(Qt::black), QBrush(Qt::red));
    ball->setPos(280, 180); // Posición inicial en el centro

    // Configurar el Timer para el bucle de físicas
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePhysics);
    timer->start(16); // 16 ms

    // Ajustar el tamaño de la ventana principal
    resize(650, 450);
}

MainWindow::~MainWindow() {
}

void MainWindow::updatePhysics() {
    // Mover la pelota
    ball->moveBy(dx, dy);

    // Obtener los límites actuales de la pelota en la escena
    QRectF rect = ball->sceneBoundingRect();

    // Colisión con la pared izquierda o derecha
    if (rect.left() <= 0 || rect.right() >= scene->width()) {
        dx = -dx; // Invertir la dirección horizontal
    }

    // Colisión con el techo o el suelo
    if (rect.top() <= 0 || rect.bottom() >= scene->height()) {
        dy = -dy; // Invertir la dirección vertical
    }
}