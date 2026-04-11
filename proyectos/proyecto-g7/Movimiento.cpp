#include <iostream> 
#include <sstream> 
#include <vector>
#include <cmath>
#include <ctype.h>


// carpetas .h para cabecera
#include "Movimiento.hpp"

using namespace std;

//Metodos Movimiento

// Constructores

ComandoMovimiento::ComandoMovimiento()
{
  tipo = TipoMovimiento::INVALIDO;
  magnitud = 0.0;
  unidad = UnidadMovimiento::INVALIDA;
}

ComandoMovimiento::ComandoMovimiento(TipoMovimiento tipo, double magnitud, UnidadMovimiento unidad)
{
  this->tipo = tipo;
  this->magnitud = magnitud;
  this->unidad = unidad;
}

// Getters
TipoMovimiento ComandoMovimiento::getTipo() const
{
  return this->tipo;
}

double ComandoMovimiento::getMagnitud() const
{
  return this->magnitud;
}

UnidadMovimiento ComandoMovimiento::getUnidad() const
{
  return this->unidad;
}

string ComandoMovimiento::getTipoString() const
{
  if (tipo == TipoMovimiento::AVANZAR) return "avanzar";
  if (tipo == TipoMovimiento::GIRAR)   return "girar";
  return "invalido";
}

string ComandoMovimiento::getUnidadString() const
{
  if (unidad == UnidadMovimiento::CM)  return "cm";
  if (unidad == UnidadMovimiento::DM)  return "dm";
  if (unidad == UnidadMovimiento::M)   return "m";
  if (unidad == UnidadMovimiento::KM)  return "km";
  if (unidad == UnidadMovimiento::GRD) return "grd";
  if (unidad == UnidadMovimiento::RAD) return "rad";
  return "invalida";
}

// Convertir magnitud a LONGUITUD  o ÁNGULO en unidades estándar (metros o radianes)
double ComandoMovimiento::getMagnitudEnMetros() const
{
  if(this->tipo==TipoMovimiento::AVANZAR)
  {
    if (unidad == UnidadMovimiento::CM)  return magnitud / 100;
    if (unidad == UnidadMovimiento::DM)  return magnitud / 10;
    if (unidad == UnidadMovimiento::M)   return magnitud;
    if (unidad == UnidadMovimiento::KM)  return magnitud * 1000;
  }
  return magnitud;
}    

// Solo para AVANZAR

double ComandoMovimiento::getMagnitudEnRadianes() const{
  if(tipo == TipoMovimiento::GIRAR)
  {
    if(unidad == UnidadMovimiento::GRD) return this->magnitud * M_PI / 180;
    return magnitud;
  }
  return 0.0;
}

// Validación
bool ComandoMovimiento::esTipoValido(string t) {
    return (t == "avanzar" || t == "girar");
}

bool ComandoMovimiento::esUnidadAvanzar(string u) {
    return (u == "cm" || u == "dm" || u == "m" || u == "km");
}

bool ComandoMovimiento::esUnidadGirar(string u) {
    return (u == "grd" || u == "rad");
}

bool ComandoMovimiento::esUnidadValida(TipoMovimiento tipo, UnidadMovimiento unidad) {
    if (tipo == TipoMovimiento::AVANZAR) {
        return (unidad == UnidadMovimiento::CM  ||
                unidad == UnidadMovimiento::DM  ||
                unidad == UnidadMovimiento::M   ||
                unidad == UnidadMovimiento::KM);
    }
    if (tipo == TipoMovimiento::GIRAR) {
        return (unidad == UnidadMovimiento::GRD ||
                unidad == UnidadMovimiento::RAD);
    }
    return false;
}

string minusculas(string s)
{
  for(int i = 0; i<s.size(); i++)
    {
      s[i] = tolower(s[i]);
    }
  return s;
}

TipoMovimiento ComandoMovimiento::stringATipo(string t) {
  t = minusculas(t);
    if (t == "avanzar") return TipoMovimiento::AVANZAR;
    if (t == "girar")   return TipoMovimiento::GIRAR;
    return TipoMovimiento::INVALIDO;
}

// Pre: u es un string cualquiera
// Post: retorna la UnidadMovimiento correspondiente, o INVALIDA
UnidadMovimiento ComandoMovimiento::stringAUnidad(string u) {
  u = minusculas(u);
    if (u == "cm")  return UnidadMovimiento::CM;
    if (u == "dm")  return UnidadMovimiento::DM;
    if (u == "m")   return UnidadMovimiento::M;
    if (u == "km")  return UnidadMovimiento::KM;
    if (u == "grd") return UnidadMovimiento::GRD;
    if (u == "rad") return UnidadMovimiento::RAD;
    return UnidadMovimiento::INVALIDA;
}

