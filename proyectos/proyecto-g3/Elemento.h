#ifndef ELEMENTO_H
#define ELEMENTO_H
#include "UnidadMedida.h"
#include "Punto.h"
#include <stdexcept>

enum TipoElemento {
  ROCA, CRATER, MONTICULO, DUNA
};

template <class T, class C>
class Elemento {

    private:
    TipoElemento tipo;
    T tamano;
    UnidadMedida unidadMedida;
    Punto<C> posicion;

    public:
    Elemento(TipoElemento ntipo, T ntamano, UnidadMedida nunidadMedida, Punto<C> nposicion);

    //getters
    TipoElemento getTipoElemento() const;
    string tipoElemento_toString(TipoElemento te) const;
    static TipoElemento obtenerTipoElemento(const string& te);
    T getTamano() const;
    UnidadMedida getUnidadMedida() const;
    C getCx() const;
    C getCy() const;
    Punto<C> getPunto() const;
    void setPunto(const Punto<C>& punto);
};

#include "Elemento.hxx"

#endif //ELEMENTO_H
