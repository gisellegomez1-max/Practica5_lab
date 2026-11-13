#ifndef RESOLUTORCOLISIONES_H
#define RESOLUTORCOLISIONES_H
#include "bola.h"
#include "cuadrado.h"

class ResolutorColisiones {
public:
    ResolutorColisiones(double coefRestitucionObstaculos = 0.7);

    bool resolverPared(Bola& bola, double ancho, double alto);
    bool resolverBolaCuadrado(Bola& bola, const Cuadrado& cuadrado);
    bool resolverBolaBola(Bola& a, Bola& b);


private:
    double e;   // coeficiente de restitución de los obstáculos
};
#endif