#include "consola.h"
#include <iostream>

int main()
{
    //Detalle de finisima coquetería
    system("clear");
    Consola c;

    bool control = true;
    while(control)
    {
        std::cout << "$: ";
        std::string input = c.ingresoConsola(control);
        std::vector<std::string> inputSeparado = c.separarString(input);
        c.llamarFunciones(inputSeparado);
    }

}