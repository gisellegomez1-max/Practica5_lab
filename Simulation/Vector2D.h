#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    double x;
    double y;

    Vector2D(double px = 0.0, double py = 0.0);

    double magnitud() const;
    Vector2D normalizar() const;
    double productoPunto(const Vector2D &otro) const;
};

#endif // VECTOR2D_H
