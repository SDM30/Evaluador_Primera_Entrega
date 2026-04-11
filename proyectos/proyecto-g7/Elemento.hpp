#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

#include<string>
#include "Punto.hpp"

using namespace std;

enum class TipoElemento
{
  ROCA,
  CRATER,
  MONTICULO,
  DUNA,
  INVALIDO
};

enum class UnidadElemento {
    CM, DM, M, KM,
    INVALIDA
};

class Elemento
{
  private:
    TipoElemento tipo;
    double tamano;
    UnidadElemento unidad;
    Punto posicion;
  
  public:
    Elemento();

    Elemento(TipoElemento tipo, double tamano, UnidadElemento unidad, Punto posicion);

    static TipoElemento stringATipo(string t);

    static UnidadElemento stringAUnidad(string u);

    TipoElemento getTipo() const;

    string getTipoString() const;

    double getTamano() const;

    UnidadElemento getUnidad() const;

    string getUnidadString() const;

    Punto getPosicion() const;

    string getPuntoString() const;
};

#endif
