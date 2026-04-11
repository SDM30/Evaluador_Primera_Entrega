/*
 * TAD_Movimiento_imp.cpp
 * ----------------------
 * 
 * Comentarios
 * 
 */

#ifndef TAD_MOVIMIENTO_IMP_CPP
#define TAD_MOVIMIENTO_IMP_CPP

#include "TAD_Movimiento.h"
//#include <iostream>

using namespace std;

//Método Constructor parametrizado.
Movimiento::Movimiento(string tipo_mov, double magnitud, string unidades): tipo_mov(tipo_mov), magnitud(magnitud), unidades(unidades) {}

//Getters.
string Movimiento::getTipo_mov() const{
    return this->tipo_mov;
}

double Movimiento::getMagnitud() const{
    return this->magnitud;
}

string Movimiento::getUnidades() const{
    return this->unidades;
}

//Setters.
void Movimiento::setTipo_mov(string tipo_mov){
    this->tipo_mov = tipo_mov;
}

void Movimiento::setMagnitud(double magnitud){
    this->magnitud = magnitud;
}

void Movimiento::setUnidades(string unidades){
    this->unidades = unidades;
}

#endif

//EOF - TAD_Movimiento_imp.cpp