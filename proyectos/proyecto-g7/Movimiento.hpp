#ifndef Movimiento_hpp 
#define Movimiento_hpp

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// ========== CLASE COMANDO MOVIMIENTO ========== //

//Reperesenta el dezplazamiento del robot sobre la superficie.

enum class TipoMovimiento {
    AVANZAR,
    GIRAR,
    INVALIDO
};

enum class UnidadMovimiento {
    CM, DM, M, KM,   // para avanzar
    GRD, RAD,         // para girar
    INVALIDA
};

class ComandoMovimiento {
private:
    TipoMovimiento tipo;
    double magnitud;
    UnidadMovimiento unidad;

public:

    // Constructores

    ComandoMovimiento();

    ComandoMovimiento(TipoMovimiento tipo, double magnitud, UnidadMovimiento unidad);              

    // Getters
    TipoMovimiento getTipo() const;

    double getMagnitud() const;

    UnidadMovimiento getUnidad() const;

    string getTipoString() const;

    string getUnidadString() const;

    // Convertir magnitud a LONGUITUD  o ÁNGULO en unidades estándar (metros o radianes)
    double getMagnitudEnMetros() const;

    // Solo para AVANZAR

    double getMagnitudEnRadianes() const;

    //Validacion
    static bool esTipoValido(string t);

    static bool esUnidadAvanzar(string u);

    static bool esUnidadGirar(string u);

    static bool esUnidadValida(TipoMovimiento tipo, UnidadMovimiento unidad);

    static TipoMovimiento stringATipo(string t);

    static UnidadMovimiento stringAUnidad(string u);
};

#endif
