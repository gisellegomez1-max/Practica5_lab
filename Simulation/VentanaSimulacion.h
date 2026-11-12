#ifndef VENTANASIMULACION_H
#define VENTANASIMULACION_H

#include <QWidget>
#include <QTimer>
#include "Simulador.h"
#include "RegistroDatos.h"

class VentanaSimulacion : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaSimulacion(QWidget *parent = nullptr);
    ~VentanaSimulacion();

    void iniciar();
    void pausar();

public slots:
    void actualizarVista();

protected:
    void paintEvent(QPaintEvent *evento) override;

private:
    Simulador simulador;
    RegistroDatos registro;
    QTimer *temporizador;
};

#endif // VENTANASIMULACION_H
