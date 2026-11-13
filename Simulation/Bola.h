#ifndef BOLA_H
#define BOLA_H

#include "Entidad.h"
#include "Vector2D.h"

class Bola : public Entidad
{
public:
    Bola(double x, double y, double vx, double vy,
         double radio, double masa, const QColor &color);

    void mover(double dt);
    Vector2D obtenerVelocidad() const;
    void establecerVelocidad(const Vector2D &velocidad);

    double getRadio() const;
    double getMasa() const;
    void setMasa(double m)  { masa = m; }
    void setRadio(double r) { radio = r; }
    double energiaCinetica() const;

    void dibujar(QPainter *painter) const override;

private:
    double vx;
    double vy;
    double radio;
    double masa;
};

#endif // BOLA_H
