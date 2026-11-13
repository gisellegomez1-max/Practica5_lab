#include "resolutorcolisiones.h"
#include <algorithm>
#include <cmath>

ResolutorColisiones::ResolutorColisiones(double coef) : e(coef) {}

// Perfectamente elástica
bool ResolutorColisiones::resolverPared(Bola& b, double ancho, double alto) {
    bool choco = false;
    double x = b.getX(), y = b.getY(), r = b.getRadio();
    Vector2D v = b.obtenerVelocidad();

    if (x - r < 0)      { x = r;         v.x = -v.x; choco = true; }
    else if (x + r > ancho) { x = ancho - r; v.x = -v.x; choco = true; }

    if (y - r < 0)      { y = r;         v.y = -v.y; choco = true; }
    else if (y + r > alto)  { y = alto - r;  v.y = -v.y; choco = true; }

    if (choco) {
        b.setPosicion(x, y);
        b.setVelocidad(v);
    }
    return choco;
}

// Inelástica con coeficiente e
bool ResolutorColisiones::resolverBolaCuadrado(Bola& b, const Cuadrado& c) {
    QRectF L = c.obtenerLimites();
    double x = b.getX(), y = b.getY(), r = b.getRadio();

    double cx = std::clamp(x, L.left(),  L.right());
    double cy = std::clamp(y, L.top(),   L.bottom());
    double dx = x - cx, dy = y - cy;
    if (dx*dx + dy*dy >= r*r) return false;

    double penIzq = (x + r) - L.left();
    double penDer = L.right() - (x - r);
    double penArr = (y + r) - L.top();
    double penAbj = L.bottom() - (y - r);

    double pen = penIzq;  Vector2D n(-1, 0);                  // izquierdo
    if (penDer < pen) { pen = penDer; n = Vector2D( 1, 0); }  // derecho
    if (penArr < pen) { pen = penArr; n = Vector2D( 0,-1); }  // arriba
    if (penAbj < pen) { pen = penAbj; n = Vector2D( 0, 1); }  // abajo

    b.setPosicion(x + n.x * pen, y + n.y * pen);

    Vector2D v = b.obtenerVelocidad();
    double vn = v.productoPunto(n);
    if (vn < 0) {
        Vector2D vPerp = n * vn;        // componente perpendicular
        Vector2D vPar  = v - vPerp;     // componente paralela
        b.setVelocidad(vPar - vPerp * e);  // v' = v∥ - e·v⊥
    }
    return true;
}

// Completamente inelástica
bool ResolutorColisiones::resolverBolaBola(Bola& a, Bola& b) {
    return false;
}