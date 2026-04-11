#ifndef __COMANDO__
#define __COMANDO__
#include "movimiento.h"
#include "analisis.h"

class Comando
{
    private:
        bool esAnalisis;
        Analisis analisis;
        Movimiento movimiento;

    public:
        Comando(Analisis A): analisis(A), esAnalisis(true) {}        
        Comando(Movimiento M): movimiento(M), esAnalisis(false) {}

        bool esTipoAnalisis() const { return esAnalisis; }
        const Analisis& getAnalisis() const { return analisis; }
        const Movimiento& getMovimiento() const { return movimiento; }
};

#endif //__COMANDO__