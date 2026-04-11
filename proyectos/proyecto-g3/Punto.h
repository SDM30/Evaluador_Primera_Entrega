#ifndef PUNTO_H
#define PUNTO_H

template <class T>
class Punto {

private:
    T x;
    T y;

public:

    Punto();
    Punto(T x, T y): x(x), y(y) {}

    T getX() const;
    T getY() const;

    void setX(T xvalue);
    void setY(T yvalue);

};

#include "Punto.hxx"

#endif