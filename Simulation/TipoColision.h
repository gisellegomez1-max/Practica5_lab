#ifndef TIPOCOLISION_H
#define TIPOCOLISION_H

enum class TipoColision
{
    ELASTICA,               // bola - pared (e = 1)
    INELASTICA,             // bola - bola (0 < e < 1)
    COMPLETAMENTE_INELASTICA // bola - cuadrado (e = 0)
};

#endif // TIPOCOLISION_H
