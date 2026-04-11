/*
 * Analisis.h
 * --------------------------------------------------------------------------
 * Definición de la clase Analisis.
 *
 * El TAD contenido en este archivo consiste en un comando de análisis para
 * el Curiosity, que le indica tipo de examen a efectuar, el objeto sobre el
 * cual se ejecutará el análisis y un comentario adicional, de carácter opcional.
 *
 */

#include <iostream>

using namespace std;

#ifndef TAD_ANALISIS_H
#define TAD_ANALISIS_H

class Analisis{

    private:

    string tipo_an;
    string objeto;
    string* comentario = nullptr;
    bool hayComentario = false;

    public:

    //Constructor parametrizado con comentario.
    Analisis(string tipo_an, string objeto, string &comentario);

    //Constructor parametrizado sin comentario
    Analisis(string tipo_an, string objeto); //Sobrecarga de métodos.

    //Getters.
    string getTipo_an() const;
    string getObjeto() const;
    string getComentario() const;
    bool getHayComentario() const;

    //Setters.
    void setTipo_an(string tipo_an);
    void setObjeto(string objeto);
    void setComentario(string &comentario);
    //No existe setter de hayComentario porque la bandera se modifica únicametne cuando se agrega un comentario.

};

#endif

//EOF - TAD_Analisis.h