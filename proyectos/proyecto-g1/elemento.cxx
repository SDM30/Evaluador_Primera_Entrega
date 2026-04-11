#include "elemento.h"

bool Elemento::esTipoCorrecto(std::string tipo)
{   
    for (char &c : tipo)
    {
        c = std::tolower(c);
    }

    return tipo == "roca" || tipo == "crater" || tipo == "monticulo" || tipo == "duna";
}

bool Elemento::esUnidadCorrecta(std::string unidad)
{   
    for (char &c : unidad)
    {
        c = std::tolower(c);
    }

    return unidad == "cm" || unidad == "dm" || unidad == "m" || unidad == "km";

}