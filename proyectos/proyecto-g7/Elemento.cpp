#include "Elemento.hpp"
#include"Punto.hpp"

#include<string>

using namespace std;

Elemento::Elemento()
{
  tipo = TipoElemento::INVALIDO;
  tamano = 0.0;
  unidad = UnidadElemento::INVALIDA;
  posicion = crearPunto(0.0, 0.0);
}

Elemento::Elemento(TipoElemento tipo, double tamano, UnidadElemento unidad, Punto posicion)
{
  this->tipo     = tipo;
  this->tamano   = tamano;
  this->unidad   = unidad;
  this->posicion = posicion;
}

TipoElemento Elemento::stringATipo(string t)
{
  if (t == "roca")      return TipoElemento::ROCA;
  if (t == "crater")    return TipoElemento::CRATER;
  if (t == "monticulo") return TipoElemento::MONTICULO;
  if (t == "duna")      return TipoElemento::DUNA;
  return TipoElemento::INVALIDO;
}

UnidadElemento Elemento::stringAUnidad(string u) {
    if (u == "cm") return UnidadElemento::CM;
    if (u == "dm") return UnidadElemento::DM;
    if (u == "m")  return UnidadElemento::M;
    if (u == "km") return UnidadElemento::KM;
    return UnidadElemento::INVALIDA;
}

TipoElemento Elemento::getTipo()     const 
{ 
  return tipo; 
}

string Elemento::getTipoString() const {
    if (tipo == TipoElemento::ROCA)      return "roca";
    if (tipo == TipoElemento::CRATER)    return "crater";
    if (tipo == TipoElemento::MONTICULO) return "monticulo";
    if (tipo == TipoElemento::DUNA)      return "duna";
    return "invalido";
}

double Elemento::getTamano()   const 
{ 
  return tamano; 
}

UnidadElemento Elemento::getUnidad()   const 
{ 
  return unidad; 
}

string Elemento::getUnidadString() const {
    if (unidad == UnidadElemento::CM) return "cm";
    if (unidad == UnidadElemento::DM) return "dm";
    if (unidad == UnidadElemento::M)  return "m";
    if (unidad == UnidadElemento::KM) return "km";
    return "invalida";
}

Punto  Elemento::getPosicion() const 
{ 
  return posicion; 
}

string Elemento::getPuntoString() const {
    return to_string(posicion.x)+ " " + to_string(posicion.y);
}
