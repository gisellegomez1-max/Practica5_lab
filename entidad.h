#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <QColor>
#include <QPainter>

class Entidad {
public:
    Entidad(double x = 0, double y = 0, QColor color = Qt::black)
        : x(x), y(y), color(color) {}
    virtual ~Entidad() {}

    virtual void dibujar(QPainter* painter) = 0;   // abstracto

protected:
    double x, y;
    QColor color;
};
#endif