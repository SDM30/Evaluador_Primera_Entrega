#include "distancias.h"
#include <iostream>

//DOCUMENTO PARA LA SEGUNDA ENTREGA
//-> IGNORAR MIENTRAS TANTO
void Distancias::ubicarElementos()
{
    std::cout << "ubicar elementos ejecutandose. . .";
}

void Distancias::enCuadrante(std::string x1, std::string x2, std::string y1, std::string y2)
{
    int X1, X2, Y1, Y2;
    try
    {
        X1 = stoi(x1);
        X2 = stoi(x2);
        Y1 = stoi(y1);
        Y2 = stoi(y2);
    }
    catch(const std::invalid_argument e)
    {
        std::cout << "Los argumentos tienen que ser de tipo entero";
        return;
    }
    std::cout << "ejecutando funcion en cuadrante. . .";
}
