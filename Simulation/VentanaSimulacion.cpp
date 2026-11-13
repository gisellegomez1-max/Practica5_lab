#include "VentanaSimulacion.h"
#include <QPainter>

namespace {
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;
const int INTERVALO_MS = 16; // ~60 fotogramas por segundo
}

VentanaSimulacion::VentanaSimulacion(QWidget *parent)
    : QWidget(parent),
      simulador(ANCHO_VENTANA, ALTO_VENTANA),
      temporizador(new QTimer(this))
{
    setFixedSize(ANCHO_VENTANA, ALTO_VENTANA);
    setWindowTitle("Simulación de colisiones");
    setFocusPolicy(Qt::StrongFocus);

    simulador.inicializar();
    registro.abrirArchivo("resultados.csv"); // se crea en la carpeta de ejecución (build)

    connect(temporizador, &QTimer::timeout, this, &VentanaSimulacion::actualizarVista);
}

VentanaSimulacion::~VentanaSimulacion()
{
    registro.cerrarArchivo();
}

void VentanaSimulacion::iniciar()
{
    temporizador->start(INTERVALO_MS);
}

void VentanaSimulacion::pausar()
{
    temporizador->stop();
}

void VentanaSimulacion::actualizarVista()
{
    const double dt = INTERVALO_MS / 1000.0;

    simulador.actualizar(dt);
    registro.guardarEstado(simulador.getTiempo(), simulador.getBolas());

    update(); // pide repintar la ventana
}

void VentanaSimulacion::paintEvent(QPaintEvent *evento)
{
    Q_UNUSED(evento);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(250, 250, 250));

    for (const Cuadrado *cuadrado : simulador.getCuadrados())
        cuadrado->dibujar(&painter);

    for (const Bola *bola : simulador.getBolas())
        bola->dibujar(&painter);

    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("t = %1 s").arg(simulador.getTiempo(), 0, 'f', 2));
}

void VentanaSimulacion::keyPressEvent(QKeyEvent *evento)
{
    if (evento->key() == Qt::Key_R) {
        reiniciar();
    } else if (evento->key() == Qt::Key_P) {
        if (temporizador->isActive()) pausar();
        else iniciar();
    } else {
        QWidget::keyPressEvent(evento);
    }
}

void VentanaSimulacion::reiniciar()
{
    temporizador->stop();

    simulador.reiniciar();                  // limpia y vuelve a crear el escenario

    registro.cerrarArchivo();               // archivo nuevo para la nueva corrida
    registro.abrirArchivo("resultados.csv");

    update();
    temporizador->start(INTERVALO_MS);
}