/*
 * TAD_Punto_interes_imp.cpp
 * ----------------------
 * 
 * Comentarios
 * 
 */

#ifndef TAD_PUNTO_INTERES_IMP_CPP
#define TAD_PUNTO_INTERES_IMP_CPP

#include "TAD_Punto_interes.h"
//#include <iostream>

using namespace std;

//Constructor parametrizado.
Punto_interes::Punto_interes(string tipo_ele, double tamano, string unidad_med, double x, double y): tipo_ele(tipo_ele), tamano(tamano), unidad_med(unidad_med),
                                                                                                        x(x), y(y) {}

//Getters.

string Punto_interes::getTipo_ele() const{
    return this->tipo_ele;
}

double Punto_interes::getTamano() const{
    return this->tamano;
}

string Punto_interes::getUnidad_med() const{
    return this->unidad_med;
}

double Punto_interes::getX() const{
    return this->x;
}

double Punto_interes::getY() const{
    return this->y;
}

//Setters.

void Punto_interes::setTipo_ele(string tipo_ele){
    this->tipo_ele = tipo_ele;
}

void Punto_interes::setTamano(double tamano){
    this->tamano = tamano;
}

void Punto_interes::setUnidad_med(string unidad_med){
    this->unidad_med = unidad_med;
}

void Punto_interes::setX(double x){
    this->x = x;
}

void Punto_interes::setY(double y){
    this->y = y;
}

#endif

//EOF - TAD_Punto_interes_imp.cpp