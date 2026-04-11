/*
 *
 *
 */

#include <iostream>

#include "TAD_Movimiento.h"
#include "TAD_Analisis.h"

using namespace std;

#ifndef TAD_DESPLAZAMIENTO_H
#define TAD_DESPLAZAMIENTO_H

class Desplazamiento{

    private:

    Movimiento* mov = nullptr;
    Analisis* ana = nullptr;
    bool esMov;
    
    public:

    //Constructor parametrizado para tipo Movimiento.
    Desplazamiento(Movimiento &mov);

    //Constructor parametrizado para tipo Analisis.
    Desplazamiento(Analisis &ana);

    //Getters.
    Movimiento getMov() const;
    Analisis getAna() const;
    bool getEsMov() const;

    //Setters.
    void setMov(Movimiento &mov);
    void setAna(Analisis &ana);
    void setEsMov(bool esMov);

};

#endif

//EOF - TAD_Desplazamiento.h