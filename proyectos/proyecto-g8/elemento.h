#ifndef _ELEMENTO_H_
#define _ELEMENTO_H_

#include <string>
using namespace std;

// TAD Elemento
// Representa un punto de interes encontrado en el suelo marciano.
class Elemento {
private:
    string tipoElemento; // "roca","crater","monticulo","duna"
    double tamanio;      // dimension del elemento, tamanio > 0
    string unidadMedida; // "cm","dm","m","km"
    double coordenadaX;  // posicion en eje x (metros)
    double coordenadaY;  // posicion en eje y (metros)

public:
    // Crea un elemento con los datos dados.
    // Pre: tipo valido, tam > 0, unidad valida
    Elemento(string tipo, double tam, string unidad, double x, double y);

    string getTipoElemento() const;
    double getTamanio()      const;
    string getUnidadMedida() const;
    double getCoordenadaX()  const;
    double getCoordenadaY()  const;
};

#endif