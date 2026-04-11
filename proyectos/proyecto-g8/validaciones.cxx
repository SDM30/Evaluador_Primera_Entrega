#include "validaciones.h"
#include <sstream>

bool comandoValido (string comando){
    return comando == "cargar_comandos" ||
           comando == "cargar_elementos" ||
           comando == "agregar_movimiento" ||
           comando == "agregar_analisis" ||
           comando == "agregar_elemento" ||
           comando == "guardar" ||
           comando == "simular_comandos" ||
           comando == "salir" ||
           comando == "ubicar_elementos" ||
           comando == "en_cuadrante" ||
           comando == "crear_mapa" ||
           comando == "ayuda" ||
           comando == "ruta_mas_larga" ;
}
//Movimiento
bool validarTipoMovimiento (string tipo){
    if (tipo == "avanzar" || tipo == "girar") 
      return true;
     return false;
}

bool validarUnidadMovimiento (string tipo, string unidadMedida){
    if (tipo == "avanzar"){
        return unidadMedida == "cm" || unidadMedida == "dm" ||
               unidadMedida == "m" || unidadMedida == "km";
    }
    if (tipo == "girar"){
        return unidadMedida == "grd" || unidadMedida == "rad";
    }
    return false;
}
//Analisis
bool validarTipoAnalisis (string tipo){
    if (tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar") return true;
    return false;
}
bool validarComentario(string comentario){
    if (comentario.empty()) return true;
    if (comentario.length() >= 2 && comentario.front() == '\'' && comentario.back() == '\''){
        return true;
    }
    return false;
}

//elementos
bool validarTipoElemento (string tipo){
    return tipo == "roca" ||
           tipo == "crater" ||
           tipo == "monticulo" ||
           tipo == "duna";
}
bool validarUnidadMedida (string tipo, string unidadMedida){
        return unidadMedida == "cm" || unidadMedida == "dm" ||
               unidadMedida == "m" || unidadMedida == "km";
    
}
bool validarTipoArchivo (string tipo){
    return (tipo == "comandos" || tipo == "elementos");
}
// Retorna true si el string representa un numero real valido (entero o decimal)
bool validarNumero(string valor) {
    if (valor.empty()) {
    return false;
    }
    istringstream ss(valor);
    double d;
    ss >> d;
    return ss.eof() && !ss.fail();
}