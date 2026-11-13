#include "cuadrado.h"

Cuadrado::Cuadrado(double x, double y, double lado, QColor color)
    : Entidad(x, y, color), lado(lado) {}

QRectF Cuadrado::obtenerLimites() const {
    return QRectF(x, y, lado, lado);
}

void Cuadrado::dibujar(QPainter* painter) {
    painter->setBrush(color);
    painter->drawRect(obtenerLimites());
}