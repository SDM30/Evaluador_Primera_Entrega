#ifndef _VALIDACIONES_H_
#define _VALIDACIONES_H_
#include <string>
using namespace std;
bool comandoValido(string comando);
bool validarNumero(string valor);
bool validarTipoMovimiento(string tipo);
bool validarUnidadMovimiento(string tipoMov, string unidad);
bool validarTipoAnalisis(string tipo);
bool validarComentario(string comentario);
bool validarTipoElemento(string tipo);
bool validarUnidadMedida(string tipo, string unidadMedida);
bool validarTipoArchivo(string tipo);
#endif