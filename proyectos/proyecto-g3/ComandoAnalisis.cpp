#include "ComandoAnalisis.h"
#include <string>
#include <stdexcept>

using namespace std;

ComandoAnalisis::ComandoAnalisis(){};

ComandoAnalisis::ComandoAnalisis(Tipo_Analisis ta, string objeto, string comentario)
{
    this->tipo_analisis=ta;
    this->objeto=objeto;
    this->comentario=comentario;
}

Tipo_Analisis ComandoAnalisis::getTipoAnalisis() const
{
    return tipo_analisis;
}

string ComandoAnalisis::tipoAnalisis_toString(Tipo_Analisis ta) const
{
    switch(ta){
        case FOTOGRAFIAR:
            return "fotografiar";
        break;
        case COMPOSICION:
            return "composicion";
        break;
        case PERFORAR:
            return "perforar";
        break;
        default:
            return "desconocido";
    }
}

Tipo_Analisis ComandoAnalisis::obtenerTipoAnalisis(const string& ta)
{
    if(ta=="fotografiar"){
        return FOTOGRAFIAR;
    } else if(ta=="composicion"){
        return COMPOSICION;
    } else  if(ta=="perforar"){
        return PERFORAR;
    } else {
        throw invalid_argument("Tipo analisis invalido");
    }
}

string ComandoAnalisis::getObjeto() const
{
    return objeto;
}

string ComandoAnalisis::getComentario() const
{
    return comentario;
}
