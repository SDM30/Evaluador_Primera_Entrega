/*
 * TAD_Desplazamiento_imp.cpp
 * ----------------------
 * 
 * Comentarios
 * 
 */

#ifndef TAD_DESPLAZAMIENTO_IMP_CPP
#define TAD_DESPLAZAMIENTO_IMP_CPP

#include "TAD_Desplazamiento.h"
//#include <iostream>

using namespace std;

//Constructor parametrizado para tipo Movimiento.
Desplazamiento::Desplazamiento(Movimiento &mov): mov(new Movimiento(mov)), ana(nullptr), esMov(true) {} //Se utiliza el new Movimiento(mov) para crear una copia de mov y dirigir al puntero a su dirección, dado que
                                                                                                        //si no fuese así, al agregar un nuevo Desplazamiento tipo Movimiento en el Curiosity, el puntero permanecería 
                                                                                                        // apuntando a mov, que es una variable local a la función de aggDesplazamiento_ana. Dado que mov es una variable 
                                                                                                        // local, al finalizar la función mencionada, se elimina, propiciando que el puntero pierda un punto al que dirigirse.
                                                                                                        // Lo mismo sucede para el caso del creador parametrizado para tipo de objetos Analisis.

//Constructor parametrizado para tipo Analisis.
Desplazamiento::Desplazamiento(Analisis &ana): mov(nullptr), ana(new Analisis(ana)), esMov(false) {}

//Getters.
Movimiento Desplazamiento::getMov() const{
    return *(this->mov);
}

Analisis Desplazamiento::getAna() const{
    return *(this->ana); //Revisar, ¿qué sucede si ana o mov se encuentran como nullptr?
}

bool Desplazamiento::getEsMov() const{
    return this->esMov;
}

//Setters.
void Desplazamiento::setMov(Movimiento &mov){
    this->mov = &mov;
}

void Desplazamiento::setAna(Analisis &ana){
    this->ana = &ana;
}

void Desplazamiento::setEsMov(bool esMov){
    this->esMov = esMov;
}

#endif

//EOF - TAD_Desplazamiento_imp.cpp