#ifndef COMANDO_H
#define COMANDO_H

#include "ComandoMovimiento.h"
#include "ComandoAnalisis.h"

enum TipoComando {
    MOVIMIENTO,
    ANALISIS
};

class Comando {

private:
    TipoComando tipo;
    ComandoMovimiento<double> movimiento;
    ComandoAnalisis analisis;

public:

    // Constructor para movimiento
    Comando(const ComandoMovimiento<double>& mov);

    // Constructor para analisis
    Comando(const ComandoAnalisis& ana);

    TipoComando getTipo() const;

    ComandoMovimiento<double> getMovimiento() const;
    ComandoAnalisis getAnalisis() const;
};

#endif