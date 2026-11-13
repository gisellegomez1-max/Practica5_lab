#include "RegistroDatos.h"

RegistroDatos::RegistroDatos()
    : encabezadoEscrito(false)
{
}

RegistroDatos::~RegistroDatos()
{
    cerrarArchivo();
}

bool RegistroDatos::abrirArchivo(const QString &nombre)
{
    cerrarArchivo();
    nombreArchivo = nombre;
    archivo.setFileName(nombreArchivo);

    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    salida.setDevice(&archivo);
    encabezadoEscrito = false;
    return true;
}

void RegistroDatos::guardarEstado(double tiempo, const QVector<Bola *> &bolas)
{
    if (!archivo.isOpen())
        return;

    if (!encabezadoEscrito) {
        salida << "t";
        for (int i = 0; i < bolas.size(); ++i) {
            const int n = i + 1;
            salida << ",x" << n << ",y" << n << ",vx" << n << ",vy" << n << ",Ec" << n;
        }
        salida << ",Ec_total\n";
        encabezadoEscrito = true;
    }

    double energiaTotal = 0.0;
    salida << QString::number(tiempo, 'f', 4);

    for (const Bola *bola : bolas) {
        const Vector2D v = bola->obtenerVelocidad();
        const double ec = bola->energiaCinetica();
        energiaTotal += ec;

        salida << ',' << QString::number(bola->getX(), 'f', 3)
               << ',' << QString::number(bola->getY(), 'f', 3)
               << ',' << QString::number(v.x, 'f', 3)
               << ',' << QString::number(v.y, 'f', 3)
               << ',' << QString::number(ec, 'f', 3);
    }

    salida << ',' << QString::number(energiaTotal, 'f', 3) << '\n';
}

void RegistroDatos::cerrarArchivo()
{
    if (archivo.isOpen()) {
        salida.flush();
        archivo.close();
    }
}
