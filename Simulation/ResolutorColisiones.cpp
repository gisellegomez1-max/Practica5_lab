#include "ResolutorColisiones.h"
#include <QtGlobal>
#include <cmath>
#include <algorithm>

ResolutorColisiones::ResolutorColisiones(double coefRestitucionBolas)
    : coefRestitucionBolas(coefRestitucionBolas)
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


void ResolutorColisiones::resolverBolaBola(Bola *a, Bola *b)
{
    const double dx = b->getX() - a->getX();
    const double dy = b->getY() - a->getY();
    const double dist = std::sqrt(dx * dx + dy * dy);
    const double sumaRadios = a->getRadio() + b->getRadio();

    if (dist >= sumaRadios)
        return; // no hay contacto

    // Normal unitaria que va de a hacia b
    Vector2D n(1.0, 0.0);
    if (dist > 1e-9)
        n = Vector2D(dx / dist, dy / dist);

    // Separar las bolas para que no queden solapadas
    const double solape = sumaRadios - dist;
    a->setX(a->getX() - n.x * solape / 2.0);
    a->setY(a->getY() - n.y * solape / 2.0);
    b->setX(b->getX() + n.x * solape / 2.0);
    b->setY(b->getY() + n.y * solape / 2.0);

    Vector2D va = a->obtenerVelocidad();
    Vector2D vb = b->obtenerVelocidad();

    // Velocidad relativa proyectada sobre la normal (> 0 si se acercan)
    const Vector2D vRel(va.x - vb.x, va.y - vb.y);
    const double vn = vRel.productoPunto(n);
    if (vn <= 0.0)
        return; // ya se están alejando

    const double e = coeficiente(TipoColision::INELASTICA);
    const double ma = a->getMasa();
    const double mb = b->getMasa();
    const double j = (1.0 + e) * vn / (1.0 / ma + 1.0 / mb);

    va.x -= (j / ma) * n.x;
    va.y -= (j / ma) * n.y;
    vb.x += (j / mb) * n.x;
    vb.y += (j / mb) * n.y;

    a->establecerVelocidad(va);
    b->establecerVelocidad(vb);
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

    // Solo si la bola venía hacia el cuadrado
    const Vector2D v = bola->obtenerVelocidad();
    if (v.productoPunto(n) < 0.0) {
        // Completamente inelástica: m*v + M*0 = (m + M)*vf, con M -> infinito => vf = 0
        bola->establecerVelocidad(Vector2D(0.0, 0.0));
    }
}
