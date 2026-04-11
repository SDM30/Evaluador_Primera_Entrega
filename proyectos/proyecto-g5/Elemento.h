#ifndef ELEMENTO_H
#define ELEMENTO_H
#include <string>
using namespace std;

// me baso en el tAD Elemento que representa un punto de interes como una roca, un crater, un monticulo o una duna. Guarda su tipo, tamano, unidad de medida y coordenadas.
class Elemento
{
private:
    string tipoComponente; // "roca", "crater", "monticulo" o "duna"
    double tamano;         // dimension del elemento
    string unidadMedida;   // unidad del tamano: cm, dm, m, km
    double coordX;         // coordenada x de terrenp
    double coordY;         // coordenada y de terreno
public:
    // Constructor por defecto
    Elemento();
    // Constructor con parametros
    Elemento(string tipo, double tamano, string unidad, double x, double y);
    // Getters
    string getTipo();
    double getTamano();
    string getUnidad();
    double getCoordX();
    double getCoordY();
};
#endif