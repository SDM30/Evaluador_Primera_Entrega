#ifndef __COMUNICACIONES__
#define __COMUNICACIONES__
#include <string>
#include "gestorDeArchivo.h"

class Comunicaciones
{
private:
GestorArchivo gestor;
        public:
                void cargarComandos(std::string);
                void cargarElementos(std::string);
                void agregarElemento(std::string tipo, std::string tam, std::string unidad, std::string x, std::string y);
                void agregarAnalisis(std::string analisis, std::string objeto, std::string comentario);
                void agregarMovimiento(std::string movimiento, std::string magnitud, std::string unidad);
                void guardar(std::string tipo, std::string nombre);
                void simularComandos(std::string x, std::string y);
};

#endif //__COMUNICACIONES__