#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QColor>
#include <QPainter>

// Clase abstracta: base de todo objeto que se dibuja en la simulación.
class Entidad
{
public:
    Entidad(double x, double y, const QColor &color);
    virtual ~Entidad();

    virtual void dibujar(QPainter *painter) const = 0;

    double getX() const;
    double getY() const;
    QColor getColor() const;

    void setX(double nuevoX);
    void setY(double nuevoY);

protected:
    double x;
    double y;
    QColor color;
};

#endif // ENTIDAD_H
