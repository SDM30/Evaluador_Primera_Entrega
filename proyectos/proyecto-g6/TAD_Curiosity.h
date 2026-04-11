/*
 *
 *
 */

#include <iostream>
#include <list>
#include <vector>

#include "TAD_Desplazamiento.h"
#include "TAD_Punto_interes.h"

using namespace std;

#ifndef TAD_CURIOSITY_H
#define TAD_CURIOSITY_H

class Curiosity{

    private:

    list<Desplazamiento> desplazamientos;
    vector<Punto_interes> puntos_interes;
    
    public:

    //No es necesario un constructor genérico porque, por defecto, se produce.
    
    //Getters.
    list<Desplazamiento> getDesplazamientos() const;
    vector<Punto_interes> getPuntos_interes() const;

    //En vez de setters, se utilizan métodos de agregación.

    //Método para agregar un Desplazamiento tipo Movimiento a la lista de Desplazamiento.
    void aggDesplazamiento_mov(string tipo_mov, double magnitud, string unidades);
    
    //Método para agregar un Desplazamiento tipo Análisis con comentario a la lista de Desplazamiento.
    void aggDesplazamiento_ana(string tipo_an, string objeto, string &comentario);

    //Método para agregar un Desplazamiento tipo Análisis sin comentario a la lista de Desplazamiento.
    void aggDesplazamiento_ana(string tipo_an, string objeto);

    //Método para añadir un Punto_interés a la lista de Puntos_interes.
    void aggPunto_interes(string tipo_ele, double tamano, string unidad_med, double x, double y);

    //Método para cargar comandos desde un archivo:
    int cargarComandosArchivo(string dir);

    //Método para eliminar comandos:
    void eliminarComandos();

    //Método para cargar puntos de interés desde un archivo:
    int cargarElementosArchivo(string dir);

    //Método para eliminar elementos:
    void eliminarElementos();

    //Función para guardar comandos o elementos en un archivo:

    void guardar(string tipo, string dir);

    //Función para simular comandos:

    void simular_comandos(double x_inicial, double y_inicial);

    //Métodos auxiliares para observar contenido:

    void revContenidoAn();
    void revContenidoMov();
    void revContenidoPI();

};

#endif

//EOF - TAD_Curiosity.h