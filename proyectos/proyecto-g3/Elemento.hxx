#ifndef ELEMENTO_HXX
#define ELEMENTO_HXX

#include "Elemento.h"
#include <stdexcept>

using namespace std;

template <class T, class C>
Elemento<T,C>::Elemento(TipoElemento ntipo, T ntamano, UnidadMedida nunidadMedida, Punto<C> nposicion) {
    if (ntamano < 0) {
        throw invalid_argument("Tamano menor a 0");
    }
    if (nunidadMedida == RAD || nunidadMedida == GRD) {
        throw invalid_argument("Unidad de medida invalida");
    }
    if (ntipo != ROCA && ntipo != CRATER && ntipo != MONTICULO && ntipo !=DUNA) {
        throw invalid_argument("Elemento invalido");
    }
    if(nunidadMedida==DESCONOCIDO){
        throw invalid_argument("Debe ingresar una unidad de medida correcta");
    }

    this -> tipo = ntipo;
    this -> tamano = ntamano;
    this -> unidadMedida = nunidadMedida;
    this -> posicion = nposicion;
}

template <class T, class C>
TipoElemento Elemento<T,C>::getTipoElemento() const {
    return this -> tipo;
}

template <class T, class C>
string Elemento<T,C>::tipoElemento_toString(TipoElemento te) const
{
    switch(te){
        case ROCA:
            return "roca";
        break;
        case CRATER:
            return "crater";
        break;
        case MONTICULO:
            return "monticulo";
        break;
        case DUNA:
            return "duna";
        break;
        default:
            return "desconocido";
    }
}

template <class T, class C>
TipoElemento Elemento<T,C>::obtenerTipoElemento(const string& te)
{
    if(te=="roca"){
        return ROCA;
    } else if(te=="crater"){
        return CRATER;
    } else  if(te=="monticulo"){
        return MONTICULO;
    } else if(te=="duna"){
        return DUNA;
    } else {
        throw invalid_argument("Tipo Elemento invalido");
    }
}

template <class T, class C>
T Elemento<T,C>::getTamano() const {
    return this -> tamano;
}
template <class T, class C>
UnidadMedida Elemento<T,C>::getUnidadMedida() const {
    return this -> unidadMedida;
}
template <class T, class C>
C Elemento<T,C>::getCx() const {
    return this -> posicion.getX();
}
template <class T, class C>
C Elemento<T,C>::getCy() const {
    return this -> posicion.getY();
}

template <class T, class C>
Punto<C> Elemento<T,C>::getPunto() const {
    return posicion;
}

template <class T, class C>
void Elemento<T,C>::setPunto(const Punto<C>& punto) {
    posicion = punto;
}

#endif
