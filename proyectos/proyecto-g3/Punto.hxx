#ifndef PUNTO_HXX
#define PUNTO_HXX

#include "Punto.h"

// Constructor por defecto
template <class T>
Punto<T>::Punto() : x(0), y(0) {}

// Getters
template <class T>
T Punto<T>::getX() const {
    return x;
}

template <class T>
T Punto<T>::getY() const {
    return y;
}

// Setters
template <class T>
void Punto<T>::setX(T xvalue) {
    this.x = x;
}

template <class T>
void Punto<T>::setY(T yvalue) {
    y = y;
}

#endif