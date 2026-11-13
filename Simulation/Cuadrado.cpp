#include "Cuadrado.h"

Cuadrado::Cuadrado(double x, double y, double lado, const QColor &color)
    : Entidad(x, y, color), lado(lado)
{
}

QRectF Cuadrado::obtenerLimites() const
{
    return QRectF(x, y, lado, lado);
}

double Cuadrado::getLado() const
{
    return lado;
}

void Cuadrado::dibujar(QPainter *painter) const
{
    painter->setPen(QPen(Qt::black, 1.5));
    painter->setBrush(color);
    painter->drawRect(obtenerLimites());
}
