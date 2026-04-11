#include "elemento.h"

// Constructor
// Pre: tipo valido, tam > 0, unidad valida
Elemento::Elemento(string tipo, double tam, string unidad, double x, double y) {
    tipoElemento = tipo;
    tamanio      = tam;
    unidadMedida = unidad;
    coordenadaX  = x;
    coordenadaY  = y;
}

string Elemento::getTipoElemento() const { return tipoElemento; }
double Elemento::getTamanio()      const { return tamanio; }
string Elemento::getUnidadMedida() const { return unidadMedida; }
double Elemento::getCoordenadaX()  const { return coordenadaX; }
double Elemento::getCoordenadaY()  const { return coordenadaY; }