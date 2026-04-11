#include "ListaComandos.h"

// Constructor: la list empieza vacia por defecto
ListaComandos::ListaComandos()
{
}
// Agrega un comando de movimiento al final
void ListaComandos::agregarMovimiento(ComandoMovimiento cmd)
{
    EntradaComando nueva(cmd);
    entradas.push_back(nueva);
}
// Agrega un comando de analisis al final
void ListaComandos::agregarAnalisis(ComandoAnalisis cmd)
{
    EntradaComando nueva(cmd);
    entradas.push_back(nueva);
}
// Retorna true si no hay ningun comando
bool ListaComandos::estaVacia()
{
    return entradas.empty();
}
// Retorna el numero total de comandos
int ListaComandos::cantidad()
{
    return (int)entradas.size();
}
// Cuenta los comandos de movimiento
int ListaComandos::cantidadMovimientos()
{
    int contador = 0;
    list<EntradaComando>::iterator it;
    it = entradas.begin();
    for (; it != entradas.end(); it++)
    {
        if (it->tipo == ENTRADA_MOVIMIENTO)
        {
            contador++;
        }
    }
    return contador;
}
// Cuenta los comandos de analisis
int ListaComandos::cantidadAnalisis()
{
    int contador = 0;
    list<EntradaComando>::iterator it;
    it= entradas.begin();
    for (; it != entradas.end(); it++)
    {
        if (it->tipo == ENTRADA_ANALISIS)
        {
            contador++;
        }
    }
    return contador;
}
// Elimina todos los comandos
void ListaComandos::limpiar()
{
    entradas.clear();
}
// Retorna la lista completa para recorrerla
list<EntradaComando>& ListaComandos::getEntradas()
{
    return entradas;
}
