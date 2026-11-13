#include "Simulador.h"
#include <QRandomGenerator>
#include <QtGlobal>
#include <cmath>

Simulador::Simulador(double ancho, double alto)
    : ancho(ancho), alto(alto), tiempo(0.0), resolutor(0.7)
{
}

Simulador::~Simulador()
{
    limpiar();
}

void Simulador::limpiar()
{
    qDeleteAll(bolas);
    bolas.clear();
    qDeleteAll(cuadrados);
    cuadrados.clear();
}

void Simulador::agregarBola(Bola *bola)
{
    bolas.append(bola);
}

void Simulador::agregarCuadrado(Cuadrado *cuadrado)
{
    cuadrados.append(cuadrado);
}

const QVector<Bola *> &Simulador::getBolas() const
{
    return bolas;
}

const QVector<Cuadrado *> &Simulador::getCuadrados() const
{
    return cuadrados;
}

double Simulador::getAncho() const
{
    return ancho;
}

double Simulador::getAlto() const
{
    return alto;
}

double Simulador::getTiempo() const
{
    return tiempo;
}

// Verifica que una bola de ese radio en (x, y) no toque cuadrados ni otras bolas
bool Simulador::posicionLibre(double x, double y, double radio) const
{
    const double margen = 5.0;

    for (const Cuadrado *c : cuadrados) {
        const QRectF lim = c->obtenerLimites();
        const double cx = qBound(lim.left(), x, lim.right());
        const double cy = qBound(lim.top(), y, lim.bottom());
        const double d = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
        if (d < radio + margen)
            return false;
    }

    for (const Bola *b : bolas) {
        const double d = std::sqrt((x - b->getX()) * (x - b->getX())
                                   + (y - b->getY()) * (y - b->getY()));
        if (d < radio + b->getRadio() + margen)
            return false;
    }

    return true;
}

void Simulador::inicializar()
{
    limpiar();
    tiempo = 0.0;

    // Cuadrados fijos (posiciones proporcionales al tamaño del área)
    const double lado = 70.0;
    agregarCuadrado(new Cuadrado(0.20 * ancho, 0.20 * alto, lado, QColor(130, 130, 130)));
    agregarCuadrado(new Cuadrado(0.65 * ancho, 0.15 * alto, lado, QColor(130, 130, 130)));
    agregarCuadrado(new Cuadrado(0.42 * ancho, 0.62 * alto, lado, QColor(130, 130, 130)));
    agregarCuadrado(new Cuadrado(0.75 * ancho, 0.70 * alto, lado, QColor(130, 130, 130)));

    // Dos bolas con posición y dirección aleatorias
    QRandomGenerator *rng = QRandomGenerator::global();
    const QColor colores[2] = { QColor(220, 50, 50), QColor(50, 90, 220) };
    const double dosPi = 6.283185307179586;

    for (int i = 0; i < 2; ++i) {
        const double radio = 20.0 + 10.0 * i;
        const double masa = radio * radio * 0.01;

        double x = radio;
        double y = radio;
        for (int intento = 0; intento < 1000; ++intento) {
            x = radio + rng->generateDouble() * (ancho - 2.0 * radio);
            y = radio + rng->generateDouble() * (alto - 2.0 * radio);
            if (posicionLibre(x, y, radio))
                break;
        }

        const double angulo = rng->generateDouble() * dosPi;
        const double rapidez = 150.0 + rng->generateDouble() * 150.0; // px/s
        const double vx = rapidez * std::cos(angulo);
        const double vy = rapidez * std::sin(angulo);

        agregarBola(new Bola(x, y, vx, vy, radio, masa, colores[i]));
    }
}

void Simulador::actualizar(double dt)
{
    for (Bola *bola : bolas)
        bola->mover(dt);

    detectarColisiones();
    tiempo += dt;
}

void Simulador::detectarColisiones()
{
    // Bola - pared
    for (Bola *bola : bolas)
        resolutor.resolverPared(bola, ancho, alto);

    // Bola - bola
    for (int i = 0; i < bolas.size(); ++i)
        for (int j = i + 1; j < bolas.size(); ++j)
            resolutor.resolverBolaBola(bolas[i], bolas[j]);

    // Bola - cuadrado
    for (Bola *bola : bolas)
        for (const Cuadrado *cuadrado : cuadrados)
            resolutor.resolverBolaCuadrado(bola, cuadrado);
}
