#include "movimiento.h"

bool Movimiento::esUnidadCorrecta(std::string unidad, std::string tipoMovimiento)
{   
    for (char &c : unidad)
    {
        c = std::tolower(c);
    }

    if(tipoMovimiento == "avanzar")
    {
        if(unidad == "cm" || unidad == "dm" || unidad == "m" || unidad == "km") return true;
    }
    else
    {
        if(unidad == "grd" || unidad == "rad") return true;
    }

    return false;
}

bool Movimiento::esTipoCorrecto(std::string tipoMovimiento)
{
    for (char &c : tipoMovimiento)
    {
        c = std::tolower(c);
    }

    return tipoMovimiento == "avanzar" || tipoMovimiento == "girar";
}