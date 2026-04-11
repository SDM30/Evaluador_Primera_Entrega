#include "Comando.h"
#include "ComandoMovimiento.h"

    // Constructor para movimiento
Comando::Comando(const ComandoMovimiento<double>& mov)
        : tipo(MOVIMIENTO), 
        movimiento(mov)
{
}

    // Constructor para analisis
Comando::Comando(const ComandoAnalisis& ana)
        : tipo(ANALISIS), 
        analisis(ana)
{
}

TipoComando Comando::getTipo() const {
    return tipo;
}

ComandoMovimiento<double> Comando::getMovimiento() const {
    return movimiento;
}

ComandoAnalisis Comando::getAnalisis() const {
    return analisis;
}