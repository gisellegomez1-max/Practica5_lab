#ifndef RESOLUTORCOLISIONES_H
#define RESOLUTORCOLISIONES_H

#include "Bola.h"
#include "Cuadrado.h"
#include "TipoColision.h"

// Cada método de resolución detecta si hay contacto y, de haberlo,
// corrige la posición y la velocidad de las bolas involucradas.
class ResolutorColisiones
{
public:
    explicit ResolutorColisiones(double coefRestitucionBolas = 0.7);

    void resolverPared(Bola *bola, double ancho, double alto);
    void resolverBolaBola(Bola *a, Bola *b);
    void resolverBolaCuadrado(Bola *bola, const Cuadrado *cuadrado);

    double getCoefRestitucionBolas() const;
    void setCoefRestitucionBolas(double coef);

private:
    double coefRestitucionBolas;

    // Coeficiente de restitución asociado a cada tipo de colisión.
    double coeficiente(TipoColision tipo) const;
};

#endif // RESOLUTORCOLISIONES_H
