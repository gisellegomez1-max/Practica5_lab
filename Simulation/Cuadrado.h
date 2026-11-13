#ifndef CUADRADO_H
#define CUADRADO_H

#include "Entidad.h"
#include <QRectF>

// Cuadrado fijo. (x, y) es la esquina superior izquierda.
class Cuadrado : public Entidad
{
public:
    Cuadrado(double x, double y, double lado, const QColor &color);

    QRectF obtenerLimites() const;
    double getLado() const;

    void dibujar(QPainter *painter) const override;

private:
    double lado;
};

#endif // CUADRADO_H
