#include "Elemento.h"

// Constructor por defecto
Elemento::Elemento()
{
    tipoComponente= "";
    tamano= 0.0;
    unidadMedida= "";
    coordX= 0.0;
    coordY = 0.0;
}
// Constructor con parametros
Elemento::Elemento(string tipo, double tamano, string unidad, double x, double y)
{
    tipoComponente= tipo;
    this->tamano= tamano;
    unidadMedida= unidad;
    coordX = x;
    coordY = y;
}
//getters
string Elemento::getTipo()
{
    return tipoComponente;
}
double Elemento::getTamano()
{
    return tamano;
}
string Elemento::getUnidad()
{
    return unidadMedida;
}
double Elemento::getCoordX()
{
    return coordX;
}
double Elemento::getCoordY()
{
    return coordY;
}
