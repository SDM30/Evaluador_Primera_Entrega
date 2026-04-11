#include "Analisis.hpp"
using namespace std;

ComandoAnalisis::ComandoAnalisis() {
    tipo       = TipoAnalisis::INVALIDO;
    objeto     = "";
    comentario = "";
}

ComandoAnalisis::ComandoAnalisis(TipoAnalisis tipo, string objeto, string comentario) {
    this->tipo       = tipo;
    this->objeto     = objeto;
    this->comentario = comentario;
}

// Getters
TipoAnalisis ComandoAnalisis::getTipo() const 
{ 
  return tipo; 
}

string ComandoAnalisis::getTipoString()
{
  if (tipo == TipoAnalisis::FOTOGRAFIAR) return "fotografiar";
  if (tipo == TipoAnalisis::COMPOSICION) return "composicion";
  if (tipo == TipoAnalisis::PERFORAR)    return "perforar";
  return "invalido";
}

string ComandoAnalisis::getObjeto()     const
{ 
  return objeto; 
}

string ComandoAnalisis::getComentario() const 
{ 
  return comentario; 
}

TipoAnalisis ComandoAnalisis::stringATipo(string t)
{
  if (t == "fotografiar") return TipoAnalisis::FOTOGRAFIAR;
  if (t == "composicion") return TipoAnalisis::COMPOSICION;
  if (t == "perforar")    return TipoAnalisis::PERFORAR;
  return TipoAnalisis::INVALIDO;
}
