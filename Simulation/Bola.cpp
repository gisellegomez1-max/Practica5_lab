#include "Bola.h"

Bola::Bola(double x, double y, double vx, double vy,
           double radio, double masa, const QColor &color)
    : Entidad(x, y, color), vx(vx), vy(vy), radio(radio), masa(masa)
{
}

void Bola::mover(double dt)
{
    x += vx * dt;
    y += vy * dt;
}

Vector2D Bola::obtenerVelocidad() const
{
    return Vector2D(vx, vy);
}

void Bola::establecerVelocidad(const Vector2D &velocidad)
{
    vx = velocidad.x;
    vy = velocidad.y;
}

double Bola::getRadio() const
{
    return radio;
}

double Bola::getMasa() const
{
    return masa;
}

double Bola::energiaCinetica() const
{
    return 0.5 * masa * (vx * vx + vy * vy);
}

void Bola::dibujar(QPainter *painter) const
{
    painter->setPen(QPen(Qt::black, 1.5));
    painter->setBrush(color);
    painter->drawEllipse(QPointF(x, y), radio, radio);
}
