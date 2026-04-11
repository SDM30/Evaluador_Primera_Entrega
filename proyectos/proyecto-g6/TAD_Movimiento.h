/*
 * Movimiento.h
 * --------------------------------------------------------------------------
 * Definición de la clase Movimiento.
 *
 * El presente TAD corresponde a un comando de movimiento para el Curiosity
 * que cuenta con: tipo, magnitud (numérica) y unidad de medida (especificadas)
 * en la documentación del proyecto, más específicamente en la tabla 1.
 *
 */

#include <iostream>

using namespace std;

#ifndef TAD_MOVIMIENTO_H
#define TAD_MOVIMIENTO_H

class Movimiento{

    private:

    string tipo_mov;
    double magnitud;
    string unidades;

    public:

    //Constructor parametrizado.
    Movimiento(string tipo_mov, double magnitud, string unidades);

    //Getters.
    string getTipo_mov() const;
    double getMagnitud() const;
    string getUnidades() const;

    //Setters.
    void setTipo_mov(string tipo_mov);
    void setMagnitud (double magnitud);
    void setUnidades(string unidades);

};

#endif

//EOF - TAD_Movimiento.h