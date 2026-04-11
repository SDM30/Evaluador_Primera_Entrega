#ifndef _SISTEMA_H_
#define _SISTEMA_H_

#include "comando.h"
#include "elemento.h"
#include <list>
#include <string>
using namespace std;

// TAD Sistema
// Controlador central que gestiona la lista de comandos
// y la lista de elementos del robot Curiosity.
class Sistema {
private:
    list<Comando>  comandos;  // lista de comandos en orden de carga
    list<Elemento> elementos; // lista de puntos de interes

public:
    // Carga comandos desde archivo, sobreescribiendo los anteriores.
    // Pre: nombreArchivo no vacio
    string cargarComandos(string nombreArchivo);

    // Carga elementos desde archivo, sobreescribiendo los anteriores.
    // Pre: nombreArchivo no vacio
    string cargarElementos(string nombreArchivo);

    // Crea y agrega al final de comandos un comando de movimiento.
    // Pre: parametros ya validados en main
    string agregarMovimiento(string tipoMov, double mag, string unidad);

    // Crea y agrega al final de comandos un comando de analisis.
    // Pre: parametros ya validados en main
    string agregarAnalisis(string tipoAnal, string obj, string com);

    // Crea y agrega al final de elementos un nuevo elemento.
    // Pre: parametros ya validados en main
    string agregarElemento(string tipo, double tam, string unidad,
                           double x, double y);

    // Guarda en archivo la informacion segun tipoArchivo
    // ("comandos" o "elementos").
    // Pre: la lista correspondiente no esta vacia
    string guardar(string tipoArchivo, string nombreArchivo);

    // Simula los comandos de movimiento desde la posicion (x, y).
    // Orientacion inicial: mirando hacia +x (theta = 0).
    // Angulos positivos: antihorario. Angulos negativos: horario.
    // Solo procesa comandos de movimiento, ignora los de analisis.
    // Pre: comandos no esta vacia
    string simularComandos(double x, double y);
};

#endif