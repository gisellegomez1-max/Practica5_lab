#include <QApplication>
#include "VentanaSimulacion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VentanaSimulacion ventana;
    ventana.show();
    ventana.iniciar();

    return a.exec();
}
