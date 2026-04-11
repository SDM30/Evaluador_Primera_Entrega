#ifndef COMANDOMOVIMIENTO_H
#define COMANDOMOVIMIENTO_H

#include <string>
#include <vector>
#include <iostream>
#include "UnidadMedida.h"

using namespace std;

enum Tipo_Movimiento{
    AVANZAR,
    GIRAR
};

template <class T>
class ComandoMovimiento{

private:

    Tipo_Movimiento tipo_movimiento;
    T magnitud;
    UnidadMedida unidad_medida;

public:
    ComandoMovimiento();
    ComandoMovimiento(Tipo_Movimiento tipo_movimiento, T magnitud, UnidadMedida unidad_medida);

    //getters
    Tipo_Movimiento getTipoMovimiento() const;
    string tipoMovimiento_toString(Tipo_Movimiento tm) const;
    static Tipo_Movimiento obtenerTipoMovimiento(const string& tm);
    T getMagnitud() const;
    UnidadMedida getUnidadMedida() const;

};

#include "ComandoMovimiento.hxx"

#endif