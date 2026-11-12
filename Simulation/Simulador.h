#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <QVector>
#include "Bola.h"
#include "Cuadrado.h"
#include "ResolutorColisiones.h"

class Simulador
{
public:
    Simulador(double ancho, double alto);
    ~Simulador();

    void inicializar();
    void actualizar(double dt);
    void detectarColisiones();

    // El simulador toma posesión de los objetos agregados (los libera en el destructor)
    void agregarBola(Bola *bola);
    void agregarCuadrado(Cuadrado *cuadrado);

    const QVector<Bola *> &getBolas() const;
    const QVector<Cuadrado *> &getCuadrados() const;
    double getAncho() const;
    double getAlto() const;
    double getTiempo() const;

private:
    QVector<Bola *> bolas;
    QVector<Cuadrado *> cuadrados;
    double ancho;
    double alto;
    double tiempo;
    ResolutorColisiones resolutor;

    void limpiar();
    bool posicionLibre(double x, double y, double radio) const;

    Simulador(const Simulador &) = delete;
    Simulador &operator=(const Simulador &) = delete;
};

#endif // SIMULADOR_H
