/*
 * TAD_Analisis_imp.cpp
 * ----------------------
 * 
 * Comentarios
 * 
 */

#ifndef TAD_ANALISIS_IMP_CPP
#define TAD_ANALISIS_IMP_CPP

#include "TAD_Analisis.h"
#include <iostream>

//Método Constructor parametrizado con comentario.
Analisis::Analisis(string tipo_an, string objeto, string &comentario): tipo_an(tipo_an), objeto(objeto),
                                                                        comentario(new string(comentario)), hayComentario(true) {} //Al asignar el comentario, se utiliza la expresión new string(comentario) para evitar que
                                                                                                                                    // el apuntador a comentario permanezca dirigido a una variable local del main que variará
                                                                                                                                    //mientras se realice las iteraciones del programa para recibir distintos comandos.

//Método Constructor parametrizado sin comentario.
Analisis::Analisis(string tipo_an, string objeto): tipo_an(tipo_an), objeto(objeto),        //Sobrecarga de métodos.
                                                    comentario(nullptr), hayComentario(false) {}

//Getters.
string Analisis::getTipo_an() const{
    return this->tipo_an;
}

string Analisis::getObjeto() const{
    return this->objeto;
}

string Analisis::getComentario() const{
    if(this->hayComentario){
        return *(this->comentario);    
    } else{
        return "";
    }
}

bool Analisis::getHayComentario() const{
    return this->hayComentario;
}

//Setters.
void Analisis::setTipo_an(string tipo_an){
    this->tipo_an = tipo_an;
}

void Analisis::setObjeto(string objeto){
    this->objeto = objeto;
}

void Analisis::setComentario(string &comentario){
    if(this->hayComentario){
        *(this->comentario) = comentario;
    } else{
        this->comentario = new string(comentario);
        this->hayComentario = true;
    }
}

//El setter de hayComentario no existe porque la única forma de modificar esa bandera es agregando un comentario.

#endif

//EOF - TAD_Analisis_imp.cpp