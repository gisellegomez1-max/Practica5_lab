#ifndef REGISTRODATOS_H
#define REGISTRODATOS_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "Bola.h"

// Guarda en un archivo CSV el estado de las bolas en cada instante:
// t, x_i, y_i, vx_i, vy_i, Ec_i (para cada bola i) y Ec_total.
class RegistroDatos
{
public:
    RegistroDatos();
    ~RegistroDatos();

    bool abrirArchivo(const QString &nombre);
    void guardarEstado(double tiempo, const QVector<Bola *> &bolas);
    void cerrarArchivo();

private:
    QString nombreArchivo;
    QFile archivo;
    QTextStream salida;
    bool encabezadoEscrito;

    RegistroDatos(const RegistroDatos &) = delete;
    RegistroDatos &operator=(const RegistroDatos &) = delete;
};

#endif // REGISTRODATOS_H
