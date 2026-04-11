#ifndef _COMANDO_H_
#define _COMANDO_H_

#include <string>
using namespace std;

// TAD Comando
// Representa un comando de movimiento o de analisis
// que puede enviarse al robot Curiosity.
class Comando {
private:
    // Estado compartido
    string tipo;           // "movimiento" o "analisis"

    // Estado para comandos de movimiento
    string tipoMovimiento; // "avanzar" o "girar"
    double magnitud;       // valor del movimiento, magnitud > 0
    string unidadMedida;   // "cm","dm","m","km" / "grd","rad"

    // Estado para comandos de analisis
    string tipoAnalisis;   // "fotografiar","composicion","perforar"
    string objeto;         // nombre del elemento a analizar
    string comentario;     // opcional, entre comillas simples o vacio

public:
    // Crea un comando de movimiento.
    // Pre: tipoMov es "avanzar" o "girar", mag > 0, unidad valida segun tabla
    Comando(string tipoMov, double mag, string unidad);

    // Crea un comando de analisis.
    // Pre: tipoAnal es "fotografiar","composicion" o "perforar", obj no vacio
    // comentario puede estar vacio o entre comillas simples
    Comando(string tipoAnal, string obj, string com);

    // Retorna el tipo del comando ("movimiento" o "analisis")
    string getTipo() const;

    // --- Getters movimiento (Pre: tipo == "movimiento") ---
    string getTipoMovimiento() const;
    double getMagnitud()       const;
    string getUnidadMedida()   const;

    // --- Getters analisis (Pre: tipo == "analisis") ---
    string getTipoAnalisis() const;
    string getObjeto()       const;
    string getComentario()   const;
};

#endif