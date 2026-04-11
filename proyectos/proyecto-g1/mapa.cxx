#include "mapa.h"
#include <iostream>

//DOCUMENTO PARA LA SEGUNDA ENTREGA
//-> IGNORAR MIENTRAS TANTO
void Mapa::crearMapa(std::string coeficiente)
{
    double coef;
    try
    {
        coef = std::stod(coeficiente);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "El coeficiente no es un numero decimal";
        return;
    }
    std::cout << "Mapa creado"; 
}

void Mapa::rutaMasLarga()
{
    std::cout << "**calcula la ruta mas larga**";
}