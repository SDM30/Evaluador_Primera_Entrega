#include "comando.h"

// Constructor para comando de movimiento
// Pre: tipoMov es "avanzar" o "girar", mag > 0, unidad valida
Comando::Comando(string tipoMov, double mag, string unidad) {
    tipo           = "movimiento";
    tipoMovimiento = tipoMov;
    magnitud       = mag;
    unidadMedida   = unidad;
    tipoAnalisis   = "";
    objeto         = "";
    comentario     = "";
}

// Constructor para comando de analisis
// Pre: tipoAnal valido, obj no vacio, com vacio o entre comillas simples
Comando::Comando(string tipoAnal, string obj, string com) {
    tipo           = "analisis";
    tipoAnalisis   = tipoAnal;
    objeto         = obj;
    comentario     = com;
    tipoMovimiento = "";
    magnitud       = 0.0;
    unidadMedida   = "";
}

string Comando::getTipo()           const { return tipo; }
string Comando::getTipoMovimiento() const { return tipoMovimiento; }
double Comando::getMagnitud()       const { return magnitud; }
string Comando::getUnidadMedida()   const { return unidadMedida; }
string Comando::getTipoAnalisis()   const { return tipoAnalisis; }
string Comando::getObjeto()         const { return objeto; }
string Comando::getComentario()     const { return comentario; }