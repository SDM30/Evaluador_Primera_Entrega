#include "ComandoAnalisis.h"
// Constructor por defecto vacio
ComandoAnalisis::ComandoAnalisis()
{
    tipoAnalisis = "";
    objeto = "";
    comentario= "";
}
// Constructor con parametros para guardae el tipo, el objeto y el comentario
ComandoAnalisis::ComandoAnalisis(string tipo, string objeto, string comentario)
{
    tipoAnalisis= tipo;
    this->objeto= objeto;
    this->comentario = comentario;
}
// Getters para obtener el tipo de analisis, el objeto y el comentario
string ComandoAnalisis::getTipoAnalisis()
{
    return tipoAnalisis;
}
string ComandoAnalisis::getObjeto()
{
    return objeto;
}
string ComandoAnalisis::getComentario()
{
    return comentario;
}
