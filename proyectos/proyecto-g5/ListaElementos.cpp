#include "ListaElementos.h"
// Constructor: la list empieza vacia por defecto
ListaElementos::ListaElementos()
{
}
// Agrega un elemento al final de la lista
void ListaElementos::agregarElemento(Elemento elemento)
{
    elementos.push_back(elemento);
}
// Retorna true si no hay ningun elemento
bool ListaElementos::estaVacia()
{
    return elementos.empty();
}
// Retorna el numero de elementos almacenados
int ListaElementos::cantidadElementos()
{
    return (int)elementos.size();
}
// Elimina todos los elementos
void ListaElementos::limpiar()
{
    elementos.clear();
}
// Retorna la lista completa para recorrerla
list<Elemento>& ListaElementos::getElementos()
{
    return elementos;
}