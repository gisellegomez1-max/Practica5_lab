#ifndef CUADRADO_H
#define CUADRADO_H
#include <QRectF>
#include "entidad.h"

class Cuadrado : public Entidad {
public:
    // (x, y) = esquina superior izquierda
    Cuadrado(double x, double y, double lado, QColor color = Qt::gray);

    QRectF obtenerLimites() const;
    void dibujar(QPainter* painter) override;

private:
    double lado;
};
#endif