#include "ResolutorColisiones.h"
#include <QtGlobal>
#include <cmath>
#include <algorithm>
#include <QString>

ResolutorColisiones::ResolutorColisiones(double coefBolas, double coefObstaculos)
    : coefRestitucionBolas(coefBolas),
    coefRestitucionObstaculos(coefObstaculos)
{
}


double ResolutorColisiones::getCoefRestitucionBolas() const
{
    return coefRestitucionBolas;
}

void ResolutorColisiones::setCoefRestitucionBolas(double coef)
{
    coefRestitucionBolas = coef;
}

double ResolutorColisiones::coeficiente(TipoColision tipo) const
{
    switch (tipo) {
    case TipoColision::ELASTICA:
        return 1.0;
    case TipoColision::INELASTICA:
        return coefRestitucionBolas;
    case TipoColision::COMPLETAMENTE_INELASTICA:
        return 0.0;
    }
    return 1.0;
}

void ResolutorColisiones::resolverPared(Bola *bola, double ancho, double alto)
{
    const double e = coeficiente(TipoColision::ELASTICA);
    const double r = bola->getRadio();
    Vector2D v = bola->obtenerVelocidad();

    if (bola->getX() - r < 0.0) {
        bola->setX(r);
        v.x = std::fabs(v.x) * e;
    } else if (bola->getX() + r > ancho) {
        bola->setX(ancho - r);
        v.x = -std::fabs(v.x) * e;
    }

    if (bola->getY() - r < 0.0) {
        bola->setY(r);
        v.y = std::fabs(v.y) * e;
    } else if (bola->getY() + r > alto) {
        bola->setY(alto - r);
        v.y = -std::fabs(v.y) * e;
    }

    bola->establecerVelocidad(v);
}


bool ResolutorColisiones::resolverBolaBola(Bola *a, Bola *b)
{
    const double dx = b->getX() - a->getX();
    const double dy = b->getY() - a->getY();
    const double dist = std::sqrt(dx * dx + dy * dy);

    if (dist >= a->getRadio() + b->getRadio())
        return false; // no hay contacto

    const double m1 = a->getMasa();
    const double m2 = b->getMasa();
    const double M  = m1 + m2;

    const Vector2D v1 = a->obtenerVelocidad();
    const Vector2D v2 = b->obtenerVelocidad();

    // Conservación del momento: m1·v1 + m2·v2 = (m1 + m2)·v'
    const Vector2D vf((m1 * v1.x + m2 * v2.x) / M,
                      (m1 * v1.y + m2 * v2.y) / M);

    // Nueva posición: centro de masa
    const double xf = (m1 * a->getX() + m2 * b->getX()) / M;
    const double yf = (m1 * a->getY() + m2 * b->getY()) / M;

    // Nuevo radio: se suman las áreas (π r² = π r1² + π r2²)
    const double rf = std::sqrt(a->getRadio() * a->getRadio()
                                + b->getRadio() * b->getRadio());

    // La bola "a" se convierte en el cuerpo fusionado
    a->setMasa(M);
    a->setRadio(rf);
    a->setX(xf);
    a->setY(yf);
    a->establecerVelocidad(vf);

    return true; // el Simulador debe eliminar "b"
}

void ResolutorColisiones::resolverBolaCuadrado(Bola *bola, const Cuadrado *cuadrado)
{
    const QRectF lim = cuadrado->obtenerLimites();
    const double r = bola->getRadio();
    const double bx = bola->getX();
    const double by = bola->getY();

    // Punto del cuadrado más cercano al centro de la bola
    const double cx = qBound(lim.left(), bx, lim.right());
    const double cy = qBound(lim.top(), by, lim.bottom());

    const double dx = bx - cx;
    const double dy = by - cy;
    const double dist = std::sqrt(dx * dx + dy * dy);

    if (dist >= r)
        return; // no hay contacto

    Vector2D n;
    double empuje;

    if (dist > 1e-9) {
        n = Vector2D(dx / dist, dy / dist);
        empuje = r - dist;
    } else {
        // El centro quedó dentro del cuadrado: salir por el lado más cercano
        const double izq = bx - lim.left();
        const double der = lim.right() - bx;
        const double arr = by - lim.top();
        const double aba = lim.bottom() - by;
        const double m = std::min(std::min(izq, der), std::min(arr, aba));

        if (m == izq)      n = Vector2D(-1.0, 0.0);
        else if (m == der) n = Vector2D(1.0, 0.0);
        else if (m == arr) n = Vector2D(0.0, -1.0);
        else               n = Vector2D(0.0, 1.0);

        empuje = m + r;
    }

    // Sacar la bola del cuadrado
    bola->setX(bx + n.x * empuje);
    bola->setY(by + n.y * empuje);

    // Determinar con cuál lado chocó: el eje dominante de la normal
    Vector2D nLado;
    QString lado;
    if (std::fabs(n.x) >= std::fabs(n.y)) {
        nLado = Vector2D(n.x > 0 ? 1.0 : -1.0, 0.0);
        lado = (n.x > 0) ? "derecho" : "izquierdo";
    } else {
        nLado = Vector2D(0.0, n.y > 0 ? 1.0 : -1.0);
        lado = (n.y > 0) ? "inferior" : "superior";
    }
    Q_UNUSED(lado); // úsalo para registrar la colisión o con qDebug() << lado;

    // Rebote inelástico: solo si la bola venía hacia el cuadrado
    const Vector2D v = bola->obtenerVelocidad();
    const double vn = v.productoPunto(nLado);
    if (vn < 0.0) {
        const double e = coefRestitucionObstaculos;
        const Vector2D vPerp(nLado.x * vn, nLado.y * vn);   // perpendicular al lado
        const Vector2D vPar(v.x - vPerp.x, v.y - vPerp.y);  // paralela al lado

        // v' = v∥ - e·v⊥
        bola->establecerVelocidad(Vector2D(vPar.x - e * vPerp.x,
                                           vPar.y - e * vPerp.y));
    }
}
