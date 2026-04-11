#ifndef LISTACOMANDOS_H
#define LISTACOMANDOS_H
#include <list>
#include "ComandoMovimiento.h"
#include "ComandoAnalisis.h"
using namespace std;

// Banderas para saber que tipo de comando tiene cada entrada
#define ENTRADA_MOVIMIENTO 0
#define ENTRADA_ANALISIS   1

// EntradaComando: guarda un comando (movimiento o analisis)junto con una bandera que dice cual de los dos es.
// Permite mezclar ambos tipos en una sola lista sin perder el orden.
struct EntradaComando
{
    int tipo; // 0 = movimiento, 1 = analisis
    ComandoMovimiento movimiento; // datos del movimiento (si aplica)
    ComandoAnalisis analisis;   // datos del analisis (si aplica)
    // Constructor para movimiento
    EntradaComando(ComandoMovimiento m)
    {
        tipo = ENTRADA_MOVIMIENTO;
        movimiento = m;
    }
    // Constructor para analisis
    EntradaComando(ComandoAnalisis a)
    {
        tipo= ENTRADA_ANALISIS;
        analisis = a;
    }
};

// TAD ListaComandos, mi lista enlazada que guarda comandos de movimiento y analisis mezclados, sin cambiar orden de llegada
class ListaComandos
{
private:
    list<EntradaComando> entradas;
public:
    // Constructor: crea una lista vacia
    ListaComandos();
    // Agrega un comando de movimiento al final de la lista
    void agregarMovimiento(ComandoMovimiento cmd);
    // Agrega un comando de analisis al final de la lista
    void agregarAnalisis(ComandoAnalisis cmd);
    // Retorna true si la lista no tiene ningun comando
    bool estaVacia();
    // Retorna el total de comandos en la lista
    int cantidad();
    // Retorna cuantos comandos de movimiento hay
    int cantidadMovimientos();
    // Retorna cuantos comandos de analisis hay
    int cantidadAnalisis();
    // Elimina todos los comandos de la lista
    void limpiar();
    // Retorna la lista completa para poder recorrerla
    list<EntradaComando>& getEntradas();
};
#endif