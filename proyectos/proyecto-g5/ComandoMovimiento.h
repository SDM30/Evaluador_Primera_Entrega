#ifndef COMANDOMOVIMIENTO_H
#define COMANDOMOVIMIENTO_H
#include <string>
using namespace std;
// Aqui me basop en el TAD ComandoMovimiento. Representa un comando que le dice al robot como moverse ya sea si avanzar una distancia o girar un angulo determinado.
class ComandoMovimiento
{
private:
    string tipoMovimiento; // "avanzar" o "girar"
    double magnitud;       // cantidad del movimiento (distancia o angulo)
    string unidadMedida;   // cm, dm, m, km (avanzar) | grd, rad (girar)
public:
    // Constructor por defecto: crea un comando vacio
    ComandoMovimiento();
    // Constructor con parametros
    ComandoMovimiento(string tipo, double magnitud, string unidad);
    // Getters
    string getTipoMovimiento();
    double getMagnitud();
    string getUnidad();
};
#endif