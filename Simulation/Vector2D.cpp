#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(double px, double py)
    : x(px), y(py)
{
}

double Vector2D::magnitud() const
{
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalizar() const
{
    const double m = magnitud();
    if (m < 1e-12)
        return Vector2D(0.0, 0.0);
    return Vector2D(x / m, y / m);
}

double Vector2D::productoPunto(const Vector2D &otro) const
{
    return x * otro.x + y * otro.y;
}
