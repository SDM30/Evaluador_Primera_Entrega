/*
 *
 *
 */

#include <iostream>

using namespace std;

#ifndef TAD_PUNTO_INTERES_H
#define TAD_PUNTO_INTERES_H

class Punto_interes{

    private:

    string tipo_ele;
    double tamano;
    string unidad_med;
    double x;
    double y;
    
    public:

    //Constructor parametrizado.
    Punto_interes(string tipo_ele, double tamano, string unidad_med, double x, double y);

    //Getters.

    string getTipo_ele() const;
    double getTamano() const;
    string getUnidad_med() const;
    double getX() const;
    double getY() const;

    //Setters.

    void setTipo_ele(string tipo_ele);
    void setTamano(double tamano);
    void setUnidad_med(string unidad_med);
    void setX(double x);
    void setY(double y);

};

#endif

//EOF - TAD_Punto_interes.h