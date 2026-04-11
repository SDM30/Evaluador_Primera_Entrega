#include "analisis.h"

bool Analisis::esAnalisisCorrecto(std::string tipo)
{
    for (char &c : tipo)
    {
        c = std::tolower(c);
    }

    return (tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar");
}