#ifndef LISTAELEMENTOS_H
#define LISTAELEMENTOS_H
#include <list>
#include "Elemento.h"
using namespace std;
// me baso en el TAD ListaElementos. Es una lista enlazada que guarda los puntos de interes encontrados
class ListaElementos
{
private:
    list<Elemento> elementos;
public:
    // Constructor: crea una lista vacia
    ListaElementos();

    // Agrega un elemento al final de la lista
    void agregarElemento(Elemento elemento);

    // Retorna true si no hay ningun elemento
    bool estaVacia();

    // Retorna el numero de elementos almacenados
    int cantidadElementos();

    // Elimina todos los elementos
    void limpiar();

    // Retorna la lista completa para poder recorrerla
    list<Elemento>& getElementos();
};
#endif