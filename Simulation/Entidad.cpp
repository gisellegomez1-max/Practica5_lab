#include "Entidad.h"

Entidad::Entidad(double x, double y, const QColor &color)
    : x(x), y(y), color(color)
{
}

Entidad::~Entidad()
{
}

double Entidad::getX() const
{
    return x;
}

double Entidad::getY() const
{
    return y;
}

QColor Entidad::getColor() const
{
    return color;
}

void Entidad::setX(double nuevoX)
{
    x = nuevoX;
}

void Entidad::setY(double nuevoY)
{
    y = nuevoY;
}
