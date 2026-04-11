#include "ComandoMovimiento.h"
// Constructor por defecto: deja los atributos en valores cero o vacios
ComandoMovimiento::ComandoMovimiento()
{
    tipoMovimiento= "";
    magnitud= 0.0;
    unidadMedida= "";
}
// Constructor con parametros: guarda el tipo, la magnitud y la unidad
ComandoMovimiento::ComandoMovimiento(string tipo, double magnitud, string unidad)
{
    tipoMovimiento = tipo;
    this->magnitud = magnitud; // el this-> es para diferenciar el atributo magnitud del parametro magnitud, ya que tienen el mismo nombre
    unidadMedida   = unidad;
}

string ComandoMovimiento::getTipoMovimiento()
{
    return tipoMovimiento;
}
double ComandoMovimiento::getMagnitud()
{
    return magnitud;
}
string ComandoMovimiento::getUnidad()
{
    return unidadMedida;
}
